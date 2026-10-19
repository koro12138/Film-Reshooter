kernel void Filter2dMain5x5C2(global Tp*src,int istep,
global Tp*dst,int ostep,
int height,int y_work_size,int x_work_size,
constant float*filter MAX_CONSTANT_SIZE,
struct Scalar border_value)
{
const int gx=get_global_id(0);
int gy=get_global_id(1);
const int elem_counts=4;
const int ksh=2;
const int channel=2;
const int x_idx=gx*elem_counts*channel;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int8 v8s32_offset_src;
V16Tp v16tp_src[5];
if((gy>=ksh)&&(gy<(height-ksh)))
{
v8s32_offset_src=mad24(gy+(int8)(-2,-1,0,1,2,0,0,0),istep,x_idx);
v16tp_src[0]=VLOAD(src+v8s32_offset_src.s0,16);
v16tp_src[1]=VLOAD(src+v8s32_offset_src.s1,16);
v16tp_src[2]=VLOAD(src+v8s32_offset_src.s2,16);
v16tp_src[3]=VLOAD(src+v8s32_offset_src.s3,16);
v16tp_src[4]=VLOAD(src+v8s32_offset_src.s4,16);
}
else
{
#if BORDER_CONSTANT
short4 v4s16_flag_border;
v4s16_flag_border.lo=convert_short2(TOP_BORDER_IDX(gy+(int2)(-2,-1)));
v4s16_flag_border.hi=convert_short2(BOTTOM_BORDER_IDX(gy+(int2)(1,2),height));
v8s32_offset_src=mad24((int8)(convert_int4(abs(v4s16_flag_border)),(int4)gy),istep,x_idx);
v4s16_flag_border=isequal(convert_half4(v4s16_flag_border),(half4)(-1.f));
short4 v4s16_flag_body=v4s16_flag_border+(short4)(1);
V16Tp v16tp_border_value;
v16tp_border_value.lo=(V8Tp)(border_value.val[0]);
v16tp_border_value.hi=(V8Tp)(border_value.val[1]);
v16tp_src[0]=v4s16_flag_body.s0?VLOAD(src+v8s32_offset_src.s0,16):v16tp_border_value;
v16tp_src[1]=v4s16_flag_body.s1?VLOAD(src+v8s32_offset_src.s1,16):v16tp_border_value;
v16tp_src[2]=VLOAD(src+v8s32_offset_src.s4,16);
v16tp_src[3]=v4s16_flag_body.s2?VLOAD(src+v8s32_offset_src.s2,16):v16tp_border_value;
v16tp_src[4]=v4s16_flag_body.s3?VLOAD(src+v8s32_offset_src.s3,16):v16tp_border_value;
#elif BORDER_REFLECT_101
int8 v8_s32_offset_y=convert_int8(abs(gy+(int8)(-2,-1,0,1,2,0,0,0)));
v8s32_offset_src=mad24(select(v8_s32_offset_y,((height-1)<<1)-v8_s32_offset_y,v8_s32_offset_y>(height-1)),istep,x_idx);
v16tp_src[0]=VLOAD(src+v8s32_offset_src.s0,16);
v16tp_src[1]=VLOAD(src+v8s32_offset_src.s1,16);
v16tp_src[2]=VLOAD(src+v8s32_offset_src.s2,16);
v16tp_src[3]=VLOAD(src+v8s32_offset_src.s3,16);
v16tp_src[4]=VLOAD(src+v8s32_offset_src.s4,16);
#else
v8s32_offset_src=mad24(clamp(gy+(int8)(-2,-1,0,1,2,0,0,0),0,height-1),istep,x_idx);
v16tp_src[0]=VLOAD(src+v8s32_offset_src.s0,16);
v16tp_src[1]=VLOAD(src+v8s32_offset_src.s1,16);
v16tp_src[2]=VLOAD(src+v8s32_offset_src.s2,16);
v16tp_src[3]=VLOAD(src+v8s32_offset_src.s3,16);
v16tp_src[4]=VLOAD(src+v8s32_offset_src.s4,16);
#endif
}
float16 v16f32_sum_l,v16f32_sum_c,v16f32_src;
float8 v8f32_sum_r;
float8 v8f32_result=(float8)0;
__attribute__((opencl_unroll_hint(5)))
for(int i=0;i<5;++i)
{
const int ker_id=5*i;
v16f32_src=FILTER2D_CONVERT(v16tp_src[i],float16);
v16f32_sum_l=v16f32_src.s0123456723456789*(float16)((float8)(filter[ker_id]),(float8)(filter[ker_id+1]));
v16f32_sum_c=v16f32_src.s456789AB6789ABCD*(float16)((float8)(filter[ker_id+2]),(float8)(filter[ker_id+3]));
v8f32_sum_r=v16f32_src.s89ABCDEF*filter[ker_id+4];
v8f32_result+=v16f32_sum_l.hi+v16f32_sum_l.lo+v16f32_sum_c.hi+v16f32_sum_c.lo+v8f32_sum_r;
}
V8Tp v8tp_result=CONVERT_SAT(v8f32_result,V8Tp);
VSTORE(v8tp_result,dst+mad24(gy,ostep,x_idx+ksh*channel),8);
}

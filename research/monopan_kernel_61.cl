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
gy=min(gy<<1,height-2);
float16 v16f32_src[6];
if(gy>=ksh&&(gy+1)<(height-ksh))
{
v8s32_offset_src=mad24(gy+(int8)(-2,-1,0,1,2,3,0,0),istep,x_idx);
v16f32_src[0]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s0,16),float16);
v16f32_src[1]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s1,16),float16);
v16f32_src[2]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s2,16),float16);
v16f32_src[3]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s3,16),float16);
v16f32_src[4]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s4,16),float16);
v16f32_src[5]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s5,16),float16);
}
else
{
#if BORDER_CONSTANT
short4 v4s16_flag_border;
v4s16_flag_border.lo=convert_short2(TOP_BORDER_IDX(gy+(int2)(-2,-1)));
v4s16_flag_border.hi=convert_short2(BOTTOM_BORDER_IDX(gy+(int2)(2,3),height));
v8s32_offset_src=mad24((int8)(convert_int4(abs(v4s16_flag_border)),gy+(int4)(0,1,0,0)),istep,x_idx);
v4s16_flag_border=isequal(convert_half4(v4s16_flag_border),(half4)(-1.f));
short4 v4s16_flag_body=v4s16_flag_border+(short4)(1);
v4s16_flag_border=convert_short4(abs(v4s16_flag_border));
float16 v16f32_border_value;
v16f32_border_value.lo=(float8)(border_value.val[0]);
v16f32_border_value.hi=(float8)(border_value.val[1]);
v16f32_src[0]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s0,16),float16)*(float)(v4s16_flag_body.s0)+
v16f32_border_value*(float)(v4s16_flag_border.s0);
v16f32_src[1]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s1,16),float16)*(float)(v4s16_flag_body.s1)+
v16f32_border_value*(float)(v4s16_flag_border.s1);
v16f32_src[2]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s4,16),float16);
v16f32_src[3]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s5,16),float16);
v16f32_src[4]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s2,16),float16)*(float)(v4s16_flag_body.s2)+
v16f32_border_value*(float)(v4s16_flag_border.s2);
v16f32_src[5]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s3,16),float16)*(float)(v4s16_flag_body.s3)+
v16f32_border_value*(float)(v4s16_flag_border.s3);
#elif BORDER_REFLECT_101
int8 v8_s32_offset_y=convert_int8(abs(gy+(int8)(-2,-1,0,1,2,3,0,0)));
v8s32_offset_src=mad24(select(v8_s32_offset_y,((height-1)<<1)-v8_s32_offset_y,v8_s32_offset_y>(height-1)),istep,x_idx);
v16f32_src[0]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s0,16),float16);
v16f32_src[1]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s1,16),float16);
v16f32_src[2]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s2,16),float16);
v16f32_src[3]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s3,16),float16);
v16f32_src[4]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s4,16),float16);
v16f32_src[5]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s5,16),float16);
#else
v8s32_offset_src=mad24(clamp(gy+(int8)(-2,-1,0,1,2,3,0,0),0,height-1),istep,x_idx);
v16f32_src[0]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s0,16),float16);
v16f32_src[1]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s1,16),float16);
v16f32_src[2]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s2,16),float16);
v16f32_src[3]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s3,16),float16);
v16f32_src[4]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s4,16),float16);
v16f32_src[5]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s5,16),float16);
#endif
}
float16 v16f32_sum_l,v16f32_sum_c;
float8 v8f32_sum_r;
float8 v8f32_result=(float8)0;
__attribute__((opencl_unroll_hint(5)))
for(int i=0;i<5;++i)
{
const int ker_id=5*i;
v16f32_sum_l=v16f32_src[i].s0123456723456789*(float16)((float8)(filter[ker_id]),(float8)(filter[ker_id+1]));
v16f32_sum_c=v16f32_src[i].s456789AB6789ABCD*(float16)((float8)(filter[ker_id+2]),(float8)(filter[ker_id+3]));
v8f32_sum_r=v16f32_src[i].s89ABCDEF*filter[ker_id+4];
v8f32_result+=v16f32_sum_l.hi+v16f32_sum_l.lo+v16f32_sum_c.hi+v16f32_sum_c.lo+v8f32_sum_r;
}
V8Tp v8tp_result=CONVERT_SAT(v8f32_result,V8Tp);
int2 v2s32_offset_dst=mad24(gy+(int2)(0,1),ostep,x_idx+ksh*channel);
VSTORE(v8tp_result,dst+v2s32_offset_dst.s0,8);
v8f32_result=(float8)0;
__attribute__((opencl_unroll_hint(5)))
for(int i=1;i<6;++i)
{
const int ker_id=5*(i-1);
v16f32_sum_l=v16f32_src[i].s0123456723456789*(float16)((float8)(filter[ker_id]),(float8)(filter[ker_id+1]));
v16f32_sum_c=v16f32_src[i].s456789AB6789ABCD*(float16)((float8)(filter[ker_id+2]),(float8)(filter[ker_id+3]));
v8f32_sum_r=v16f32_src[i].s89ABCDEF*filter[ker_id+4];
v8f32_result+=v16f32_sum_l.hi+v16f32_sum_l.lo+v16f32_sum_c.hi+v16f32_sum_c.lo+v8f32_sum_r;
}
v8tp_result=CONVERT_SAT(v8f32_result,V8Tp);
VSTORE(v8tp_result,dst+v2s32_offset_dst.s1,8);
}

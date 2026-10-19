kernel void Filter2dMain5x5C1(global Tp*src,int istep,
global Tp*dst,int ostep,
int height,int y_work_size,int x_work_size,
constant float*filter MAX_CONSTANT_SIZE,
struct Scalar border_value)
{
const int gx=get_global_id(0);
int gy=get_global_id(1);
const int elem_counts=4;
const int ksh=2;
const int x_idx=gx*elem_counts;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int8 v8s32_offset_src;
gy=min(gy<<1,height-2);
float8 v8f32_src[6];
if((gy>=ksh)&&((gy+1)<(height-ksh)))
{
v8s32_offset_src=mad24(gy+(int8)(-2,-1,0,1,2,3,0,0),istep,x_idx);
v8f32_src[0]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s0,8),float8);
v8f32_src[1]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s1,8),float8);
v8f32_src[2]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s2,8),float8);
v8f32_src[3]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s3,8),float8);
v8f32_src[4]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s4,8),float8);
v8f32_src[5]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s5,8),float8);
}
else
{
#if BORDER_CONSTANT
short4 v4s16_flag_body;
v4s16_flag_body.lo=convert_short2(TOP_BORDER_IDX(gy+(int2)(-2,-1)));
v4s16_flag_body.hi=convert_short2(BOTTOM_BORDER_IDX(gy+(int2)(2,3),height));
v8s32_offset_src=mad24((int8)(convert_int4(abs(v4s16_flag_body)),gy+(int4)(0,1,0,0)),istep,x_idx);
v4s16_flag_body=isequal(convert_half4(v4s16_flag_body),(half4)(-1.f));
float4 v4f32_val_border=CONVERT(abs(v4s16_flag_body),float4)*(float)border_value.val[0];
v4s16_flag_body=v4s16_flag_body+(short)(1);
v8f32_src[0]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s0,8),float8)*(float)(v4s16_flag_body.s0)+v4f32_val_border.s0;
v8f32_src[1]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s1,8),float8)*(float)(v4s16_flag_body.s1)+v4f32_val_border.s1;
v8f32_src[2]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s4,8),float8);
v8f32_src[3]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s5,8),float8);
v8f32_src[4]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s2,8),float8)*(float)(v4s16_flag_body.s2)+v4f32_val_border.s2;
v8f32_src[5]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s3,8),float8)*(float)(v4s16_flag_body.s3)+v4f32_val_border.s3;
#elif BORDER_REFLECT_101
int8 v8s32_offset_y=convert_int8(abs(gy+(int8)(-2,-1,0,1,2,3,0,0)));
v8s32_offset_src=mad24(select(v8s32_offset_y,((height-1)<<1)-v8s32_offset_y,v8s32_offset_y>(height-1)),istep,x_idx);
v8f32_src[0]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s0,8),float8);
v8f32_src[1]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s1,8),float8);
v8f32_src[2]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s2,8),float8);
v8f32_src[3]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s3,8),float8);
v8f32_src[4]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s4,8),float8);
v8f32_src[5]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s5,8),float8);
#else
v8s32_offset_src=mad24(clamp(gy+(int8)(-2,-1,0,1,2,3,0,0),0,height-1),istep,x_idx);
v8f32_src[0]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s0,8),float8);
v8f32_src[1]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s1,8),float8);
v8f32_src[2]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s2,8),float8);
v8f32_src[3]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s3,8),float8);
v8f32_src[4]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s4,8),float8);
v8f32_src[5]=FILTER2D_CONVERT(VLOAD(src+v8s32_offset_src.s5,8),float8);
#endif
}
float8 v8f32_sum_l,v8f32_sum_c;
float4 v4f32_sum_r;
float4 v4f32_result0=(float4)0,v4f32_result1=(float4)0;
__attribute__((opencl_unroll_hint(5)))
for(int i=0;i<5;++i)
{
const int ker_id=5*i;
float8 ker_param0=(float8)((float4)(filter[ker_id]),(float4)(filter[ker_id+1]));
float8 ker_param1=(float8)((float4)(filter[ker_id+2]),(float4)(filter[ker_id+3]));
float ker_param2=filter[ker_id+4];
v8f32_sum_l=v8f32_src[i].s01231234*ker_param0;
v8f32_sum_c=v8f32_src[i].s23453456*ker_param1;
v4f32_sum_r=v8f32_src[i].s4567*ker_param2;
v4f32_result0+=v8f32_sum_l.hi+v8f32_sum_l.lo+v8f32_sum_c.hi+v8f32_sum_c.lo+v4f32_sum_r;
v8f32_sum_l=v8f32_src[i+1].s01231234*ker_param0;
v8f32_sum_c=v8f32_src[i+1].s23453456*ker_param1;
v4f32_sum_r=v8f32_src[i+1].s4567*ker_param2;
v4f32_result1+=v8f32_sum_l.hi+v8f32_sum_l.lo+v8f32_sum_c.hi+v8f32_sum_c.lo+v4f32_sum_r;
}
V4Tp v4tp_result=CONVERT_SAT(v4f32_result0,V4Tp);
int2 v2s32_offset_dst=mad24(gy+(int2)(0,1),ostep,x_idx+ksh);
VSTORE(v4tp_result,dst+v2s32_offset_dst.s0,4);
v4tp_result=CONVERT_SAT(v4f32_result1,V4Tp);
VSTORE(v4tp_result,dst+v2s32_offset_dst.s1,4);
}

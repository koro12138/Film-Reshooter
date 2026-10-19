kernel void Filter2dMain3x3C1(global Tp*src,int istep,
global Tp*dst,int ostep,
int height,int y_work_size,int x_work_size,
constant float*filter MAX_CONSTANT_SIZE,
struct Scalar border_value)
{
const int gx=get_global_id(0);
int gy=get_global_id(1);
const int elem_counts=6;
const int ksh=1;
const int x_idx=gx*elem_counts;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
float8 v8f32_src[3];
int3 v3s32_offset_src;
if((gy>=ksh)&&(gy<(height-ksh)))
{
v3s32_offset_src=mad24(gy+(int3)(-1,0,1),istep,x_idx);
v8f32_src[0]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s0,8),float8);
v8f32_src[1]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s1,8),float8);
v8f32_src[2]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s2,8),float8);
}
else
{
#if BORDER_CONSTANT
short2 v2s16_flag_body=convert_short2((int2)(TOP_BORDER_IDX(gy-1),BOTTOM_BORDER_IDX(gy+1,height)));
v3s32_offset_src=mad24((int3)(convert_int2(abs(v2s16_flag_body)),gy),istep,x_idx);
v2s16_flag_body=isequal(convert_half2(v2s16_flag_body),(half2)(-1.f));
float2 v2f32_val_border=CONVERT(abs(v2s16_flag_body),float2)*(float)border_value.val[0];
v2s16_flag_body=v2s16_flag_body+(short)(1);
v8f32_src[0]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s0,8),float8)*(float)(v2s16_flag_body.s0)+v2f32_val_border.s0;
v8f32_src[1]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s2,8),float8);
v8f32_src[2]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s1,8),float8)*(float)(v2s16_flag_body.s1)+v2f32_val_border.s1;
#elif BORDER_REFLECT_101
int3 v3s32_offset_y=convert_int3(abs(gy+(int3)(-1,0,1)));
v3s32_offset_src=mad24(select(v3s32_offset_y,height-2,v3s32_offset_y>(height-1)),istep,x_idx);
v8f32_src[0]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s0,8),float8);
v8f32_src[1]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s1,8),float8);
v8f32_src[2]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s2,8),float8);
#else
v3s32_offset_src=mad24(clamp(gy+(int3)(-1,0,1),0,height-1),istep,x_idx);
v8f32_src[0]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s0,8),float8);
v8f32_src[1]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s1,8),float8);
v8f32_src[2]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s2,8),float8);
#endif
}
float8 v8f32_sum_l,v8f32_sum_c,v8f32_sum_r;
float8 v8f32_result=(float8)0;
__attribute__((opencl_unroll_hint(3)))
for(int i=0;i<3;++i)
{
const int ker_id=3*i;
v8f32_sum_l=ROT_R(v8f32_src[i],8,0)*(filter[ker_id+0]);
v8f32_sum_c=ROT_R(v8f32_src[i],8,7)*(filter[ker_id+1]);
v8f32_sum_r=ROT_R(v8f32_src[i],8,6)*(filter[ker_id+2]);
v8f32_result+=v8f32_sum_l+v8f32_sum_c+v8f32_sum_r;
}
V8Tp v8tp_result=CONVERT_SAT(v8f32_result,V8Tp);
int offset_dst=mad24(gy,ostep,x_idx+ksh);
VSTORE(v8tp_result.s0123,dst+offset_dst,4);
VSTORE(v8tp_result.s45,dst+offset_dst+4,2);
}

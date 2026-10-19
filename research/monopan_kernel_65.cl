kernel void Filter2dMain7x7C1(global Tp*src,int istep,
global Tp*dst,int ostep,
int height,int y_work_size,int x_work_size,
constant float*filter MAX_CONSTANT_SIZE,
struct Scalar border_value)
{
const int gx=get_global_id(0);
int gy=get_global_id(1);
const int elem_counts=2;
const int ksh=3;
const int x_idx=gx*elem_counts;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int8 v8s32_offset_src;
V8Tp v8f32_src[7];
if(gy>=ksh&&gy<(height-ksh))
{
v8s32_offset_src=mad24(gy+(int8)(-3,-2,-1,0,1,2,3,0),istep,x_idx);
v8f32_src[0]=VLOAD(src+v8s32_offset_src.s0,8);
v8f32_src[1]=VLOAD(src+v8s32_offset_src.s1,8);
v8f32_src[2]=VLOAD(src+v8s32_offset_src.s2,8);
v8f32_src[3]=VLOAD(src+v8s32_offset_src.s3,8);
v8f32_src[4]=VLOAD(src+v8s32_offset_src.s4,8);
v8f32_src[5]=VLOAD(src+v8s32_offset_src.s5,8);
v8f32_src[6]=VLOAD(src+v8s32_offset_src.s6,8);
}
else
{
#if BORDER_CONSTANT
short3 v3s16_y_idx_p=convert_short3(TOP_BORDER_IDX(gy+(int3)(-3,-2,-1)));
short3 v3s16_y_idx_n=convert_short3(BOTTOM_BORDER_IDX(gy+(int3)(1,2,3),height));
short8 v8s16_flag_body=(short8)(v3s16_y_idx_p,(short)gy,v3s16_y_idx_n,(short)0);
v8s32_offset_src=mad24(convert_int8(abs(v8s16_flag_body)),istep,x_idx);
v8s16_flag_body=isequal(convert_half8(v8s16_flag_body),(half8)(-1.f));
V8Tp v8tp_val_border=CONVERT(abs(v8s16_flag_body),V8Tp)*(Tp)(border_value.val[0]);
v8s16_flag_body=v8s16_flag_body+(short)(1);
v8f32_src[0]=VLOAD(src+v8s32_offset_src.s0,8)*(Tp)(v8s16_flag_body.s0)+v8tp_val_border.s0;
v8f32_src[1]=VLOAD(src+v8s32_offset_src.s1,8)*(Tp)(v8s16_flag_body.s1)+v8tp_val_border.s1;
v8f32_src[2]=VLOAD(src+v8s32_offset_src.s2,8)*(Tp)(v8s16_flag_body.s2)+v8tp_val_border.s2;
v8f32_src[3]=VLOAD(src+v8s32_offset_src.s3,8);
v8f32_src[4]=VLOAD(src+v8s32_offset_src.s4,8)*(Tp)(v8s16_flag_body.s4)+v8tp_val_border.s4;
v8f32_src[5]=VLOAD(src+v8s32_offset_src.s5,8)*(Tp)(v8s16_flag_body.s5)+v8tp_val_border.s5;
v8f32_src[6]=VLOAD(src+v8s32_offset_src.s6,8)*(Tp)(v8s16_flag_body.s6)+v8tp_val_border.s6;
#elif BORDER_REFLECT_101
int8 v8_s32_offset_y=convert_int8(abs(gy+(int8)(-3,-2,-1,0,1,2,3,0)));
v8s32_offset_src=mad24(select(v8_s32_offset_y,((height-1)<<1)-v8_s32_offset_y,v8_s32_offset_y>(height-1)),istep,x_idx);
v8f32_src[0]=VLOAD(src+v8s32_offset_src.s0,8);
v8f32_src[1]=VLOAD(src+v8s32_offset_src.s1,8);
v8f32_src[2]=VLOAD(src+v8s32_offset_src.s2,8);
v8f32_src[3]=VLOAD(src+v8s32_offset_src.s3,8);
v8f32_src[4]=VLOAD(src+v8s32_offset_src.s4,8);
v8f32_src[5]=VLOAD(src+v8s32_offset_src.s5,8);
v8f32_src[6]=VLOAD(src+v8s32_offset_src.s6,8);
#else
v8s32_offset_src=mad24(clamp(gy+(int8)(-3,-2,-1,0,1,2,3,0),0,height-1),istep,x_idx);
v8f32_src[0]=VLOAD(src+v8s32_offset_src.s0,8);
v8f32_src[1]=VLOAD(src+v8s32_offset_src.s1,8);
v8f32_src[2]=VLOAD(src+v8s32_offset_src.s2,8);
v8f32_src[3]=VLOAD(src+v8s32_offset_src.s3,8);
v8f32_src[4]=VLOAD(src+v8s32_offset_src.s4,8);
v8f32_src[5]=VLOAD(src+v8s32_offset_src.s5,8);
v8f32_src[6]=VLOAD(src+v8s32_offset_src.s6,8);
#endif
}
float16 v16f32_sum=(float16)0;
__attribute__((opencl_unroll_hint(7)))
for(int i=0;i<7;++i)
{
const int ker_id=7*i;
v16f32_sum+=FILTER2D_CONVERT((V16Tp)(v8f32_src[i].s01,v8f32_src[i].s12,v8f32_src[i].s23,v8f32_src[i].s34,
v8f32_src[i].s45,v8f32_src[i].s56,v8f32_src[i].s67,(V2Tp)0),float16)*
(float16)((float2)filter[ker_id],(float2)filter[ker_id+1],
(float2)filter[ker_id+2],(float2)filter[ker_id+3],(float2)filter[ker_id+4],
(float2)filter[ker_id+5],(float2)filter[ker_id+6],(float2)0);
}
float2 v2f32_result=(float2)(SUM_REDUCE(v16f32_sum.even,8),SUM_REDUCE(v16f32_sum.odd,8));
V2Tp v2tp_result=CONVERT_SAT(v2f32_result,V2Tp);
VSTORE(v2tp_result,dst+mad24(gy,ostep,x_idx+ksh),2);
}

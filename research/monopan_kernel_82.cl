kernel void GaussianMain7x7C1(global St*src,int istep,
global Dt*dst,int ostep,
int height,int y_work_size,int x_work_size,
constant Kt*filter MAX_CONSTANT_SIZE,
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
V8InterType v8it_src[7];
if((gy>=ksh)&&(gy<(height-ksh)))
{
v8s32_offset_src=mad24(gy+(int8)(-3,-2,-1,0,1,2,3,4),istep,x_idx);
v8it_src[0]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s0,8),V8InterType);
v8it_src[1]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s1,8),V8InterType);
v8it_src[2]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s2,8),V8InterType);
v8it_src[3]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s3,8),V8InterType);
v8it_src[4]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s4,8),V8InterType);
v8it_src[5]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s5,8),V8InterType);
v8it_src[6]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s6,8),V8InterType);
}
else
{
#if BORDER_CONSTANT
short3 v3s16_y_idx_p=convert_short3(TOP_BORDER_IDX(gy+(int3)(-3,-2,-1)));
short3 v3s16_y_idx_n=convert_short3(BOTTOM_BORDER_IDX(gy+(int3)(1,2,3),height));
short8 v8s16_flag_body=(short8)(v3s16_y_idx_p,v3s16_y_idx_n,(short)gy,(short)(gy+1));
v8s32_offset_src=mad24(convert_int8(abs(v8s16_flag_body)),istep,x_idx);
v8s16_flag_body=isequal(convert_half8(v8s16_flag_body),(half8)(-1.f));
V8InterType v8it_border_value=(InterType)border_value.val[0]*CONVERT(v8s16_flag_body,V8InterType);
v8s16_flag_body=v8s16_flag_body+(short)(1);
v8it_src[0]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s0,8),V8InterType)*(InterType)(v8s16_flag_body.s0)+v8it_border_value.s0;
v8it_src[1]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s1,8),V8InterType)*(InterType)(v8s16_flag_body.s1)+v8it_border_value.s1;
v8it_src[2]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s2,8),V8InterType)*(InterType)(v8s16_flag_body.s2)+v8it_border_value.s2;
v8it_src[3]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s6,8),V8InterType);
v8it_src[4]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s3,8),V8InterType)*(InterType)(v8s16_flag_body.s3)+v8it_border_value.s3;
v8it_src[5]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s4,8),V8InterType)*(InterType)(v8s16_flag_body.s4)+v8it_border_value.s4;
v8it_src[6]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s5,8),V8InterType)*(InterType)(v8s16_flag_body.s5)+v8it_border_value.s5;
#elif BORDER_REFLECT_101
int8 offset_y=convert_int8(abs(gy+(int8)(-3,-2,-1,0,1,2,3,4)));
v8s32_offset_src=mad24(select(offset_y,((height-1)<<1)-offset_y,offset_y>(height-1)),istep,x_idx);
v8it_src[0]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s0,8),V8InterType);
v8it_src[1]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s1,8),V8InterType);
v8it_src[2]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s2,8),V8InterType);
v8it_src[3]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s3,8),V8InterType);
v8it_src[4]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s4,8),V8InterType);
v8it_src[5]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s5,8),V8InterType);
v8it_src[6]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s6,8),V8InterType);
#else
v8s32_offset_src=mad24(clamp(gy+(int8)(-3,-2,-1,0,1,2,3,4),0,height-1),istep,x_idx);
v8it_src[0]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s0,8),V8InterType);
v8it_src[1]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s1,8),V8InterType);
v8it_src[2]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s2,8),V8InterType);
v8it_src[3]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s3,8),V8InterType);
v8it_src[4]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s4,8),V8InterType);
v8it_src[5]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s5,8),V8InterType);
v8it_src[6]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s6,8),V8InterType);
#endif
}
#if IS_FLOAT(InterType)
V8InterType v8it_sum=fma(v8it_src[0]+v8it_src[6],filter[0],fma(v8it_src[1]+v8it_src[5],filter[1],
fma(v8it_src[2]+v8it_src[4],filter[2],v8it_src[3]*filter[3])));
V2InterType v2it_result=fma(v8it_sum.s01+v8it_sum.s67,filter[0],fma(v8it_sum.s12+v8it_sum.s56,filter[1],
fma(v8it_sum.s23+v8it_sum.s45,filter[2],v8it_sum.s34*filter[3])));
#else
V8InterType v8it_sum=(v8it_src[0]+v8it_src[6])*filter[0]+(v8it_src[1]+v8it_src[5])*filter[1]+
(v8it_src[2]+v8it_src[4])*filter[2]+v8it_src[3]*filter[3];
V2InterType v2it_result=(v8it_sum.s01+v8it_sum.s67)*filter[0]+(v8it_sum.s12+v8it_sum.s56)*filter[1]+
(v8it_sum.s23+v8it_sum.s45)*filter[2]+v8it_sum.s34*filter[3];
#endif
#if IS_FLOAT(InterType)
V2Dt v2dt_result=CONVERT(v2it_result,V2Dt);
#else
V2Dt v2dt_result=CONVERT_SAT((v2it_result+(InterType)(1<<(Q-1)))>>Q,V2Dt);
#endif
VSTORE(v2dt_result,dst+mad24(gy,ostep,x_idx+ksh),2);
}

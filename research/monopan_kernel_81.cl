kernel void GaussianMain7x7C1(global St*src,int istep,
global Dt*dst,int ostep,
int height,int y_work_size,int x_work_size,
constant Kt*filter MAX_CONSTANT_SIZE,
struct Scalar border_value)
{
const int gx=get_global_id(0);
int gy=get_global_id(1);
const int elem_counts=10;
const int ksh=3;
const int x_idx=gx*elem_counts;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
#if!IS_UINT(InterType)
gy=min(gy<<1,height-2);
#endif
int8 v8s32_offset_src;
#if!IS_UINT(InterType)
V16InterType v16it_src[8];
if(gy>=ksh&&(gy+1)<(height-ksh))
#else
V16InterType v16it_src[7];
if(gy>=ksh&&gy<(height-ksh))
#endif
{
v8s32_offset_src=mad24(gy+(int8)(-3,-2,-1,0,1,2,3,4),istep,x_idx);
v16it_src[0]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s0,16),V16InterType);
v16it_src[1]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s1,16),V16InterType);
v16it_src[2]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s2,16),V16InterType);
v16it_src[3]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s3,16),V16InterType);
v16it_src[4]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s4,16),V16InterType);
v16it_src[5]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s5,16),V16InterType);
v16it_src[6]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s6,16),V16InterType);
#if!IS_UINT(InterType)
v16it_src[7]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s7,16),V16InterType);
#endif
}
else
{
#if BORDER_CONSTANT
short3 v3s16_y_idx_p=convert_short3(TOP_BORDER_IDX(gy+(int3)(-3,-2,-1)));
#if!IS_UINT(InterType)
short3 v3s16_y_idx_n=convert_short3(BOTTOM_BORDER_IDX(gy+(int3)(2,3,4),height));
#else
short3 v3s16_y_idx_n=convert_short3(BOTTOM_BORDER_IDX(gy+(int3)(1,2,3),height));
#endif
short8 v8s16_flag_body=(short8)(v3s16_y_idx_p,v3s16_y_idx_n,(short)gy,(short)(gy+1));
v8s32_offset_src=mad24(convert_int8(abs(v8s16_flag_body)),istep,x_idx);
v8s16_flag_body=isequal(convert_half8(v8s16_flag_body),(half8)(-1.f));
V8InterType v8it_border_value=(InterType)border_value.val[0]*CONVERT(v8s16_flag_body,V8InterType);
v8s16_flag_body=v8s16_flag_body+(short)(1);
v16it_src[0]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s0,16),V16InterType)*(InterType)(v8s16_flag_body.s0)+v8it_border_value.s0;
v16it_src[1]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s1,16),V16InterType)*(InterType)(v8s16_flag_body.s1)+v8it_border_value.s1;
v16it_src[2]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s2,16),V16InterType)*(InterType)(v8s16_flag_body.s2)+v8it_border_value.s2;
v16it_src[3]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s6,16),V16InterType);
#if!IS_UINT(InterType)
v16it_src[4]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s7,16),V16InterType);
v16it_src[5]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s3,16),V16InterType)*(InterType)(v8s16_flag_body.s3)+v8it_border_value.s3;
v16it_src[6]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s4,16),V16InterType)*(InterType)(v8s16_flag_body.s4)+v8it_border_value.s4;
v16it_src[7]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s5,16),V16InterType)*(InterType)(v8s16_flag_body.s5)+v8it_border_value.s5;
#else
v16it_src[4]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s3,16),V16InterType)*(InterType)(v8s16_flag_body.s3)+v8it_border_value.s3;
v16it_src[5]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s4,16),V16InterType)*(InterType)(v8s16_flag_body.s4)+v8it_border_value.s4;
v16it_src[6]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s5,16),V16InterType)*(InterType)(v8s16_flag_body.s5)+v8it_border_value.s5;
#endif
#elif BORDER_REFLECT_101
int8 offset_y=convert_int8(abs(gy+(int8)(-3,-2,-1,0,1,2,3,4)));
v8s32_offset_src=mad24(select(offset_y,((height-1)<<1)-offset_y,offset_y>(height-1)),istep,x_idx);
v16it_src[0]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s0,16),V16InterType);
v16it_src[1]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s1,16),V16InterType);
v16it_src[2]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s2,16),V16InterType);
v16it_src[3]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s3,16),V16InterType);
v16it_src[4]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s4,16),V16InterType);
v16it_src[5]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s5,16),V16InterType);
v16it_src[6]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s6,16),V16InterType);
#if!IS_UINT(InterType)
v16it_src[7]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s7,16),V16InterType);
#endif
#else
v8s32_offset_src=mad24(clamp(gy+(int8)(-3,-2,-1,0,1,2,3,4),0,height-1),istep,x_idx);
v16it_src[0]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s0,16),V16InterType);
v16it_src[1]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s1,16),V16InterType);
v16it_src[2]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s2,16),V16InterType);
v16it_src[3]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s3,16),V16InterType);
v16it_src[4]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s4,16),V16InterType);
v16it_src[5]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s5,16),V16InterType);
v16it_src[6]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s6,16),V16InterType);
#if!IS_UINT(InterType)
v16it_src[7]=GAUSSIAN_CONVERT(VLOAD(src+v8s32_offset_src.s7,16),V16InterType);
#endif
#endif
}
V8Dt v8dt_result;
V2Dt v2dt_result;
v16it_src[0]=(v16it_src[0]+v16it_src[6])*filter[0]+(v16it_src[1]+v16it_src[5])*filter[1]+
(v16it_src[2]+v16it_src[4])*filter[2]+v16it_src[3]*filter[3];
v16it_src[0]=(v16it_src[0].s0123456789abcdef+v16it_src[0].s6789abcdefabcdef)*filter[0]+
(v16it_src[0].s123456789aabcdef+v16it_src[0].s56789abcdeabcdef)*filter[1]+
(v16it_src[0].s23456789ababcdef+v16it_src[0].s456789abcdabcdef)*filter[2]+v16it_src[0].s3456789abcabcdef*filter[3];
#if!IS_UINT(InterType)
v8dt_result=CONVERT(v16it_src[0].s01234567,V8Dt);
v2dt_result=CONVERT(v16it_src[0].s89,V2Dt);
#else
const InterType round_offset=(InterType)(1<<(Q-1));
v16it_src[0]=(v16it_src[0]+round_offset)>>Q;
v8dt_result=CONVERT_SAT(v16it_src[0].s01234567,V8Dt);
v2dt_result=CONVERT_SAT(v16it_src[0].s89,V2Dt);
#endif
int2 v2s32_offset_dst=mad24(gy+(int2)(0,1),ostep,x_idx+ksh);
VSTORE(v8dt_result,dst+v2s32_offset_dst.s0,8);
VSTORE(v2dt_result,dst+v2s32_offset_dst.s0+8,2);
#if!IS_UINT(InterType)
v16it_src[1]=(v16it_src[1]+v16it_src[7])*filter[0]+(v16it_src[2]+v16it_src[6])*filter[1]+
(v16it_src[3]+v16it_src[5])*filter[2]+v16it_src[4]*filter[3];
v16it_src[1]=(v16it_src[1].s0123456789abcdef+v16it_src[1].s6789abcdefabcdef)*filter[0]+
(v16it_src[1].s123456789aabcdef+v16it_src[1].s56789abcdeabcdef)*filter[1]+
(v16it_src[1].s23456789ababcdef+v16it_src[1].s456789abcdabcdef)*filter[2]+v16it_src[1].s3456789abcabcdef*filter[3];
v8dt_result=CONVERT(v16it_src[1].s01234567,V8Dt);
v2dt_result=CONVERT(v16it_src[1].s89,V2Dt);
VSTORE(v8dt_result,dst+v2s32_offset_dst.s1,8);
VSTORE(v2dt_result,dst+v2s32_offset_dst.s1+8,2);
#endif
}

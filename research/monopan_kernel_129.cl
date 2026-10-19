kernel void SobelMain3x3C1(global St*src,int istep,
global Dt*dst,int ostep,
int height,float scale,
int y_work_size,int x_work_size,
struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
int elem_counts=6;
int ksh=1;
int x_idx=gx*elem_counts;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int offset_src_p,offset_src_c,offset_src_n,offset_dst;
V8InterType v8it_src_p,v8it_src_c,v8it_src_n;
V8InterType v8it_sum_l,v8it_sum_c,v8it_sum_r;
V8InterType v8it_result;
V8Dt v8dt_result;
if(gy>=ksh&&gy<(height-ksh))
{
offset_src_p=mad24(gy-1,istep,x_idx);
offset_src_c=mad24(gy,istep,x_idx);
offset_src_n=mad24(gy+1,istep,x_idx);
v8it_src_p=SOBEL_CONVERT(VLOAD(src+offset_src_p,8),V8InterType);
v8it_src_c=SOBEL_CONVERT(VLOAD(src+offset_src_c,8),V8InterType);
v8it_src_n=SOBEL_CONVERT(VLOAD(src+offset_src_n,8),V8InterType);
}
else
{
int y_idx_p,y_idx_c,y_idx_n;
y_idx_p=TOP_BORDER_IDX(gy-1);
y_idx_c=gy;
y_idx_n=BOTTOM_BORDER_IDX(gy+1,height);
offset_src_p=mad24(y_idx_p,istep,x_idx);
offset_src_c=mad24(y_idx_c,istep,x_idx);
offset_src_n=mad24(y_idx_n,istep,x_idx);
#if BORDER_CONSTANT
V8InterType v8it_border_value=(V8InterType)border_value.val[0];
v8it_src_p=(y_idx_p<0)?(V8InterType)v8it_border_value:SOBEL_CONVERT(VLOAD(src+offset_src_p,8),V8InterType);
v8it_src_c=SOBEL_CONVERT(VLOAD(src+offset_src_c,8),V8InterType);
v8it_src_n=(y_idx_n<0)?(V8InterType)v8it_border_value:SOBEL_CONVERT(VLOAD(src+offset_src_n,8),V8InterType);
#else
v8it_src_p=SOBEL_CONVERT(VLOAD(src+offset_src_p,8),V8InterType);
v8it_src_c=SOBEL_CONVERT(VLOAD(src+offset_src_c,8),V8InterType);
v8it_src_n=SOBEL_CONVERT(VLOAD(src+offset_src_n,8),V8InterType);
#endif
}
#if 0==DY
v8it_sum_l=(v8it_src_p+v8it_src_n)+v8it_src_c*(V8InterType)2;
#elif 1==DY
v8it_sum_l=v8it_src_n-v8it_src_p;
#elif 2==DY
v8it_sum_l=(v8it_src_p+v8it_src_n)-v8it_src_c*(V8InterType)2;
#else
v8it_sum_l=(v8it_src_p+v8it_src_n)*(V8InterType)3+v8it_src_c*(V8InterType)10;
#endif
v8it_sum_c=ROT_R(v8it_sum_l,8,7);
v8it_sum_r=ROT_R(v8it_sum_l,8,6);
#if 0==DX
v8it_result=(v8it_sum_l+v8it_sum_r)+v8it_sum_c*(V8InterType)2;
#elif 1==DX
v8it_result=v8it_sum_r-v8it_sum_l;
#elif 2==DX
v8it_result=(v8it_sum_l+v8it_sum_r)-v8it_sum_c*(V8InterType)2;
#else
v8it_result=(v8it_sum_l+v8it_sum_r)*(V8InterType)3+v8it_sum_c*(V8InterType)10;
#endif
#if IS_FLOAT(InterType)
v8dt_result=CONVERT(v8it_result,V8Dt);
#else
v8dt_result=CONVERT_SAT(v8it_result,V8Dt);
#endif
#if WITH_SCALE
v8dt_result=CONVERT_SAT(CONVERT(v8dt_result,float8)*(float8)scale,V8Dt);
#endif
offset_dst=mad24(gy,ostep,x_idx+ksh);
VSTORE(v8dt_result.s0123,dst+offset_dst,4);
VSTORE(v8dt_result.s45,dst+offset_dst+4,2);
}

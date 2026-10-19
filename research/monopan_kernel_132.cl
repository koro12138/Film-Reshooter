kernel void SobelMain5x5C1(global St*src,int istep,
global Dt*dst,int ostep,
int height,float scale,
int y_work_size,int x_work_size,
struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
int elem_counts=4;
int ksh=2;
int x_idx=gx*elem_counts;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int offset_src_p1,offset_src_p0,offset_src_c,offset_src_n0,offset_src_n1;
int offset_dst;
V8InterType v8it_src_p1,v8it_src_p0,v8it_src_c,v8it_src_n0,v8it_src_n1,v8it_sum;
V4InterType v4it_sum_l1,v4it_sum_l0,v4it_sum_c,v4it_sum_r0,v4it_sum_r1,v4it_result;
V4Dt v4dt_result;
if(gy>=ksh&&gy<(height-ksh))
{
offset_src_p1=mad24(gy-2,istep,x_idx);
offset_src_p0=mad24(gy-1,istep,x_idx);
offset_src_c=mad24(gy,istep,x_idx);
offset_src_n0=mad24(gy+1,istep,x_idx);
offset_src_n1=mad24(gy+2,istep,x_idx);
v8it_src_p1=SOBEL_CONVERT(VLOAD(src+offset_src_p1,8),V8InterType);
v8it_src_p0=SOBEL_CONVERT(VLOAD(src+offset_src_p0,8),V8InterType);
v8it_src_c=SOBEL_CONVERT(VLOAD(src+offset_src_c,8),V8InterType);
v8it_src_n0=SOBEL_CONVERT(VLOAD(src+offset_src_n0,8),V8InterType);
v8it_src_n1=SOBEL_CONVERT(VLOAD(src+offset_src_n1,8),V8InterType);
}
else
{
int y_idx_p1,y_idx_p0,y_idx_c,y_idx_n0,y_idx_n1;
y_idx_p1=TOP_BORDER_IDX(gy-2);
y_idx_p0=TOP_BORDER_IDX(gy-1);
y_idx_c=gy;
y_idx_n0=BOTTOM_BORDER_IDX(gy+1,height);
y_idx_n1=BOTTOM_BORDER_IDX(gy+2,height);
offset_src_p1=mad24(y_idx_p1,istep,x_idx);
offset_src_p0=mad24(y_idx_p0,istep,x_idx);
offset_src_c=mad24(y_idx_c,istep,x_idx);
offset_src_n0=mad24(y_idx_n0,istep,x_idx);
offset_src_n1=mad24(y_idx_n1,istep,x_idx);
#if BORDER_CONSTANT
V8InterType v8it_border_value=(V8InterType)border_value.val[0];
v8it_src_p1=(y_idx_p1<0)?(V8InterType)v8it_border_value:SOBEL_CONVERT(VLOAD(src+offset_src_p1,8),V8InterType);
v8it_src_p0=(y_idx_p0<0)?(V8InterType)v8it_border_value:SOBEL_CONVERT(VLOAD(src+offset_src_p0,8),V8InterType);
v8it_src_c=SOBEL_CONVERT(VLOAD(src+offset_src_c,8),V8InterType);
v8it_src_n0=(y_idx_n0<0)?(V8InterType)v8it_border_value:SOBEL_CONVERT(VLOAD(src+offset_src_n0,8),V8InterType);
v8it_src_n1=(y_idx_n1<0)?(V8InterType)v8it_border_value:SOBEL_CONVERT(VLOAD(src+offset_src_n1,8),V8InterType);
#else
v8it_src_p1=SOBEL_CONVERT(VLOAD(src+offset_src_p1,8),V8InterType);
v8it_src_p0=SOBEL_CONVERT(VLOAD(src+offset_src_p0,8),V8InterType);
v8it_src_c=SOBEL_CONVERT(VLOAD(src+offset_src_c,8),V8InterType);
v8it_src_n0=SOBEL_CONVERT(VLOAD(src+offset_src_n0,8),V8InterType);
v8it_src_n1=SOBEL_CONVERT(VLOAD(src+offset_src_n1,8),V8InterType);
#endif
}
v8it_sum=v8it_src_p1*(V8InterType)v0+v8it_src_p0*(V8InterType)v1+
v8it_src_c*(V8InterType)v2+v8it_src_n0*(V8InterType)v3+
v8it_src_n1*(V8InterType)v4;
v4it_sum_l1=(V4InterType)(v8it_sum.s0123);
v4it_sum_l0=(V4InterType)(v8it_sum.s1234);
v4it_sum_c=(V4InterType)(v8it_sum.s2345);
v4it_sum_r0=(V4InterType)(v8it_sum.s3456);
v4it_sum_r1=(V4InterType)(v8it_sum.s4567);
v4it_result=v4it_sum_l1*(V4InterType)h0+v4it_sum_l0*(V4InterType)h1+
v4it_sum_c*(V4InterType)h2+v4it_sum_r0*(V4InterType)h3+
v4it_sum_r1*(V4InterType)h4;
#if IS_FLOAT(InterType)
v4dt_result=CONVERT(v4it_result,V4Dt);
#else
v4dt_result=CONVERT_SAT(v4it_result,V4Dt);
#endif
#if WITH_SCALE
v4dt_result=CONVERT_SAT(CONVERT(v4dt_result,float4)*(float4)scale,V4Dt);
#endif
offset_dst=mad24(gy,ostep,x_idx+ksh);
VSTORE(v4dt_result,dst+offset_dst,4);
}

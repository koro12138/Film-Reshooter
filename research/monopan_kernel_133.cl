kernel void SobelMain5x5C2(global St*src,int istep,
global Dt*dst,int ostep,
int height,float scale,
int y_work_size,int x_work_size,
struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
int elem_counts=4;
int ksh=2;
int channel=2;
int x_idx=gx*elem_counts*channel;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int offset_src_p1,offset_src_p0,offset_src_c,offset_src_n0,offset_src_n1;
int offset_dst;
V16InterType v16it_src_p1,v16it_src_p0,v16it_src_c,v16it_src_n0,v16it_src_n1,v16it_sum;
V8InterType v8it_sum_l1,v8it_sum_l0,v8it_sum_c,v8it_sum_r0,v8it_sum_r1;
V8InterType v8it_result;
V8Dt v8dt_result;
if(gy>=ksh&&gy<(height-ksh))
{
offset_src_p1=mad24(gy-2,istep,x_idx);
offset_src_p0=mad24(gy-1,istep,x_idx);
offset_src_c=mad24(gy,istep,x_idx);
offset_src_n0=mad24(gy+1,istep,x_idx);
offset_src_n1=mad24(gy+2,istep,x_idx);
v16it_src_p1=SOBEL_CONVERT(VLOAD(src+offset_src_p1,16),V16InterType);
v16it_src_p0=SOBEL_CONVERT(VLOAD(src+offset_src_p0,16),V16InterType);
v16it_src_c=SOBEL_CONVERT(VLOAD(src+offset_src_c,16),V16InterType);
v16it_src_n0=SOBEL_CONVERT(VLOAD(src+offset_src_n0,16),V16InterType);
v16it_src_n1=SOBEL_CONVERT(VLOAD(src+offset_src_n1,16),V16InterType);
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
V2InterType v2it_border_value={(InterType)border_value.val[0],(InterType)border_value.val[1]};
V8InterType v8it_border_value={v2it_border_value,v2it_border_value,v2it_border_value,v2it_border_value};
V16InterType v16it_border_value={v8it_border_value,v8it_border_value};
v16it_src_p1=y_idx_p1<0?v16it_border_value:SOBEL_CONVERT(VLOAD(src+offset_src_p1,16),V16InterType);
v16it_src_p0=y_idx_p0<0?v16it_border_value:SOBEL_CONVERT(VLOAD(src+offset_src_p0,16),V16InterType);
v16it_src_c=SOBEL_CONVERT(VLOAD(src+offset_src_c,16),V16InterType);
v16it_src_n0=y_idx_n0<0?v16it_border_value:SOBEL_CONVERT(VLOAD(src+offset_src_n0,16),V16InterType);
v16it_src_n1=y_idx_n1<0?v16it_border_value:SOBEL_CONVERT(VLOAD(src+offset_src_n1,16),V16InterType);
#else
v16it_src_p1=SOBEL_CONVERT(VLOAD(src+offset_src_p1,16),V16InterType);
v16it_src_p0=SOBEL_CONVERT(VLOAD(src+offset_src_p0,16),V16InterType);
v16it_src_c=SOBEL_CONVERT(VLOAD(src+offset_src_c,16),V16InterType);
v16it_src_n0=SOBEL_CONVERT(VLOAD(src+offset_src_n0,16),V16InterType);
v16it_src_n1=SOBEL_CONVERT(VLOAD(src+offset_src_n1,16),V16InterType);
#endif
}
v16it_sum=v16it_src_p1*(V16InterType)v0+v16it_src_p0*(V16InterType)v1+
v16it_src_c*(V16InterType)v2+v16it_src_n0*(V16InterType)v3+
v16it_src_n1*(V16InterType)v4;
v8it_sum_l1=(V8InterType)(v16it_sum.s01234567);
v8it_sum_l0=(V8InterType)(v16it_sum.s23456789);
v8it_sum_c=(V8InterType)(v16it_sum.s456789AB);
v8it_sum_r0=(V8InterType)(v16it_sum.s6789ABCD);
v8it_sum_r1=(V8InterType)(v16it_sum.s89ABCDEF);
v8it_result=v8it_sum_l1*(V8InterType)h0+v8it_sum_l0*(V8InterType)h1+
v8it_sum_c*(V8InterType)h2+v8it_sum_r0*(V8InterType)h3+
v8it_sum_r1*(V8InterType)h4;
#if IS_FLOAT(InterType)
v8dt_result=CONVERT(v8it_result,V8Dt);
#else
v8dt_result=CONVERT_SAT(v8it_result,V8Dt);
#endif
#if WITH_SCALE
v8dt_result=CONVERT_SAT(CONVERT(v8dt_result,float8)*(float8)scale,V8Dt);
#endif
offset_dst=mad24(gy,ostep,x_idx+ksh*channel);
VSTORE(v8dt_result,dst+offset_dst,8);
}

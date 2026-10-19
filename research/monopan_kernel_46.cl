kernel void BoxfilterMain7x7C1(global St*src,int istep,
global Dt*dst,int ostep,
int height,int x_work_size,int y_work_size,
struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
const int elem_counts=2;
const int ksh=3;
const int x_idx=gx*elem_counts;
const int y_idx=gy<<1;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int y_idx_p2,y_idx_p1,y_idx_p0,y_idx_c0,y_idx_c1,y_idx_n0,y_idx_n1,y_idx_n2;
int offset_src_p2,offset_src_p1,offset_src_p0,offset_src_c0,offset_src_c1,offset_src_n0,offset_src_n1,offset_src_n2;
int offset_dst;
V8InterType v8it_src_p2,v8it_src_p1,v8it_src_p0,v8it_src_c0,v8it_src_c1,v8it_src_n0,v8it_src_n1,v8it_src_n2;
V8InterType v8it_sum_m,v8it_sum_c0,v8it_sum_c1;
V2InterType v2it_sum_l2,v2it_sum_l1,v2it_sum_l0,v2it_sum_c0,v2it_sum_c1,v2it_sum_n0,v2it_sum_n1,v2it_sum_n2;
V2InterType v2it_result_c0,v2it_result_c1;
V2Dt v2dt_result_c0,v2dt_result_c1;
if(y_idx>=ksh&&y_idx+1<(height-ksh))
{
offset_src_p2=mad24(y_idx-3,istep,x_idx);
offset_src_p1=mad24(y_idx-2,istep,x_idx);
offset_src_p0=mad24(y_idx-1,istep,x_idx);
offset_src_c0=mad24(y_idx,istep,x_idx);
offset_src_c1=mad24(y_idx+1,istep,x_idx);
offset_src_n0=mad24(y_idx+2,istep,x_idx);
offset_src_n1=mad24(y_idx+3,istep,x_idx);
offset_src_n2=mad24(y_idx+4,istep,x_idx);
v8it_src_p2=BOXFILTER_CONVERT(VLOAD(src+offset_src_p2,8),V8InterType);
v8it_src_p1=BOXFILTER_CONVERT(VLOAD(src+offset_src_p1,8),V8InterType);
v8it_src_p0=BOXFILTER_CONVERT(VLOAD(src+offset_src_p0,8),V8InterType);
v8it_src_c0=BOXFILTER_CONVERT(VLOAD(src+offset_src_c0,8),V8InterType);
v8it_src_c1=BOXFILTER_CONVERT(VLOAD(src+offset_src_c1,8),V8InterType);
v8it_src_n0=BOXFILTER_CONVERT(VLOAD(src+offset_src_n0,8),V8InterType);
v8it_src_n1=BOXFILTER_CONVERT(VLOAD(src+offset_src_n1,8),V8InterType);
v8it_src_n2=BOXFILTER_CONVERT(VLOAD(src+offset_src_n2,8),V8InterType);
}
else
{
y_idx_p2=TOP_BORDER_IDX(y_idx-3);
y_idx_p1=TOP_BORDER_IDX(y_idx-2);
y_idx_p0=TOP_BORDER_IDX(y_idx-1);
y_idx_c0=y_idx;
y_idx_c1=BOTTOM_BORDER_IDX(y_idx+1,height);
y_idx_n0=BOTTOM_BORDER_IDX(y_idx+2,height);
y_idx_n1=BOTTOM_BORDER_IDX(y_idx+3,height);
y_idx_n2=BOTTOM_BORDER_IDX(y_idx+4,height);
offset_src_p2=mad24(y_idx_p2,istep,x_idx);
offset_src_p1=mad24(y_idx_p1,istep,x_idx);
offset_src_p0=mad24(y_idx_p0,istep,x_idx);
offset_src_c0=mad24(y_idx_c0,istep,x_idx);
offset_src_c1=mad24(y_idx_c1,istep,x_idx);
offset_src_n0=mad24(y_idx_n0,istep,x_idx);
offset_src_n1=mad24(y_idx_n1,istep,x_idx);
offset_src_n2=mad24(y_idx_n2,istep,x_idx);
#if BORDER_CONSTANT
V8InterType v8it_border_value=(V8InterType)border_value.val[0];
v8it_src_p2=(y_idx_p2<0)?(V8InterType)v8it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_p2,8),V8InterType);
v8it_src_p1=(y_idx_p1<0)?(V8InterType)v8it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_p1,8),V8InterType);
v8it_src_p0=(y_idx_p0<0)?(V8InterType)v8it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_p0,8),V8InterType);
v8it_src_c0=BOXFILTER_CONVERT(VLOAD(src+offset_src_c0,8),V8InterType);
v8it_src_c1=(y_idx_c1<0)?(V8InterType)v8it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_c1,8),V8InterType);
v8it_src_n0=(y_idx_n0<0)?(V8InterType)v8it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_n0,8),V8InterType);
v8it_src_n1=(y_idx_n1<0)?(V8InterType)v8it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_n1,8),V8InterType);
v8it_src_n2=(y_idx_n2<0)?(V8InterType)v8it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_n2,8),V8InterType);
#else
v8it_src_p2=BOXFILTER_CONVERT(VLOAD(src+offset_src_p2,8),V8InterType);
v8it_src_p1=BOXFILTER_CONVERT(VLOAD(src+offset_src_p1,8),V8InterType);
v8it_src_p0=BOXFILTER_CONVERT(VLOAD(src+offset_src_p0,8),V8InterType);
v8it_src_c0=BOXFILTER_CONVERT(VLOAD(src+offset_src_c0,8),V8InterType);
v8it_src_c1=BOXFILTER_CONVERT(VLOAD(src+offset_src_c1,8),V8InterType);
v8it_src_n0=BOXFILTER_CONVERT(VLOAD(src+offset_src_n0,8),V8InterType);
v8it_src_n1=BOXFILTER_CONVERT(VLOAD(src+offset_src_n1,8),V8InterType);
v8it_src_n2=BOXFILTER_CONVERT(VLOAD(src+offset_src_n2,8),V8InterType);
#endif
}
v8it_sum_m=v8it_src_p1+v8it_src_p0+v8it_src_c0+
v8it_src_c1+v8it_src_n0+v8it_src_n1;
v8it_sum_c0=v8it_sum_m+v8it_src_p2;
v8it_sum_c1=v8it_sum_m+v8it_src_n2;
v2it_result_c0=v8it_sum_c0.s01+v8it_sum_c0.s12+v8it_sum_c0.s23+v8it_sum_c0.s34+
v8it_sum_c0.s45+v8it_sum_c0.s56+v8it_sum_c0.s67;
v2it_result_c1=v8it_sum_c1.s01+v8it_sum_c1.s12+v8it_sum_c1.s23+v8it_sum_c1.s34+
v8it_sum_c1.s45+v8it_sum_c1.s56+v8it_sum_c1.s67;
v2dt_result_c0=CONVERT(v2it_result_c0/(V2InterType)49,V2Dt);
v2dt_result_c1=CONVERT(v2it_result_c1/(V2InterType)49,V2Dt);
offset_dst=mad24(y_idx,ostep,x_idx+ksh);
VSTORE(v2dt_result_c0,dst+offset_dst,2);
if(y_idx+1>=height)
{
return;
}
offset_dst=mad24(y_idx+1,ostep,x_idx+ksh);
VSTORE(v2dt_result_c1,dst+offset_dst,2);
}

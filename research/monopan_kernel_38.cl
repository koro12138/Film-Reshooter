kernel void BoxfilterMain3x3C1(global St*src,int istep,
global Dt*dst,int ostep,
int height,int x_work_size,int y_work_size,
struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
const int elem_counts=6;
const int ksh=1;
const int x_idx=gx*elem_counts;
const int y_idx=gy<<1;
if(gx>=x_work_size||(gy>=y_work_size))
{
return;
}
int offset_src_p,offset_src_c0,offset_src_c1,offset_src_n,offset_dst;
V8InterType v8it_src_p,v8it_src_c0,v8it_src_c1,v8it_src_n;
V8InterType v8it_sum_c0,v8it_sum_c1,v8it_sum_m;
V8Dt v8dt_result_c0,v8dt_result_c1;
if(y_idx>=ksh&&y_idx+1<(height-ksh))
{
offset_src_p=mad24(y_idx-1,istep,x_idx);
offset_src_c0=mad24(y_idx,istep,x_idx);
offset_src_c1=mad24(y_idx+1,istep,x_idx);
offset_src_n=mad24(y_idx+2,istep,x_idx);
v8it_src_p=BOXFILTER_CONVERT(VLOAD(src+offset_src_p,8),V8InterType);
v8it_src_c0=BOXFILTER_CONVERT(VLOAD(src+offset_src_c0,8),V8InterType);
v8it_src_c1=BOXFILTER_CONVERT(VLOAD(src+offset_src_c1,8),V8InterType);
v8it_src_n=BOXFILTER_CONVERT(VLOAD(src+offset_src_n,8),V8InterType);
}
else
{
int y_idx_p,y_idx_c0,y_idx_c1,y_idx_n;
y_idx_p=TOP_BORDER_IDX(y_idx-1);
y_idx_c0=y_idx;
y_idx_c1=BOTTOM_BORDER_IDX(y_idx+1,height);
y_idx_n=BOTTOM_BORDER_IDX(y_idx+2,height);
offset_src_p=mad24(y_idx_p,istep,x_idx);
offset_src_c0=mad24(y_idx_c0,istep,x_idx);
offset_src_c1=mad24(y_idx_c1,istep,x_idx);
offset_src_n=mad24(y_idx_n,istep,x_idx);
#if BORDER_CONSTANT
V8InterType v8it_border_value=(V8InterType)border_value.val[0];
v8it_src_p=(y_idx_p<0)?(V8InterType)v8it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_p,8),V8InterType);
v8it_src_c0=BOXFILTER_CONVERT(VLOAD(src+offset_src_c0,8),V8InterType);
v8it_src_c1=(y_idx_c1<0)?(V8InterType)v8it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_c1,8),V8InterType);
v8it_src_n=(y_idx_n<0)?(V8InterType)v8it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_n,8),V8InterType);
#else
v8it_src_p=BOXFILTER_CONVERT(VLOAD(src+offset_src_p,8),V8InterType);
v8it_src_c0=BOXFILTER_CONVERT(VLOAD(src+offset_src_c0,8),V8InterType);
v8it_src_c1=BOXFILTER_CONVERT(VLOAD(src+offset_src_c1,8),V8InterType);
v8it_src_n=BOXFILTER_CONVERT(VLOAD(src+offset_src_n,8),V8InterType);
#endif
}
v8it_sum_m=v8it_src_c0+v8it_src_c1;
v8it_sum_c0=v8it_sum_m+v8it_src_p;
v8it_sum_c1=v8it_sum_m+v8it_src_n;
v8it_sum_c0=v8it_sum_c0+ROT_R(v8it_sum_c0,8,7)+ROT_R(v8it_sum_c0,8,6);
v8it_sum_c1=v8it_sum_c1+ROT_R(v8it_sum_c1,8,7)+ROT_R(v8it_sum_c1,8,6);
v8dt_result_c0=CONVERT(v8it_sum_c0/(V8InterType)9,V8Dt);
v8dt_result_c1=CONVERT(v8it_sum_c1/(V8InterType)9,V8Dt);
offset_dst=mad24(y_idx,ostep,x_idx+ksh);
VSTORE(v8dt_result_c0.s0123,dst+offset_dst,4);
VSTORE(v8dt_result_c0.s45,dst+offset_dst+4,2);
if(y_idx+1>=height)
{
return;
}
offset_dst=mad24(y_idx+1,ostep,x_idx+ksh);
VSTORE(v8dt_result_c1.s0123,dst+offset_dst,4);
VSTORE(v8dt_result_c1.s45,dst+offset_dst+4,2);
}

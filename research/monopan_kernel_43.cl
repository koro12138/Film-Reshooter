kernel void BoxfilterMain5x5C2(global St*src,int istep,
global Dt*dst,int ostep,
int height,int x_work_size,int y_work_size,
struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
const int elem_counts=4;
const int ksh=2;
const int channel=2;
const int x_idx=gx*elem_counts*channel;
const int y_idx=gy;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int y_idx_p1,y_idx_p0,y_idx_c0,y_idx_c1,y_idx_n0;
int offset_src_p1,offset_src_p0,offset_src_c0,offset_src_c1,offset_src_n0;
int offset_dst;
V16InterType v16it_src_p1,v16it_src_p0,v16it_src_c0,v16it_src_c1,v16it_src_n0;
V16InterType v16it_sum_m,v16it_sum_c0;
V8InterType v8it_sum_c0;
V8Dt v8dt_result_c0;
if(y_idx>=ksh&&y_idx<(height-ksh))
{
offset_src_p1=mad24(y_idx-2,istep,x_idx);
offset_src_p0=mad24(y_idx-1,istep,x_idx);
offset_src_c0=mad24(y_idx,istep,x_idx);
offset_src_c1=mad24(y_idx+1,istep,x_idx);
offset_src_n0=mad24(y_idx+2,istep,x_idx);
v16it_src_p1=BOXFILTER_CONVERT(VLOAD(src+offset_src_p1,16),V16InterType);
v16it_src_p0=BOXFILTER_CONVERT(VLOAD(src+offset_src_p0,16),V16InterType);
v16it_src_c0=BOXFILTER_CONVERT(VLOAD(src+offset_src_c0,16),V16InterType);
v16it_src_c1=BOXFILTER_CONVERT(VLOAD(src+offset_src_c1,16),V16InterType);
v16it_src_n0=BOXFILTER_CONVERT(VLOAD(src+offset_src_n0,16),V16InterType);
}
else
{
y_idx_p1=TOP_BORDER_IDX(y_idx-2);
y_idx_p0=TOP_BORDER_IDX(y_idx-1);
y_idx_c0=y_idx;
y_idx_c1=BOTTOM_BORDER_IDX(y_idx+1,height);
y_idx_n0=BOTTOM_BORDER_IDX(y_idx+2,height);
offset_src_p1=mad24(y_idx_p1,istep,x_idx);
offset_src_p0=mad24(y_idx_p0,istep,x_idx);
offset_src_c0=mad24(y_idx_c0,istep,x_idx);
offset_src_c1=mad24(y_idx_c1,istep,x_idx);
offset_src_n0=mad24(y_idx_n0,istep,x_idx);
#if BORDER_CONSTANT
V2InterType v2it_border_value={(InterType)border_value.val[0],(InterType)border_value.val[1]};
V8InterType v8it_border_value={v2it_border_value,v2it_border_value,v2it_border_value,v2it_border_value};
V16InterType v16it_border_value={v8it_border_value,v8it_border_value};
v16it_src_p1=y_idx_p1<0?v16it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_p1,16),V16InterType);
v16it_src_p0=y_idx_p0<0?v16it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_p0,16),V16InterType);
v16it_src_c0=BOXFILTER_CONVERT(VLOAD(src+offset_src_c0,16),V16InterType);
v16it_src_c1=y_idx_c1<0?v16it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_c1,16),V16InterType);
v16it_src_n0=y_idx_n0<0?v16it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_n0,16),V16InterType);
#else
v16it_src_p1=BOXFILTER_CONVERT(VLOAD(src+offset_src_p1,16),V16InterType);
v16it_src_p0=BOXFILTER_CONVERT(VLOAD(src+offset_src_p0,16),V16InterType);
v16it_src_c0=BOXFILTER_CONVERT(VLOAD(src+offset_src_c0,16),V16InterType);
v16it_src_c1=BOXFILTER_CONVERT(VLOAD(src+offset_src_c1,16),V16InterType);
v16it_src_n0=BOXFILTER_CONVERT(VLOAD(src+offset_src_n0,16),V16InterType);
#endif
}
v16it_sum_m=v16it_src_p0+v16it_src_c0+v16it_src_c1+v16it_src_n0;
v16it_sum_c0=v16it_sum_m+v16it_src_p1;
v8it_sum_c0=v16it_sum_c0.s01234567+v16it_sum_c0.s23456789+v16it_sum_c0.s456789AB+
v16it_sum_c0.s6789ABCD+v16it_sum_c0.s89ABCDEF;
v8dt_result_c0=CONVERT(v8it_sum_c0/(V8InterType)25,V8Dt);
offset_dst=mad24(y_idx,ostep,x_idx+ksh*channel);
VSTORE(v8dt_result_c0,dst+offset_dst,8);
}

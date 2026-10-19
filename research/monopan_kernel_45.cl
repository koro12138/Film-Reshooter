kernel void BoxfilterMain5x5C3(global St*src,int istep,
global Dt*dst,int ostep,
int height,int x_work_size,int y_work_size,
struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
const int elem_counts=1;
const int ksh=2;
const int channel=3;
const int x_idx=gx*elem_counts*channel;
const int y_idx=gy;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int y_idx_p1,y_idx_p0,y_idx_c,y_idx_n0,y_idx_n1;
int offset_src_p1,offset_src_p0,offset_src_c,offset_src_n0,offset_src_n1;
int offset_dst;
V16InterType v16it_src_p1,v16it_src_p0,v16it_src_c,v16it_src_n0,v16it_src_n1;
V16InterType v16it_sum;
V3InterType v3it_result;
V3Dt v3dt_result;
if(y_idx>=ksh&&y_idx<(height-ksh))
{
offset_src_p1=mad24(y_idx-2,istep,x_idx);
offset_src_p0=mad24(y_idx-1,istep,x_idx);
offset_src_c=mad24(y_idx,istep,x_idx);
offset_src_n0=mad24(y_idx+1,istep,x_idx);
offset_src_n1=mad24(y_idx+2,istep,x_idx);
v16it_src_p1=BOXFILTER_CONVERT(VLOAD(src+offset_src_p1,16),V16InterType);
v16it_src_p0=BOXFILTER_CONVERT(VLOAD(src+offset_src_p0,16),V16InterType);
v16it_src_c=BOXFILTER_CONVERT(VLOAD(src+offset_src_c,16),V16InterType);
v16it_src_n0=BOXFILTER_CONVERT(VLOAD(src+offset_src_n0,16),V16InterType);
v16it_src_n1=BOXFILTER_CONVERT(VLOAD(src+offset_src_n1,16),V16InterType);
}
else
{
y_idx_p1=TOP_BORDER_IDX(y_idx-2);
y_idx_p0=TOP_BORDER_IDX(y_idx-1);
y_idx_c=y_idx;
y_idx_n0=BOTTOM_BORDER_IDX(y_idx+1,height);
y_idx_n1=BOTTOM_BORDER_IDX(y_idx+2,height);
offset_src_p1=mad24(y_idx_p1,istep,x_idx);
offset_src_p0=mad24(y_idx_p0,istep,x_idx);
offset_src_c=mad24(y_idx_c,istep,x_idx);
offset_src_n0=mad24(y_idx_n0,istep,x_idx);
offset_src_n1=mad24(y_idx_n1,istep,x_idx);
#if BORDER_CONSTANT
V3InterType v3it_border_value={(InterType)border_value.val[0],(InterType)border_value.val[1],(InterType)border_value.val[2]};
V16InterType v16it_border_value={v3it_border_value,v3it_border_value,v3it_border_value,v3it_border_value,v3it_border_value,v3it_border_value.s0};
v16it_src_p1=y_idx_p1<0?v16it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_p1,16),V16InterType);
v16it_src_p0=y_idx_p0<0?v16it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_p0,16),V16InterType);
v16it_src_c=BOXFILTER_CONVERT(VLOAD(src+offset_src_c,16),V16InterType);
v16it_src_n0=y_idx_n0<0?v16it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_n0,16),V16InterType);
v16it_src_n1=y_idx_n1<0?v16it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_n1,16),V16InterType);
#else
v16it_src_p1=BOXFILTER_CONVERT(VLOAD(src+offset_src_p1,16),V16InterType);
v16it_src_p0=BOXFILTER_CONVERT(VLOAD(src+offset_src_p0,16),V16InterType);
v16it_src_c=BOXFILTER_CONVERT(VLOAD(src+offset_src_c,16),V16InterType);
v16it_src_n0=BOXFILTER_CONVERT(VLOAD(src+offset_src_n0,16),V16InterType);
v16it_src_n1=BOXFILTER_CONVERT(VLOAD(src+offset_src_n1,16),V16InterType);
#endif
}
v16it_sum=v16it_src_p1+v16it_src_p0+v16it_src_c+v16it_src_n0+v16it_src_n1;
v3it_result=v16it_sum.s012+v16it_sum.s345+v16it_sum.s678+v16it_sum.s9ab+v16it_sum.scde;
v3dt_result=CONVERT(v3it_result/(V3InterType)25,V3Dt);
offset_dst=mad24(y_idx,ostep,x_idx+ksh*channel);
VSTORE(v3dt_result,dst+offset_dst,3);
}

kernel void BoxfilterMain3x3C2(global St*src,int istep,
global Dt*dst,int ostep,
int height,int x_work_size,int y_work_size,
struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
const int elem_counts=6;
const int ksh=1;
const int channel=2;
const int x_idx=gx*elem_counts*channel;
const int y_idx=gy<<1;
if(gx>=x_work_size||(gy>=y_work_size))
{
return;
}
int offset_src_p,offset_src_c0,offset_src_c1,offset_src_n,offset_dst;
V16InterType v16it_src_p,v16it_src_c0,v16it_src_c1,v16it_src_n;
V16InterType v16it_sum_c0,v16it_sum_c1,v16it_sum_middle;
V16Dt v16dt_result_c0,v16dt_result_c1;
if(y_idx>=ksh&&y_idx+1<(height-ksh))
{
offset_src_p=mad24(y_idx-1,istep,x_idx);
offset_src_c0=mad24(y_idx,istep,x_idx);
offset_src_c1=mad24(y_idx+1,istep,x_idx);
offset_src_n=mad24(y_idx+2,istep,x_idx);
v16it_src_p=BOXFILTER_CONVERT(VLOAD(src+offset_src_p,16),V16InterType);
v16it_src_c0=BOXFILTER_CONVERT(VLOAD(src+offset_src_c0,16),V16InterType);
v16it_src_c1=BOXFILTER_CONVERT(VLOAD(src+offset_src_c1,16),V16InterType);
v16it_src_n=BOXFILTER_CONVERT(VLOAD(src+offset_src_n,16),V16InterType);
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
V2InterType v2it_border_value={(InterType)border_value.val[0],(InterType)border_value.val[1]};
V16InterType v16it_border_value={v2it_border_value,v2it_border_value,v2it_border_value,v2it_border_value,
v2it_border_value,v2it_border_value,v2it_border_value,v2it_border_value};
v16it_src_p=(y_idx_p<0)?(V16InterType)v16it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_p,16),V16InterType);
v16it_src_c0=BOXFILTER_CONVERT(VLOAD(src+offset_src_c0,16),V16InterType);
v16it_src_c1=(y_idx_c1<0)?(V16InterType)v16it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_c1,16),V16InterType);
v16it_src_n=(y_idx_n<0)?(V16InterType)v16it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_n,16),V16InterType);
#else
v16it_src_p=BOXFILTER_CONVERT(VLOAD(src+offset_src_p,16),V16InterType);
v16it_src_c0=BOXFILTER_CONVERT(VLOAD(src+offset_src_c0,16),V16InterType);
v16it_src_c1=BOXFILTER_CONVERT(VLOAD(src+offset_src_c1,16),V16InterType);
v16it_src_n=BOXFILTER_CONVERT(VLOAD(src+offset_src_n,16),V16InterType);
#endif
}
v16it_sum_middle=v16it_src_c0+v16it_src_c1;
v16it_sum_c0=v16it_sum_middle+v16it_src_p;
v16it_sum_c1=v16it_sum_middle+v16it_src_n;
v16it_sum_c0=v16it_sum_c0+ROT_R(v16it_sum_c0,16,14)+ROT_R(v16it_sum_c0,16,12);
v16it_sum_c1=v16it_sum_c1+ROT_R(v16it_sum_c1,16,14)+ROT_R(v16it_sum_c1,16,12);
v16dt_result_c0=CONVERT(v16it_sum_c0/(V16InterType)9,V16Dt);
v16dt_result_c1=CONVERT(v16it_sum_c1/(V16InterType)9,V16Dt);
offset_dst=mad24(y_idx,ostep,x_idx+ksh*channel);
VSTORE(v16dt_result_c0.s01234567,dst+offset_dst,8);
VSTORE(v16dt_result_c0.s89AB,dst+offset_dst+8,4);
if(y_idx+1>=height)
{
return;
}
offset_dst=mad24(y_idx+1,ostep,x_idx+ksh*channel);
VSTORE(v16dt_result_c1.s01234567,dst+offset_dst,8);
VSTORE(v16dt_result_c1.s89AB,dst+offset_dst+8,4);
}

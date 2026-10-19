kernel void BoxfilterMain3x3C3(global St*src,int istep,
global Dt*dst,int ostep,
int height,int x_work_size,int y_work_size,
struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
const int elem_counts=6;
const int ksh=1;
const int channel=3;
const int x_idx=gx*elem_counts*channel;
const int y_idx=gy;
if(gx>=x_work_size||(gy>=y_work_size))
{
return;
}
int y_idx_p,y_idx_c,y_idx_n;
int offset_src_p,offset_src_c,offset_src_n,offset_dst;
V16InterType v16it_src_p,v16it_src_c,v16it_src_n,v16it_sum;
V8InterType v8it_src_p,v8it_src_c,v8it_src_n,v8it_sum;
V8InterType v8it_sum_l,v8it_sum_c,v8it_sum_r;
V16InterType v16it_result;
V2InterType v2it_result;
V16Dt v16dt_result;
V2Dt v2dt_result;
if(y_idx>=ksh&&y_idx<(height-ksh))
{
offset_src_p=mad24(y_idx-1,istep,x_idx);
offset_src_c=mad24(y_idx,istep,x_idx);
offset_src_n=mad24(y_idx+1,istep,x_idx);
v16it_src_p=BOXFILTER_CONVERT(VLOAD(src+offset_src_p,16),V16InterType);
v16it_src_c=BOXFILTER_CONVERT(VLOAD(src+offset_src_c,16),V16InterType);
v16it_src_n=BOXFILTER_CONVERT(VLOAD(src+offset_src_n,16),V16InterType);
v8it_src_p=BOXFILTER_CONVERT(VLOAD(src+offset_src_p+16,8),V8InterType);
v8it_src_c=BOXFILTER_CONVERT(VLOAD(src+offset_src_c+16,8),V8InterType);
v8it_src_n=BOXFILTER_CONVERT(VLOAD(src+offset_src_n+16,8),V8InterType);
}
else
{
y_idx_p=TOP_BORDER_IDX(y_idx-1);
y_idx_c=y_idx;
y_idx_n=BOTTOM_BORDER_IDX(y_idx+1,height);
offset_src_p=mad24(y_idx_p,istep,x_idx);
offset_src_c=mad24(y_idx_c,istep,x_idx);
offset_src_n=mad24(y_idx_n,istep,x_idx);
#if BORDER_CONSTANT
V3InterType v3it_border_value={(InterType)border_value.val[0],(InterType)border_value.val[1],(InterType)border_value.val[2]};
V16InterType v16it_border_value={v3it_border_value,v3it_border_value,v3it_border_value,v3it_border_value,v3it_border_value,v3it_border_value.s0};
V8InterType v8it_border_value={v3it_border_value.s12,v3it_border_value,v3it_border_value};
v16it_src_p=(y_idx_p<0)?v16it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_p,16),V16InterType);
v16it_src_c=BOXFILTER_CONVERT(VLOAD(src+offset_src_c,16),V16InterType);
v16it_src_n=(y_idx_n<0)?v16it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_n,16),V16InterType);
v8it_src_p=(y_idx_p<0)?v8it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_p+16,8),V8InterType);
v8it_src_c=BOXFILTER_CONVERT(VLOAD(src+offset_src_c+16,8),V8InterType);
v8it_src_n=(y_idx_n<0)?v8it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_n+16,8),V8InterType);
#else
v16it_src_p=BOXFILTER_CONVERT(VLOAD(src+offset_src_p,16),V16InterType);
v16it_src_c=BOXFILTER_CONVERT(VLOAD(src+offset_src_c,16),V16InterType);
v16it_src_n=BOXFILTER_CONVERT(VLOAD(src+offset_src_n,16),V16InterType);
v8it_src_p=BOXFILTER_CONVERT(VLOAD(src+offset_src_p+16,8),V8InterType);
v8it_src_c=BOXFILTER_CONVERT(VLOAD(src+offset_src_c+16,8),V8InterType);
v8it_src_n=BOXFILTER_CONVERT(VLOAD(src+offset_src_n+16,8),V8InterType);
#endif
}
v16it_sum=v16it_src_p+v16it_src_c+v16it_src_n;
v8it_sum=v8it_src_p+v8it_src_c+v8it_src_n;
v8it_sum_l=(V8InterType)(v16it_sum.s0369,v16it_sum.sCF,v8it_sum.s25);
v8it_sum_c=(V8InterType)(v16it_sum.s147A,v16it_sum.sD,v8it_sum.s036);
v8it_sum_r=(V8InterType)(v16it_sum.s258B,v16it_sum.sE,v8it_sum.s147);
v8it_sum_l=v8it_sum_l+ROT_R(v8it_sum_l,8,7)+ROT_R(v8it_sum_l,8,6);
v8it_sum_c=v8it_sum_c+ROT_R(v8it_sum_c,8,7)+ROT_R(v8it_sum_c,8,6);
v8it_sum_r=v8it_sum_r+ROT_R(v8it_sum_r,8,7)+ROT_R(v8it_sum_r,8,6);
v16it_result=(V16InterType)(v8it_sum_l.s0,v8it_sum_c.s0,v8it_sum_r.s0,v8it_sum_l.s1,
v8it_sum_c.s1,v8it_sum_r.s1,v8it_sum_l.s2,v8it_sum_c.s2,
v8it_sum_r.s2,v8it_sum_l.s3,v8it_sum_c.s3,v8it_sum_r.s3,
v8it_sum_l.s4,v8it_sum_c.s4,v8it_sum_r.s4,v8it_sum_l.s5);
v2it_result=(V2InterType)(v8it_sum_c.s5,v8it_sum_r.s5);
v16dt_result=CONVERT(v16it_result/(V16InterType)9,V16Dt);
v2dt_result=CONVERT(v2it_result/(V2InterType)9,V2Dt);
offset_dst=mad24(y_idx,ostep,x_idx+ksh*channel);
VSTORE(v16dt_result,dst+offset_dst,16);
VSTORE(v2dt_result,dst+offset_dst+16,2);
}

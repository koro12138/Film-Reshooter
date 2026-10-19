kernel void BoxfilterMain5x5C3(global St*src,int istep,
global Dt*dst,int ostep,
int height,int x_work_size,int y_work_size,
struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
const int elem_counts=4;
const int ksh=2;
const int channel=3;
const int x_idx=gx*elem_counts*channel;
const int y_idx=gy<<1;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int y_idx_p1,y_idx_p0,y_idx_c0,y_idx_c1,y_idx_n0,y_idx_n1;
int offset_src_p1,offset_src_p0,offset_src_c0,offset_src_c1,offset_src_n0,offset_src_n1;
int offset_dst;
V16InterType v16it_src_p1,v16it_src_p0,v16it_src_c0,v16it_src_c1,v16it_src_n0,v16it_src_n1;
V16InterType v16it_sum_m,v16it_sum_c0,v16it_sum_c1;
V16InterType v16it_sum_l1,v16it_sum_l0,v16it_sum_c,v16it_sum_r0,v16it_sum_r1;
V16InterType v16it_result_c0,v16it_result_c1;
V8InterType v8it_src_p1,v8it_src_p0,v8it_src_c0,v8it_src_c1,v8it_src_n0,v8it_src_n1;
V8InterType v8it_sum_m,v8it_sum_c0,v8it_sum_c1;
V8Dt v8dt_result_c0,v8dt_result_c1;
V4Dt v4dt_result_c0,v4dt_result_c1;
if(y_idx>=ksh&&y_idx+1<(height-ksh))
{
offset_src_p1=mad24(y_idx-2,istep,x_idx);
offset_src_p0=mad24(y_idx-1,istep,x_idx);
offset_src_c0=mad24(y_idx,istep,x_idx);
offset_src_c1=mad24(y_idx+1,istep,x_idx);
offset_src_n0=mad24(y_idx+2,istep,x_idx);
offset_src_n1=mad24(y_idx+3,istep,x_idx);
v16it_src_p1=BOXFILTER_CONVERT(VLOAD(src+offset_src_p1,16),V16InterType);
v8it_src_p1=BOXFILTER_CONVERT(VLOAD(src+offset_src_p1+16,8),V8InterType);
v16it_src_p0=BOXFILTER_CONVERT(VLOAD(src+offset_src_p0,16),V16InterType);
v8it_src_p0=BOXFILTER_CONVERT(VLOAD(src+offset_src_p0+16,8),V8InterType);
v16it_src_c0=BOXFILTER_CONVERT(VLOAD(src+offset_src_c0,16),V16InterType);
v8it_src_c0=BOXFILTER_CONVERT(VLOAD(src+offset_src_c0+16,8),V8InterType);
v16it_src_c1=BOXFILTER_CONVERT(VLOAD(src+offset_src_c1,16),V16InterType);
v8it_src_c1=BOXFILTER_CONVERT(VLOAD(src+offset_src_c1+16,8),V8InterType);
v16it_src_n0=BOXFILTER_CONVERT(VLOAD(src+offset_src_n0,16),V16InterType);
v8it_src_n0=BOXFILTER_CONVERT(VLOAD(src+offset_src_n0+16,8),V8InterType);
v16it_src_n1=BOXFILTER_CONVERT(VLOAD(src+offset_src_n1,16),V16InterType);
v8it_src_n1=BOXFILTER_CONVERT(VLOAD(src+offset_src_n1+16,8),V8InterType);
}
else
{
y_idx_p1=TOP_BORDER_IDX(y_idx-2);
y_idx_p0=TOP_BORDER_IDX(y_idx-1);
y_idx_c0=y_idx;
y_idx_c1=BOTTOM_BORDER_IDX(y_idx+1,height);
y_idx_n0=BOTTOM_BORDER_IDX(y_idx+2,height);
y_idx_n1=BOTTOM_BORDER_IDX(y_idx+3,height);
offset_src_p1=mad24(y_idx_p1,istep,x_idx);
offset_src_p0=mad24(y_idx_p0,istep,x_idx);
offset_src_c0=mad24(y_idx_c0,istep,x_idx);
offset_src_c1=mad24(y_idx_c1,istep,x_idx);
offset_src_n0=mad24(y_idx_n0,istep,x_idx);
offset_src_n1=mad24(y_idx_n1,istep,x_idx);
#if BORDER_CONSTANT
V3InterType v3it_border_value={(InterType)border_value.val[0],(InterType)border_value.val[1],(InterType)border_value.val[2]};
V16InterType v16it_border_value={v3it_border_value,v3it_border_value,v3it_border_value,v3it_border_value,v3it_border_value,v3it_border_value.s0};
V8InterType v8it_border_value={v3it_border_value.s12,v3it_border_value,v3it_border_value};
v16it_src_p1=y_idx_p1<0?v16it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_p1,16),V16InterType);
v8it_src_p1=y_idx_p1<0?v8it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_p1+16,8),V8InterType);
v16it_src_p0=y_idx_p0<0?v16it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_p0,16),V16InterType);
v8it_src_p0=y_idx_p0<0?v8it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_p0+16,8),V8InterType);
v16it_src_c0=BOXFILTER_CONVERT(VLOAD(src+offset_src_c0,16),V16InterType);
v8it_src_c0=BOXFILTER_CONVERT(VLOAD(src+offset_src_c0+16,8),V8InterType);
v16it_src_c1=y_idx_c1<0?v16it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_c1,16),V16InterType);
v8it_src_c1=y_idx_c1<0?v8it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_c1+16,8),V8InterType);
v16it_src_n0=y_idx_n0<0?v16it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_n0,16),V16InterType);
v8it_src_n0=y_idx_n0<0?v8it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_n0+16,8),V8InterType);
v16it_src_n1=y_idx_n1<0?v16it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_n1,16),V16InterType);
v8it_src_n1=y_idx_n1<0?v8it_border_value:BOXFILTER_CONVERT(VLOAD(src+offset_src_n1+16,8),V8InterType);
#else
v16it_src_p1=BOXFILTER_CONVERT(VLOAD(src+offset_src_p1,16),V16InterType);
v8it_src_p1=BOXFILTER_CONVERT(VLOAD(src+offset_src_p1+16,8),V8InterType);
v16it_src_p0=BOXFILTER_CONVERT(VLOAD(src+offset_src_p0,16),V16InterType);
v8it_src_p0=BOXFILTER_CONVERT(VLOAD(src+offset_src_p0+16,8),V8InterType);
v16it_src_c0=BOXFILTER_CONVERT(VLOAD(src+offset_src_c0,16),V16InterType);
v8it_src_c0=BOXFILTER_CONVERT(VLOAD(src+offset_src_c0+16,8),V8InterType);
v16it_src_c1=BOXFILTER_CONVERT(VLOAD(src+offset_src_c1,16),V16InterType);
v8it_src_c1=BOXFILTER_CONVERT(VLOAD(src+offset_src_c1+16,8),V8InterType);
v16it_src_n0=BOXFILTER_CONVERT(VLOAD(src+offset_src_n0,16),V16InterType);
v8it_src_n0=BOXFILTER_CONVERT(VLOAD(src+offset_src_n0+16,8),V8InterType);
v16it_src_n1=BOXFILTER_CONVERT(VLOAD(src+offset_src_n1,16),V16InterType);
v8it_src_n1=BOXFILTER_CONVERT(VLOAD(src+offset_src_n1+16,8),V8InterType);
#endif
}
v16it_sum_m=v16it_src_p0+v16it_src_c0+v16it_src_c1+v16it_src_n0;
v8it_sum_m=v8it_src_p0+v8it_src_c0+v8it_src_c1+v8it_src_n0;
v16it_sum_c0=v16it_sum_m+v16it_src_p1;
v8it_sum_c0=v8it_sum_m+v8it_src_p1;
v16it_sum_c1=v16it_sum_m+v16it_src_n1;
v8it_sum_c1=v8it_sum_m+v8it_src_n1;
v16it_sum_l1=v16it_sum_c0;
v16it_sum_l0=(V16InterType){v16it_sum_c0.s3456789A,v16it_sum_c0.sBCDE,v16it_sum_c0.sF,v8it_sum_c0.s012};
v16it_sum_c=(V16InterType){v16it_sum_c0.s6789ABCD,v16it_sum_c0.sEF,v8it_sum_c0.s01,v8it_sum_c0.s2345};
v16it_sum_r0=(V16InterType){v16it_sum_c0.s9ABC,v16it_sum_c0.sDEF,v8it_sum_c0.s01234567,v8it_sum_c0.s0};
v16it_sum_r1=(V16InterType){v16it_sum_c0.sCDEF,v8it_sum_c0.s01234567,v8it_sum_c0.s0123};
v16it_result_c0=v16it_sum_l1+v16it_sum_l0+v16it_sum_c+v16it_sum_r0+v16it_sum_r1;
v16it_sum_l1=v16it_sum_c1;
v16it_sum_l0=(V16InterType){v16it_sum_c1.s3456789A,v16it_sum_c1.sBCDE,v16it_sum_c1.sF,v8it_sum_c1.s012};
v16it_sum_c=(V16InterType){v16it_sum_c1.s6789ABCD,v16it_sum_c1.sEF,v8it_sum_c1.s01,v8it_sum_c1.s2345};
v16it_sum_r0=(V16InterType){v16it_sum_c1.s9ABC,v16it_sum_c1.sDEF,v8it_sum_c1.s01234567,v8it_sum_c1.s0};
v16it_sum_r1=(V16InterType){v16it_sum_c1.sCDEF,v8it_sum_c1.s01234567,v8it_sum_c1.s0123};
v16it_result_c1=v16it_sum_l1+v16it_sum_l0+v16it_sum_c+v16it_sum_r0+v16it_sum_r1;
v16it_result_c0=v16it_result_c0/(V16InterType)25;
v16it_result_c1=v16it_result_c1/(V16InterType)25;
v8dt_result_c0=CONVERT(v16it_result_c0.s01234567,V8Dt);
v4dt_result_c0=CONVERT(v16it_result_c0.s89AB,V4Dt);
v8dt_result_c1=CONVERT(v16it_result_c1.s01234567,V8Dt);
v4dt_result_c1=CONVERT(v16it_result_c1.s89AB,V4Dt);
offset_dst=mad24(y_idx,ostep,x_idx+ksh*channel);
VSTORE(v8dt_result_c0,dst+offset_dst,8);
VSTORE(v4dt_result_c0,dst+offset_dst+8,4);
if(y_idx+1>=height)
{
return;
}
offset_dst=mad24(y_idx+1,ostep,x_idx+ksh*channel);
VSTORE(v8dt_result_c1,dst+offset_dst,8);
VSTORE(v4dt_result_c1,dst+offset_dst+8,4);
}

kernel void LaplacianMain5x5C3(global St*src,int istep,
global Dt*dst,int ostep,
int height,int y_work_size,int x_work_size,
struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
const int elem_counts=1;
const int ksh=2;
const int channel=3;
const int x_idx=gx*elem_counts*channel;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int y_idx_p1,y_idx_p0,y_idx_c,y_idx_n0,y_idx_n1;
int offset_src_p1,offset_src_p0,offset_src_c,offset_src_n0,offset_src_n1;
int offset_dst;
V16St v16it_src_p1,v16it_src_p0,v16it_src_n0,v16it_src_n1;
V16InterType v16it_sum_pn1_l,v16it_sum_pn0_l,v16it_src_c;
V3InterType v3it_result;
V3Dt v3dt_result;
if(gy>=ksh&&gy<(height-ksh))
{
offset_src_p1=mad24(gy-2,istep,x_idx);
offset_src_p0=mad24(gy-1,istep,x_idx);
offset_src_c=mad24(gy,istep,x_idx);
offset_src_n0=mad24(gy+1,istep,x_idx);
offset_src_n1=mad24(gy+2,istep,x_idx);
v16it_src_p1=VLOAD(src+offset_src_p1,16);
v16it_src_n1=VLOAD(src+offset_src_n1,16);
v16it_src_p0=VLOAD(src+offset_src_p0,16);
v16it_src_n0=VLOAD(src+offset_src_n0,16);
v16it_src_c=LAPLACIAN_CONVERT(VLOAD(src+offset_src_c,16),V16InterType);
}
else
{
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
V3St v3it_border_value={(St)border_value.val[0],(St)border_value.val[1],(St)border_value.val[2]};
V16St v16it_border_value={v3it_border_value,v3it_border_value,v3it_border_value,v3it_border_value,v3it_border_value,v3it_border_value.s0};
v16it_src_p1=y_idx_p1<0?v16it_border_value:VLOAD(src+offset_src_p1,16);
v16it_src_n1=y_idx_n1<0?v16it_border_value:VLOAD(src+offset_src_n1,16);
v16it_src_p0=y_idx_p0<0?v16it_border_value:VLOAD(src+offset_src_p0,16);
v16it_src_n0=y_idx_n0<0?v16it_border_value:VLOAD(src+offset_src_n0,16);
#else
v16it_src_p1=VLOAD(src+offset_src_p1,16);
v16it_src_n1=VLOAD(src+offset_src_n1,16);
v16it_src_p0=VLOAD(src+offset_src_p0,16);
v16it_src_n0=VLOAD(src+offset_src_n0,16);
#endif
v16it_src_c=LAPLACIAN_CONVERT(VLOAD(src+offset_src_c,16),V16InterType);
}
v16it_sum_pn1_l=LAPLACIAN_CONVERT(v16it_src_p1,V16InterType)+LAPLACIAN_CONVERT(v16it_src_n1,V16InterType);
v16it_sum_pn0_l=LAPLACIAN_CONVERT(v16it_src_p0,V16InterType)+LAPLACIAN_CONVERT(v16it_src_n0,V16InterType);
v3it_result=(v16it_sum_pn1_l.s012+v16it_sum_pn1_l.sCDE)*(V3InterType)2+
(v16it_sum_pn1_l.s345+v16it_sum_pn1_l.s9AB)*(V3InterType)4+v16it_sum_pn1_l.s678*(V3InterType)4+
(v16it_sum_pn0_l.s012+v16it_sum_pn0_l.sCDE)*(V3InterType)4+v16it_sum_pn0_l.s678*(V3InterType)-8+
(v16it_src_c.s012+v16it_src_c.sCDE)*(V3InterType)4+(v16it_src_c.s345+v16it_src_c.s9AB)*(V3InterType)-8+
v16it_src_c.s678*(V3InterType)-24;
#if IS_FLOAT(InterType)
v3dt_result=CONVERT(v3it_result,V3Dt);
#else
v3dt_result=CONVERT_SAT(v3it_result,V3Dt);
#endif
offset_dst=mad24(gy,ostep,x_idx+ksh*channel);
VSTORE(v3dt_result,dst+offset_dst,3);
}

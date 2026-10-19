kernel void LaplacianMain5x5C3(global St*src,int istep,
global Dt*dst,int ostep,
int height,int y_work_size,int x_work_size,
struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
const int elem_counts=4;
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
V16InterType v16it_src_p1,v16it_src_p0,v16it_src_c,v16it_src_n0,v16it_src_n1,v16it_sum;
V8InterType v8it_src_p1,v8it_src_p0,v8it_src_c,v8it_src_n0,v8it_src_n1;
V16InterType v16it_sum_pn1_l,v16it_sum_pn0_l;
V8InterType v8it_sum_pn1_r,v8it_sum_pn0_r;
V16InterType v16it_sum_pn1,v16it_sum_pn0,v16it_sum_c,v16it_result;
V16Dt v16dt_result;
if(gy>=ksh&&gy<(height-ksh))
{
offset_src_p1=mad24(gy-2,istep,x_idx);
offset_src_p0=mad24(gy-1,istep,x_idx);
offset_src_c=mad24(gy,istep,x_idx);
offset_src_n0=mad24(gy+1,istep,x_idx);
offset_src_n1=mad24(gy+2,istep,x_idx);
v16it_src_p1=LAPLACIAN_CONVERT(VLOAD(src+offset_src_p1,16),V16InterType);
v8it_src_p1=LAPLACIAN_CONVERT(VLOAD(src+offset_src_p1+16,8),V8InterType);
v16it_src_n1=LAPLACIAN_CONVERT(VLOAD(src+offset_src_n1,16),V16InterType);
v8it_src_n1=LAPLACIAN_CONVERT(VLOAD(src+offset_src_n1+16,8),V8InterType);
v16it_sum_pn1_l=v16it_src_p1+v16it_src_n1;
v8it_sum_pn1_r=v8it_src_p1+v8it_src_n1;
v16it_src_p0=LAPLACIAN_CONVERT(VLOAD(src+offset_src_p0,16),V16InterType);
v8it_src_p0=LAPLACIAN_CONVERT(VLOAD(src+offset_src_p0+16,8),V8InterType);
v16it_src_n0=LAPLACIAN_CONVERT(VLOAD(src+offset_src_n0,16),V16InterType);
v8it_src_n0=LAPLACIAN_CONVERT(VLOAD(src+offset_src_n0+16,8),V8InterType);
v16it_sum_pn0_l=v16it_src_p0+v16it_src_n0;
v8it_sum_pn0_r=v8it_src_p0+v8it_src_n0;
v16it_src_c=LAPLACIAN_CONVERT(VLOAD(src+offset_src_c,16),V16InterType);
v8it_src_c=LAPLACIAN_CONVERT(VLOAD(src+offset_src_c+16,8),V8InterType);
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
V3InterType v3it_border_value={(InterType)border_value.val[0],(InterType)border_value.val[1],(InterType)border_value.val[2]};
V16InterType v16it_border_value={v3it_border_value,v3it_border_value,v3it_border_value,v3it_border_value,v3it_border_value,v3it_border_value.s0};
V8InterType v8it_border_value={v3it_border_value.s12,v3it_border_value,v3it_border_value};
v16it_src_p1=y_idx_p1<0?v16it_border_value:LAPLACIAN_CONVERT(VLOAD(src+offset_src_p1,16),V16InterType);
v8it_src_p1=y_idx_p1<0?v8it_border_value:LAPLACIAN_CONVERT(VLOAD(src+offset_src_p1+16,8),V8InterType);
v16it_src_n1=y_idx_n1<0?v16it_border_value:LAPLACIAN_CONVERT(VLOAD(src+offset_src_n1,16),V16InterType);
v8it_src_n1=y_idx_n1<0?v8it_border_value:LAPLACIAN_CONVERT(VLOAD(src+offset_src_n1+16,8),V8InterType);
v16it_sum_pn1_l=v16it_src_p1+v16it_src_n1;
v8it_sum_pn1_r=v8it_src_p1+v8it_src_n1;
v16it_src_p0=y_idx_p0<0?v16it_border_value:LAPLACIAN_CONVERT(VLOAD(src+offset_src_p0,16),V16InterType);
v8it_src_p0=y_idx_p0<0?v8it_border_value:LAPLACIAN_CONVERT(VLOAD(src+offset_src_p0+16,8),V8InterType);
v16it_src_n0=y_idx_n0<0?v16it_border_value:LAPLACIAN_CONVERT(VLOAD(src+offset_src_n0,16),V16InterType);
v8it_src_n0=y_idx_n0<0?v8it_border_value:LAPLACIAN_CONVERT(VLOAD(src+offset_src_n0+16,8),V8InterType);
v16it_sum_pn0_l=v16it_src_p0+v16it_src_n0;
v8it_sum_pn0_r=v8it_src_p0+v8it_src_n0;
v16it_src_c=LAPLACIAN_CONVERT(VLOAD(src+offset_src_c,16),V16InterType);
v8it_src_c=LAPLACIAN_CONVERT(VLOAD(src+offset_src_c+16,8),V8InterType);
#else
v16it_src_p1=LAPLACIAN_CONVERT(VLOAD(src+offset_src_p1,16),V16InterType);
v8it_src_p1=LAPLACIAN_CONVERT(VLOAD(src+offset_src_p1+16,8),V8InterType);
v16it_src_n1=LAPLACIAN_CONVERT(VLOAD(src+offset_src_n1,16),V16InterType);
v8it_src_n1=LAPLACIAN_CONVERT(VLOAD(src+offset_src_n1+16,8),V8InterType);
v16it_sum_pn1_l=v16it_src_p1+v16it_src_n1;
v8it_sum_pn1_r=v8it_src_p1+v8it_src_n1;
v16it_src_p0=LAPLACIAN_CONVERT(VLOAD(src+offset_src_p0,16),V16InterType);
v8it_src_p0=LAPLACIAN_CONVERT(VLOAD(src+offset_src_p0+16,8),V8InterType);
v16it_src_n0=LAPLACIAN_CONVERT(VLOAD(src+offset_src_n0,16),V16InterType);
v8it_src_n0=LAPLACIAN_CONVERT(VLOAD(src+offset_src_n0+16,8),V8InterType);
v16it_sum_pn0_l=v16it_src_p0+v16it_src_n0;
v8it_sum_pn0_r=v8it_src_p0+v8it_src_n0;
v16it_src_c=LAPLACIAN_CONVERT(VLOAD(src+offset_src_c,16),V16InterType);
v8it_src_c=LAPLACIAN_CONVERT(VLOAD(src+offset_src_c+16,8),V8InterType);
#endif
}
v16it_sum_pn1=((v16it_sum_pn1_l+(V16InterType)(v16it_sum_pn1_l.sCDEF,v8it_sum_pn1_r,v16it_sum_pn1_l.s0123))*(V16InterType)2)+
(((V16InterType)(v16it_sum_pn1_l.s3456789A,v16it_sum_pn1_l.sBCDE,v16it_sum_pn1_l.sF,v8it_sum_pn1_r.s012)+
(V16InterType)(v16it_sum_pn1_l.s9ABC,v16it_sum_pn1_l.sDEF,v8it_sum_pn1_r,v16it_sum_pn1_l.s0))*(V16InterType)4)+
((V16InterType)(v16it_sum_pn1_l.s6789ABCD,v16it_sum_pn1_l.sEF,v8it_sum_pn1_r.s0123,v8it_sum_pn1_r.s45)*(V16InterType)4);
v16it_sum_pn0=((v16it_sum_pn0_l+(V16InterType)(v16it_sum_pn0_l.sCDEF,v8it_sum_pn0_r,v16it_sum_pn0_l.s0123))*(V16InterType)4)+
((V16InterType)(v16it_sum_pn0_l.s6789ABCD,v16it_sum_pn0_l.sEF,v8it_sum_pn0_r.s0123,v8it_sum_pn0_r.s45)*(V16InterType)-8);
v16it_sum_c=((v16it_src_c+(V16InterType)(v16it_src_c.sCDEF,v8it_src_c,v16it_src_c.s0123))*(V16InterType)4)+
(((V16InterType)(v16it_src_c.s3456789A,v16it_src_c.sBCDE,v16it_src_c.sF,v8it_src_c.s012)+
(V16InterType)(v16it_src_c.s9ABC,v16it_src_c.sDEF,v8it_src_c,v16it_src_c.s0))*(V16InterType)-8)+
((V16InterType)(v16it_src_c.s6789ABCD,v16it_src_c.sEF,v8it_src_c.s0123,v8it_src_c.s45)*(V16InterType)-24);
v16it_result=v16it_sum_pn1+v16it_sum_pn0+v16it_sum_c;
#if IS_FLOAT(InterType)
v16dt_result=CONVERT(v16it_result,V16Dt);
#else
v16dt_result=CONVERT_SAT(v16it_result,V16Dt);
#endif
offset_dst=mad24(gy,ostep,x_idx+ksh*channel);
VSTORE(v16dt_result.s01234567,dst+offset_dst,8);
VSTORE(v16dt_result.s89AB,dst+offset_dst+8,4);
}

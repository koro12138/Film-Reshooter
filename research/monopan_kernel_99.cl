kernel void LaplacianMain5x5C2(global St*src,int istep,
global Dt*dst,int ostep,
int height,int y_work_size,int x_work_size,
struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
const int elem_counts=4;
const int ksh=2;
const int channel=2;
const int x_idx=gx*elem_counts*channel;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int y_idx_p1,y_idx_p0,y_idx_c,y_idx_n0,y_idx_n1;
int offset_src_p1,offset_src_p0,offset_src_c,offset_src_n0,offset_src_n1;
int offset_dst;
V16St v16it_src_p1,v16it_src_p0,v16it_src_n0,v16it_src_n1;
V16InterType v16it_sum_pn1,v16it_sum_pn0,v16it_src_c;
V8InterType v8it_sum_pn1,v8it_sum_pn0,v8it_sum_c;
V8InterType v8it_result;
V8Dt v8dt_result;
if(gy>=ksh&&gy<(height-ksh))
{
offset_src_p1=mad24(gy-2,istep,x_idx);
offset_src_p0=mad24(gy-1,istep,x_idx);
offset_src_c=mad24(gy,istep,x_idx);
offset_src_n0=mad24(gy+1,istep,x_idx);
offset_src_n1=mad24(gy+2,istep,x_idx);
v16it_src_p1=VLOAD(src+offset_src_p1,16);
v16it_src_p0=VLOAD(src+offset_src_p0,16);
v16it_src_n0=VLOAD(src+offset_src_n0,16);
v16it_src_n1=VLOAD(src+offset_src_n1,16);
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
V2St v2it_border_value={(St)border_value.val[0],(St)border_value.val[1]};
V8St v8it_border_value={v2it_border_value,v2it_border_value,v2it_border_value,v2it_border_value};
V16St v16it_border_value={v8it_border_value,v8it_border_value};
v16it_src_p1=y_idx_p1<0?v16it_border_value:VLOAD(src+offset_src_p1,16);
v16it_src_p0=y_idx_p0<0?v16it_border_value:VLOAD(src+offset_src_p0,16);
v16it_src_n0=y_idx_n0<0?v16it_border_value:VLOAD(src+offset_src_n0,16);
v16it_src_n1=y_idx_n1<0?v16it_border_value:VLOAD(src+offset_src_n1,16);
#else
v16it_src_p1=VLOAD(src+offset_src_p1,16);
v16it_src_p0=VLOAD(src+offset_src_p0,16);
v16it_src_n0=VLOAD(src+offset_src_n0,16);
v16it_src_n1=VLOAD(src+offset_src_n1,16);
#endif
v16it_src_c=LAPLACIAN_CONVERT(VLOAD(src+offset_src_c,16),V16InterType);
}
v16it_sum_pn1=LAPLACIAN_CONVERT(v16it_src_p1,V16InterType)+LAPLACIAN_CONVERT(v16it_src_n1,V16InterType);
v16it_sum_pn0=LAPLACIAN_CONVERT(v16it_src_p0,V16InterType)+LAPLACIAN_CONVERT(v16it_src_n0,V16InterType);
v8it_sum_pn1=((V8InterType)(v16it_sum_pn1.s01234567+v16it_sum_pn1.s89ABCDEF)*(V8InterType)2)+
((V8InterType)(v16it_sum_pn1.s23456789+v16it_sum_pn1.s6789ABCD)*(V8InterType)4)+
((V8InterType)(v16it_sum_pn1.s456789AB)*(V8InterType)4);
v8it_sum_pn0=((V8InterType)(v16it_sum_pn0.s01234567+v16it_sum_pn0.s89ABCDEF)*(V8InterType)4)+
((V8InterType)(v16it_sum_pn0.s456789AB)*(V8InterType)-8);
v8it_sum_c=((V8InterType)(v16it_src_c.s01234567+v16it_src_c.s89ABCDEF)*(V8InterType)4)+
((V8InterType)(v16it_src_c.s23456789+v16it_src_c.s6789ABCD)*(V8InterType)-8)+
((V8InterType)(v16it_src_c.s456789AB)*(V8InterType)-24);
v8it_result=v8it_sum_pn1+v8it_sum_pn0+v8it_sum_c;
#if IS_FLOAT(InterType)
v8dt_result=CONVERT(v8it_result,V8Dt);
#else
v8dt_result=CONVERT_SAT(v8it_result,V8Dt);
#endif
offset_dst=mad24(gy,ostep,x_idx+ksh*channel);
VSTORE(v8dt_result,dst+offset_dst,8);
}

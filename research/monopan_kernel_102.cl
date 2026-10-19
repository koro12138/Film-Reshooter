kernel void LaplacianMain7x7C1(global St*src,int istep,
global Dt*dst,int ostep,
int height,int y_work_size,int x_work_size,
struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
const int elem_counts=2;
const int ksh=3;
const int x_idx=gx*elem_counts;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int y_idx_p2,y_idx_p1,y_idx_p0,y_idx_c,y_idx_n0,y_idx_n1,y_idx_n2;
int offset_src_p2,offset_src_p1,offset_src_p0,offset_src_c,offset_src_n0,offset_src_n1,offset_src_n2;
int offset_dst;
V8InterType v8it_src_p2,v8it_src_p1,v8it_src_p0,v8it_src_c,v8it_src_n0,v8it_src_n1,v8it_src_n2;
V8InterType v8it_sum_pn2,v8it_sum_pn1,v8it_sum_pn0;
V2InterType v2it_sum_pn2,v2it_sum_pn1,v2it_sum_pn0,v2it_sum_c;
V2InterType v2it_result;
V2Dt v2dt_result;
if(gy>=ksh&&gy<(height-ksh))
{
offset_src_p2=mad24(gy-3,istep,x_idx);
offset_src_p1=mad24(gy-2,istep,x_idx);
offset_src_p0=mad24(gy-1,istep,x_idx);
offset_src_c=mad24(gy,istep,x_idx);
offset_src_n0=mad24(gy+1,istep,x_idx);
offset_src_n1=mad24(gy+2,istep,x_idx);
offset_src_n2=mad24(gy+3,istep,x_idx);
v8it_src_p2=LAPLACIAN_CONVERT(VLOAD(src+offset_src_p2,8),V8InterType);
v8it_src_p1=LAPLACIAN_CONVERT(VLOAD(src+offset_src_p1,8),V8InterType);
v8it_src_p0=LAPLACIAN_CONVERT(VLOAD(src+offset_src_p0,8),V8InterType);
v8it_src_c=LAPLACIAN_CONVERT(VLOAD(src+offset_src_c,8),V8InterType);
v8it_src_n0=LAPLACIAN_CONVERT(VLOAD(src+offset_src_n0,8),V8InterType);
v8it_src_n1=LAPLACIAN_CONVERT(VLOAD(src+offset_src_n1,8),V8InterType);
v8it_src_n2=LAPLACIAN_CONVERT(VLOAD(src+offset_src_n2,8),V8InterType);
}
else
{
y_idx_p2=TOP_BORDER_IDX(gy-3);
y_idx_p1=TOP_BORDER_IDX(gy-2);
y_idx_p0=TOP_BORDER_IDX(gy-1);
y_idx_c=gy;
y_idx_n0=BOTTOM_BORDER_IDX(gy+1,height);
y_idx_n1=BOTTOM_BORDER_IDX(gy+2,height);
y_idx_n2=BOTTOM_BORDER_IDX(gy+3,height);
offset_src_p2=mad24(y_idx_p2,istep,x_idx);
offset_src_p1=mad24(y_idx_p1,istep,x_idx);
offset_src_p0=mad24(y_idx_p0,istep,x_idx);
offset_src_c=mad24(y_idx_c,istep,x_idx);
offset_src_n0=mad24(y_idx_n0,istep,x_idx);
offset_src_n1=mad24(y_idx_n1,istep,x_idx);
offset_src_n2=mad24(y_idx_n2,istep,x_idx);
#if BORDER_CONSTANT
V8InterType v8it_border_value=(V8InterType)border_value.val[0];
v8it_src_p2=(y_idx_p2<0)?(V8InterType)v8it_border_value:LAPLACIAN_CONVERT(VLOAD(src+offset_src_p2,8),V8InterType);
v8it_src_p1=(y_idx_p1<0)?(V8InterType)v8it_border_value:LAPLACIAN_CONVERT(VLOAD(src+offset_src_p1,8),V8InterType);
v8it_src_p0=(y_idx_p0<0)?(V8InterType)v8it_border_value:LAPLACIAN_CONVERT(VLOAD(src+offset_src_p0,8),V8InterType);
v8it_src_c=LAPLACIAN_CONVERT(VLOAD(src+offset_src_c,8),V8InterType);
v8it_src_n0=(y_idx_n0<0)?(V8InterType)v8it_border_value:LAPLACIAN_CONVERT(VLOAD(src+offset_src_n0,8),V8InterType);
v8it_src_n1=(y_idx_n1<0)?(V8InterType)v8it_border_value:LAPLACIAN_CONVERT(VLOAD(src+offset_src_n1,8),V8InterType);
v8it_src_n2=(y_idx_n2<0)?(V8InterType)v8it_border_value:LAPLACIAN_CONVERT(VLOAD(src+offset_src_n2,8),V8InterType);
#else
v8it_src_p2=LAPLACIAN_CONVERT(VLOAD(src+offset_src_p2,8),V8InterType);
v8it_src_p1=LAPLACIAN_CONVERT(VLOAD(src+offset_src_p1,8),V8InterType);
v8it_src_p0=LAPLACIAN_CONVERT(VLOAD(src+offset_src_p0,8),V8InterType);
v8it_src_c=LAPLACIAN_CONVERT(VLOAD(src+offset_src_c,8),V8InterType);
v8it_src_n0=LAPLACIAN_CONVERT(VLOAD(src+offset_src_n0,8),V8InterType);
v8it_src_n1=LAPLACIAN_CONVERT(VLOAD(src+offset_src_n1,8),V8InterType);
v8it_src_n2=LAPLACIAN_CONVERT(VLOAD(src+offset_src_n2,8),V8InterType);
#endif
}
v8it_sum_pn2=v8it_src_p2+v8it_src_n2;
v8it_sum_pn1=v8it_src_p1+v8it_src_n1;
v8it_sum_pn0=v8it_src_p0+v8it_src_n0;
v2it_sum_pn2=((V2InterType)(v8it_sum_pn2.s01+v8it_sum_pn2.s67)*(V2InterType)2)+
((V2InterType)(v8it_sum_pn2.s12+v8it_sum_pn2.s56)*(V2InterType)8)+
((V2InterType)(v8it_sum_pn2.s23+v8it_sum_pn2.s45)*(V2InterType)14)+
((V2InterType)(v8it_sum_pn2.s34)*(V2InterType)16);
v2it_sum_pn1=((V2InterType)(v8it_sum_pn1.s01+v8it_sum_pn1.s67)*(V2InterType)8)+
((V2InterType)(v8it_sum_pn1.s12+v8it_sum_pn1.s56)*(V2InterType)24)+
((V2InterType)(v8it_sum_pn1.s23+v8it_sum_pn1.s45)*(V2InterType)24)+
((V2InterType)(v8it_sum_pn1.s34)*(V2InterType)16);
v2it_sum_pn0=((V2InterType)(v8it_sum_pn0.s01+v8it_sum_pn0.s67)*(V2InterType)14)+
((V2InterType)(v8it_sum_pn0.s12+v8it_sum_pn0.s56)*(V2InterType)24)+
((V2InterType)(v8it_sum_pn0.s23+v8it_sum_pn0.s45)*(V2InterType)-30)+
((V2InterType)(v8it_sum_pn0.s34)*(V2InterType)-80);
v2it_sum_c=((V2InterType)(v8it_src_c.s01+v8it_src_c.s67)*(V2InterType)16)+
((V2InterType)(v8it_src_c.s12+v8it_src_c.s56)*(V2InterType)16)+
((V2InterType)(v8it_src_c.s23+v8it_src_c.s45)*(V2InterType)-80)+
((V2InterType)(v8it_src_c.s34)*(V2InterType)-160);
v2it_result=v2it_sum_pn2+v2it_sum_pn1+v2it_sum_pn0+v2it_sum_c;
#if IS_FLOAT(InterType)
v2dt_result=CONVERT(v2it_result,V2Dt);
#else
v2dt_result=CONVERT_SAT(v2it_result,V2Dt);
#endif
offset_dst=mad24(gy,ostep,x_idx+ksh);
VSTORE(v2dt_result,dst+offset_dst,2);
}

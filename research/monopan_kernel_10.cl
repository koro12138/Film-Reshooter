kernel void ResizeAreaDownX4C2(global Tp*src,int istep,
global Tp*dst,int ostep,
float scale_x,float scale_y,
int iwidth,int iheight,
int owidth,int oheight)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
const int elem_counts=4;
int dst_x=gx*elem_counts;
int dst_y=gy;
if(dst_x>=owidth||(dst_y>=oheight))
{
return;
}
dst_x=min(dst_x,owidth-elem_counts);
int offset_dst=mad24(dst_y,ostep,dst_x*2);
dst_x<<=3;
int offset_src_c=mad24(4*dst_y,istep,dst_x);
int offset_src_n0=offset_src_c+istep;
int offset_src_n1=offset_src_n0+istep;
int offset_src_n2=offset_src_n1+istep;
V16Tp v16tp_cx0_src,v16tp_cx1_src,v16tp_n0x0_src,v16tp_n0x1_src;
V16Tp v16tp_n1x0_src,v16tp_n1x1_src,v16tp_n2x0_src,v16tp_n2x1_src;
V16InterType v16it_tmp0,v16it_tmp1,v16it_sum;
V8InterType v8it_mid;
V8Tp v8tp_result;
v16tp_cx0_src=VLOAD(src+offset_src_c,16);
v16tp_cx1_src=VLOAD(src+offset_src_c+16,16);
v16tp_n0x0_src=VLOAD(src+offset_src_n0,16);
v16tp_n0x1_src=VLOAD(src+offset_src_n0+16,16);
v16tp_n1x0_src=VLOAD(src+offset_src_n1,16);
v16tp_n1x1_src=VLOAD(src+offset_src_n1+16,16);
v16tp_n2x0_src=VLOAD(src+offset_src_n2,16);
v16tp_n2x1_src=VLOAD(src+offset_src_n2+16,16);
v16it_tmp0=RESIZE_CONVERT(v16tp_cx0_src,V16InterType)+RESIZE_CONVERT(v16tp_n0x0_src,V16InterType);
v16it_tmp0=RESIZE_CONVERT(v16tp_n1x0_src,V16InterType)+v16it_tmp0;
v16it_tmp0=RESIZE_CONVERT(v16tp_n2x0_src,V16InterType)+v16it_tmp0;
v16it_tmp1=RESIZE_CONVERT(v16tp_cx1_src,V16InterType)+RESIZE_CONVERT(v16tp_n0x1_src,V16InterType);
v16it_tmp1=RESIZE_CONVERT(v16tp_n1x1_src,V16InterType)+v16it_tmp1;
v16it_tmp1=RESIZE_CONVERT(v16tp_n2x1_src,V16InterType)+v16it_tmp1;
v16it_sum=(V16InterType)(v16it_tmp0.s01,v16it_tmp0.s45,v16it_tmp0.s89,v16it_tmp0.sCD,
v16it_tmp1.s01,v16it_tmp1.s45,v16it_tmp1.s89,v16it_tmp1.sCD)+
(V16InterType)(v16it_tmp0.s23,v16it_tmp0.s67,v16it_tmp0.sAB,v16it_tmp0.sEF,
v16it_tmp1.s23,v16it_tmp1.s67,v16it_tmp1.sAB,v16it_tmp1.sEF);
v8it_mid=(V8InterType)(v16it_sum.s01,v16it_sum.s45,v16it_sum.s89,v16it_sum.sCD)+
(V8InterType)(v16it_sum.s23,v16it_sum.s67,v16it_sum.sAB,v16it_sum.sEF);
#if IS_FLOAT(InterType)
v8it_mid=v8it_mid*(V8InterType)(0.0625f);
#else
v8it_mid=(v8it_mid+(V8InterType)(8))>>(V8InterType)(4);
#endif
v8tp_result=RESIZE_CONVERT(v8it_mid,V8Tp);
VSTORE(v8tp_result,dst+offset_dst,8);
}

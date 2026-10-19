kernel void ResizeAreaDownX2C2(global Tp*src,int istep,
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
dst_x<<=2;
int offset_src_c=mad24(2*dst_y,istep,dst_x);
int offset_src_n0=offset_src_c+istep;
V16Tp v16tp_c_src,v16tp_n0_src;
V16InterType v16it_mid;
V8InterType v8it_mid;
V8Tp v8tp_result;
v16tp_c_src=VLOAD(src+offset_src_c,16);
v16tp_n0_src=VLOAD(src+offset_src_n0,16);
v16it_mid=RESIZE_CONVERT(v16tp_c_src,V16InterType)+RESIZE_CONVERT(v16tp_n0_src,V16InterType);
v8it_mid=(V8InterType)(v16it_mid.s01,v16it_mid.s45,v16it_mid.s89,v16it_mid.sCD)+
(V8InterType)(v16it_mid.s23,v16it_mid.s67,v16it_mid.sAB,v16it_mid.sEF);
#if IS_FLOAT(InterType)
v8it_mid=v8it_mid*(V8InterType)(0.25f);
#else
v8it_mid=(v8it_mid+(V8InterType)(2))>>(V8InterType)(2);
#endif
v8tp_result=RESIZE_CONVERT(v8it_mid,V8Tp);
VSTORE(v8tp_result,dst+offset_dst,8);
}

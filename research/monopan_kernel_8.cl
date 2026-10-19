kernel void ResizeAreaDownX2C3(global Tp*src,int istep,
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
int offset_dst=mad24(dst_y,ostep,dst_x*3);
dst_x*=6;
int offset_src_c=mad24(2*dst_y,istep,dst_x);
int offset_src_n0=offset_src_c+istep;
V16Tp v16tp_cx0_src,v16tp_n0x0_src;
V8Tp v8tp_cx1_src,v8tp_n0x1_src;
V16InterType v16it_sum;
V8InterType v8it_mid,v8it_sum;
V4InterType v4it_mid;
V8Tp v8tp_result;
V4Tp v4tp_result;
v16tp_cx0_src=VLOAD(src+offset_src_c,16);
v8tp_cx1_src=VLOAD(src+offset_src_c+16,8);
v16tp_n0x0_src=VLOAD(src+offset_src_n0,16);
v8tp_n0x1_src=VLOAD(src+offset_src_n0+16,8);
v16it_sum=RESIZE_CONVERT(v16tp_cx0_src,V16InterType)+RESIZE_CONVERT(v16tp_n0x0_src,V16InterType);
v8it_sum=RESIZE_CONVERT(v8tp_cx1_src,V8InterType)+RESIZE_CONVERT(v8tp_n0x1_src,V8InterType);
v8it_mid=(V8InterType)(v16it_sum.s012,v16it_sum.s678,v16it_sum.sCD)+
(V8InterType)(v16it_sum.s345,v16it_sum.s9AB,v16it_sum.sF,v8it_sum.s0);
v4it_mid=(V4InterType)(v16it_sum.sE,v8it_sum.s234)+
(V4InterType)(v8it_sum.s1,v8it_sum.s567);
#if IS_FLOAT(InterType)
v8it_mid=v8it_mid*(V8InterType)(0.25f);
v4it_mid=v4it_mid*(V4InterType)(0.25f);
#else
v8it_mid=(v8it_mid+(V8InterType)(2))>>(V8InterType)(2);
v4it_mid=(v4it_mid+(V4InterType)(2))>>(V4InterType)(2);
#endif
v8tp_result=RESIZE_CONVERT(v8it_mid,V8Tp);
v4tp_result=RESIZE_CONVERT(v4it_mid,V4Tp);
VSTORE(v8tp_result,dst+offset_dst,8);
VSTORE(v4tp_result,dst+offset_dst+8,4);
}

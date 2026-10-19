kernel void ResizeAreaDownX2C1(global Tp*src,int istep,
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
int offset_dst=mad24(dst_y,ostep,dst_x);
dst_x<<=1;
int offset_src_c=mad24(2*dst_y,istep,dst_x);
int offset_src_n0=offset_src_c+istep;
V8Tp v8tp_c_src,v8tp_n0_src;
V8InterType v8it_mid;
V4InterType v4it_mid;
V4Tp v4tp_result;
v8tp_c_src=VLOAD(src+offset_src_c,8);
v8tp_n0_src=VLOAD(src+offset_src_n0,8);
v8it_mid=RESIZE_CONVERT(v8tp_c_src,V8InterType)+RESIZE_CONVERT(v8tp_n0_src,V8InterType);
v4it_mid=v8it_mid.even+v8it_mid.odd;
#if IS_FLOAT(InterType)
v4it_mid=v4it_mid*(V4InterType)(0.25f);
#else
v4it_mid=(v4it_mid+(V4InterType)(2))>>(V4InterType)(2);
#endif
v4tp_result=RESIZE_CONVERT(v4it_mid,V4Tp);
VSTORE(v4tp_result,dst+offset_dst,4);
}

kernel void ResizeAreaDownX4C1(global Tp*src,int istep,
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
dst_x<<=2;
int offset_src_c=mad24(4*dst_y,istep,dst_x);
int offset_src_n0=offset_src_c+istep;
int offset_src_n1=offset_src_n0+istep;
int offset_src_n2=offset_src_n1+istep;
V16Tp v16tp_c_src,v16tp_n0_src,v16tp_n1_src,v16tp_n2_src;
V16InterType v16it_sum;
V8InterType v8it_mid;
V4InterType v4it_mid;
V4Tp v4tp_result;
v16tp_c_src=VLOAD(src+offset_src_c,16);
v16tp_n0_src=VLOAD(src+offset_src_n0,16);
v16tp_n1_src=VLOAD(src+offset_src_n1,16);
v16tp_n2_src=VLOAD(src+offset_src_n2,16);
v16it_sum=RESIZE_CONVERT(v16tp_c_src,V16InterType)+RESIZE_CONVERT(v16tp_n0_src,V16InterType);
v16it_sum=RESIZE_CONVERT(v16tp_n1_src,V16InterType)+v16it_sum;
v16it_sum=RESIZE_CONVERT(v16tp_n2_src,V16InterType)+v16it_sum;
v8it_mid=v16it_sum.even+v16it_sum.odd;
v4it_mid=v8it_mid.even+v8it_mid.odd;
#if IS_FLOAT(InterType)
v4it_mid=v4it_mid*(V4InterType)(0.0625f);
#else
v4it_mid=(v4it_mid+(V4InterType)(8))>>(V4InterType)(4);
#endif
v4tp_result=RESIZE_CONVERT(v4it_mid,V4Tp);
VSTORE(v4tp_result,dst+offset_dst,4);
}

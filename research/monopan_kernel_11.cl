kernel void ResizeAreaDownX4C3(global Tp*src,int istep,
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
dst_x*=12;
int offset_src_c=mad24(4*dst_y,istep,dst_x);
int offset_src_n0=offset_src_c+istep;
int offset_src_n1=offset_src_n0+istep;
int offset_src_n2=offset_src_n1+istep;
V16Tp v16tp_cx0_src,v16tp_cx1_src,v16tp_cx2_src,v16tp_n0x0_src,v16tp_n0x1_src,v16tp_n0x2_src;
V16Tp v16tp_n1x0_src,v16tp_n1x1_src,v16tp_n1x2_src,v16tp_n2x0_src,v16tp_n2x1_src,v16tp_n2x2_src;
V16InterType v16it_tmp[3],v16it_sum;
V8InterType v8it_sum,v8it_mid;
V4InterType v4it_mid;
V8Tp v8tp_result;
V4Tp v4tp_result;
v16tp_cx0_src=VLOAD(src+offset_src_c,16);
v16tp_cx1_src=VLOAD(src+offset_src_c+16,16);
v16tp_cx2_src=VLOAD(src+offset_src_c+32,16);
v16tp_n0x0_src=VLOAD(src+offset_src_n0,16);
v16tp_n0x1_src=VLOAD(src+offset_src_n0+16,16);
v16tp_n0x2_src=VLOAD(src+offset_src_n0+32,16);
v16tp_n1x0_src=VLOAD(src+offset_src_n1,16);
v16tp_n1x1_src=VLOAD(src+offset_src_n1+16,16);
v16tp_n1x2_src=VLOAD(src+offset_src_n1+32,16);
v16tp_n2x0_src=VLOAD(src+offset_src_n2,16);
v16tp_n2x1_src=VLOAD(src+offset_src_n2+16,16);
v16tp_n2x2_src=VLOAD(src+offset_src_n2+32,16);
v16it_tmp[0]=RESIZE_CONVERT(v16tp_cx0_src,V16InterType)+RESIZE_CONVERT(v16tp_n0x0_src,V16InterType);
v16it_tmp[0]=RESIZE_CONVERT(v16tp_n1x0_src,V16InterType)+v16it_tmp[0];
v16it_tmp[0]=RESIZE_CONVERT(v16tp_n2x0_src,V16InterType)+v16it_tmp[0];
v16it_tmp[1]=RESIZE_CONVERT(v16tp_cx1_src,V16InterType)+RESIZE_CONVERT(v16tp_n0x1_src,V16InterType);
v16it_tmp[1]=RESIZE_CONVERT(v16tp_n1x1_src,V16InterType)+v16it_tmp[1];
v16it_tmp[1]=RESIZE_CONVERT(v16tp_n2x1_src,V16InterType)+v16it_tmp[1];
v16it_tmp[2]=RESIZE_CONVERT(v16tp_cx2_src,V16InterType)+RESIZE_CONVERT(v16tp_n0x2_src,V16InterType);
v16it_tmp[2]=RESIZE_CONVERT(v16tp_n1x2_src,V16InterType)+v16it_tmp[2];
v16it_tmp[2]=RESIZE_CONVERT(v16tp_n2x2_src,V16InterType)+v16it_tmp[2];
v16it_sum=(V16InterType)(v16it_tmp[0].s012,v16it_tmp[0].s678,v16it_tmp[0].sCDE,v16it_tmp[1].s234,
v16it_tmp[1].s89A,v16it_tmp[1].sE)+
(V16InterType)(v16it_tmp[0].s345,v16it_tmp[0].s9AB,v16it_tmp[0].sF,v16it_tmp[1].s01,
v16it_tmp[1].s567,v16it_tmp[1].sBCD,v16it_tmp[2].s1);
v8it_sum=(V8InterType)(v16it_tmp[1].sF,v16it_tmp[2].s0,v16it_tmp[2].s456,v16it_tmp[2].sABC)+
(V8InterType)(v16it_tmp[2].s23,v16it_tmp[2].s789,v16it_tmp[2].sDEF);
v8it_mid=(V8InterType)(v16it_sum.s012,v16it_sum.s678,v16it_sum.sCD)+
(V8InterType)(v16it_sum.s345,v16it_sum.s9AB,v16it_sum.sF,v8it_sum.s0);
v4it_mid=(V4InterType)(v16it_sum.sE,v8it_sum.s234)+
(V4InterType)(v8it_sum.s1,v8it_sum.s567);
#if IS_FLOAT(InterType)
v8it_mid=v8it_mid*(V8InterType)(0.0625f);
v4it_mid=v4it_mid*(V4InterType)(0.0625f);
#else
v8it_mid=(v8it_mid+(V8InterType)(8))>>(V8InterType)(4);
v4it_mid=(v4it_mid+(V4InterType)(8))>>(V4InterType)(4);
#endif
v8tp_result=RESIZE_CONVERT(v8it_mid,V8Tp);
v4tp_result=RESIZE_CONVERT(v4it_mid,V4Tp);
VSTORE(v8tp_result,dst+offset_dst,8);
VSTORE(v4tp_result,dst+offset_dst+8,4);
}

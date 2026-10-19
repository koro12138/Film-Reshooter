kernel void ResizeAreaUpX2C2(global Tp*src,int istep,
global Tp*dst,int ostep,
float scale_x,float scale_y,
int iwidth,int iheight,
int owidth,int oheight)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
const int elem_counts=4;
int dst_x=gx*elem_counts;
int dst_y=gy*2;
if(dst_x>=owidth||(dst_y>=oheight))
{
return;
}
dst_x=min(dst_x,owidth-elem_counts);
int offset_dst_c=mad24(dst_y,ostep,dst_x*2);
int offset_dst_n0=offset_dst_c+ostep;
int offset_src=mad24(gy,istep,dst_x);
V4Tp v4tp_src=VLOAD(src+offset_src,4);
V8Tp v8tp_dst=(V8Tp)(v4tp_src.s01,v4tp_src.s01,v4tp_src.s23,v4tp_src.s23);
VSTORE(v8tp_dst,dst+offset_dst_c,8);
VSTORE(v8tp_dst,dst+offset_dst_n0,8);
}

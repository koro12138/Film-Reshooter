kernel void ResizeAreaUpX2C3(global Tp*src,int istep,
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
int offset_dst_c=mad24(dst_y,ostep,dst_x*3);
int offset_dst_n0=offset_dst_c+ostep;
dst_x>>=1;
int offset_src=mad24(gy,istep,dst_x*3);
V3Tp v3st_src_c,v3st_src_r;
V8Tp v8tp_result_c;
V4Tp v4tp_result_r;
v3st_src_c=VLOAD(src+offset_src,3);
v3st_src_r=VLOAD(src+offset_src+3,3);
v8tp_result_c=(V8Tp)(v3st_src_c,v3st_src_c,v3st_src_r.s01);
v4tp_result_r=(V4Tp)(v3st_src_r.s2,v3st_src_r);
VSTORE(v8tp_result_c,dst+offset_dst_c,8);
VSTORE(v4tp_result_r,dst+offset_dst_c+8,4);
VSTORE(v8tp_result_c,dst+offset_dst_n0,8);
VSTORE(v4tp_result_r,dst+offset_dst_n0+8,4);
}

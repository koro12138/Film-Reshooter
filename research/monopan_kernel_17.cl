kernel void ResizeAreaUpX4C3(global Tp*src,int istep,
global Tp*dst,int ostep,
float scale_x,float scale_y,
int iwidth,int iheight,
int owidth,int oheight)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
int dst_x=gx*4;
int dst_y=gy*4;
if(dst_x>=owidth||(dst_y>=oheight))
{
return;
}
int offset_src=mad24(gy,istep,gx*3);
int offset_dst_c=mad24(dst_y,ostep,dst_x*3);
int offset_dst_n0=offset_dst_c+ostep;
int offset_dst_n1=offset_dst_n0+ostep;
int offset_dst_n2=offset_dst_n1+ostep;
V3Tp v3st_src;
V8Tp v8tp_result;
V4Tp v4tp_result;
v3st_src=VLOAD(src+offset_src,3);
v8tp_result=(V8Tp)(v3st_src,v3st_src,v3st_src.s01);
v4tp_result=(V4Tp)(v3st_src.s2,v3st_src);
VSTORE(v8tp_result,dst+offset_dst_c,8);
VSTORE(v4tp_result,dst+offset_dst_c+8,4);
VSTORE(v8tp_result,dst+offset_dst_n0,8);
VSTORE(v4tp_result,dst+offset_dst_n0+8,4);
VSTORE(v8tp_result,dst+offset_dst_n1,8);
VSTORE(v4tp_result,dst+offset_dst_n1+8,4);
VSTORE(v8tp_result,dst+offset_dst_n2,8);
VSTORE(v4tp_result,dst+offset_dst_n2+8,4);
}

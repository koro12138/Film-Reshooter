kernel void ResizeAreaUpX4C1(global Tp*src,int istep,
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
int offset_src=mad24(gy,istep,gx);
int offset_dst_c=mad24(dst_y,ostep,dst_x);
int offset_dst_n0=offset_dst_c+ostep;
int offset_dst_n1=offset_dst_n0+ostep;
int offset_dst_n2=offset_dst_n1+ostep;
Tp src_data;
V4Tp v4tp_result;
src_data=VLOAD(src+offset_src,1);
v4tp_result=(V4Tp)(src_data);
VSTORE(v4tp_result,dst+offset_dst_c,4);
VSTORE(v4tp_result,dst+offset_dst_n0,4);
VSTORE(v4tp_result,dst+offset_dst_n1,4);
VSTORE(v4tp_result,dst+offset_dst_n2,4);
}

kernel void ResizeAreaUpX4C2(global Tp*src,int istep,
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
int offset_src=mad24(gy,istep,gx*2);
int offset_dst_c=mad24(dst_y,ostep,dst_x*2);
int offset_dst_n0=offset_dst_c+ostep;
int offset_dst_n1=offset_dst_n0+ostep;
int offset_dst_n2=offset_dst_n1+ostep;
V2Tp v2tp_src;
V8Tp v8tp_result;
v2tp_src=VLOAD(src+offset_src,2);
v8tp_result=(V8Tp)(v2tp_src,v2tp_src,v2tp_src,v2tp_src);
VSTORE(v8tp_result,dst+offset_dst_c,8);
VSTORE(v8tp_result,dst+offset_dst_n0,8);
VSTORE(v8tp_result,dst+offset_dst_n1,8);
VSTORE(v8tp_result,dst+offset_dst_n2,8);
}

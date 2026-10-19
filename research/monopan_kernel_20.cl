#define VTp VTYPE(Tp,CHANNEL)
#define VFt VTYPE(float,CHANNEL)
kernel void ResizeBnCommonC3C4(global Tp*src,int istep,
global Tp*dst,int ostep,
int iwidth,int iheight,
int owidth,int oheight)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
if(gx>=owidth||gy>=oheight)
{
return;
}
int sx;
int sy;
float a0,a1;
float b0,b1;
ResizeBnCoefScalar(iwidth,owidth,gx,&sx,&a0,&a1);
ResizeBnCoefScalar(iheight,oheight,gy,&sy,&b0,&b1);
global Tp*src_c=src+istep*sy;
global Tp*src_n=src_c+istep;
global Tp*dst_c=dst+ostep*gy;
int sx0=sx*CHANNEL;
int sx1=sx0+CHANNEL;
VTp vtp_src_c0=VLOAD(src_c+sx0,CHANNEL);
VTp vtp_src_c1=VLOAD(src_c+sx1,CHANNEL);
VTp vtp_src_n0=VLOAD(src_n+sx0,CHANNEL);
VTp vtp_src_n1=VLOAD(src_n+sx1,CHANNEL);
VFt vf32_row_c=a0*CONVERT(vtp_src_c0,VFt)+a1*CONVERT(vtp_src_c1,VFt);
VFt vf32_row_n=a0*CONVERT(vtp_src_n0,VFt)+a1*CONVERT(vtp_src_n1,VFt);
VFt vf32_col=b0*vf32_row_c+b1*vf32_row_n;
VSTORE(RESIZE_CONVERT_SAT_ROUND(vf32_col,VTp,rte),dst_c+gx*CHANNEL,CHANNEL);
}

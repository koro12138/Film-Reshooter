#define VTp VTYPE(Tp,ELEM_COUNTS)
kernel void MulAndScaleSpectrums(global Tp*src0,int istep0,
global Tp*src1,int istep1,
global Tp*dst,int ostep,
int width,int y_work_size,int x_work_size)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
if(gx>=x_work_size||gy>=y_work_size)
{
return;
}
int idx=min(gx*ELEM_COUNTS,width*2-ELEM_COUNTS);
int offset_src0=mad24(gy,istep0,idx);
int offset_src1=mad24(gy,istep1,idx);
int offset_dst=mad24(gy,ostep,idx);
VTp vtp_src0=VLOAD(src0+offset_src0,ELEM_COUNTS);
VTp vtp_src1=VLOAD(src1+offset_src1,ELEM_COUNTS);
VTp vtp_dst;
#if CONJ
vtp_dst.even=vtp_src0.even*vtp_src1.even+vtp_src0.odd*vtp_src1.odd;
vtp_dst.odd=vtp_src0.odd*vtp_src1.even-vtp_src0.even*vtp_src1.odd;
#else
vtp_dst.even=vtp_src0.even*vtp_src1.even-vtp_src0.odd*vtp_src1.odd;
vtp_dst.odd=vtp_src0.even*vtp_src1.odd+vtp_src0.odd*vtp_src1.even;
#endif
VSTORE(vtp_dst,dst+offset_dst,ELEM_COUNTS);
}

kernel void CvtBgra2Gray(global uchar*src,int istep,
global uchar*dst,int ostep,
int width,int y_work_size,int x_work_size,
int b_coeff,int g_coeff,int r_coeff,int shift)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int idx=min((gx<<2),width-4);
int src_offset=mad24(gy,istep,idx*4);
int dst_offset=mad24(gy,ostep,idx);
int16 v16s32_bgr=convert_int16(VLOAD(src+src_offset,16));
int4 v4s32_b=(int4)(v16s32_bgr.s0,v16s32_bgr.s4,v16s32_bgr.s8,v16s32_bgr.sc);
int4 v4s32_g=(int4)(v16s32_bgr.s1,v16s32_bgr.s5,v16s32_bgr.s9,v16s32_bgr.sd);
int4 v4s32_r=(int4)(v16s32_bgr.s2,v16s32_bgr.s6,v16s32_bgr.sa,v16s32_bgr.se);
uchar4 v4u8_reault=convert_uchar4((v4s32_b*b_coeff+v4s32_g*g_coeff+v4s32_r*r_coeff+(1<<(shift-1)))>>shift);
VSTORE(v4u8_reault,dst+dst_offset,4);
}

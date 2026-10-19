kernel void CvtBgr2Gray(global uchar*src,int istep,
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
int src_offset=mad24(gy,istep,idx*3);
int dst_offset=mad24(gy,ostep,idx);
int8 v8s32_bgr=convert_int8(VLOAD(src+src_offset,8));
int4 v4s32_bgr=convert_int4(VLOAD(src+src_offset+8,4));
int4 v4s32_b=(int4)(v8s32_bgr.s0,v8s32_bgr.s3,v8s32_bgr.s6,v4s32_bgr.s1);
int4 v4s32_g=(int4)(v8s32_bgr.s1,v8s32_bgr.s4,v8s32_bgr.s7,v4s32_bgr.s2);
int4 v4s32_r=(int4)(v8s32_bgr.s2,v8s32_bgr.s5,v4s32_bgr.s0,v4s32_bgr.s3);
uchar4 v4u8_reault=convert_uchar4((v4s32_b*b_coeff+v4s32_g*g_coeff+v4s32_r*r_coeff+(1<<(shift-1)))>>shift);
VSTORE(v4u8_reault,dst+dst_offset,4);
}

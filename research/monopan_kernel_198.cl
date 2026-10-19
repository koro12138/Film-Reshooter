kernel void CvtY4442Rgb(global uchar*src0,int istep0,
global uchar*src1,int istep1,
global uchar*src2,int istep2,
global uchar*dst,int ostep,
int width,int y_work_size,int x_work_size)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int flag=(gx==(x_work_size-1));
int offset_row_src=select((gx<<3),width-8,flag);
int offset_row_dst=select((gx<<3)*3,width*3-24,flag);
int offset_src0=mad24(gy,istep0,offset_row_src);
int offset_src1=mad24(gy,istep1,offset_row_src);
int offset_src2=mad24(gy,istep2,offset_row_src);
int offset_dst=mad24(gy,ostep,offset_row_dst);
uchar8 v8u8_src0=VLOAD(src0+offset_src0,8);
uchar8 v8u8_src1=VLOAD(src1+offset_src1,8);
uchar8 v8u8_src2=VLOAD(src2+offset_src2,8);
int8 v8s32_ruv,v8s32_guv,v8s32_buv;
uchar8 v8u8_rgb0,v8u8_rgb1,v8u8_rgb2;
int8 v8s32_u=CONVERT(v8u8_src1,int8)-(int8)(128);
int8 v8s32_v=CONVERT(v8u8_src2,int8)-(int8)(128);
v8s32_ruv=mad24((int8)(v2r),v8s32_v,(int8)(1<<(CVTCOLOR_COEF_BITS-1)));
v8s32_guv=mad24((int8)(u2g),v8s32_u,mad24((int8)(v2g),v8s32_v,(int8)(1<<(CVTCOLOR_COEF_BITS-1))));
v8s32_buv=mad24((int8)(u2b),v8s32_u,(int8)(1<<(CVTCOLOR_COEF_BITS-1)));
#if CVTCOLOR_YUV2RGB_601
int8 v8s32_y=mul24(CONVERT(v8u8_src0,int8),(int8)(y2rgb));
#else
int8 v8s32_y=max(CONVERT(v8u8_src0,int8)-(int8)(16),(int8)(0));
v8s32_y=mul24(v8s32_y,(int8)(y2rgb));
#endif
uchar8 v8u8_r=CONVERT_SAT((v8s32_y+v8s32_ruv)>>CVTCOLOR_COEF_BITS,uchar8);
uchar8 v8u8_g=CONVERT_SAT((v8s32_y+v8s32_guv)>>CVTCOLOR_COEF_BITS,uchar8);
uchar8 v8u8_b=CONVERT_SAT((v8s32_y+v8s32_buv)>>CVTCOLOR_COEF_BITS,uchar8);
v8u8_rgb0=(uchar8)(v8u8_r.s0,v8u8_g.s0,v8u8_b.s0,v8u8_r.s1,v8u8_g.s1,v8u8_b.s1,v8u8_r.s2,v8u8_g.s2);
v8u8_rgb1=(uchar8)(v8u8_b.s2,v8u8_r.s3,v8u8_g.s3,v8u8_b.s3,v8u8_r.s4,v8u8_g.s4,v8u8_b.s4,v8u8_r.s5);
v8u8_rgb2=(uchar8)(v8u8_g.s5,v8u8_b.s5,v8u8_r.s6,v8u8_g.s6,v8u8_b.s6,v8u8_r.s7,v8u8_g.s7,v8u8_b.s7);
VSTORE(v8u8_rgb0,dst+offset_dst,8);
VSTORE(v8u8_rgb1,dst+offset_dst+8,8);
VSTORE(v8u8_rgb2,dst+offset_dst+16,8);
}

kernel void CvtY4202Rgb(global uchar*src0,int istep0,
global uchar*src1,int istep1,
global uchar*src2,int istep2,
global uchar*dst,int ostep,
int width,int y_work_size,int x_work_size,
uchar swap_uv)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int flag=(gx==(x_work_size-1));
int offset_row_src0=select((gx<<3),width-8,flag);
int offset_row_src1=select((gx<<2),(width>>1)-4,flag);
int offset_row_dst=select((gx<<3)*3,width*3-24,flag);
int y_idx_c=(gy<<1);
int y_idx_n=y_idx_c+1;
int offset_src0_c=mad24(y_idx_c,istep0,offset_row_src0);
int offset_src0_n=mad24(y_idx_n,istep0,offset_row_src0);
int offset_src1=mad24(gy,istep1,offset_row_src1);
int offset_src2=mad24(gy,istep2,offset_row_src1);
int offset_dst_c=mad24(y_idx_c,ostep,offset_row_dst);
int offset_dst_n=mad24(y_idx_n,ostep,offset_row_dst);
uchar8 v8u8_src0_c=VLOAD(src0+offset_src0_c,8);
uchar8 v8u8_src0_n=VLOAD(src0+offset_src0_n,8);
uchar4 v4u8_src1=VLOAD(src1+offset_src1,4);
uchar4 v4u8_src2=VLOAD(src2+offset_src2,4);
uchar4 v4u8_u=select(v4u8_src1,v4u8_src2,(uchar4)(swap_uv<<7));
uchar4 v4u8_v=select(v4u8_src2,v4u8_src1,(uchar4)(swap_uv<<7));
int8 v8s32_ruv,v8s32_guv,v8s32_buv;
uchar8 v8u8_rgb0,v8u8_rgb1,v8u8_rgb2;
int4 v4s32_u=CONVERT(v4u8_u,int4)-(int4)(128);
int4 v4s32_v=CONVERT(v4u8_v,int4)-(int4)(128);
int4 v4s32_ruv=mad24((int4)(v2r),v4s32_v,(int4)(1<<(CVTCOLOR_COEF_BITS-1)));
int4 v4s32_guv=mad24((int4)(u2g),v4s32_u,mad24((int4)(v2g),v4s32_v,(int4)(1<<(CVTCOLOR_COEF_BITS-1))));
int4 v4s32_buv=mad24((int4)(u2b),v4s32_u,(int4)(1<<(CVTCOLOR_COEF_BITS-1)));
v8s32_ruv=(int8)(v4s32_ruv.s0,v4s32_ruv.s0,v4s32_ruv.s1,v4s32_ruv.s1,
v4s32_ruv.s2,v4s32_ruv.s2,v4s32_ruv.s3,v4s32_ruv.s3);
v8s32_guv=(int8)(v4s32_guv.s0,v4s32_guv.s0,v4s32_guv.s1,v4s32_guv.s1,
v4s32_guv.s2,v4s32_guv.s2,v4s32_guv.s3,v4s32_guv.s3);
v8s32_buv=(int8)(v4s32_buv.s0,v4s32_buv.s0,v4s32_buv.s1,v4s32_buv.s1,
v4s32_buv.s2,v4s32_buv.s2,v4s32_buv.s3,v4s32_buv.s3);
#if CVTCOLOR_YUV2RGB_601
int8 v8s32_yc=mul24(CONVERT(v8u8_src0_c,int8),(int8)(y2rgb));
#else
int8 v8s32_yc=max(CONVERT(v8u8_src0_c,int8)-(int8)(16),(int8)(0));
v8s32_yc=mul24(v8s32_yc,(int8)(y2rgb));
#endif
uchar8 v8u8_r=CONVERT_SAT((v8s32_yc+v8s32_ruv)>>CVTCOLOR_COEF_BITS,uchar8);
uchar8 v8u8_g=CONVERT_SAT((v8s32_yc+v8s32_guv)>>CVTCOLOR_COEF_BITS,uchar8);
uchar8 v8u8_b=CONVERT_SAT((v8s32_yc+v8s32_buv)>>CVTCOLOR_COEF_BITS,uchar8);
v8u8_rgb0=(uchar8)(v8u8_r.s0,v8u8_g.s0,v8u8_b.s0,v8u8_r.s1,v8u8_g.s1,v8u8_b.s1,v8u8_r.s2,v8u8_g.s2);
v8u8_rgb1=(uchar8)(v8u8_b.s2,v8u8_r.s3,v8u8_g.s3,v8u8_b.s3,v8u8_r.s4,v8u8_g.s4,v8u8_b.s4,v8u8_r.s5);
v8u8_rgb2=(uchar8)(v8u8_g.s5,v8u8_b.s5,v8u8_r.s6,v8u8_g.s6,v8u8_b.s6,v8u8_r.s7,v8u8_g.s7,v8u8_b.s7);
VSTORE(v8u8_rgb0,dst+offset_dst_c,8);
VSTORE(v8u8_rgb1,dst+offset_dst_c+8,8);
VSTORE(v8u8_rgb2,dst+offset_dst_c+16,8);
#if CVTCOLOR_YUV2RGB_601
int8 v8s32_yn=mul24(CONVERT(v8u8_src0_n,int8),(int8)(y2rgb));
#else
int8 v8s32_yn=max(CONVERT(v8u8_src0_n,int8)-(int8)(16),(int8)(0));
v8s32_yn=mul24(v8s32_yn,(int8)(y2rgb));
#endif
v8u8_r=CONVERT_SAT((v8s32_yn+v8s32_ruv)>>CVTCOLOR_COEF_BITS,uchar8);
v8u8_g=CONVERT_SAT((v8s32_yn+v8s32_guv)>>CVTCOLOR_COEF_BITS,uchar8);
v8u8_b=CONVERT_SAT((v8s32_yn+v8s32_buv)>>CVTCOLOR_COEF_BITS,uchar8);
v8u8_rgb0=(uchar8)(v8u8_r.s0,v8u8_g.s0,v8u8_b.s0,v8u8_r.s1,v8u8_g.s1,v8u8_b.s1,v8u8_r.s2,v8u8_g.s2);
v8u8_rgb1=(uchar8)(v8u8_b.s2,v8u8_r.s3,v8u8_g.s3,v8u8_b.s3,v8u8_r.s4,v8u8_g.s4,v8u8_b.s4,v8u8_r.s5);
v8u8_rgb2=(uchar8)(v8u8_g.s5,v8u8_b.s5,v8u8_r.s6,v8u8_g.s6,v8u8_b.s6,v8u8_r.s7,v8u8_g.s7,v8u8_b.s7);
VSTORE(v8u8_rgb0,dst+offset_dst_n,8);
VSTORE(v8u8_rgb1,dst+offset_dst_n+8,8);
VSTORE(v8u8_rgb2,dst+offset_dst_n+16,8);
}

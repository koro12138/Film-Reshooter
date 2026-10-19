kernel void CvtY4222Rgb(global uchar*src,int istep,
global uchar*dst,int ostep,
int width,int y_work_size,int x_work_size,
uchar swap_uv,uchar swap_y)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int flag=(gx==(x_work_size-1));
int offset_row_src=select((gx<<4),width*2-16,flag);
int offset_row_dst=select((gx<<3)*3,width*3-24,flag);
int offset_src=mad24(gy,istep,offset_row_src);
int offset_dst=mad24(gy,ostep,offset_row_dst);
uchar16 v16u8_src=VLOAD(src+offset_src,16);
uchar8 v8u8_y=select(v16u8_src.even,v16u8_src.odd,(uchar8)(swap_y<<7));
uchar8 v8u8_uv=select(v16u8_src.odd,v16u8_src.even,(uchar8)(swap_y<<7));
uchar4 v4u8_u=select(v8u8_uv.even,v8u8_uv.odd,(uchar4)(swap_uv<<7));
uchar4 v4u8_v=select(v8u8_uv.odd,v8u8_uv.even,(uchar4)(swap_uv<<7));
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
int8 v8s32_y=mul24(CONVERT(v8u8_y,int8),(int8)(y2rgb));
#else
int8 v8s32_y=max(CONVERT(v8u8_y,int8)-(int8)(16),(int8)(0));
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

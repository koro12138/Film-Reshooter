kernel void CvtRgb2Y444(global uchar*src,int istep,
global uchar*dst_y,int ostepy,
global uchar*dst_u,int ostepu,
global uchar*dst_v,int ostepv,
int uv_const,int width,
int y_work_size,int x_work_size)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int y_idx_c=(gy<<1);
int y_idx_n=y_idx_c+1;
int x_idx=gx<<3;
int flag=(gx!=(x_work_size-1));
x_idx=select(width-8,x_idx,flag);
int offset_x0=mad24(y_idx_c,istep,x_idx*3);
int offset_x1=mad24(y_idx_n,istep,x_idx*3);
int offset_y0=mad24(y_idx_c,ostepy,x_idx);
int offset_y1=mad24(y_idx_n,ostepy,x_idx);
int offset_uv0=mad24(y_idx_c,ostepu,x_idx);
int offset_uv1=mad24(y_idx_n,ostepu,x_idx);
uchar8 v8u8_srcp_l=VLOAD(src+offset_x0,8);
uchar8 v8u8_srcp_c=VLOAD(src+offset_x0+8,8);
uchar8 v8u8_srcp_r=VLOAD(src+offset_x0+16,8);
int8 v8s32_srcp_r=CONVERT((uchar8)(v8u8_srcp_l.s036,v8u8_srcp_c.s147,v8u8_srcp_r.s25),int8);
int8 v8s32_srcp_g=CONVERT((uchar8)(v8u8_srcp_l.s147,v8u8_srcp_c.s25,v8u8_srcp_r.s036),int8);
int8 v8s32_srcp_b=CONVERT((uchar8)(v8u8_srcp_l.s25,v8u8_srcp_c.s036,v8u8_srcp_r.s147),int8);
int8 v8s32_py=v8s32_srcp_b*b2y+v8s32_srcp_r*r2y+v8s32_srcp_g*g2y;
uchar8 v8u8_dyp=CONVERT_SAT((v8s32_py+(int8)yc+(int8)(1<<(CVTCOLOR_COEF_BITS-1)))>>CVTCOLOR_COEF_BITS,uchar8);
VSTORE(v8u8_dyp,dst_y+offset_y0,8);
int8 v8s32_u0=v8s32_srcp_b*b2u+v8s32_srcp_r*r2u+v8s32_srcp_g*g2u;
int8 v8s32_v0=v8s32_srcp_b*b2v+v8s32_srcp_r*r2v+v8s32_srcp_g*g2v;
uchar8 v8u8_u0=CONVERT_SAT((v8s32_u0+(int8)(uv_const)+(int8)(1<<(CVTCOLOR_COEF_BITS-1)))>>CVTCOLOR_COEF_BITS,uchar8);
uchar8 v8u8_v0=CONVERT_SAT((v8s32_v0+(int8)(uv_const)+(int8)(1<<(CVTCOLOR_COEF_BITS-1)))>>CVTCOLOR_COEF_BITS,uchar8);
VSTORE(v8u8_u0,dst_u+offset_uv0,8);
VSTORE(v8u8_v0,dst_v+offset_uv0,8);
uchar8 v8u8_srcn_l=VLOAD(src+offset_x1,8);
uchar8 v8u8_srcn_c=VLOAD(src+offset_x1+8,8);
uchar8 v8u8_srcn_r=VLOAD(src+offset_x1+16,8);
int8 v8s32_srcn_r=CONVERT((uchar8)(v8u8_srcn_l.s036,v8u8_srcn_c.s147,v8u8_srcn_r.s25),int8);
int8 v8s32_srcn_g=CONVERT((uchar8)(v8u8_srcn_l.s147,v8u8_srcn_c.s25,v8u8_srcn_r.s036),int8);
int8 v8s32_srcn_b=CONVERT((uchar8)(v8u8_srcn_l.s25,v8u8_srcn_c.s036,v8u8_srcn_r.s147),int8);
int8 v8s32_ny=v8s32_srcn_b*b2y+v8s32_srcn_r*r2y+v8s32_srcn_g*g2y;
uchar8 v8u8_dyn=CONVERT_SAT((v8s32_ny+(int8)yc+(int8)(1<<(CVTCOLOR_COEF_BITS-1)))>>CVTCOLOR_COEF_BITS,uchar8);
VSTORE(v8u8_dyn,dst_y+offset_y1,8);
int8 v8s32_u1=v8s32_srcn_b*b2u+v8s32_srcn_r*r2u+v8s32_srcn_g*g2u;
int8 v8s32_v1=v8s32_srcn_b*b2v+v8s32_srcn_r*r2v+v8s32_srcn_g*g2v;
uchar8 v8u8_u1=CONVERT_SAT((v8s32_u1+(int8)(uv_const)+(int8)(1<<(CVTCOLOR_COEF_BITS-1)))>>CVTCOLOR_COEF_BITS,uchar8);
uchar8 v8u8_v1=CONVERT_SAT((v8s32_v1+(int8)(uv_const)+(int8)(1<<(CVTCOLOR_COEF_BITS-1)))>>CVTCOLOR_COEF_BITS,uchar8);
VSTORE(v8u8_u1,dst_u+offset_uv1,8);
VSTORE(v8u8_v1,dst_v+offset_uv1,8);
}

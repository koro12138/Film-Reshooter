kernel void CvtRgb2NvP010(global ushort*src,int istep,
global ushort*dst_y,int ostepy,
global ushort*dst_uv,int ostepuv,
int uv_const,int width,
int y_work_size,int x_work_size,
int uidx)
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
int offset_uv=mad24(gy,ostepuv,x_idx);
ushort8 v8u16_srcp_l=VLOAD(src+offset_x0,8);
ushort8 v8u16_srcp_c=VLOAD(src+offset_x0+8,8);
ushort8 v8u16_srcp_r=VLOAD(src+offset_x0+(8<<1),8);
ushort8 v8u16_srcn_l=VLOAD(src+offset_x1,8);
ushort8 v8u16_srcn_c=VLOAD(src+offset_x1+8,8);
ushort8 v8u16_srcn_r=VLOAD(src+offset_x1+(8<<1),8);
int8 v8s32_srcp_r=CONVERT((ushort8)(v8u16_srcp_l.s036,v8u16_srcp_c.s147,v8u16_srcp_r.s25),int8);
int8 v8s32_srcp_g=CONVERT((ushort8)(v8u16_srcp_l.s147,v8u16_srcp_c.s25,v8u16_srcp_r.s036),int8);
int8 v8s32_srcp_b=CONVERT((ushort8)(v8u16_srcp_l.s25,v8u16_srcp_c.s036,v8u16_srcp_r.s147),int8);
int8 v8s32_py=(int8)(yc<<2)+v8s32_srcp_b*b2y+v8s32_srcp_r*r2y+v8s32_srcp_g*g2y;
ushort8 v8u16_dyp=CONVERT_SAT((v8s32_py+(int8)(1<<(CVTCOLOR_COEF_BITS-1)))>>CVTCOLOR_COEF_BITS,ushort8);
VSTORE(v8u16_dyp,dst_y+offset_y0,8);
int8 v8s32_srcn_r=CONVERT((ushort8)(v8u16_srcn_l.s036,v8u16_srcn_c.s147,v8u16_srcn_r.s25),int8);
int8 v8s32_srcn_g=CONVERT((ushort8)(v8u16_srcn_l.s147,v8u16_srcn_c.s25,v8u16_srcn_r.s036),int8);
int8 v8s32_srcn_b=CONVERT((ushort8)(v8u16_srcn_l.s25,v8u16_srcn_c.s036,v8u16_srcn_r.s147),int8);
int8 v8s32_ny=(int8)(yc<<2)+v8s32_srcn_b*b2y+v8s32_srcn_r*r2y+v8s32_srcn_g*g2y;
ushort8 v8u16_dyn=CONVERT_SAT((v8s32_ny+(int8)(1<<(CVTCOLOR_COEF_BITS-1)))>>CVTCOLOR_COEF_BITS,ushort8);
VSTORE(v8u16_dyn,dst_y+offset_y1,8);
int4 v4s32_u=v8s32_srcp_b.even*b2u+v8s32_srcp_r.even*r2u+v8s32_srcp_g.even*g2u;
int4 v4s32_v=v8s32_srcp_b.even*b2v+v8s32_srcp_r.even*r2v+v8s32_srcp_g.even*g2v;
ushort4 v4u16_u=CONVERT_SAT((v4s32_u+(int4)(uv_const)+(int4)(1<<(CVTCOLOR_COEF_BITS-1)))>>CVTCOLOR_COEF_BITS,ushort4);
ushort4 v4u16_v=CONVERT_SAT((v4s32_v+(int4)(uv_const)+(int4)(1<<(CVTCOLOR_COEF_BITS-1)))>>CVTCOLOR_COEF_BITS,ushort4);
ushort8 v8u16_mask=(ushort8)(0,4,1,5,2,6,3,7);
ushort8 v8u16_duv=shuffle2(select(v4u16_u,v4u16_v,(short4)(uidx<<15)),select(v4u16_v,v4u16_u,(short4)(uidx<<15)),v8u16_mask);
VSTORE(v8u16_duv,dst_uv+offset_uv,8);
}

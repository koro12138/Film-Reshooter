kernel void ResizeCuRemainC2(global Tp*src,int istep,
global Tp*dst,int ostep,
float scale_x,float scale_y,
int iwidth,int iheight,int owidth,
int x_work_size,int y_work_size)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
float fx=(gx+0.5f)*scale_x-0.5f;
float fy=(gy+0.5f)*scale_y-0.5f;
int sx=floor(fx)-1;
int sy=floor(fy)-1;
float4 v4f32_alpha;
v4f32_alpha.s0=fx-sx;
v4f32_alpha.s1=v4f32_alpha.s0-1.f;
v4f32_alpha.s2=2.f-v4f32_alpha.s0;
v4f32_alpha.s0=GetBicubicCoef(v4f32_alpha.s0);
v4f32_alpha.s1=GetBicubicCoef(v4f32_alpha.s1);
v4f32_alpha.s2=GetBicubicCoef(v4f32_alpha.s2);
v4f32_alpha.s3=1.f-v4f32_alpha.s0-v4f32_alpha.s1-v4f32_alpha.s2;
float4 v4f32_beta;
v4f32_beta.s0=fy-sy;
v4f32_beta.s1=v4f32_beta.s0-1.f;
v4f32_beta.s2=2.f-v4f32_beta.s0;
v4f32_beta.s0=GetBicubicCoef(v4f32_beta.s0);
v4f32_beta.s1=GetBicubicCoef(v4f32_beta.s1);
v4f32_beta.s2=GetBicubicCoef(v4f32_beta.s2);
v4f32_beta.s3=1.f-v4f32_beta.s0-v4f32_beta.s1-v4f32_beta.s2;
int16 v16s32_x_bias=(int16)(0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3);
int16 v16s32_y_bias=(int16)(0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3);
int16 v16s32_x=mul24(clamp(v16s32_x_bias+sx,0,iwidth-1),2);
int16 v16s32_y=clamp(v16s32_y_bias+sy,0,iheight-1);
int16 v16s32_idx=mad24(v16s32_y,istep,v16s32_x);
float2 v2f32_cc,v2f32_cr0,v2f32_cr1,v2f32_cr2;
float2 v2f32_n0c,v2f32_n0r0,v2f32_n0r1,v2f32_n0r2;
float2 v2f32_n1c,v2f32_n1r0,v2f32_n1r1,v2f32_n1r2;
float2 v2f32_n2c,v2f32_n2r0,v2f32_n2r1,v2f32_n2r2;
v2f32_cc=RESIZE_CONVERT(VLOAD(src+v16s32_idx.s0,2),float2);
v2f32_cr0=RESIZE_CONVERT(VLOAD(src+v16s32_idx.s1,2),float2);
v2f32_cr1=RESIZE_CONVERT(VLOAD(src+v16s32_idx.s2,2),float2);
v2f32_cr2=RESIZE_CONVERT(VLOAD(src+v16s32_idx.s3,2),float2);
v2f32_n0c=RESIZE_CONVERT(VLOAD(src+v16s32_idx.s4,2),float2);
v2f32_n0r0=RESIZE_CONVERT(VLOAD(src+v16s32_idx.s5,2),float2);
v2f32_n0r1=RESIZE_CONVERT(VLOAD(src+v16s32_idx.s6,2),float2);
v2f32_n0r2=RESIZE_CONVERT(VLOAD(src+v16s32_idx.s7,2),float2);
v2f32_n1c=RESIZE_CONVERT(VLOAD(src+v16s32_idx.s8,2),float2);
v2f32_n1r0=RESIZE_CONVERT(VLOAD(src+v16s32_idx.s9,2),float2);
v2f32_n1r1=RESIZE_CONVERT(VLOAD(src+v16s32_idx.sa,2),float2);
v2f32_n1r2=RESIZE_CONVERT(VLOAD(src+v16s32_idx.sb,2),float2);
v2f32_n2c=RESIZE_CONVERT(VLOAD(src+v16s32_idx.sc,2),float2);
v2f32_n2r0=RESIZE_CONVERT(VLOAD(src+v16s32_idx.sd,2),float2);
v2f32_n2r1=RESIZE_CONVERT(VLOAD(src+v16s32_idx.se,2),float2);
v2f32_n2r2=RESIZE_CONVERT(VLOAD(src+v16s32_idx.sf,2),float2);
float16 v16f32_val=(float16)(v2f32_cc.s0,v2f32_cr0.s0,v2f32_cr1.s0,v2f32_cr2.s0,
v2f32_n0c.s0,v2f32_n0r0.s0,v2f32_n0r1.s0,v2f32_n0r2.s0,
v2f32_n1c.s0,v2f32_n1r0.s0,v2f32_n1r1.s0,v2f32_n1r2.s0,
v2f32_n2c.s0,v2f32_n2r0.s0,v2f32_n2r1.s0,v2f32_n2r2.s0);
float4 v4f32_tmp;
v4f32_tmp.s0=dot(v16f32_val.s0123,v4f32_alpha);
v4f32_tmp.s1=dot(v16f32_val.s4567,v4f32_alpha);
v4f32_tmp.s2=dot(v16f32_val.s89ab,v4f32_alpha);
v4f32_tmp.s3=dot(v16f32_val.scdef,v4f32_alpha);
V2Tp v2tp_result;
v2tp_result.s0=RESIZE_CONVERT_SAT_ROUND(dot(v4f32_tmp,v4f32_beta),Tp,rte);
v16f32_val=(float16)(v2f32_cc.s1,v2f32_cr0.s1,v2f32_cr1.s1,v2f32_cr2.s1,
v2f32_n0c.s1,v2f32_n0r0.s1,v2f32_n0r1.s1,v2f32_n0r2.s1,
v2f32_n1c.s1,v2f32_n1r0.s1,v2f32_n1r1.s1,v2f32_n1r2.s1,
v2f32_n2c.s1,v2f32_n2r0.s1,v2f32_n2r1.s1,v2f32_n2r2.s1);
v4f32_tmp.s0=dot(v16f32_val.s0123,v4f32_alpha);
v4f32_tmp.s1=dot(v16f32_val.s4567,v4f32_alpha);
v4f32_tmp.s2=dot(v16f32_val.s89ab,v4f32_alpha);
v4f32_tmp.s3=dot(v16f32_val.scdef,v4f32_alpha);
v2tp_result.s1=RESIZE_CONVERT_SAT_ROUND(dot(v4f32_tmp,v4f32_beta),Tp,rte);
VSTORE(v2tp_result,dst+mad24(gy,ostep,gx*2),2);
gx=owidth-1-gx;
fx=(gx+0.5f)*scale_x-0.5f;
sx=floor(fx)-1;
v4f32_alpha.s0=fx-sx;
v4f32_alpha.s1=v4f32_alpha.s0-1.f;
v4f32_alpha.s2=2.f-v4f32_alpha.s0;
v4f32_alpha.s0=GetBicubicCoef(v4f32_alpha.s0);
v4f32_alpha.s1=GetBicubicCoef(v4f32_alpha.s1);
v4f32_alpha.s2=GetBicubicCoef(v4f32_alpha.s2);
v4f32_alpha.s3=1.f-v4f32_alpha.s0-v4f32_alpha.s1-v4f32_alpha.s2;
v16s32_x=mul24(clamp(v16s32_x_bias+sx,0,iwidth-1),2);
v16s32_idx=mad24(v16s32_y,istep,v16s32_x);
v2f32_cc=RESIZE_CONVERT(VLOAD(src+v16s32_idx.s0,2),float2);
v2f32_cr0=RESIZE_CONVERT(VLOAD(src+v16s32_idx.s1,2),float2);
v2f32_cr1=RESIZE_CONVERT(VLOAD(src+v16s32_idx.s2,2),float2);
v2f32_cr2=RESIZE_CONVERT(VLOAD(src+v16s32_idx.s3,2),float2);
v2f32_n0c=RESIZE_CONVERT(VLOAD(src+v16s32_idx.s4,2),float2);
v2f32_n0r0=RESIZE_CONVERT(VLOAD(src+v16s32_idx.s5,2),float2);
v2f32_n0r1=RESIZE_CONVERT(VLOAD(src+v16s32_idx.s6,2),float2);
v2f32_n0r2=RESIZE_CONVERT(VLOAD(src+v16s32_idx.s7,2),float2);
v2f32_n1c=RESIZE_CONVERT(VLOAD(src+v16s32_idx.s8,2),float2);
v2f32_n1r0=RESIZE_CONVERT(VLOAD(src+v16s32_idx.s9,2),float2);
v2f32_n1r1=RESIZE_CONVERT(VLOAD(src+v16s32_idx.sa,2),float2);
v2f32_n1r2=RESIZE_CONVERT(VLOAD(src+v16s32_idx.sb,2),float2);
v2f32_n2c=RESIZE_CONVERT(VLOAD(src+v16s32_idx.sc,2),float2);
v2f32_n2r0=RESIZE_CONVERT(VLOAD(src+v16s32_idx.sd,2),float2);
v2f32_n2r1=RESIZE_CONVERT(VLOAD(src+v16s32_idx.se,2),float2);
v2f32_n2r2=RESIZE_CONVERT(VLOAD(src+v16s32_idx.sf,2),float2);
v16f32_val=(float16)(v2f32_cc.s0,v2f32_cr0.s0,v2f32_cr1.s0,v2f32_cr2.s0,
v2f32_n0c.s0,v2f32_n0r0.s0,v2f32_n0r1.s0,v2f32_n0r2.s0,
v2f32_n1c.s0,v2f32_n1r0.s0,v2f32_n1r1.s0,v2f32_n1r2.s0,
v2f32_n2c.s0,v2f32_n2r0.s0,v2f32_n2r1.s0,v2f32_n2r2.s0);
v4f32_tmp.s0=dot(v16f32_val.s0123,v4f32_alpha);
v4f32_tmp.s1=dot(v16f32_val.s4567,v4f32_alpha);
v4f32_tmp.s2=dot(v16f32_val.s89ab,v4f32_alpha);
v4f32_tmp.s3=dot(v16f32_val.scdef,v4f32_alpha);
v2tp_result.s0=RESIZE_CONVERT_SAT_ROUND(dot(v4f32_tmp,v4f32_beta),Tp,rte);
v16f32_val=(float16)(v2f32_cc.s1,v2f32_cr0.s1,v2f32_cr1.s1,v2f32_cr2.s1,
v2f32_n0c.s1,v2f32_n0r0.s1,v2f32_n0r1.s1,v2f32_n0r2.s1,
v2f32_n1c.s1,v2f32_n1r0.s1,v2f32_n1r1.s1,v2f32_n1r2.s1,
v2f32_n2c.s1,v2f32_n2r0.s1,v2f32_n2r1.s1,v2f32_n2r2.s1);
v4f32_tmp.s0=dot(v16f32_val.s0123,v4f32_alpha);
v4f32_tmp.s1=dot(v16f32_val.s4567,v4f32_alpha);
v4f32_tmp.s2=dot(v16f32_val.s89ab,v4f32_alpha);
v4f32_tmp.s3=dot(v16f32_val.scdef,v4f32_alpha);
v2tp_result.s1=RESIZE_CONVERT_SAT_ROUND(dot(v4f32_tmp,v4f32_beta),Tp,rte);
VSTORE(v2tp_result,dst+mad24(gy,ostep,gx*2),2);
}

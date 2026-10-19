kernel void ResizeCuMainC3(global Tp*src,int istep,
global Tp*dst,int ostep,
float scale_x,float scale_y,int border,
int iwidth,int iheight,
int owidth,int oheight,
int x_work_size,int y_work_size)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
gx+=border;
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
int4 v4s32_y_bias=(int4)(0,1,2,3);
int4 v4s32_y=clamp(v4s32_y_bias+sy,0,iheight-1);
int4 v4s32_idx=mad24(v4s32_y,istep,(int4)(sx*3));
float8 v8f32_src_cc,v8f32_src_n0c,v8f32_src_n1c,v8f32_src_n2c;
float4 v4f32_src_cr,v4f32_src_n0r,v4f32_src_n1r,v4f32_src_n2r;
v8f32_src_cc=RESIZE_CONVERT(VLOAD(src+v4s32_idx.s0,8),float8);
v4f32_src_cr=RESIZE_CONVERT(VLOAD(src+v4s32_idx.s0+8,4),float4);
v8f32_src_n0c=RESIZE_CONVERT(VLOAD(src+v4s32_idx.s1,8),float8);
v4f32_src_n0r=RESIZE_CONVERT(VLOAD(src+v4s32_idx.s1+8,4),float4);
v8f32_src_n1c=RESIZE_CONVERT(VLOAD(src+v4s32_idx.s2,8),float8);
v4f32_src_n1r=RESIZE_CONVERT(VLOAD(src+v4s32_idx.s2+8,4),float4);
v8f32_src_n2c=RESIZE_CONVERT(VLOAD(src+v4s32_idx.s3,8),float8);
v4f32_src_n2r=RESIZE_CONVERT(VLOAD(src+v4s32_idx.s3+8,4),float4);
float16 v16f32_val=(float16)(v8f32_src_cc.s0,v8f32_src_cc.s3,v8f32_src_cc.s6,v4f32_src_cr.s1,
v8f32_src_n0c.s0,v8f32_src_n0c.s3,v8f32_src_n0c.s6,v4f32_src_n0r.s1,
v8f32_src_n1c.s0,v8f32_src_n1c.s3,v8f32_src_n1c.s6,v4f32_src_n1r.s1,
v8f32_src_n2c.s0,v8f32_src_n2c.s3,v8f32_src_n2c.s6,v4f32_src_n2r.s1);
float4 v4f32_c0_tmp,v4f32_c1_tmp,v4f32_c2_tmp;
v4f32_c0_tmp.s0=dot(v16f32_val.s0123,v4f32_alpha);
v4f32_c0_tmp.s1=dot(v16f32_val.s4567,v4f32_alpha);
v4f32_c0_tmp.s2=dot(v16f32_val.s89ab,v4f32_alpha);
v4f32_c0_tmp.s3=dot(v16f32_val.scdef,v4f32_alpha);
v16f32_val=(float16)(v8f32_src_cc.s1,v8f32_src_cc.s4,v8f32_src_cc.s7,v4f32_src_cr.s2,
v8f32_src_n0c.s1,v8f32_src_n0c.s4,v8f32_src_n0c.s7,v4f32_src_n0r.s2,
v8f32_src_n1c.s1,v8f32_src_n1c.s4,v8f32_src_n1c.s7,v4f32_src_n1r.s2,
v8f32_src_n2c.s1,v8f32_src_n2c.s4,v8f32_src_n2c.s7,v4f32_src_n2r.s2);
v4f32_c1_tmp.s0=dot(v16f32_val.s0123,v4f32_alpha);
v4f32_c1_tmp.s1=dot(v16f32_val.s4567,v4f32_alpha);
v4f32_c1_tmp.s2=dot(v16f32_val.s89ab,v4f32_alpha);
v4f32_c1_tmp.s3=dot(v16f32_val.scdef,v4f32_alpha);
v16f32_val=(float16)(v8f32_src_cc.s2,v8f32_src_cc.s5,v4f32_src_cr.s0,v4f32_src_cr.s3,
v8f32_src_n0c.s2,v8f32_src_n0c.s5,v4f32_src_n0r.s0,v4f32_src_n0r.s3,
v8f32_src_n1c.s2,v8f32_src_n1c.s5,v4f32_src_n1r.s0,v4f32_src_n1r.s3,
v8f32_src_n2c.s2,v8f32_src_n2c.s5,v4f32_src_n2r.s0,v4f32_src_n2r.s3);
v4f32_c2_tmp.s0=dot(v16f32_val.s0123,v4f32_alpha);
v4f32_c2_tmp.s1=dot(v16f32_val.s4567,v4f32_alpha);
v4f32_c2_tmp.s2=dot(v16f32_val.s89ab,v4f32_alpha);
v4f32_c2_tmp.s3=dot(v16f32_val.scdef,v4f32_alpha);
V3Tp v3tp_result;
v3tp_result.s0=RESIZE_CONVERT_SAT_ROUND(dot(v4f32_c0_tmp,v4f32_beta),Tp,rte);
v3tp_result.s1=RESIZE_CONVERT_SAT_ROUND(dot(v4f32_c1_tmp,v4f32_beta),Tp,rte);
v3tp_result.s2=RESIZE_CONVERT_SAT_ROUND(dot(v4f32_c2_tmp,v4f32_beta),Tp,rte);
VSTORE(v3tp_result,dst+mad24(gy,ostep,gx*3),3);
}

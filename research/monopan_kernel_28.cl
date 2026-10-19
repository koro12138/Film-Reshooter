kernel void ResizeCuMainC2(global Tp*src,int istep,
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
int4 v4s32_idx=mad24(v4s32_y,istep,(int4)(sx*2));
float8 v8f32_src_c,v8f32_src_n0,v8f32_src_n1,v8f32_src_n2;
v8f32_src_c=RESIZE_CONVERT(VLOAD(src+v4s32_idx.s0,8),float8);
v8f32_src_n0=RESIZE_CONVERT(VLOAD(src+v4s32_idx.s1,8),float8);
v8f32_src_n1=RESIZE_CONVERT(VLOAD(src+v4s32_idx.s2,8),float8);
v8f32_src_n2=RESIZE_CONVERT(VLOAD(src+v4s32_idx.s3,8),float8);
float4 v4f32_c0_tmp,v4f32_c1_tmp;
v4f32_c0_tmp.s0=dot(v8f32_src_c.even,v4f32_alpha);
v4f32_c0_tmp.s1=dot(v8f32_src_n0.even,v4f32_alpha);
v4f32_c0_tmp.s2=dot(v8f32_src_n1.even,v4f32_alpha);
v4f32_c0_tmp.s3=dot(v8f32_src_n2.even,v4f32_alpha);
v4f32_c1_tmp.s0=dot(v8f32_src_c.odd,v4f32_alpha);
v4f32_c1_tmp.s1=dot(v8f32_src_n0.odd,v4f32_alpha);
v4f32_c1_tmp.s2=dot(v8f32_src_n1.odd,v4f32_alpha);
v4f32_c1_tmp.s3=dot(v8f32_src_n2.odd,v4f32_alpha);
V2Tp v2tp_result;
v2tp_result.s0=RESIZE_CONVERT_SAT_ROUND(dot(v4f32_c0_tmp,v4f32_beta),Tp,rte);
v2tp_result.s1=RESIZE_CONVERT_SAT_ROUND(dot(v4f32_c1_tmp,v4f32_beta),Tp,rte);
VSTORE(v2tp_result,dst+mad24(gy,ostep,gx*2),2);
}

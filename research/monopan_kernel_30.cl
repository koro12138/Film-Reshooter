kernel void ResizeCuRemainC1(global Tp*src,int istep,
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
v4f32_alpha.s0=(fx-sx);
v4f32_alpha.s1=v4f32_alpha.s0-1.f;
v4f32_alpha.s2=2.f-v4f32_alpha.s0;
v4f32_alpha.s0=GetBicubicCoef(v4f32_alpha.s0);
v4f32_alpha.s1=GetBicubicCoef(v4f32_alpha.s1);
v4f32_alpha.s2=GetBicubicCoef(v4f32_alpha.s2);
v4f32_alpha.s3=1.f-v4f32_alpha.s0-v4f32_alpha.s1-v4f32_alpha.s2;
float4 v4f32_beta;
v4f32_beta.s0=(fy-sy);
v4f32_beta.s1=v4f32_beta.s0-1.f;
v4f32_beta.s2=2.f-v4f32_beta.s0;
v4f32_beta.s0=GetBicubicCoef(v4f32_beta.s0);
v4f32_beta.s1=GetBicubicCoef(v4f32_beta.s1);
v4f32_beta.s2=GetBicubicCoef(v4f32_beta.s2);
v4f32_beta.s3=1.f-v4f32_beta.s0-v4f32_beta.s1-v4f32_beta.s2;
int16 v16s32_x_bias=(int16)(0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3);
int16 v16s32_y_bias=(int16)(0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3);
int16 v16s32_x=clamp(v16s32_x_bias+sx,0,iwidth-1);
int16 v16s32_y=clamp(v16s32_y_bias+sy,0,iheight-1);
int16 v16s32_idx=mad24(v16s32_y,istep,v16s32_x);
float16 v16f32_val=(float16)(src[v16s32_idx.s0],src[v16s32_idx.s1],src[v16s32_idx.s2],src[v16s32_idx.s3],
src[v16s32_idx.s4],src[v16s32_idx.s5],src[v16s32_idx.s6],src[v16s32_idx.s7],
src[v16s32_idx.s8],src[v16s32_idx.s9],src[v16s32_idx.sa],src[v16s32_idx.sb],
src[v16s32_idx.sc],src[v16s32_idx.sd],src[v16s32_idx.se],src[v16s32_idx.sf]);
float4 v4f32_tmp;
v4f32_tmp.s0=dot(v16f32_val.s0123,v4f32_alpha);
v4f32_tmp.s1=dot(v16f32_val.s4567,v4f32_alpha);
v4f32_tmp.s2=dot(v16f32_val.s89ab,v4f32_alpha);
v4f32_tmp.s3=dot(v16f32_val.scdef,v4f32_alpha);
Tp result=RESIZE_CONVERT_SAT_ROUND(dot(v4f32_tmp,v4f32_beta),Tp,rte);
dst[mad24(gy,ostep,gx)]=result;
gx=owidth-1-gx;
fx=(gx+0.5f)*scale_x-0.5f;
fy=(gy+0.5f)*scale_y-0.5f;
sx=floor(fx)-1;
v4f32_alpha.s0=(fx-sx);
v4f32_alpha.s1=v4f32_alpha.s0-1.f;
v4f32_alpha.s2=2.f-v4f32_alpha.s0;
v4f32_alpha.s0=GetBicubicCoef(v4f32_alpha.s0);
v4f32_alpha.s1=GetBicubicCoef(v4f32_alpha.s1);
v4f32_alpha.s2=GetBicubicCoef(v4f32_alpha.s2);
v4f32_alpha.s3=1.f-v4f32_alpha.s0-v4f32_alpha.s1-v4f32_alpha.s2;
v16s32_x=clamp(v16s32_x_bias+sx,0,iwidth-1);
v16s32_idx=mad24(v16s32_y,istep,v16s32_x);
v16f32_val=(float16)(src[v16s32_idx.s0],src[v16s32_idx.s1],src[v16s32_idx.s2],src[v16s32_idx.s3],
src[v16s32_idx.s4],src[v16s32_idx.s5],src[v16s32_idx.s6],src[v16s32_idx.s7],
src[v16s32_idx.s8],src[v16s32_idx.s9],src[v16s32_idx.sa],src[v16s32_idx.sb],
src[v16s32_idx.sc],src[v16s32_idx.sd],src[v16s32_idx.se],src[v16s32_idx.sf]);
v4f32_tmp.s0=dot(v16f32_val.s0123,v4f32_alpha);
v4f32_tmp.s1=dot(v16f32_val.s4567,v4f32_alpha);
v4f32_tmp.s2=dot(v16f32_val.s89ab,v4f32_alpha);
v4f32_tmp.s3=dot(v16f32_val.scdef,v4f32_alpha);
result=RESIZE_CONVERT_SAT_ROUND(dot(v4f32_tmp,v4f32_beta),Tp,rte);
dst[mad24(gy,ostep,gx)]=result;
}

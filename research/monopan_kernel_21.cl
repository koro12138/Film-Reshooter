kernel void ResizeCuMainDownX2C1(global Tp*src,int istep,
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
float4 v4f32_beta,v4f32_alpha;
int src_y=clamp(gy*2-1,0,iheight-4);
int src_x=clamp(gx*2-1,0,iwidth-4);
v4f32_beta=select((float4)(-0.09375f,0.59375f,0.59375f,-0.09375f),(float4)(0.5f,0.59375f,-0.09375f,0.f),(int4)(0)==(int4)(gy));
v4f32_beta=select(v4f32_beta,(float4)(0.f,-0.09375f,0.59375f,0.5f),((int4)(gy)==(int4)(oheight-1)));
v4f32_alpha=select((float4)(-0.09375f,0.59375f,0.59375f,-0.09375f),(float4)(0.5f,0.59375f,-0.09375f,0.f),((int4)(0)==(int4)(gx)));
v4f32_alpha=select(v4f32_alpha,(float4)(0.f,-0.09375f,0.59375f,0.5f),((int4)(gx)==(int4)(owidth-1)));
int offset_src=mad24(src_y,istep,src_x);
V4Tp v4tp_src_c=VLOAD(src+offset_src,4);
V4Tp v4tp_src_n0=VLOAD(src+offset_src+istep,4);
V4Tp v4tp_src_n1=VLOAD(src+offset_src+istep*2,4);
V4Tp v4tp_src_n2=VLOAD(src+offset_src+istep*3,4);
float4 v4f32_temp;
v4f32_temp.s0=dot(RESIZE_CONVERT(v4tp_src_c,float4),v4f32_alpha);
v4f32_temp.s1=dot(RESIZE_CONVERT(v4tp_src_n0,float4),v4f32_alpha);
v4f32_temp.s2=dot(RESIZE_CONVERT(v4tp_src_n1,float4),v4f32_alpha);
v4f32_temp.s3=dot(RESIZE_CONVERT(v4tp_src_n2,float4),v4f32_alpha);
Tp result;
result=RESIZE_CONVERT_SAT_ROUND(dot(v4f32_temp,v4f32_beta),Tp,rte);
int offset_dst=mad24(gy,ostep,gx);
dst[offset_dst]=result;
}

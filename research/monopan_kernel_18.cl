kernel void ResizeBnCommonC1(global Tp*src,int istep,
global Tp*dst,int ostep,
int iwidth,int iheight,
int owidth,int oheight)
{
int gx=get_global_id(0)<<2;
int gy=get_global_id(1);
if(gx>=owidth||gy>=oheight)
{
return;
}
gx=min(gx,owidth-4);
int4 v4s32_sx;
int sy;
float4 v4f32_a0,v4f32_a1;
float b0,b1;
ResizeBnCoefVector(iwidth,owidth,gx,&v4s32_sx,&v4f32_a0,&v4f32_a1);
ResizeBnCoefScalar(iheight,oheight,gy,&sy,&b0,&b1);
global Tp*src_c=src+istep*sy;
global Tp*src_n=src_c+istep;
global Tp*dst_c=dst+ostep*gy;
V8Tp v8tp_src0=(V8Tp)(vload2(0,src_c+v4s32_sx.s0),vload2(0,src_c+v4s32_sx.s1),vload2(0,src_c+v4s32_sx.s2),vload2(0,src_c+v4s32_sx.s3));
V8Tp v8tp_src1=(V8Tp)(vload2(0,src_n+v4s32_sx.s0),vload2(0,src_n+v4s32_sx.s1),vload2(0,src_n+v4s32_sx.s2),vload2(0,src_n+v4s32_sx.s3));
float4 v4f32_row0=v4f32_a0*CONVERT(v8tp_src0.even,float4)+v4f32_a1*CONVERT(v8tp_src0.odd,float4);
float4 v4f32_row1=v4f32_a0*CONVERT(v8tp_src1.even,float4)+v4f32_a1*CONVERT(v8tp_src1.odd,float4);
float4 v4f32_col=b0*v4f32_row0+b1*v4f32_row1;
vstore4(RESIZE_CONVERT_SAT_ROUND(v4f32_col,V4Tp,rte),0,dst_c+gx);
}

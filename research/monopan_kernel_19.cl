kernel void ResizeBnCommonC2(global Tp*src,int istep,
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
v4s32_sx=v4s32_sx*2;
V8Tp v8tp_src_c0=(V8Tp)(vload4(0,src_c+v4s32_sx.s0),vload4(0,src_c+v4s32_sx.s1));
V8Tp v8tp_src_c1=(V8Tp)(vload4(0,src_c+v4s32_sx.s2),vload4(0,src_c+v4s32_sx.s3));
V8Tp v8tp_src_n0=(V8Tp)(vload4(0,src_n+v4s32_sx.s0),vload4(0,src_n+v4s32_sx.s1));
V8Tp v8tp_src_n1=(V8Tp)(vload4(0,src_n+v4s32_sx.s2),vload4(0,src_n+v4s32_sx.s3));
float4 v4f32_a0_lo=v4f32_a0.s0011;
float4 v4f32_a1_lo=v4f32_a1.s0011;
float4 v4f32_a0_hi=v4f32_a0.s2233;
float4 v4f32_a1_hi=v4f32_a1.s2233;
float4 v4f32_row_c0=v4f32_a0_lo*CONVERT(v8tp_src_c0.s0145,float4)+v4f32_a1_lo*CONVERT(v8tp_src_c0.s2367,float4);
float4 v4f32_row_n0=v4f32_a0_lo*CONVERT(v8tp_src_n0.s0145,float4)+v4f32_a1_lo*CONVERT(v8tp_src_n0.s2367,float4);
float4 v4f32_row_c1=v4f32_a0_hi*CONVERT(v8tp_src_c1.s0145,float4)+v4f32_a1_hi*CONVERT(v8tp_src_c1.s2367,float4);
float4 v4f32_row_n1=v4f32_a0_hi*CONVERT(v8tp_src_n1.s0145,float4)+v4f32_a1_hi*CONVERT(v8tp_src_n1.s2367,float4);
float4 v4f32_col_c0=b0*v4f32_row_c0+b1*v4f32_row_n0;
float4 v4f32_col_c1=b0*v4f32_row_c1+b1*v4f32_row_n1;
int gx2=gx<<1;
vstore4(RESIZE_CONVERT_SAT_ROUND(v4f32_col_c0,V4Tp,rte),0,dst_c+gx2);
vstore4(RESIZE_CONVERT_SAT_ROUND(v4f32_col_c1,V4Tp,rte),0,dst_c+gx2+4);
}

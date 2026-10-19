kernel void ResizeAreaUpCommC2(global Tp*src,int istep,
global Tp*dst,int ostep,
float scale_x,float scale_y,
int iwidth,int iheight,
int owidth,int oheight)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
const int elem_counts=4;
int dst_x=gx*elem_counts;
int dst_y=gy;
if(dst_x>=owidth||dst_y>=oheight)
{
return;
}
dst_x=min(dst_x,owidth-elem_counts);
float scale_x_inv=1.f/scale_x;
int sy=floor(gy*scale_y);
float fy=(float)((gy+1)-(sy+1)/scale_y);
fy=select(fy-floor(fy),0.f,fy<=0.f);
fy=select(fy,0.0f,sy<0);
fy=select(fy,1.0f,sy>iheight-2);
sy=clamp(sy,0,iheight-2);
float4 v4f32_fx_t1=(float4)(dst_x)+(float4)(0.f,1.f,2.f,3.f);
int4 v4s32_sx=CONVERT(floor(v4f32_fx_t1*scale_x),int4);
v4f32_fx_t1=(v4f32_fx_t1+(float4)(1.f))-(convert_float4(v4s32_sx)+(float4)(1.f))*scale_x_inv;
v4f32_fx_t1=select(v4f32_fx_t1-floor(v4f32_fx_t1),(float4)(0.f),v4f32_fx_t1<=(float4)(0.f));
v4f32_fx_t1=select(v4f32_fx_t1,(float4)0.0f,v4s32_sx<(int4)0);
v4f32_fx_t1=select(v4f32_fx_t1,(float4)1.0f,v4s32_sx>(int4)(iwidth-2));
float4 v4f32_fx_t0=(float4)1.f-v4f32_fx_t1;
v4s32_sx=clamp(v4s32_sx,(int4)0,(int4)(iwidth-2));
global Tp*src_row0=src+sy*istep;
global Tp*src_row1=src_row0+istep;
global Tp*dst_row=dst+gy*ostep;
float8 v8f32_row0,v8f32_row1;
float4 v4f32_tmp;
v4f32_tmp=RESIZE_CONVERT(VLOAD(src_row0+2*v4s32_sx.x,4),float4);
v8f32_row0.s0=dot(v4f32_tmp.xz,(float2)(v4f32_fx_t0.x,v4f32_fx_t1.x));
v8f32_row0.s1=dot(v4f32_tmp.yw,(float2)(v4f32_fx_t0.x,v4f32_fx_t1.x));
v4f32_tmp=RESIZE_CONVERT(VLOAD(src_row0+2*v4s32_sx.y,4),float4);
v8f32_row0.s2=dot(v4f32_tmp.xz,(float2)(v4f32_fx_t0.y,v4f32_fx_t1.y));
v8f32_row0.s3=dot(v4f32_tmp.yw,(float2)(v4f32_fx_t0.y,v4f32_fx_t1.y));
v4f32_tmp=RESIZE_CONVERT(VLOAD(src_row0+2*v4s32_sx.z,4),float4);
v8f32_row0.s4=dot(v4f32_tmp.xz,(float2)(v4f32_fx_t0.z,v4f32_fx_t1.z));
v8f32_row0.s5=dot(v4f32_tmp.yw,(float2)(v4f32_fx_t0.z,v4f32_fx_t1.z));
v4f32_tmp=RESIZE_CONVERT(VLOAD(src_row0+2*v4s32_sx.w,4),float4);
v8f32_row0.s6=dot(v4f32_tmp.xz,(float2)(v4f32_fx_t0.w,v4f32_fx_t1.w));
v8f32_row0.s7=dot(v4f32_tmp.yw,(float2)(v4f32_fx_t0.w,v4f32_fx_t1.w));
v4f32_tmp=RESIZE_CONVERT(VLOAD(src_row1+2*v4s32_sx.x,4),float4);
v8f32_row1.s0=dot(v4f32_tmp.xz,(float2)(v4f32_fx_t0.x,v4f32_fx_t1.x));
v8f32_row1.s1=dot(v4f32_tmp.yw,(float2)(v4f32_fx_t0.x,v4f32_fx_t1.x));
v4f32_tmp=RESIZE_CONVERT(VLOAD(src_row1+2*v4s32_sx.y,4),float4);
v8f32_row1.s2=dot(v4f32_tmp.xz,(float2)(v4f32_fx_t0.y,v4f32_fx_t1.y));
v8f32_row1.s3=dot(v4f32_tmp.yw,(float2)(v4f32_fx_t0.y,v4f32_fx_t1.y));
v4f32_tmp=RESIZE_CONVERT(VLOAD(src_row1+2*v4s32_sx.z,4),float4);
v8f32_row1.s4=dot(v4f32_tmp.xz,(float2)(v4f32_fx_t0.z,v4f32_fx_t1.z));
v8f32_row1.s5=dot(v4f32_tmp.yw,(float2)(v4f32_fx_t0.z,v4f32_fx_t1.z));
v4f32_tmp=RESIZE_CONVERT(VLOAD(src_row1+2*v4s32_sx.w,4),float4);
v8f32_row1.s6=dot(v4f32_tmp.xz,(float2)(v4f32_fx_t0.w,v4f32_fx_t1.w));
v8f32_row1.s7=dot(v4f32_tmp.yw,(float2)(v4f32_fx_t0.w,v4f32_fx_t1.w));
float8 v8f32_result=v8f32_row0*(float8)(1-fy)+v8f32_row1*(float8)fy;
VSTORE(RESIZE_CONVERT_SAT_ROUND(v8f32_result,V8Tp,rte),dst_row+2*dst_x,8);
}

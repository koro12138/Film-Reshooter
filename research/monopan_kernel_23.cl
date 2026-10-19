kernel void ResizeCuMainDownX2C3(global Tp*src,int istep,
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
int src_x=mul24(clamp(gx*2-1,0,iwidth-4),3);
v4f32_beta=select((float4)(-0.09375f,0.59375f,0.59375f,-0.09375f),(float4)(0.5f,0.59375f,-0.09375f,0.f),(int4)(0)==(int4)(gy));
v4f32_beta=select(v4f32_beta,(float4)(0.f,-0.09375f,0.59375f,0.5f),((int4)(gy)==(int4)(oheight-1)));
v4f32_alpha=select((float4)(-0.09375f,0.59375f,0.59375f,-0.09375f),(float4)(0.5f,0.59375f,-0.09375f,0.f),((int4)(0)==(int4)(gx)));
v4f32_alpha=select(v4f32_alpha,(float4)(0.f,-0.09375f,0.59375f,0.5f),((int4)(gx)==(int4)(owidth-1)));
int offset_src=mad24(src_y,istep,src_x);
V8Tp v8tp_src_cc=VLOAD(src+offset_src,8);
V4Tp v4tp_src_cr=VLOAD(src+offset_src+8,4);
V8Tp v8tp_src_n0c=VLOAD(src+offset_src+istep,8);
V4Tp v4tp_src_n0r=VLOAD(src+offset_src+istep+8,4);
V8Tp v8tp_src_n1c=VLOAD(src+offset_src+istep*2,8);
V4Tp v4tp_src_n1r=VLOAD(src+offset_src+istep*2+8,4);
V8Tp v8tp_src_n2c=VLOAD(src+offset_src+istep*3,8);
V4Tp v4tp_src_n2r=VLOAD(src+offset_src+istep*3+8,4);
float4 v4f32_temp_l,v4f32_temp_c,v4f32_temp_r;
float4 v4tp_src_l,v4tp_src_c,v4tp_src_r;
v4tp_src_l=RESIZE_CONVERT((V4Tp)(v8tp_src_cc.s036,v4tp_src_cr.s1),float4);
v4tp_src_c=RESIZE_CONVERT((V4Tp)(v8tp_src_cc.s147,v4tp_src_cr.s2),float4);
v4tp_src_r=RESIZE_CONVERT((V4Tp)(v8tp_src_cc.s25,v4tp_src_cr.s03),float4);
v4f32_temp_l.s0=dot(v4tp_src_l,v4f32_alpha);
v4f32_temp_c.s0=dot(v4tp_src_c,v4f32_alpha);
v4f32_temp_r.s0=dot(v4tp_src_r,v4f32_alpha);
v4tp_src_l=RESIZE_CONVERT((V4Tp)(v8tp_src_n0c.s036,v4tp_src_n0r.s1),float4);
v4tp_src_c=RESIZE_CONVERT((V4Tp)(v8tp_src_n0c.s147,v4tp_src_n0r.s2),float4);
v4tp_src_r=RESIZE_CONVERT((V4Tp)(v8tp_src_n0c.s25,v4tp_src_n0r.s03),float4);
v4f32_temp_l.s1=dot(v4tp_src_l,v4f32_alpha);
v4f32_temp_c.s1=dot(v4tp_src_c,v4f32_alpha);
v4f32_temp_r.s1=dot(v4tp_src_r,v4f32_alpha);
v4tp_src_l=RESIZE_CONVERT((V4Tp)(v8tp_src_n1c.s036,v4tp_src_n1r.s1),float4);
v4tp_src_c=RESIZE_CONVERT((V4Tp)(v8tp_src_n1c.s147,v4tp_src_n1r.s2),float4);
v4tp_src_r=RESIZE_CONVERT((V4Tp)(v8tp_src_n1c.s25,v4tp_src_n1r.s03),float4);
v4f32_temp_l.s2=dot(v4tp_src_l,v4f32_alpha);
v4f32_temp_c.s2=dot(v4tp_src_c,v4f32_alpha);
v4f32_temp_r.s2=dot(v4tp_src_r,v4f32_alpha);
v4tp_src_l=RESIZE_CONVERT((V4Tp)(v8tp_src_n2c.s036,v4tp_src_n2r.s1),float4);
v4tp_src_c=RESIZE_CONVERT((V4Tp)(v8tp_src_n2c.s147,v4tp_src_n2r.s2),float4);
v4tp_src_r=RESIZE_CONVERT((V4Tp)(v8tp_src_n2c.s25,v4tp_src_n2r.s03),float4);
v4f32_temp_l.s3=dot(v4tp_src_l,v4f32_alpha);
v4f32_temp_c.s3=dot(v4tp_src_c,v4f32_alpha);
v4f32_temp_r.s3=dot(v4tp_src_r,v4f32_alpha);
V3Tp v3tp_result;
v3tp_result.s0=RESIZE_CONVERT_SAT_ROUND(dot(v4f32_temp_l,v4f32_beta),Tp,rte);
v3tp_result.s1=RESIZE_CONVERT_SAT_ROUND(dot(v4f32_temp_c,v4f32_beta),Tp,rte);
v3tp_result.s2=RESIZE_CONVERT_SAT_ROUND(dot(v4f32_temp_r,v4f32_beta),Tp,rte);
int offset_dst=mad24(gy,ostep,gx*3);
VSTORE(v3tp_result,dst+offset_dst,3);
}

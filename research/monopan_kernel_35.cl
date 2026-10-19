kernel void BilateralMain3x3C3(global St*src,int istep,
global Dt*dst,int ostep,
int width,int height,
int x_work_size,int y_work_size,
constant float*space_weight MAX_CONSTANT_SIZE,
read_only image2d_t color_weight,int color_len,
float scale_index,
struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
int elem_counts=4;
int ksh=1;
int channel=3;
int x_idx=gx*elem_counts*channel;
if(gx>=x_work_size||(gy>=y_work_size))
{
return;
}
int offset_src_p,offset_src_c,offset_src_n,offset_dst;
V8St v8st_src_p0,v8st_src_n0;
V4St v4st_src_p1,v4st_src_n1;
V16St v16st_src_c0;
V2St v2st_src_c1;
V16St v16st_src_px1,v16st_src_cx0,v16st_src_cx1,v16st_src_cx2,v16st_src_nx1;
float4 v4f32_scale,v4f32_sum_weight,v4f32_sum_r,v4f32_sum_g,v4f32_sum_b;
float16 v16f32_absdiff;
float4 v4f32_dif_r,v4f32_dif_g,v4f32_dif_b,v4f32_alpha,v4f32_idx;
int4 v4s32_idx;
float4 v4f32_color_idx0,v4f32_color_idx1,v4f32_color_weight,v4f32_weight_cur;
float4 v4f32_weight_inv,v4f32_result;
float8 v8f32_result;
V8Dt v8dt_result;
V4Dt v4dt_result;
if(gy>=ksh&&gy<(height-ksh))
{
offset_src_p=mad24(gy-1,istep,x_idx+ksh*channel);
offset_src_c=mad24(gy,istep,x_idx);
offset_src_n=mad24(gy+1,istep,x_idx+ksh*channel);
v8st_src_p0=VLOAD(src+offset_src_p,8);
v4st_src_p1=VLOAD(src+offset_src_p+8,4);
v16st_src_c0=VLOAD(src+offset_src_c,16);
v2st_src_c1=VLOAD(src+offset_src_c+16,2);
v8st_src_n0=VLOAD(src+offset_src_n,8);
v4st_src_n1=VLOAD(src+offset_src_n+8,4);
}
else
{
int y_idx_p,y_idx_c,y_idx_n;
y_idx_p=TOP_BORDER_IDX(gy-1);
y_idx_c=gy;
y_idx_n=BOTTOM_BORDER_IDX(gy+1,height);
offset_src_p=mad24(y_idx_p,istep,x_idx+ksh*channel);
offset_src_c=mad24(y_idx_c,istep,x_idx);
offset_src_n=mad24(y_idx_n,istep,x_idx+ksh*channel);
#if BORDER_CONSTANT
V8St v8st_border_value=(V8St)(border_value.val[0],border_value.val[1],border_value.val[2],border_value.val[0],
border_value.val[1],border_value.val[2],border_value.val[0],border_value.val[1]);
V4St v4st_border_value=(V4St)(border_value.val[2],border_value.val[0],border_value.val[1],border_value.val[2]);
v8st_src_p0=(y_idx_p<0)?(V8St)v8st_border_value:VLOAD(src+offset_src_p,8);
v4st_src_p1=(y_idx_p<0)?(V4St)v4st_border_value:VLOAD(src+offset_src_p+8,4);
v16st_src_c0=VLOAD(src+offset_src_c,16);
v2st_src_c1=VLOAD(src+offset_src_c+16,2);
v8st_src_n0=(y_idx_n<0)?(V8St)v8st_border_value:VLOAD(src+offset_src_n,8);
v4st_src_n1=(y_idx_n<0)?(V4St)v4st_border_value:VLOAD(src+offset_src_n+8,4);
#else
v8st_src_p0=VLOAD(src+offset_src_p,8);
v4st_src_p1=VLOAD(src+offset_src_p+8,4);
v16st_src_c0=VLOAD(src+offset_src_c,16);
v2st_src_c1=VLOAD(src+offset_src_c+16,2);
v8st_src_n0=VLOAD(src+offset_src_n,8);
v4st_src_n1=VLOAD(src+offset_src_n+8,4);
#endif
}
v16st_src_px1=(V16St)(v8st_src_p0,v4st_src_p1,0,0,0,0);
v16st_src_cx0=(V16St)(v16st_src_c0);
v16st_src_cx1=(V16St)(v16st_src_c0.s3,v16st_src_c0.s4567,v16st_src_c0.hi,0,0,0);
v16st_src_cx2=(V16St)(v16st_src_c0.s67,v16st_src_c0.hi,v2st_src_c1,0,0,0,0);
v16st_src_nx1=(V16St)(v8st_src_n0,v4st_src_n1,0,0,0,0);
v4f32_scale=(float4)scale_index;
v4f32_sum_r=(float4){0.f,0.f,0.f,0.f};
v4f32_sum_g=(float4){0.f,0.f,0.f,0.f};
v4f32_sum_b=(float4){0.f,0.f,0.f,0.f};
v4f32_sum_weight=(float4){0.f,0.f,0.f,0.f};
v16f32_absdiff=BILATERAL_ABS_CONVERT_F32(v16st_src_px1,v16st_src_cx1,float16);
v4f32_dif_r=(float4)(v16f32_absdiff.s0369);
v4f32_dif_g=(float4)(v16f32_absdiff.s147a);
v4f32_dif_b=(float4)(v16f32_absdiff.s258b);
v4f32_alpha=(v4f32_dif_r+v4f32_dif_g+v4f32_dif_b)*v4f32_scale;
v4f32_idx=floor(v4f32_alpha);
v4s32_idx=BILATERAL_CONVERT_CLAMP(v4f32_idx,int4,0,color_len-2);
v4f32_color_idx0=BILATERAL_READ_IMAGE_V4(color_weight,sampler,v4s32_idx);
#if IS_UCHAR(St)
v4f32_color_weight=v4f32_color_idx0;
#else
v4f32_color_idx1=BILATERAL_READ_IMAGE_V4(color_weight,sampler,v4s32_idx+1);
v4f32_alpha-=v4f32_idx;
v4f32_color_weight=v4f32_color_idx0+v4f32_alpha*(v4f32_color_idx1-v4f32_color_idx0);
#endif
v4f32_weight_cur=(float4)space_weight[0]*v4f32_color_weight;
v4f32_sum_weight+=v4f32_weight_cur;
v4f32_sum_r+=CONVERT(v16st_src_px1.s0369,float4)*v4f32_weight_cur;
v4f32_sum_g+=CONVERT(v16st_src_px1.s147a,float4)*v4f32_weight_cur;
v4f32_sum_b+=CONVERT(v16st_src_px1.s258b,float4)*v4f32_weight_cur;
v16f32_absdiff=BILATERAL_ABS_CONVERT_F32(v16st_src_cx0,v16st_src_cx1,float16);
v4f32_dif_r=(float4)(v16f32_absdiff.s0369);
v4f32_dif_g=(float4)(v16f32_absdiff.s147a);
v4f32_dif_b=(float4)(v16f32_absdiff.s258b);
v4f32_alpha=(v4f32_dif_r+v4f32_dif_g+v4f32_dif_b)*v4f32_scale;
v4f32_idx=floor(v4f32_alpha);
v4s32_idx=BILATERAL_CONVERT_CLAMP(v4f32_idx,int4,0,color_len-2);
v4f32_color_idx0=BILATERAL_READ_IMAGE_V4(color_weight,sampler,v4s32_idx);
#if IS_UCHAR(St)
v4f32_color_weight=v4f32_color_idx0;
#else
v4f32_color_idx1=BILATERAL_READ_IMAGE_V4(color_weight,sampler,v4s32_idx+1);
v4f32_alpha-=v4f32_idx;
v4f32_color_weight=v4f32_color_idx0+v4f32_alpha*(v4f32_color_idx1-v4f32_color_idx0);
#endif
v4f32_weight_cur=(float4)space_weight[0]*v4f32_color_weight;
v4f32_sum_weight+=v4f32_weight_cur;
v4f32_sum_r+=CONVERT(v16st_src_cx0.s0369,float4)*v4f32_weight_cur;
v4f32_sum_g+=CONVERT(v16st_src_cx0.s147a,float4)*v4f32_weight_cur;
v4f32_sum_b+=CONVERT(v16st_src_cx0.s258b,float4)*v4f32_weight_cur;
v4f32_color_idx0=(float4)(READ_IMAGE(float)(color_weight,sampler,(int2)(0,0))).s0;
v4f32_color_weight=v4f32_color_idx0;
v4f32_weight_cur=(float4)space_weight[2]*v4f32_color_weight;
v4f32_sum_weight+=v4f32_weight_cur;
v4f32_sum_r+=(CONVERT((V4St)(v16st_src_cx1.s0369),float4)*v4f32_weight_cur);
v4f32_sum_g+=(CONVERT((V4St)(v16st_src_cx1.s147a),float4)*v4f32_weight_cur);
v4f32_sum_b+=(CONVERT((V4St)(v16st_src_cx1.s258b),float4)*v4f32_weight_cur);
v16f32_absdiff=BILATERAL_ABS_CONVERT_F32(v16st_src_cx2,v16st_src_cx1,float16);
v4f32_dif_r=(float4)(v16f32_absdiff.s0369);
v4f32_dif_g=(float4)(v16f32_absdiff.s147a);
v4f32_dif_b=(float4)(v16f32_absdiff.s258b);
v4f32_alpha=(v4f32_dif_r+v4f32_dif_g+v4f32_dif_b)*v4f32_scale;
v4f32_idx=floor(v4f32_alpha);
v4s32_idx=BILATERAL_CONVERT_CLAMP(v4f32_idx,int4,0,color_len-2);
v4f32_color_idx0=BILATERAL_READ_IMAGE_V4(color_weight,sampler,v4s32_idx);
#if IS_UCHAR(St)
v4f32_color_weight=v4f32_color_idx0;
#else
v4f32_color_idx1=BILATERAL_READ_IMAGE_V4(color_weight,sampler,v4s32_idx+1);
v4f32_alpha-=v4f32_idx;
v4f32_color_weight=v4f32_color_idx0+v4f32_alpha*(v4f32_color_idx1-v4f32_color_idx0);
#endif
v4f32_weight_cur=(float4)space_weight[0]*v4f32_color_weight;
v4f32_sum_weight+=v4f32_weight_cur;
v4f32_sum_r+=CONVERT(v16st_src_cx2.s0369,float4)*v4f32_weight_cur;
v4f32_sum_g+=CONVERT(v16st_src_cx2.s147a,float4)*v4f32_weight_cur;
v4f32_sum_b+=CONVERT(v16st_src_cx2.s258b,float4)*v4f32_weight_cur;
v16f32_absdiff=BILATERAL_ABS_CONVERT_F32(v16st_src_nx1,v16st_src_cx1,float16);
v4f32_dif_r=(float4)(v16f32_absdiff.s0369);
v4f32_dif_g=(float4)(v16f32_absdiff.s147a);
v4f32_dif_b=(float4)(v16f32_absdiff.s258b);
v4f32_alpha=(v4f32_dif_r+v4f32_dif_g+v4f32_dif_b)*v4f32_scale;
v4f32_idx=floor(v4f32_alpha);
v4s32_idx=BILATERAL_CONVERT_CLAMP(v4f32_idx,int4,0,color_len-2);
v4f32_color_idx0=BILATERAL_READ_IMAGE_V4(color_weight,sampler,v4s32_idx);
#if IS_UCHAR(St)
v4f32_color_weight=v4f32_color_idx0;
#else
v4f32_color_idx1=BILATERAL_READ_IMAGE_V4(color_weight,sampler,v4s32_idx+1);
v4f32_alpha-=v4f32_idx;
v4f32_color_weight=v4f32_color_idx0+v4f32_alpha*(v4f32_color_idx1-v4f32_color_idx0);
#endif
v4f32_weight_cur=(float4)space_weight[0]*v4f32_color_weight;
v4f32_sum_weight+=v4f32_weight_cur;
v4f32_sum_r+=CONVERT(v16st_src_nx1.s0369,float4)*v4f32_weight_cur;
v4f32_sum_g+=CONVERT(v16st_src_nx1.s147a,float4)*v4f32_weight_cur;
v4f32_sum_b+=CONVERT(v16st_src_nx1.s258b,float4)*v4f32_weight_cur;
v4f32_weight_inv=1.f/v4f32_sum_weight;
v4f32_sum_r*=v4f32_weight_inv;
v4f32_sum_g*=v4f32_weight_inv;
v4f32_sum_b*=v4f32_weight_inv;
v8f32_result=(float8)(v4f32_sum_r.s0,v4f32_sum_g.s0,v4f32_sum_b.s0,v4f32_sum_r.s1,
v4f32_sum_g.s1,v4f32_sum_b.s1,v4f32_sum_r.s2,v4f32_sum_g.s2);
v4f32_result=(float4)(v4f32_sum_b.s2,v4f32_sum_r.s3,v4f32_sum_g.s3,v4f32_sum_b.s3);
v8dt_result=BILATERAL_CONVERT_ROUND(v8f32_result,V8Dt);
v4dt_result=BILATERAL_CONVERT_ROUND(v4f32_result,V4Dt);
offset_dst=mad24(gy,ostep,x_idx+ksh*channel);
VSTORE(v8dt_result,dst+offset_dst,8);
VSTORE(v4dt_result,dst+offset_dst+8,4);
}

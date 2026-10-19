kernel void BilateralMain3x3C1(global St*src,int istep,
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
int x_idx=gx*elem_counts;
if(gx>=x_work_size||(gy>=y_work_size))
{
return;
}
int offset_src_p,offset_src_c,offset_src_n,offset_dst;
V4St v4st_src_p,v4st_src_c0,v4st_src_n;
V2St v2st_src_c1;
V4St v4st_src_cx0,v4st_src_cx1,v4st_src_cx2;
float4 v4f32_src_c,v4f32_scale,v4f32_alpha,v4f32_idx;
int4 v4s32_idx;
float4 v4f32_color_weight,v4f32_color_idx0,v4f32_color_idx1;
float4 v4f32_weight_cur,v4f32_sum_weight,v4f32_sum;
V4Dt v4dt_result;
if(gy>=ksh&&gy<(height-ksh))
{
offset_src_p=mad24(gy-1,istep,x_idx+ksh);
offset_src_c=mad24(gy,istep,x_idx);
offset_src_n=mad24(gy+1,istep,x_idx+ksh);
v4st_src_p=VLOAD(src+offset_src_p,4);
v4st_src_c0=VLOAD(src+offset_src_c,4);
v2st_src_c1=VLOAD(src+offset_src_c+4,2);
v4st_src_n=VLOAD(src+offset_src_n,4);
}
else
{
int y_idx_p,y_idx_c,y_idx_n;
y_idx_p=TOP_BORDER_IDX(gy-1);
y_idx_c=gy;
y_idx_n=BOTTOM_BORDER_IDX(gy+1,height);
offset_src_p=mad24(y_idx_p,istep,x_idx+ksh);
offset_src_c=mad24(y_idx_c,istep,x_idx);
offset_src_n=mad24(y_idx_n,istep,x_idx+ksh);
#if BORDER_CONSTANT
V4St v4st_border_value=(V4St)border_value.val[0];
v4st_src_p=(y_idx_p<0)?(V4St)v4st_border_value:VLOAD(src+offset_src_p,4);
v4st_src_c0=VLOAD(src+offset_src_c,4);
v2st_src_c1=VLOAD(src+offset_src_c+4,2);
v4st_src_n=(y_idx_n<0)?(V4St)v4st_border_value:VLOAD(src+offset_src_n,4);
#else
v4st_src_p=VLOAD(src+offset_src_p,4);
v4st_src_c0=VLOAD(src+offset_src_c,4);
v2st_src_c1=VLOAD(src+offset_src_c+4,2);
v4st_src_n=VLOAD(src+offset_src_n,4);
#endif
}
v4st_src_cx0=v4st_src_c0;
v4st_src_cx1=(V4St)(v4st_src_c0.s123,v2st_src_c1.s0);
v4st_src_cx2=(V4St)(v4st_src_c0.s23,v2st_src_c1);
v4f32_scale=(float4)scale_index;
v4f32_sum_weight=(float4)(0.0f,0.f,0.f,0.f);
v4f32_sum=(float4)(0.0f,0.f,0.f,0.f);
v4f32_alpha=BILATERAL_ABS_CONVERT_F32(v4st_src_p,v4st_src_cx1,float4)*v4f32_scale;
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
v4f32_weight_cur=space_weight[0]*v4f32_color_weight;
v4f32_sum_weight+=v4f32_weight_cur;
v4f32_sum+=CONVERT(v4st_src_p,float4)*v4f32_weight_cur;
v4f32_alpha=BILATERAL_ABS_CONVERT_F32(v4st_src_cx0,v4st_src_cx1,float4)*v4f32_scale;
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
v4f32_weight_cur=space_weight[1]*v4f32_color_weight;
v4f32_sum_weight+=v4f32_weight_cur;
v4f32_sum+=CONVERT(v4st_src_cx0,float4)*v4f32_weight_cur;
v4f32_color_weight=(float4)(READ_IMAGE(float)(color_weight,sampler,(int2)(0,0)).s0);
v4f32_weight_cur=space_weight[2]*v4f32_color_weight;
v4f32_sum_weight+=v4f32_weight_cur;
v4f32_sum+=CONVERT(v4st_src_cx1,float4)*v4f32_weight_cur;
v4f32_alpha=BILATERAL_ABS_CONVERT_F32(v4st_src_cx2,v4st_src_cx1,float4)*v4f32_scale;
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
v4f32_weight_cur=space_weight[3]*v4f32_color_weight;
v4f32_sum_weight+=v4f32_weight_cur;
v4f32_sum+=CONVERT(v4st_src_cx2,float4)*v4f32_weight_cur;
v4f32_alpha=BILATERAL_ABS_CONVERT_F32(v4st_src_n,v4st_src_cx1,float4)*v4f32_scale;
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
v4f32_weight_cur=space_weight[4]*v4f32_color_weight;
v4f32_sum_weight+=v4f32_weight_cur;
v4f32_sum+=CONVERT(v4st_src_n,float4)*v4f32_weight_cur;
v4dt_result=BILATERAL_CONVERT_ROUND(v4f32_sum/v4f32_sum_weight,V4Dt);
offset_dst=mad24(gy,ostep,x_idx+ksh);
VSTORE(v4dt_result,dst+offset_dst,4);
}

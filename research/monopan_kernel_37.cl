kernel void BilateralRemain3x3C3(global St*src,int istep,
global Dt*dst,int ostep,
int width,int height,
int x_work_size,int y_work_size,
constant float*space_weight MAX_CONSTANT_SIZE,
read_only image2d_t color_weight,int color_len,
float scale_index,int main_width,
struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
int ksh=1;
int channel=3;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int x_idx_l,x_idx_c,x_idx_r;
int y_idx_p,y_idx_c,y_idx_n;
int offset_dst;
St*src_row_p,*src_row_c,*src_row_n;
St st_src_p,st_src_n;
V3St v3st_src_px1,v3st_src_cx0,v3st_src_cx1,v3st_src_cx2,v3st_src_nx1;
float f32_sum_weight,f32_alpha,f32_idx,f32_color_weight,f32_weight_cur,f32_tmp;
int s32_idx;
float3 v3f32_sum,v3f32_absdiff;
V3Dt v3dt_result;
y_idx_c=gy;
y_idx_p=TOP_BORDER_IDX(gy-1);
y_idx_n=BOTTOM_BORDER_IDX(gy+1,height);
x_idx_c=(gx>=ksh)*main_width+gx;
x_idx_l=LEFT_BORDER_IDX(x_idx_c-1)*channel;
x_idx_r=RIGHT_BORDER_IDX(x_idx_c+1,width)*channel;
x_idx_c*=channel;
src_row_p=src+mad24(y_idx_p,istep,x_idx_c);
src_row_c=src+mad24(y_idx_c,istep,x_idx_c);
src_row_n=src+mad24(y_idx_n,istep,x_idx_c);
#if BORDER_CONSTANT
V3St v3st_border_value=(V3St)(border_value.val[0],border_value.val[1],border_value.val[2]);
v3st_src_px1=(y_idx_p<0)?v3st_border_value:VLOAD(src_row_p,3);
v3st_src_cx0=(x_idx_l<0)?v3st_border_value:VLOAD(src_row_c+x_idx_l-x_idx_c,3);
v3st_src_cx1=VLOAD(src_row_c,3);
v3st_src_cx2=(x_idx_r<0)?v3st_border_value:VLOAD(src_row_c+x_idx_r-x_idx_c,3);
v3st_src_nx1=(y_idx_n<0)?v3st_border_value:VLOAD(src_row_n,3);
#else
x_idx_l-=x_idx_c;
x_idx_r-=x_idx_c;
v3st_src_px1=VLOAD(src_row_p,3);
v3st_src_cx0=VLOAD(src_row_c+x_idx_l,3);
v3st_src_cx1=VLOAD(src_row_c,3);
v3st_src_cx2=VLOAD(src_row_c+x_idx_r,3);
v3st_src_nx1=VLOAD(src_row_n,3);
#endif
f32_sum_weight=0.0f;
v3f32_sum=(float3)(0.0f);
v3f32_absdiff=BILATERAL_ABS_CONVERT_F32(v3st_src_px1,v3st_src_cx1,float3);
f32_alpha=(v3f32_absdiff.s0+v3f32_absdiff.s1+v3f32_absdiff.s2)*scale_index;
f32_idx=floor(f32_alpha);
s32_idx=BILATERAL_CONVERT_CLAMP(f32_idx,int1,0,color_len-2);
f32_tmp=READ_IMAGE(float)(color_weight,sampler,(int2)(s32_idx,0)).s0;
#if IS_UCHAR(St)
f32_color_weight=f32_tmp;
#else
f32_alpha-=f32_idx;
f32_color_weight=f32_tmp+f32_alpha*(READ_IMAGE(float)(color_weight,sampler,(int2)(s32_idx+1,0)).s0-f32_tmp);
#endif
f32_weight_cur=space_weight[0]*f32_color_weight;
f32_sum_weight+=f32_weight_cur;
v3f32_sum.s0+=(float)v3st_src_px1.s0*f32_weight_cur;
v3f32_sum.s1+=(float)v3st_src_px1.s1*f32_weight_cur;
v3f32_sum.s2+=(float)v3st_src_px1.s2*f32_weight_cur;
v3f32_absdiff=BILATERAL_ABS_CONVERT_F32(v3st_src_cx0,v3st_src_cx1,float3);
f32_alpha=(v3f32_absdiff.s0+v3f32_absdiff.s1+v3f32_absdiff.s2)*scale_index;
f32_idx=floor(f32_alpha);
s32_idx=BILATERAL_CONVERT_CLAMP(f32_idx,int1,0,color_len-2);
f32_tmp=READ_IMAGE(float)(color_weight,sampler,(int2)(s32_idx,0)).s0;
#if IS_UCHAR(St)
f32_color_weight=f32_tmp;
#else
f32_alpha-=f32_idx;
f32_color_weight=f32_tmp+f32_alpha*(READ_IMAGE(float)(color_weight,sampler,(int2)(s32_idx+1,0)).s0-f32_tmp);
#endif
f32_weight_cur=space_weight[1]*f32_color_weight;
f32_sum_weight+=f32_weight_cur;
v3f32_sum.s0+=(float)v3st_src_cx0.s0*f32_weight_cur;
v3f32_sum.s1+=(float)v3st_src_cx0.s1*f32_weight_cur;
v3f32_sum.s2+=(float)v3st_src_cx0.s2*f32_weight_cur;
f32_weight_cur=space_weight[2]*READ_IMAGE(float)(color_weight,sampler,(int2)(0,0)).s0;
f32_sum_weight+=f32_weight_cur;
v3f32_sum.s0+=(float)v3st_src_cx1.s0*f32_weight_cur;
v3f32_sum.s1+=(float)v3st_src_cx1.s1*f32_weight_cur;
v3f32_sum.s2+=(float)v3st_src_cx1.s2*f32_weight_cur;
v3f32_absdiff=BILATERAL_ABS_CONVERT_F32(v3st_src_cx2,v3st_src_cx1,float3);
f32_alpha=(v3f32_absdiff.s0+v3f32_absdiff.s1+v3f32_absdiff.s2)*scale_index;
f32_idx=floor(f32_alpha);
s32_idx=BILATERAL_CONVERT_CLAMP(f32_idx,int1,0,color_len-2);
f32_tmp=READ_IMAGE(float)(color_weight,sampler,(int2)(s32_idx,0)).s0;
#if IS_UCHAR(St)
f32_color_weight=f32_tmp;
#else
f32_alpha-=f32_idx;
f32_color_weight=f32_tmp+f32_alpha*(READ_IMAGE(float)(color_weight,sampler,(int2)(s32_idx+1,0)).s0-f32_tmp);
#endif
f32_weight_cur=space_weight[3]*f32_color_weight;
f32_sum_weight+=f32_weight_cur;
v3f32_sum.s0+=(float)v3st_src_cx2.s0*f32_weight_cur;
v3f32_sum.s1+=(float)v3st_src_cx2.s1*f32_weight_cur;
v3f32_sum.s2+=(float)v3st_src_cx2.s2*f32_weight_cur;
v3f32_absdiff=BILATERAL_ABS_CONVERT_F32(v3st_src_nx1,v3st_src_cx1,float3);
f32_alpha=(v3f32_absdiff.s0+v3f32_absdiff.s1+v3f32_absdiff.s2)*scale_index;
f32_idx=floor(f32_alpha);
s32_idx=BILATERAL_CONVERT_CLAMP(f32_idx,int1,0,color_len-2);
f32_tmp=READ_IMAGE(float)(color_weight,sampler,(int2)(s32_idx,0)).s0;
#if IS_UCHAR(St)
f32_color_weight=f32_tmp;
#else
f32_alpha-=f32_idx;
f32_color_weight=f32_tmp+f32_alpha*(READ_IMAGE(float)(color_weight,sampler,(int2)(s32_idx+1,0)).s0-f32_tmp);
#endif
f32_weight_cur=space_weight[4]*f32_color_weight;
f32_sum_weight+=f32_weight_cur;
v3f32_sum.s0+=(float)v3st_src_nx1.s0*f32_weight_cur;
v3f32_sum.s1+=(float)v3st_src_nx1.s1*f32_weight_cur;
v3f32_sum.s2+=(float)v3st_src_nx1.s2*f32_weight_cur;
v3dt_result=BILATERAL_CONVERT_ROUND(v3f32_sum/(float3)f32_sum_weight,V3Dt);
offset_dst=mad24(y_idx_c,ostep,x_idx_c);
VSTORE(v3dt_result,dst+offset_dst,3);
}

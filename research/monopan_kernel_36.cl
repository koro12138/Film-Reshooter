kernel void BilateralRemain3x3C1(global St*src,int istep,
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
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int x_idx_l,x_idx_c,x_idx_r;
int y_idx_p,y_idx_c,y_idx_n;
int offset_dst;
St*src_row_p,*src_row_c,*src_row_n;
St st_src_p,st_src_n;
V3St v3st_src_c;
float f32_alpha,f32_idx;
int s32_idx;
float f32_color_weight;
float f32_weight_cur,f32_sum_weight,f32_sum;
Dt dt_result;
y_idx_c=gy;
y_idx_p=TOP_BORDER_IDX(gy-1);
y_idx_n=BOTTOM_BORDER_IDX(gy+1,height);
x_idx_c=(gx>=ksh)*main_width+gx;
x_idx_l=LEFT_BORDER_IDX(x_idx_c-1);
x_idx_r=RIGHT_BORDER_IDX(x_idx_c+1,width);
src_row_p=src+mad24(y_idx_p,istep,x_idx_c);
src_row_c=src+mad24(y_idx_c,istep,x_idx_c);
src_row_n=src+mad24(y_idx_n,istep,x_idx_c);
#if BORDER_CONSTANT
St value=(St)border_value.val[0];
st_src_p=(y_idx_p<0)?value:src_row_p[0];
v3st_src_c.s0=(x_idx_l<0)?value:src_row_c[x_idx_l-x_idx_c];
v3st_src_c.s1=src_row_c[0];
v3st_src_c.s2=(x_idx_r<0)?value:src_row_c[x_idx_r-x_idx_c];
st_src_n=(y_idx_n<0)?value:src_row_n[0];
#else
x_idx_l-=x_idx_c;
x_idx_r-=x_idx_c;
st_src_p=src_row_p[0];
v3st_src_c.s0=src_row_c[x_idx_l],v3st_src_c.s1=src_row_c[0],v3st_src_c.s2=src_row_c[x_idx_r];
st_src_n=src_row_n[0];
#endif
f32_sum_weight=0.0f;
f32_sum=0.0f;
f32_alpha=BILATERAL_ABS_CONVERT_F32(st_src_p,v3st_src_c.s1,float1)*scale_index;
f32_idx=floor(f32_alpha);
s32_idx=BILATERAL_CONVERT_CLAMP(f32_idx,int1,0,color_len-2);
#if IS_UCHAR(St)
f32_color_weight=READ_IMAGE(float)(color_weight,sampler,(int2)(s32_idx,0)).s0;
#else
f32_alpha-=f32_idx;
f32_color_weight=READ_IMAGE(float)(color_weight,sampler,(int2)(s32_idx,0)).s0+f32_alpha*(
READ_IMAGE(float)(color_weight,sampler,(int2)(s32_idx+1,0)).s0-
READ_IMAGE(float)(color_weight,sampler,(int2)(s32_idx,0)).s0);
#endif
f32_weight_cur=space_weight[0]*f32_color_weight;
f32_sum_weight+=f32_weight_cur;
f32_sum+=(float)st_src_p*f32_weight_cur;
f32_alpha=BILATERAL_ABS_CONVERT_F32(v3st_src_c.s0,v3st_src_c.s1,float1)*scale_index;
f32_idx=floor(f32_alpha);
s32_idx=BILATERAL_CONVERT_CLAMP(f32_idx,int1,0,color_len-2);
#if IS_UCHAR(St)
f32_color_weight=READ_IMAGE(float)(color_weight,sampler,(int2)(s32_idx,0)).s0;
#else
f32_alpha-=f32_idx;
f32_color_weight=READ_IMAGE(float)(color_weight,sampler,(int2)(s32_idx,0)).s0+f32_alpha*(
READ_IMAGE(float)(color_weight,sampler,(int2)(s32_idx+1,0)).s0-
READ_IMAGE(float)(color_weight,sampler,(int2)(s32_idx,0)).s0);
#endif
f32_weight_cur=space_weight[1]*f32_color_weight;
f32_sum_weight+=f32_weight_cur;
f32_sum+=(float)(v3st_src_c.s0)*f32_weight_cur;
f32_weight_cur=space_weight[2]*READ_IMAGE(float)(color_weight,sampler,(int2)(0,0)).s0;
f32_sum_weight+=f32_weight_cur;
f32_sum+=(float)(v3st_src_c.s1)*f32_weight_cur;
f32_alpha=BILATERAL_ABS_CONVERT_F32(v3st_src_c.s2,v3st_src_c.s1,float1)*scale_index;
f32_idx=floor(f32_alpha);
s32_idx=BILATERAL_CONVERT_CLAMP(f32_idx,int1,0,color_len-2);
#if IS_UCHAR(St)
f32_color_weight=READ_IMAGE(float)(color_weight,sampler,(int2)(s32_idx,0)).s0;
#else
f32_alpha-=f32_idx;
f32_color_weight=READ_IMAGE(float)(color_weight,sampler,(int2)(s32_idx,0)).s0+f32_alpha*(
READ_IMAGE(float)(color_weight,sampler,(int2)(s32_idx+1,0)).s0-
READ_IMAGE(float)(color_weight,sampler,(int2)(s32_idx,0)).s0);
#endif
f32_weight_cur=space_weight[3]*f32_color_weight;
f32_sum_weight+=f32_weight_cur;
f32_sum+=(float)(v3st_src_c.s2)*f32_weight_cur;
f32_alpha=BILATERAL_ABS_CONVERT_F32(st_src_n,v3st_src_c.s1,float1)*scale_index;
f32_idx=floor(f32_alpha);
s32_idx=BILATERAL_CONVERT_CLAMP(f32_idx,int1,0,color_len-2);
#if IS_UCHAR(St)
f32_color_weight=READ_IMAGE(float)(color_weight,sampler,(int2)(s32_idx,0)).s0;
#else
f32_alpha-=f32_idx;
f32_color_weight=READ_IMAGE(float)(color_weight,sampler,(int2)(s32_idx,0)).s0+f32_alpha*(
READ_IMAGE(float)(color_weight,sampler,(int2)(s32_idx+1,0)).s0-
READ_IMAGE(float)(color_weight,sampler,(int2)(s32_idx,0)).s0);
#endif
f32_weight_cur=space_weight[3]*f32_color_weight;
f32_sum_weight+=f32_weight_cur;
f32_sum+=(float)(st_src_n)*f32_weight_cur;
dt_result=BILATERAL_CONVERT_ROUND(f32_sum/f32_sum_weight,Dt);
offset_dst=mad24(y_idx_c,ostep,x_idx_c);
dst[offset_dst]=dt_result;
}

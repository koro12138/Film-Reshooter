kernel void Contrast(global uchar*src,int src_step,global uchar*dst,int dst_step,constant float*gamma MAX_CONSTANT_SIZE,
int gamma_size,int height,int width,int y_work_size,int x_work_size)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int x_elem_counts=8;
int x_idx=gx*x_elem_counts;
float scale=(gamma_size-1)/255.0;
float8 v8f32_pixel=(float8)0.0;
uchar8 v8u8_pixel_int=(uchar8)0;
float8 v8f32_pixel_frac=(float8)0.0;
uchar8 v8u8_res=(uchar8)0;
if(gx==x_work_size-1)
{
x_idx=width-x_elem_counts;
}
{
int idx_src=mad24(gy,src_step,x_idx);
uchar8 v8u8_src=vload8(0,src+idx_src);
v8f32_pixel=convert_float8(v8u8_src)*scale;
v8u8_pixel_int=convert_uchar8_sat(v8f32_pixel);
v8f32_pixel_frac=v8f32_pixel-convert_float8(v8u8_pixel_int);
float8 gamma0=(float8)(gamma[v8u8_pixel_int.s0],gamma[v8u8_pixel_int.s1],gamma[v8u8_pixel_int.s2],gamma[v8u8_pixel_int.s3],
gamma[v8u8_pixel_int.s4],gamma[v8u8_pixel_int.s5],gamma[v8u8_pixel_int.s6],gamma[v8u8_pixel_int.s7]);
float8 gamma1=(float8)(gamma[min(v8u8_pixel_int.s0+1,gamma_size-1)],gamma[min(v8u8_pixel_int.s1+1,gamma_size-1)],
gamma[min(v8u8_pixel_int.s2+1,gamma_size-1)],gamma[min(v8u8_pixel_int.s3+1,gamma_size-1)],
gamma[min(v8u8_pixel_int.s4+1,gamma_size-1)],gamma[min(v8u8_pixel_int.s5+1,gamma_size-1)],
gamma[min(v8u8_pixel_int.s6+1,gamma_size-1)],gamma[min(v8u8_pixel_int.s7+1,gamma_size-1)]);
v8u8_res=convert_uchar8_sat((gamma0+(gamma1-gamma0)*v8f32_pixel_frac)*255.0f+0.5f);
int idx_dst=mad24(gy,dst_step,x_idx);
vstore8(v8u8_res,0,dst+idx_dst);
}
}

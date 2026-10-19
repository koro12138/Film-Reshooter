kernel void SimulateResize(global uchar*src,int src_step,
global uchar*pixel_map,int pixel_step,
global ushort*batch_map,int batch_step,
global uchar*lut,int lut_step,
global uchar*rand_map_pixel,int rand_map_pixel_step,
global uchar*dst,int dst_step,
int height,int width,
int y_work_size,int x_work_size)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int x_elem_counts=8;
int x_idx=gx*x_elem_counts;
if(gx==x_work_size-1)
{
x_idx=width-x_elem_counts;
}
{
int idx_src=mad24(gy,src_step,x_idx);
uchar8 v8u8_src=vload8(0,src+idx_src);
uchar8 v8u8_pixel_map=(uchar8)(0);
ushort8 v8u16_batch_map=(ushort8)(0);
uchar8 v8u8_lut=(uchar8)(0);
int idx_rand1=mad24(gy%4096,rand_map_pixel_step,x_idx%3072);
v8u8_pixel_map.s0=pixel_map[mad24(convert_int(v8u8_src.s0),pixel_step,rand_map_pixel[idx_rand1])];
v8u8_pixel_map.s1=pixel_map[mad24(convert_int(v8u8_src.s1),pixel_step,rand_map_pixel[idx_rand1+1])];
v8u8_pixel_map.s2=pixel_map[mad24(convert_int(v8u8_src.s2),pixel_step,rand_map_pixel[idx_rand1+2])];
v8u8_pixel_map.s3=pixel_map[mad24(convert_int(v8u8_src.s3),pixel_step,rand_map_pixel[idx_rand1+3])];
v8u8_pixel_map.s4=pixel_map[mad24(convert_int(v8u8_src.s4),pixel_step,rand_map_pixel[idx_rand1+4])];
v8u8_pixel_map.s5=pixel_map[mad24(convert_int(v8u8_src.s5),pixel_step,rand_map_pixel[idx_rand1+5])];
v8u8_pixel_map.s6=pixel_map[mad24(convert_int(v8u8_src.s6),pixel_step,rand_map_pixel[idx_rand1+6])];
v8u8_pixel_map.s7=pixel_map[mad24(convert_int(v8u8_src.s7),pixel_step,rand_map_pixel[idx_rand1+7])];
int idx_rand2=mad24((y_work_size-1-gy)%4096,rand_map_pixel_step,(width-1-x_idx)%3072);
v8u16_batch_map.s0=batch_map[mad24(convert_int(v8u8_pixel_map.s0),pixel_step,rand_map_pixel[idx_rand2])];
v8u16_batch_map.s1=batch_map[mad24(convert_int(v8u8_pixel_map.s1),pixel_step,rand_map_pixel[idx_rand2-1])];
v8u16_batch_map.s2=batch_map[mad24(convert_int(v8u8_pixel_map.s2),pixel_step,rand_map_pixel[idx_rand2-2])];
v8u16_batch_map.s3=batch_map[mad24(convert_int(v8u8_pixel_map.s3),pixel_step,rand_map_pixel[idx_rand2-3])];
v8u16_batch_map.s4=batch_map[mad24(convert_int(v8u8_pixel_map.s4),pixel_step,rand_map_pixel[idx_rand2-4])];
v8u16_batch_map.s5=batch_map[mad24(convert_int(v8u8_pixel_map.s5),pixel_step,rand_map_pixel[idx_rand2-5])];
v8u16_batch_map.s6=batch_map[mad24(convert_int(v8u8_pixel_map.s6),pixel_step,rand_map_pixel[idx_rand2-6])];
v8u16_batch_map.s7=batch_map[mad24(convert_int(v8u8_pixel_map.s7),pixel_step,rand_map_pixel[idx_rand2-7])];
float8 v8f32_lut=(float8)(lut[v8u16_batch_map.s0],lut[v8u16_batch_map.s1],lut[v8u16_batch_map.s2],lut[v8u16_batch_map.s3],
lut[v8u16_batch_map.s4],lut[v8u16_batch_map.s5],lut[v8u16_batch_map.s6],lut[v8u16_batch_map.s7]);
v8u8_lut=convert_uchar8_sat(v8f32_lut*sqrt(convert_float8(v8u8_src)/255.0f)*16.0f+0.5f);
int idx_dst=mad24(gy,dst_step,x_idx);
vstore8(v8u8_lut,0,dst+idx_dst);
}
}

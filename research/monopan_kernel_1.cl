kernel void OutputMix(global uchar*src,int src_step,global uchar*dst,int dst_step,float ratio,int height,
int width,int y_work_size,int x_work_size)
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
int idx_dst=mad24(gy,dst_step,x_idx);
uchar8 v8u8_src=vload8(0,src+idx_src);
uchar8 v8u8_dst=vload8(0,dst+idx_dst);
uchar8 v8u8_res=convert_uchar8_sat(convert_float8(v8u8_dst)*ratio+convert_float8(v8u8_src)*(1-ratio));
vstore8(v8u8_res,0,dst+idx_dst);
}
}

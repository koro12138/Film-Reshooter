kernel void IdftColProcess(global float*src,int istep,
global uchar*param_buffer,int param_pitch,
global Dt*dst,int ostep,
local float*local_buffer,
local float*local_exp,
int width,int height)
{
int local_size=get_local_size(1);
int local_id=get_local_id(1);
int half_height=height/2;
int gx=get_global_id(0);
if(gx>=width)
{
return;
}
global ushort*idx_data=(global ushort*)(param_buffer+param_pitch);
global float*exp_data=(global float*)(idx_data+height);
for(int tid=local_id;tid<height;tid+=local_size)
{
local_exp[tid]=exp_data[tid];
}
for(int tid=local_id;tid<height;tid+=local_size)
{
global float*src_row=src+tid*istep;
int st_idx=idx_data[tid];
float2 v2f32_src=vload2(gx,src_row);
vstore2(v2f32_src,st_idx,local_buffer);
}
barrier(CLK_LOCAL_MEM_FENCE);
for(int tid=local_id;tid<half_height;tid+=local_size)
{
float4 v4f32_x0x1=vload4(tid,local_buffer);
float4 v4f32_y0y1=(float4)(v4f32_x0x1.lo+v4f32_x0x1.hi,v4f32_x0x1.lo-v4f32_x0x1.hi);
vstore4(v4f32_y0y1,tid,local_buffer);
}
barrier(CLK_LOCAL_MEM_FENCE);
for(int size=4;size<=height;size*=2)
{
int half_size=(size>>1);
int table_step=height*native_recip(size);
for(int tid=local_id;tid<half_height;tid+=local_size)
{
int block_id=tid*native_recip(half_size);
int block_offset=tid&(half_size-1);
int x0_idx=mad24(block_id,size,block_offset);
int x1_idx=x0_idx+half_size;
int w_idx=block_offset*table_step;
float2 v2f32_x0=vload2(x0_idx,local_buffer);
float2 v2f32_x1=vload2(x1_idx,local_buffer);
float2 v2f32_w=vload2(w_idx,local_exp);
float2 v2f32_temp=MulComplex(v2f32_x1,v2f32_w);
float2 v2f32_y0=v2f32_x0+v2f32_temp;
float2 v2f32_y1=v2f32_x0-v2f32_temp;
vstore2(v2f32_y0,x0_idx,local_buffer);
vstore2(v2f32_y1,x1_idx,local_buffer);
}
barrier(CLK_LOCAL_MEM_FENCE);
}
float2 v2f32_scale=(float2)(height,height);
for(int tid=local_id;tid<height;tid+=local_size)
{
global float*src_row=src+tid*istep;
global Dt*dst_row=dst+tid*ostep;
float2 v2f32_data=vload2(tid,local_buffer);
#if WITH_SCALE
v2f32_data=native_divide(v2f32_data,v2f32_scale);
#endif
V2Dt v2dt_data=IDFT_CONVERT(v2f32_data,V2Dt);
#if IS_DST_C1
vstore1(v2dt_data.s0,gx,dst_row);
#else
vstore2(v2dt_data,gx,dst_row);
#endif
}
}

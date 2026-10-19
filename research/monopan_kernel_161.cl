kernel void IdftRowProcess(global float*src,int istep,
global float*dst,int ostep,
global uchar*param_buffer,int param_pitch,
local float*local_buffer,
local float*local_exp,
int width,int height)
{
int local_size=get_local_size(0);
int local_id=get_local_id(0);
int gy=get_global_id(1);
int half_width=width/2;
if(gy>=height)
{
return;
}
global float*src_row=src+gy*istep;
global float*dst_row=dst+gy*ostep;
global ushort*idx_data=(global ushort*)(param_buffer);
global float*exp_data=(global float*)(idx_data+width);
for(int tid=local_id;tid<width;tid+=local_size)
{
local_exp[tid]=exp_data[tid];
}
for(int tid=local_id;tid<width;tid+=local_size)
{
int st_idx=idx_data[tid];
float2 v2f32_data=vload2(tid,src_row);
vstore2(v2f32_data,st_idx,local_buffer);
}
barrier(CLK_LOCAL_MEM_FENCE);
for(int tid=local_id;tid<half_width;tid+=local_size)
{
float4 v4f32_x0x1=vload4(tid,local_buffer);
float4 v4f32_y0y1=(float4)(v4f32_x0x1.lo+v4f32_x0x1.hi,v4f32_x0x1.lo-v4f32_x0x1.hi);
vstore4(v4f32_y0y1,tid,local_buffer);
}
barrier(CLK_LOCAL_MEM_FENCE);
float4 v4f32_w0w1=(float4)(1.0f,0.0f,vload2(width/4,local_exp));
for(int tid=local_id;tid<width/4;tid+=local_size)
{
float8 v8f32_x0x1x2x3=vload8(tid,local_buffer);
float4 v4f32_temp=MulComplex2(v4f32_w0w1,v8f32_x0x1x2x3.hi);
float8 v8f32_result=(float8)(v8f32_x0x1x2x3.lo+v4f32_temp,v8f32_x0x1x2x3.lo-v4f32_temp);
vstore8(v8f32_result,tid,local_buffer);
}
barrier(CLK_LOCAL_MEM_FENCE);
for(int size=8;size<width;size=(size<<1))
{
int half_size=(size>>1);
int table_step=width*native_recip(size);
for(int tid=local_id;tid<half_width;tid+=local_size)
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
vstore2(v2f32_x0+v2f32_temp,x0_idx,local_buffer);
vstore2(v2f32_x0-v2f32_temp,x1_idx,local_buffer);
}
barrier(CLK_LOCAL_MEM_FENCE);
}
{
int hhalf_width=half_width/2;
for(int tid=local_id;tid<hhalf_width;tid+=local_size)
{
float4 v4f32_x0x1=vload4(tid,local_buffer);
float4 v4f32_x2x3=vload4(tid+hhalf_width,local_buffer);
float4 v4f32_w0w1=vload4(tid,local_exp);
float4 v4f32_temp=MulComplex2(v4f32_x2x3,v4f32_w0w1);
vstore4(v4f32_x0x1+v4f32_temp,tid,local_buffer);
vstore4(v4f32_x0x1-v4f32_temp,tid+hhalf_width,local_buffer);
}
barrier(CLK_LOCAL_MEM_FENCE);
}
float2 v2f32_scale=(float2)(width,width);
for(int tid=local_id;tid<width;tid+=local_size)
{
float2 v2f32_data=vload2(tid,local_buffer);
#if WITH_SCALE
v2f32_data=native_divide(v2f32_data,v2f32_scale);
#endif
vstore2(v2f32_data,tid,dst_row);
}
}

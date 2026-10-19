inline void RowDft1x16(float8 v8f32_src0,float8 v8f32_src1,float8 v8f32_exp_table0,float8 v8f32_exp_table1,local float*local_data)
{
ROW_DFT_BUTTERFLY_1X16(v8f32_src0,v8f32_src1);
float8 v8f32_conj0=v8f32_src0.s07654321;
float8 v8f32_conj1=v8f32_src1.s07654321*(-1.0f);
float8 v8f32_fk0=(v8f32_src0+v8f32_conj0)*0.5f;
float8 v8f32_fk1=(v8f32_src1+v8f32_conj1)*0.5f;
float8 v8f32_temp0=v8f32_conj0-v8f32_src0;
float8 v8f32_temp1=v8f32_conj1-v8f32_src1;
float8 v8f32_gk0=v8f32_temp1*(-0.5f);
float8 v8f32_gk1=v8f32_temp0*(0.5f);
v8f32_temp0=v8f32_gk0*v8f32_exp_table0-v8f32_gk1*v8f32_exp_table1;
v8f32_temp1=v8f32_gk1*v8f32_exp_table0+v8f32_gk0*v8f32_exp_table1;
float8 v8f32_dst0=v8f32_fk0+v8f32_temp0;
float8 v8f32_dst1=v8f32_fk1+v8f32_temp1;
float8 v8f32_dst2=v8f32_dst0.s07654321;
float8 v8f32_dst3=v8f32_dst1.s07654321*(-1.0f);
v8f32_dst2.s0=v8f32_fk0.s0-v8f32_gk0.s0;
v8f32_dst3.s0=0.0f;
float16 v16f32_dst0,v16f32_dst1;
v16f32_dst0.even=v8f32_dst0;
v16f32_dst0.odd=v8f32_dst1;
v16f32_dst1.even=v8f32_dst2;
v16f32_dst1.odd=v8f32_dst3;
VSTORE(v16f32_dst0,local_data,16);
VSTORE(v16f32_dst1,local_data+16,16);
}
#define GRID_LEN (16)
kernel void GridDft16x16(global Tp*src,int istep,
global float*dst,int ostep,
constant float*param MAX_CONSTANT_SIZE,
local float*local_buffer,
int width,int height)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
int offset_x=gx<<4;
int offset_y=gy<<1;
if(offset_x>=width||offset_y>=height)
{
return;
}
int group_x=get_group_id(0);
int group_y=get_group_id(1);
int local_id_x=get_local_id(0);
int local_id_y=get_local_id(1);
int local_y_shift=local_id_y<<1;
int2 src_index=mad24(offset_y+(int2)(0,1),istep,offset_x);
const int half_grid=GRID_LEN>>1;
const int local_step=GRID_LEN<<1;
float16 v16f32_exp_table=VLOAD(param,16);
float8 v8f32_exp_table0=v16f32_exp_table.even;
float8 v8f32_exp_table1=v16f32_exp_table.odd;
int y_index[16]={0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};
int2 v2s32_y_idx=(int2)(y_index[local_y_shift],y_index[local_y_shift+1]);
int2 local_index=mad24(v2s32_y_idx,local_step,local_id_x);
float8 v8f32_src00,v8f32_src01,v8f32_src10,v8f32_src11;
{
float16 v16f32_tmp_src0=CONVERT(VLOAD(src+src_index.s0,16),float16);
float16 v16f32_tmp_src1=CONVERT(VLOAD(src+src_index.s1,16),float16);
uint8 v8u32_idx_mask=(uint8)(0,4,2,6,1,5,3,7);
uint8 v8u32_even_mask=v8u32_idx_mask<<1;
uint8 v8u32_odd_mask=v8u32_even_mask+1;
v8f32_src00=shuffle(v16f32_tmp_src0,v8u32_even_mask);
v8f32_src01=shuffle(v16f32_tmp_src0,v8u32_odd_mask);
v8f32_src10=shuffle(v16f32_tmp_src1,v8u32_even_mask);
v8f32_src11=shuffle(v16f32_tmp_src1,v8u32_odd_mask);
}
RowDft1x16(v8f32_src00,v8f32_src01,v8f32_exp_table0,v8f32_exp_table1,local_buffer+local_index.s0);
RowDft1x16(v8f32_src10,v8f32_src11,v8f32_exp_table0,v8f32_exp_table1,local_buffer+local_index.s1);
barrier(CLK_LOCAL_MEM_FENCE);
v2s32_y_idx=(int2)(local_y_shift,local_y_shift+1);
local_index=mad24(v2s32_y_idx,local_step,local_id_x);
float16 v16f32_src0,v16f32_src1,v16f32_temp;
v16f32_src0=VLOAD(local_buffer+local_index.s0,16);
v16f32_src1=VLOAD(local_buffer+local_index.s1,16);
v16f32_temp=v16f32_src1;
v16f32_src1=v16f32_src0-v16f32_temp;
v16f32_src0=v16f32_src0+v16f32_temp;
VSTORE(v16f32_src0,local_buffer+local_index.s0,16);
VSTORE(v16f32_src1,local_buffer+local_index.s1,16);
v16f32_src0=VLOAD(local_buffer+local_index.s0+16,16);
v16f32_src1=VLOAD(local_buffer+local_index.s1+16,16);
v16f32_temp=v16f32_src1;
v16f32_src1=v16f32_src0-v16f32_temp;
v16f32_src0=v16f32_src0+v16f32_temp;
VSTORE(v16f32_src0,local_buffer+local_index.s0+16,16);
VSTORE(v16f32_src1,local_buffer+local_index.s1+16,16);
barrier(CLK_LOCAL_MEM_FENCE);
#pragma unroll
for(int size=4;size<GRID_LEN;size*=2)
{
int half_size=(size>>1);
int table_step=GRID_LEN*native_recip(size);
int tid=local_id_y;
int block_id=tid*native_recip(half_size);
int block_offset=tid&(half_size-1);
int y0_idx=mad24(block_id,size,block_offset);
int y1_idx=y0_idx+half_size;
int w_idx=block_offset*table_step*2;
v16f32_src0=VLOAD(local_buffer+y0_idx*local_step,16);
v16f32_src1=VLOAD(local_buffer+y1_idx*local_step,16);
v16f32_temp.even=v16f32_src1.even*param[w_idx]-v16f32_src1.odd*param[w_idx+1];
v16f32_temp.odd=v16f32_src1.odd*param[w_idx]+v16f32_src1.even*param[w_idx+1];
v16f32_src1=v16f32_src0-v16f32_temp;
v16f32_src0=v16f32_src0+v16f32_temp;
VSTORE(v16f32_src0,local_buffer+y0_idx*local_step,16);
VSTORE(v16f32_src1,local_buffer+y1_idx*local_step,16);
v16f32_src0=VLOAD(local_buffer+y0_idx*local_step+16,16);
v16f32_src1=VLOAD(local_buffer+y1_idx*local_step+16,16);
v16f32_temp.even=v16f32_src1.even*param[w_idx]-v16f32_src1.odd*param[w_idx+1];
v16f32_temp.odd=v16f32_src1.odd*param[w_idx]+v16f32_src1.even*param[w_idx+1];
v16f32_src1=v16f32_src0-v16f32_temp;
v16f32_src0=v16f32_src0+v16f32_temp;
VSTORE(v16f32_src0,local_buffer+y0_idx*local_step+16,16);
VSTORE(v16f32_src1,local_buffer+y1_idx*local_step+16,16);
barrier(CLK_LOCAL_MEM_FENCE);
}
{
int dst_y=group_y*GRID_LEN+local_id_y;
int dst_x=group_x*GRID_LEN+local_id_x;
int dst_index0=mad24(dst_y,ostep,dst_x<<1);
int dst_index1=mad24(dst_y+half_grid,ostep,dst_x<<1);
int size=GRID_LEN;
int half_size=(size>>1);
int table_step=GRID_LEN*native_recip(size);
int tid=local_id_y;
int block_id=tid*native_recip(half_size);
int block_offset=tid&(half_size-1);
int y0_idx=mad24(block_id,size,block_offset);
int y1_idx=y0_idx+half_size;
int w_idx=block_offset*table_step*2;
v16f32_src0=VLOAD(local_buffer+y0_idx*local_step,16);
v16f32_src1=VLOAD(local_buffer+y1_idx*local_step,16);
v16f32_temp.even=v16f32_src1.even*param[w_idx]-v16f32_src1.odd*param[w_idx+1];
v16f32_temp.odd=v16f32_src1.odd*param[w_idx]+v16f32_src1.even*param[w_idx+1];
v16f32_src1=v16f32_src0-v16f32_temp;
v16f32_src0=v16f32_src0+v16f32_temp;
VSTORE(v16f32_src0,dst+dst_index0,16);
VSTORE(v16f32_src1,dst+dst_index1,16);
v16f32_src0=VLOAD(local_buffer+y0_idx*local_step+16,16);
v16f32_src1=VLOAD(local_buffer+y1_idx*local_step+16,16);
v16f32_temp.even=v16f32_src1.even*param[w_idx]-v16f32_src1.odd*param[w_idx+1];
v16f32_temp.odd=v16f32_src1.odd*param[w_idx]+v16f32_src1.even*param[w_idx+1];
v16f32_src1=v16f32_src0-v16f32_temp;
v16f32_src0=v16f32_src0+v16f32_temp;
VSTORE(v16f32_src0,dst+dst_index0+16,16);
VSTORE(v16f32_src1,dst+dst_index1+16,16);
}
}

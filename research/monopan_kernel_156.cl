inline void RowIDft1x16(float16 v16f32_src0,float16 v16f32_src1,float8 v8f32_exp_table0,float8 v8f32_exp_table1,
local float*local_data,float16 v16f32_scale)
{
float16 v16f32_temp0,v16f32_temp1;
v16f32_temp0=v16f32_src0+v16f32_src1;
v16f32_temp1=v16f32_src0-v16f32_src1;
float16 v16f32_dst0,v16f32_dst1;
v16f32_dst0=(float16)(v16f32_temp0.s01,v16f32_temp1.s01,v16f32_temp0.s89,v16f32_temp1.s89,
v16f32_temp0.s45,v16f32_temp1.s45,v16f32_temp0.scd,v16f32_temp1.scd);
v16f32_dst1=(float16)(v16f32_temp0.s23,v16f32_temp1.s23,v16f32_temp0.sab,v16f32_temp1.sab,
v16f32_temp0.s67,v16f32_temp1.s67,v16f32_temp0.sef,v16f32_temp1.sef);
ROW_IDFT_BUTTERFLY_1X8(v16f32_dst0);
ROW_IDFT_BUTTERFLY_1X8(v16f32_dst1);
v16f32_temp0.even=v16f32_dst1.even*v8f32_exp_table0-v16f32_dst1.odd*v8f32_exp_table1;
v16f32_temp0.odd=v16f32_dst1.odd*v8f32_exp_table0+v16f32_dst1.even*v8f32_exp_table1;
v16f32_dst1.even=v16f32_dst0.even-v16f32_temp0.even;
v16f32_dst1.odd=v16f32_dst0.odd-v16f32_temp0.odd;
v16f32_dst0.even=v16f32_dst0.even+v16f32_temp0.even;
v16f32_dst0.odd=v16f32_dst0.odd+v16f32_temp0.odd;
#if WITH_SCALE
v16f32_dst0=native_divide(v16f32_dst0,v16f32_scale);
v16f32_dst1=native_divide(v16f32_dst1,v16f32_scale);
#endif
VSTORE(v16f32_dst0,local_data,16);
VSTORE(v16f32_dst1,local_data+16,16);
}
#define GRID_LEN (16)
kernel void GridIDft16x16(global float*src,int istep,
global Tp*dst,int ostep,
constant float*param MAX_CONSTANT_SIZE,
local float*local_buffer,
int width,int height)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
int offset_x=clamp(gx<<4,0,width-16);
int offset_y=clamp(gy<<1,0,height-2);
int group_x=get_group_id(0);
int group_y=get_group_id(1);
int local_id_x=get_local_id(0);
int local_id_y=get_local_id(1);
int local_y_shift=local_id_y<<1;
int2 src_index=mad24(offset_y+(int2)(0,1),istep,offset_x<<1);
const int half_grid=GRID_LEN>>1;
const int local_step=GRID_LEN<<1;
float16 v16f32_exp_table=VLOAD(param,16);
float8 v8f32_exp_table0=v16f32_exp_table.even;
float8 v8f32_exp_table1=v16f32_exp_table.odd;
int y_index[16]={0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};
int2 v2s32_y_idx=(int2)(y_index[local_y_shift],y_index[local_y_shift+1]);
int2 local_index=mad24(v2s32_y_idx,local_step,local_id_x);
float16 v16f32_scale=(float16)(16.0f);
float16 v16f32_src00,v16f32_src01,v16f32_src10,v16f32_src11;
{
v16f32_src00=VLOAD(src+src_index.s0,16);
v16f32_src10=VLOAD(src+src_index.s1,16);
v16f32_src01=VLOAD(src+src_index.s0+16,16);
v16f32_src11=VLOAD(src+src_index.s1+16,16);
}
RowIDft1x16(v16f32_src00,v16f32_src01,v8f32_exp_table0,v8f32_exp_table1,local_buffer+local_index.s0,v16f32_scale);
RowIDft1x16(v16f32_src10,v16f32_src11,v8f32_exp_table0,v8f32_exp_table1,local_buffer+local_index.s1,v16f32_scale);
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
#if SAVE_REAL_ONLY
int dst_index0=mad24(dst_y,ostep,dst_x);
int dst_index1=mad24(dst_y+half_grid,ostep,dst_x);
#else
int dst_index0=mad24(dst_y,ostep,dst_x<<1);
int dst_index1=mad24(dst_y+half_grid,ostep,dst_x<<1);
#endif
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
#if WITH_SCALE
v16f32_src0=native_divide(v16f32_src0,v16f32_scale);
v16f32_src1=native_divide(v16f32_src1,v16f32_scale);
#endif
#if SAVE_REAL_ONLY
VSTORE(CONVERT_SAT(v16f32_src0.even,V8Tp),dst+dst_index0,8);
VSTORE(CONVERT_SAT(v16f32_src1.even,V8Tp),dst+dst_index1,8);
#else
VSTORE(v16f32_src0,dst+dst_index0,16);
VSTORE(v16f32_src1,dst+dst_index1,16);
#endif
v16f32_src0=VLOAD(local_buffer+y0_idx*local_step+16,16);
v16f32_src1=VLOAD(local_buffer+y1_idx*local_step+16,16);
v16f32_temp.even=v16f32_src1.even*param[w_idx]-v16f32_src1.odd*param[w_idx+1];
v16f32_temp.odd=v16f32_src1.odd*param[w_idx]+v16f32_src1.even*param[w_idx+1];
v16f32_src1=v16f32_src0-v16f32_temp;
v16f32_src0=v16f32_src0+v16f32_temp;
#if WITH_SCALE
v16f32_src0=native_divide(v16f32_src0,v16f32_scale);
v16f32_src1=native_divide(v16f32_src1,v16f32_scale);
#endif
#if SAVE_REAL_ONLY
VSTORE(CONVERT_SAT(v16f32_src0.even,V8Tp),dst+dst_index0+8,8);
VSTORE(CONVERT_SAT(v16f32_src1.even,V8Tp),dst+dst_index1+8,8);
#else
VSTORE(v16f32_src0,dst+dst_index0+16,16);
VSTORE(v16f32_src1,dst+dst_index1+16,16);
#endif
}
}

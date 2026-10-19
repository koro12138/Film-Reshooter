inline void RowIDft1x32(float16 v16f32_src0,float16 v16f32_src1,float16 v16f32_src2,float16 v16f32_src3,
float16 v16f32_exp_table0,float16 v16f32_exp_table1,
local float*local_data,float16 v16f32_scale)
{
float16 v16f32_tmp0,v16f32_tmp1,v16f32_tmp2,v16f32_tmp3;
float16 v16f32_dst0,v16f32_dst1,v16f32_dst2,v16f32_dst3;
v16f32_tmp0=v16f32_src0+v16f32_src2;
v16f32_tmp1=v16f32_src0-v16f32_src2;
v16f32_tmp2=v16f32_src1+v16f32_src3;
v16f32_tmp3=v16f32_src1-v16f32_src3;
v16f32_dst0=(float16)(v16f32_tmp0.s01,v16f32_tmp1.s01,v16f32_tmp2.s01,v16f32_tmp3.s01,
v16f32_tmp0.s89,v16f32_tmp1.s89,v16f32_tmp2.s89,v16f32_tmp3.s89);
v16f32_dst1=(float16)(v16f32_tmp0.s45,v16f32_tmp1.s45,v16f32_tmp2.s45,v16f32_tmp3.s45,
v16f32_tmp0.scd,v16f32_tmp1.scd,v16f32_tmp2.scd,v16f32_tmp3.scd);
v16f32_dst2=(float16)(v16f32_tmp0.s23,v16f32_tmp1.s23,v16f32_tmp2.s23,v16f32_tmp3.s23,
v16f32_tmp0.sab,v16f32_tmp1.sab,v16f32_tmp2.sab,v16f32_tmp3.sab);
v16f32_dst3=(float16)(v16f32_tmp0.s67,v16f32_tmp1.s67,v16f32_tmp2.s67,v16f32_tmp3.s67,
v16f32_tmp0.sef,v16f32_tmp1.sef,v16f32_tmp2.sef,v16f32_tmp3.sef);
ROW_IDFT_BUTTERFLY_1X32(v16f32_dst0,v16f32_dst1,v16f32_dst2,v16f32_dst3,v16f32_exp_table0,v16f32_exp_table1);
#if WITH_SCALE
v16f32_dst0=native_divide(v16f32_dst0,v16f32_scale);
v16f32_dst1=native_divide(v16f32_dst1,v16f32_scale);
v16f32_dst2=native_divide(v16f32_dst2,v16f32_scale);
v16f32_dst3=native_divide(v16f32_dst3,v16f32_scale);
#endif
VSTORE(v16f32_dst0,local_data,16);
VSTORE(v16f32_dst1,local_data+16,16);
VSTORE(v16f32_dst2,local_data+32,16);
VSTORE(v16f32_dst3,local_data+48,16);
}
#define GRID_LEN (32)
kernel void GridIDft32x32(global float*src,int istep,
global Tp*dst,int ostep,
constant float*param MAX_CONSTANT_SIZE,
local float*local_buffer,
int width,int height)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
int offset_x=clamp(gx<<5,0,width-32);
int offset_y=clamp(gy,0,height-1);
int group_x=get_group_id(0);
int group_y=get_group_id(1);
int local_id_x=get_local_id(0);
int local_id_y=get_local_id(1);
int local_y_shift=local_id_y;
int2 src_index=mad24(offset_y+(int2)(0,1),istep,offset_x<<1);
const int half_grid=GRID_LEN>>1;
const int local_step=GRID_LEN<<1;
float16 v16f32_exp_table0=VLOAD(param,16);
float16 v16f32_exp_table1=VLOAD(param+16,16);
float16 v16f32_exp_even=(float16)(v16f32_exp_table0.even,v16f32_exp_table1.even);
float16 v16f32_exp_odd=(float16)(v16f32_exp_table0.odd,v16f32_exp_table1.odd);
int y_index[32]={0,16,8,24,4,20,12,28,2,18,10,26,6,22,14,30,
1,17,9,25,5,21,13,29,3,19,11,27,7,23,15,31};
int2 v2s32_y_idx=(int2)(y_index[local_y_shift],y_index[local_y_shift+1]);
int2 local_index=mad24(v2s32_y_idx,local_step,local_id_x);
float16 v16f32_scale=(float16)(32.0f);
float16 v16f32_src00=VLOAD(src+src_index.s0,16);
float16 v16f32_src01=VLOAD(src+src_index.s0+16,16);
float16 v16f32_src02=VLOAD(src+src_index.s0+32,16);
float16 v16f32_src03=VLOAD(src+src_index.s0+48,16);
RowIDft1x32(v16f32_src00,v16f32_src01,v16f32_src02,v16f32_src03,v16f32_exp_even,v16f32_exp_odd,local_buffer+local_index.s0,v16f32_scale);
barrier(CLK_LOCAL_MEM_FENCE);
int local_size_y0=(local_id_y%16);
int local_size_x0=local_id_x+local_id_y/16;
local_y_shift=local_size_y0<<1;
v2s32_y_idx=(int2)(local_y_shift,local_y_shift+1);
local_index=mad24(v2s32_y_idx,local_step,local_size_x0<<5);
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
int tid=local_size_y0;
int block_id=tid*native_recip(half_size);
int block_offset=tid&(half_size-1);
int y0_idx=mad24(block_id,size,block_offset);
int y1_idx=y0_idx+half_size;
int w_idx=block_offset*table_step*2;
int local_shift0=y0_idx*local_step+(local_size_x0<<5);
int local_shift1=y1_idx*local_step+(local_size_x0<<5);
v16f32_src0=VLOAD(local_buffer+local_shift0,16);
v16f32_src1=VLOAD(local_buffer+local_shift1,16);
v16f32_temp.even=v16f32_src1.even*param[w_idx]-v16f32_src1.odd*param[w_idx+1];
v16f32_temp.odd=v16f32_src1.odd*param[w_idx]+v16f32_src1.even*param[w_idx+1];
v16f32_src1=v16f32_src0-v16f32_temp;
v16f32_src0=v16f32_src0+v16f32_temp;
VSTORE(v16f32_src0,local_buffer+local_shift0,16);
VSTORE(v16f32_src1,local_buffer+local_shift1,16);
v16f32_src0=VLOAD(local_buffer+local_shift0+16,16);
v16f32_src1=VLOAD(local_buffer+local_shift1+16,16);
v16f32_temp.even=v16f32_src1.even*param[w_idx]-v16f32_src1.odd*param[w_idx+1];
v16f32_temp.odd=v16f32_src1.odd*param[w_idx]+v16f32_src1.even*param[w_idx+1];
v16f32_src1=v16f32_src0-v16f32_temp;
v16f32_src0=v16f32_src0+v16f32_temp;
VSTORE(v16f32_src0,local_buffer+local_shift0+16,16);
VSTORE(v16f32_src1,local_buffer+local_shift1+16,16);
barrier(CLK_LOCAL_MEM_FENCE);
}
{
int dst_y=group_y*GRID_LEN+local_size_y0;
int dst_x=group_x*GRID_LEN+(local_size_x0<<4);
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
int tid=local_size_y0;
int block_id=tid*native_recip(half_size);
int block_offset=tid&(half_size-1);
int y0_idx=mad24(block_id,size,block_offset);
int y1_idx=y0_idx+half_size;
int w_idx=block_offset*table_step*2;
int local_shift0=y0_idx*local_step+(local_size_x0<<5);
int local_shift1=y1_idx*local_step+(local_size_x0<<5);
v16f32_src0=VLOAD(local_buffer+local_shift0,16);
v16f32_src1=VLOAD(local_buffer+local_shift1,16);
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
v16f32_src0=VLOAD(local_buffer+local_shift0+16,16);
v16f32_src1=VLOAD(local_buffer+local_shift1+16,16);
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

inline void RowDft1x32(float16 v16f32_src0,float16 v16f32_src1,float16 v16f32_exp_table0,float16 v16f32_exp_table1,local float*local_data)
{
float8 v8f32_src00,v8f32_src01,v8f32_src10,v8f32_src11;
v8f32_src00=v16f32_src0.lo;
v8f32_src01=v16f32_src0.hi;
v8f32_src10=v16f32_src1.lo;
v8f32_src11=v16f32_src1.hi;
ROW_DFT_BUTTERFLY_1X16(v8f32_src00,v8f32_src10);
ROW_DFT_BUTTERFLY_1X16(v8f32_src01,v8f32_src11);
{
float16 v16f32_exp_table=(float16)(1.0f,0.0f,0.92388f,-0.382683f,0.70710677f,-0.70710677f,0.382683f,-0.92388f,
0.0f,-1.0f,-0.382684f,-0.92388f,-0.70710677f,-0.70710677f,-0.92388f,-0.382683f);
float8 v8f32_temp0,v8f32_temp1;
v8f32_temp0=v8f32_src01*v16f32_exp_table.even-v8f32_src11*v16f32_exp_table.odd;
v8f32_temp1=v8f32_src11*v16f32_exp_table.even+v8f32_src01*v16f32_exp_table.odd;
v8f32_src01=v8f32_src00-v8f32_temp0;
v8f32_src11=v8f32_src10-v8f32_temp1;
v8f32_src00=v8f32_src00+v8f32_temp0;
v8f32_src10=v8f32_src10+v8f32_temp1;
}
v16f32_src0=(float16)(v8f32_src00,v8f32_src01);
v16f32_src1=(float16)(v8f32_src10,v8f32_src11);
uint16 v16u16_mask=(uint16)(0,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1);
float16 v16f32_conj0,v16f32_conj1;
v16f32_conj0=v16f32_src0.s0fedcba987654321;
v16f32_conj1=v16f32_src1.s0fedcba987654321*(-1.0f);
float16 v16f32_fk0,v16f32_fk1;
v16f32_fk0=(v16f32_src0+v16f32_conj0)*0.5f;
v16f32_fk1=(v16f32_src1+v16f32_conj1)*0.5f;
float16 v16f32_temp0,v16f32_temp1;
v16f32_temp0=v16f32_conj0-v16f32_src0;
v16f32_temp1=v16f32_conj1-v16f32_src1;
float16 v16f32_gk0,v16f32_gk1;
v16f32_gk0=v16f32_temp1*(-0.5f);
v16f32_gk1=v16f32_temp0*(0.5f);
float16 v16f32_dst0,v16f32_dst1,v16f32_dst2,v16f32_dst3;
v16f32_temp0=v16f32_gk0*v16f32_exp_table0-v16f32_gk1*v16f32_exp_table1;
v16f32_temp1=v16f32_gk1*v16f32_exp_table0+v16f32_gk0*v16f32_exp_table1;
v16f32_dst0=v16f32_fk0+v16f32_temp0;
v16f32_dst1=v16f32_fk1+v16f32_temp1;
v16f32_dst2=shuffle(v16f32_dst0,v16u16_mask);
v16f32_dst3=shuffle(v16f32_dst1,v16u16_mask)*(-1.0f);
v16f32_dst2.s0=v16f32_fk0.s0-v16f32_gk0.s0;
v16f32_dst3.s0=0.0f;
float16 v16f32_store0,v16f32_store1;
v16f32_store0.even=v16f32_dst0.lo;
v16f32_store0.odd=v16f32_dst1.lo;
v16f32_store1.even=v16f32_dst0.hi;
v16f32_store1.odd=v16f32_dst1.hi;
VSTORE(v16f32_store0,local_data,16);
VSTORE(v16f32_store1,local_data+16,16);
v16f32_store0.even=v16f32_dst2.lo;
v16f32_store0.odd=v16f32_dst3.lo;
v16f32_store1.even=v16f32_dst2.hi;
v16f32_store1.odd=v16f32_dst3.hi;
VSTORE(v16f32_store0,local_data+32,16);
VSTORE(v16f32_store1,local_data+48,16);
}
#define GRID_LEN (32)
kernel void GridDft32x32(global Tp*src,int istep,
global float*dst,int ostep,
constant float*param MAX_CONSTANT_SIZE,
local float*local_buffer,
int width,int height)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
int offset_x=gx<<5;
int offset_y=gy;
if(offset_x>=width||offset_y>=height)
{
return;
}
int group_x=get_group_id(0);
int group_y=get_group_id(1);
int local_id_x=get_local_id(0);
int local_id_y=get_local_id(1);
int local_y_shift=local_id_y;
int2 src_index=mad24(offset_y+(int2)(0,1),istep,offset_x);
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
float16 v16f32_src00,v16f32_src01;
{
float16 tmp_src00=CONVERT(VLOAD(src+src_index.s0,16),float16);
float16 tmp_src01=CONVERT(VLOAD(src+src_index.s0+16,16),float16);
float16 v16f32_src_lo,v16f32_src_hi;
v16f32_src_lo=(float16)(tmp_src00.s01,tmp_src01.s01,tmp_src00.s89,tmp_src01.s89,tmp_src00.s45,tmp_src01.s45,tmp_src00.scd,tmp_src01.scd);
v16f32_src_hi=(float16)(tmp_src00.s23,tmp_src01.s23,tmp_src00.sab,tmp_src01.sab,tmp_src00.s67,tmp_src01.s67,tmp_src00.sef,tmp_src01.sef);
v16f32_src00=(float16)(v16f32_src_lo.even,v16f32_src_hi.even);
v16f32_src01=(float16)(v16f32_src_lo.odd,v16f32_src_hi.odd);
}
RowDft1x32(v16f32_src00,v16f32_src01,v16f32_exp_even,v16f32_exp_odd,local_buffer+local_index.s0);
barrier(CLK_LOCAL_MEM_FENCE);
int local_id_y0=(local_id_y%16);
int local_id_x0=local_id_x+local_id_y/16;
local_y_shift=local_id_y0<<1;
v2s32_y_idx=(int2)(local_y_shift,local_y_shift+1);
local_index=mad24(v2s32_y_idx,local_step,local_id_x0<<5);
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
int tid=local_id_y0;
int block_id=tid*native_recip(half_size);
int block_offset=tid&(half_size-1);
int y0_idx=mad24(block_id,size,block_offset);
int y1_idx=y0_idx+half_size;
int w_idx=block_offset*table_step*2;
int local_shift0=y0_idx*local_step+(local_id_x0<<5);
int local_shift1=y1_idx*local_step+(local_id_x0<<5);
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
int dst_y=group_y*GRID_LEN+local_id_y0;
int dst_x=group_x*GRID_LEN+(local_id_x0<<4);
int dst_index0=mad24(dst_y,ostep,dst_x<<1);
int dst_index1=mad24(dst_y+half_grid,ostep,dst_x<<1);
int size=GRID_LEN;
int half_size=(size>>1);
int table_step=GRID_LEN*native_recip(size);
int tid=local_id_y0;
int block_id=tid*native_recip(half_size);
int block_offset=tid&(half_size-1);
int y0_idx=mad24(block_id,size,block_offset);
int y1_idx=y0_idx+half_size;
int w_idx=block_offset*table_step*2;
int local_shift0=y0_idx*local_step+(local_id_x0<<5);
int local_shift1=y1_idx*local_step+(local_id_x0<<5);
v16f32_src0=VLOAD(local_buffer+local_shift0,16);
v16f32_src1=VLOAD(local_buffer+local_shift1,16);
v16f32_temp.even=v16f32_src1.even*param[w_idx]-v16f32_src1.odd*param[w_idx+1];
v16f32_temp.odd=v16f32_src1.odd*param[w_idx]+v16f32_src1.even*param[w_idx+1];
v16f32_src1=v16f32_src0-v16f32_temp;
v16f32_src0=v16f32_src0+v16f32_temp;
VSTORE(v16f32_src0,dst+dst_index0,16);
VSTORE(v16f32_src1,dst+dst_index1,16);
v16f32_src0=VLOAD(local_buffer+local_shift0+16,16);
v16f32_src1=VLOAD(local_buffer+local_shift1+16,16);
v16f32_temp.even=v16f32_src1.even*param[w_idx]-v16f32_src1.odd*param[w_idx+1];
v16f32_temp.odd=v16f32_src1.odd*param[w_idx]+v16f32_src1.even*param[w_idx+1];
v16f32_src1=v16f32_src0-v16f32_temp;
v16f32_src0=v16f32_src0+v16f32_temp;
VSTORE(v16f32_src0,dst+dst_index0+16,16);
VSTORE(v16f32_src1,dst+dst_index1+16,16);
}
}

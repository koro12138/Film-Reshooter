kernel void GridIDft4x4(global float*src,int istep,
global Tp*dst,int ostep,
int width,int height)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
int offset_x=gx<<2;
int offset_y=gy<<2;
if(offset_x>=width||offset_y>=height)
{
return;
}
int4 v4f32_src_idx=mad24(offset_y+(int4)(0,1,2,3),istep,offset_x<<1);
#if SAVE_REAL_ONLY
int4 v4f32_dst_idx=mad24(offset_y+(int4)(0,1,2,3),ostep,offset_x);
#else
int4 v4f32_dst_idx=mad24(offset_y+(int4)(0,1,2,3),ostep,offset_x<<1);
#endif
float8 v8f32_src0=VLOAD(src+v4f32_src_idx.s0,8);
float8 v8f32_src1=VLOAD(src+v4f32_src_idx.s1,8);
float8 v8f32_src2=VLOAD(src+v4f32_src_idx.s2,8);
float8 v8f32_src3=VLOAD(src+v4f32_src_idx.s3,8);
float2 v2f32_exp_table=(float2)(-1.0f,1.0f);
float8 v8f32_row_dft0,v8f32_row_dft1,v8f32_row_dft2,v8f32_row_dft3;
ROW_IDFT_BUTTERFLY_1X4(v8f32_src0,v8f32_row_dft0,v2f32_exp_table);
ROW_IDFT_BUTTERFLY_1X4(v8f32_src2,v8f32_row_dft1,v2f32_exp_table);
ROW_IDFT_BUTTERFLY_1X4(v8f32_src1,v8f32_row_dft2,v2f32_exp_table);
ROW_IDFT_BUTTERFLY_1X4(v8f32_src3,v8f32_row_dft3,v2f32_exp_table);
#if WITH_SCALE
float8 v8f32_scale=(float8)(4.0f);
v8f32_row_dft0=native_divide(v8f32_row_dft0,v8f32_scale);
v8f32_row_dft1=native_divide(v8f32_row_dft1,v8f32_scale);
v8f32_row_dft2=native_divide(v8f32_row_dft2,v8f32_scale);
v8f32_row_dft3=native_divide(v8f32_row_dft3,v8f32_scale);
#endif
float8 v8f32_temp;
v8f32_temp=v8f32_row_dft1;
v8f32_row_dft1=v8f32_row_dft0-v8f32_temp;
v8f32_row_dft0=v8f32_row_dft0+v8f32_temp;
v8f32_temp=v8f32_row_dft3;
v8f32_row_dft3=v8f32_row_dft2-v8f32_temp;
v8f32_row_dft2=v8f32_row_dft2+v8f32_temp;
v8f32_temp=v8f32_row_dft2;
v8f32_row_dft2=v8f32_row_dft0-v8f32_temp;
v8f32_row_dft0=v8f32_row_dft0+v8f32_temp;
v8f32_temp.even=v8f32_row_dft3.odd*(-1.0f);
v8f32_temp.odd=v8f32_row_dft3.even;
v8f32_row_dft3=v8f32_row_dft1-v8f32_temp;
v8f32_row_dft1=v8f32_row_dft1+v8f32_temp;
#if WITH_SCALE
v8f32_row_dft0=native_divide(v8f32_row_dft0,v8f32_scale);
v8f32_row_dft1=native_divide(v8f32_row_dft1,v8f32_scale);
v8f32_row_dft2=native_divide(v8f32_row_dft2,v8f32_scale);
v8f32_row_dft3=native_divide(v8f32_row_dft3,v8f32_scale);
#endif
#if SAVE_REAL_ONLY
VSTORE(CONVERT_SAT(v8f32_row_dft0.even,V4Tp),dst+v4f32_dst_idx.s0,4);
VSTORE(CONVERT_SAT(v8f32_row_dft1.even,V4Tp),dst+v4f32_dst_idx.s1,4);
VSTORE(CONVERT_SAT(v8f32_row_dft2.even,V4Tp),dst+v4f32_dst_idx.s2,4);
VSTORE(CONVERT_SAT(v8f32_row_dft3.even,V4Tp),dst+v4f32_dst_idx.s3,4);
#else
VSTORE(v8f32_row_dft0,dst+v4f32_dst_idx.s0,8);
VSTORE(v8f32_row_dft1,dst+v4f32_dst_idx.s1,8);
VSTORE(v8f32_row_dft2,dst+v4f32_dst_idx.s2,8);
VSTORE(v8f32_row_dft3,dst+v4f32_dst_idx.s3,8);
#endif
}

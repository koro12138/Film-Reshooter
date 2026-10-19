float16 RowIDft1x8(float16 v16f32_src,float16 v16f32_scale)
{
float16 v16f32_temp;
v16f32_temp.lo=v16f32_src.lo+v16f32_src.hi;
v16f32_temp.hi=v16f32_src.lo-v16f32_src.hi;
uint8 idx_mask=(uint8)(0,4,2,6,1,5,3,7);
uint8 even_mask=idx_mask<<1;
uint8 odd_mask=even_mask+1;
float8 v8f32_dst0,v8f32_dst1;
v8f32_dst0=shuffle(v16f32_temp,even_mask);
v8f32_dst1=shuffle(v16f32_temp,odd_mask);
float8 v8f32_temp0,v8f32_temp1;
float2 v2f32_exp_table=(float2)(0,1);
v8f32_temp0.s26=v8f32_dst0.s26;
v8f32_temp1.s26=v8f32_dst1.s26;
v8f32_temp0.s37=v8f32_dst0.s37*v2f32_exp_table.s0-v8f32_dst1.s37*v2f32_exp_table.s1;
v8f32_temp1.s37=v8f32_dst1.s37*v2f32_exp_table.s0+v8f32_dst0.s37*v2f32_exp_table.s1;
v8f32_dst0.s2367=v8f32_dst0.s0145-v8f32_temp0.s2367;
v8f32_dst0.s0145=v8f32_dst0.s0145+v8f32_temp0.s2367;
v8f32_dst1.s2367=v8f32_dst1.s0145-v8f32_temp1.s2367;
v8f32_dst1.s0145=v8f32_dst1.s0145+v8f32_temp1.s2367;
float8 v8f32_exp_table=(float8)(1.0f,0.0f,0.70710677f,0.70710677f,
0.0f,1.0f,-0.70710677f,0.70710677f);
v8f32_temp0.hi=v8f32_dst0.hi*v8f32_exp_table.even-v8f32_dst1.hi*v8f32_exp_table.odd;
v8f32_temp1.hi=v8f32_dst1.hi*v8f32_exp_table.even+v8f32_dst0.hi*v8f32_exp_table.odd;
v8f32_dst0.hi=v8f32_dst0.lo-v8f32_temp0.hi;
v8f32_dst0.lo=v8f32_dst0.lo+v8f32_temp0.hi;
v8f32_dst1.hi=v8f32_dst1.lo-v8f32_temp1.hi;
v8f32_dst1.lo=v8f32_dst1.lo+v8f32_temp1.hi;
float16 v16f32_dst;
v16f32_dst.even=v8f32_dst0;
v16f32_dst.odd=v8f32_dst1;
#if WITH_SCALE
v16f32_dst=native_divide(v16f32_dst,v16f32_scale);
#endif
return v16f32_dst;
}
kernel void GridIDft8x8(global float*src,int istep,
global Tp*dst,int ostep,
int width,int height)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
int offset_x=gx<<3;
int offset_y=gy<<3;
if(offset_x>=width||offset_y>=height)
{
return;
}
int8 v8s32_src_idx=mad24(offset_y+(int8)(0,1,2,3,4,5,6,7),istep,offset_x<<1);
#if SAVE_REAL_ONLY
int8 v8s32_dst_idx=mad24(offset_y+(int8)(0,1,2,3,4,5,6,7),ostep,offset_x);
#else
int8 v8s32_dst_idx=mad24(offset_y+(int8)(0,1,2,3,4,5,6,7),ostep,offset_x<<1);
#endif
float16 v16f32_scale=(float16)(8.0f);
float16 v16f32_row_dft0,v16f32_row_dft1,v16f32_row_dft2,v16f32_row_dft3;
float16 v16f32_row_dft4,v16f32_row_dft5,v16f32_row_dft6,v16f32_row_dft7;
{
float16 v16f32_src0=VLOAD(src+v8s32_src_idx.s0,16);
float16 v16f32_src1=VLOAD(src+v8s32_src_idx.s1,16);
float16 v16f32_src2=VLOAD(src+v8s32_src_idx.s2,16);
float16 v16f32_src3=VLOAD(src+v8s32_src_idx.s3,16);
v16f32_row_dft0=RowIDft1x8(v16f32_src0,v16f32_scale);
v16f32_row_dft4=RowIDft1x8(v16f32_src1,v16f32_scale);
v16f32_row_dft2=RowIDft1x8(v16f32_src2,v16f32_scale);
v16f32_row_dft6=RowIDft1x8(v16f32_src3,v16f32_scale);
v16f32_src0=VLOAD(src+v8s32_src_idx.s4,16);
v16f32_src1=VLOAD(src+v8s32_src_idx.s5,16);
v16f32_src2=VLOAD(src+v8s32_src_idx.s6,16);
v16f32_src3=VLOAD(src+v8s32_src_idx.s7,16);
v16f32_row_dft1=RowIDft1x8(v16f32_src0,v16f32_scale);
v16f32_row_dft5=RowIDft1x8(v16f32_src1,v16f32_scale);
v16f32_row_dft3=RowIDft1x8(v16f32_src2,v16f32_scale);
v16f32_row_dft7=RowIDft1x8(v16f32_src3,v16f32_scale);
}
float16 v16f32_tmp;
v16f32_tmp=v16f32_row_dft1;
v16f32_row_dft1=v16f32_row_dft0-v16f32_tmp;
v16f32_row_dft0=v16f32_row_dft0+v16f32_tmp;
v16f32_tmp=v16f32_row_dft3;
v16f32_row_dft3=v16f32_row_dft2-v16f32_tmp;
v16f32_row_dft2=v16f32_row_dft2+v16f32_tmp;
v16f32_tmp=v16f32_row_dft5;
v16f32_row_dft5=v16f32_row_dft4-v16f32_tmp;
v16f32_row_dft4=v16f32_row_dft4+v16f32_tmp;
v16f32_tmp=v16f32_row_dft7;
v16f32_row_dft7=v16f32_row_dft6-v16f32_tmp;
v16f32_row_dft6=v16f32_row_dft6+v16f32_tmp;
v16f32_tmp=v16f32_row_dft2;
v16f32_row_dft2=v16f32_row_dft0-v16f32_tmp;
v16f32_row_dft0=v16f32_row_dft0+v16f32_tmp;
v16f32_tmp.even=v16f32_row_dft3.odd*(-1.0f);
v16f32_tmp.odd=v16f32_row_dft3.even;
v16f32_row_dft3=v16f32_row_dft1-v16f32_tmp;
v16f32_row_dft1=v16f32_row_dft1+v16f32_tmp;
v16f32_tmp=v16f32_row_dft6;
v16f32_row_dft6=v16f32_row_dft4-v16f32_tmp;
v16f32_row_dft4=v16f32_row_dft4+v16f32_tmp;
v16f32_tmp.even=v16f32_row_dft7.odd*(-1.0f);
v16f32_tmp.odd=v16f32_row_dft7.even;
v16f32_row_dft7=v16f32_row_dft5-v16f32_tmp;
v16f32_row_dft5=v16f32_row_dft5+v16f32_tmp;
v16f32_tmp=v16f32_row_dft4;
v16f32_row_dft4=v16f32_row_dft0-v16f32_tmp;
v16f32_row_dft0=v16f32_row_dft0+v16f32_tmp;
v16f32_tmp.even=v16f32_row_dft5.even*0.707107f-v16f32_row_dft5.odd*0.707107f;
v16f32_tmp.odd=v16f32_row_dft5.odd*0.707107f+v16f32_row_dft5.even*0.707107f;
v16f32_row_dft5=v16f32_row_dft1-v16f32_tmp;
v16f32_row_dft1=v16f32_row_dft1+v16f32_tmp;
v16f32_tmp.even=v16f32_row_dft6.odd*(-1.0f);
v16f32_tmp.odd=v16f32_row_dft6.even;
v16f32_row_dft6=v16f32_row_dft2-v16f32_tmp;
v16f32_row_dft2=v16f32_row_dft2+v16f32_tmp;
v16f32_tmp.even=v16f32_row_dft7.even*(-0.707107f)-v16f32_row_dft7.odd*0.707107f;
v16f32_tmp.odd=v16f32_row_dft7.odd*(-0.707107f)+v16f32_row_dft7.even*0.707107f;
v16f32_row_dft7=v16f32_row_dft3-v16f32_tmp;
v16f32_row_dft3=v16f32_row_dft3+v16f32_tmp;
#if WITH_SCALE
v16f32_row_dft0=native_divide(v16f32_row_dft0,v16f32_scale);
v16f32_row_dft1=native_divide(v16f32_row_dft1,v16f32_scale);
v16f32_row_dft2=native_divide(v16f32_row_dft2,v16f32_scale);
v16f32_row_dft3=native_divide(v16f32_row_dft3,v16f32_scale);
v16f32_row_dft4=native_divide(v16f32_row_dft4,v16f32_scale);
v16f32_row_dft5=native_divide(v16f32_row_dft5,v16f32_scale);
v16f32_row_dft6=native_divide(v16f32_row_dft6,v16f32_scale);
v16f32_row_dft7=native_divide(v16f32_row_dft7,v16f32_scale);
#endif
#if SAVE_REAL_ONLY
VSTORE(CONVERT_SAT(v16f32_row_dft0.even,V8Tp),dst+v8s32_dst_idx.s0,8);
VSTORE(CONVERT_SAT(v16f32_row_dft1.even,V8Tp),dst+v8s32_dst_idx.s1,8);
VSTORE(CONVERT_SAT(v16f32_row_dft2.even,V8Tp),dst+v8s32_dst_idx.s2,8);
VSTORE(CONVERT_SAT(v16f32_row_dft3.even,V8Tp),dst+v8s32_dst_idx.s3,8);
VSTORE(CONVERT_SAT(v16f32_row_dft4.even,V8Tp),dst+v8s32_dst_idx.s4,8);
VSTORE(CONVERT_SAT(v16f32_row_dft5.even,V8Tp),dst+v8s32_dst_idx.s5,8);
VSTORE(CONVERT_SAT(v16f32_row_dft6.even,V8Tp),dst+v8s32_dst_idx.s6,8);
VSTORE(CONVERT_SAT(v16f32_row_dft7.even,V8Tp),dst+v8s32_dst_idx.s7,8);
#else
VSTORE(v16f32_row_dft0,dst+v8s32_dst_idx.s0,16);
VSTORE(v16f32_row_dft1,dst+v8s32_dst_idx.s1,16);
VSTORE(v16f32_row_dft2,dst+v8s32_dst_idx.s2,16);
VSTORE(v16f32_row_dft3,dst+v8s32_dst_idx.s3,16);
VSTORE(v16f32_row_dft4,dst+v8s32_dst_idx.s4,16);
VSTORE(v16f32_row_dft5,dst+v8s32_dst_idx.s5,16);
VSTORE(v16f32_row_dft6,dst+v8s32_dst_idx.s6,16);
VSTORE(v16f32_row_dft7,dst+v8s32_dst_idx.s7,16);
#endif
}

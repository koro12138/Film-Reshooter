inline float16 RowDft1x8(float8 v8f32_src)
{
float8 v8f32_temp;
v8f32_temp=v8f32_src;
v8f32_src.s2367=v8f32_src.s0145-v8f32_temp.s2367;
v8f32_src.s0145=v8f32_src.s0145+v8f32_temp.s2367;
v8f32_temp.s45=v8f32_src.s45;
v8f32_temp.s67=v8f32_src.s76*(float2)(1.0f,-1.0f);
v8f32_src.hi=v8f32_src.lo-v8f32_temp.hi;
v8f32_src.lo=v8f32_src.lo+v8f32_temp.hi;
float8 v8f32_conj,v8f32_fk,v8f32_gk;
v8f32_conj=v8f32_src.s01674523;
v8f32_conj.odd=v8f32_conj.odd*(-1.0f);
v8f32_fk=(v8f32_src+v8f32_conj)*0.5f;
v8f32_temp=v8f32_conj-v8f32_src;
v8f32_gk.even=v8f32_temp.odd*(-0.5f);
v8f32_gk.odd=v8f32_temp.even*(0.5f);
float8 v8f32_exp_table=(float8)(1.0f,0.0f,0.70710677f,-0.70710677f,0.0f,-1.0f,-0.70710677f,-0.70710677f);
float8 v8f32_dst0,v8f32_dst1;
v8f32_temp.even=v8f32_gk.even*v8f32_exp_table.even-v8f32_gk.odd*v8f32_exp_table.odd;
v8f32_temp.odd=v8f32_gk.odd*v8f32_exp_table.even+v8f32_gk.even*v8f32_exp_table.odd;
v8f32_dst0=v8f32_fk+v8f32_temp;
v8f32_temp=v8f32_dst0;
v8f32_temp.odd=v8f32_dst0.odd*(-1.0f);
v8f32_temp.s01=v8f32_fk.s01-v8f32_gk.s01;
v8f32_dst1=v8f32_temp.s01674523;
float16 v16f32_dst;
v16f32_dst.lo=v8f32_dst0;
v16f32_dst.hi=v8f32_dst1;
return v16f32_dst;
}
kernel void GridDft8x8(global Tp*src,int istep,
global float*dst,int ostep,
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
int8 v8s32_src_idx=mad24(offset_y+(int8)(0,1,2,3,4,5,6,7),istep,offset_x);
int8 v8s32_dst_idx=mad24(offset_y+(int8)(0,1,2,3,4,5,6,7),ostep,offset_x<<1);
float16 v16f32_dft0,v16f32_dft1,v16f32_dft2,v16f32_dft3;
float16 v16f32_dft4,v16f32_dft5,v16f32_dft6,v16f32_dft7;
{
float8 v8f32_src0,v8f32_src1,v8f32_src2,v8f32_src3;
float8 v8f32_tmp_src0=CONVERT(VLOAD(src+v8s32_src_idx.s0,8),float8);
float8 v8f32_tmp_src1=CONVERT(VLOAD(src+v8s32_src_idx.s1,8),float8);
float8 v8f32_tmp_src2=CONVERT(VLOAD(src+v8s32_src_idx.s2,8),float8);
float8 v8f32_tmp_src3=CONVERT(VLOAD(src+v8s32_src_idx.s3,8),float8);
v8f32_src0=v8f32_tmp_src0.s01452367;
v8f32_src1=v8f32_tmp_src1.s01452367;
v8f32_src2=v8f32_tmp_src2.s01452367;
v8f32_src3=v8f32_tmp_src3.s01452367;
v16f32_dft0=RowDft1x8(v8f32_src0);
v16f32_dft4=RowDft1x8(v8f32_src1);
v16f32_dft2=RowDft1x8(v8f32_src2);
v16f32_dft6=RowDft1x8(v8f32_src3);
v8f32_tmp_src0=CONVERT(VLOAD(src+v8s32_src_idx.s4,8),float8);
v8f32_tmp_src1=CONVERT(VLOAD(src+v8s32_src_idx.s5,8),float8);
v8f32_tmp_src2=CONVERT(VLOAD(src+v8s32_src_idx.s6,8),float8);
v8f32_tmp_src3=CONVERT(VLOAD(src+v8s32_src_idx.s7,8),float8);
v8f32_src0=v8f32_tmp_src0.s01452367;
v8f32_src1=v8f32_tmp_src1.s01452367;
v8f32_src2=v8f32_tmp_src2.s01452367;
v8f32_src3=v8f32_tmp_src3.s01452367;
v16f32_dft1=RowDft1x8(v8f32_src0);
v16f32_dft5=RowDft1x8(v8f32_src1);
v16f32_dft3=RowDft1x8(v8f32_src2);
v16f32_dft7=RowDft1x8(v8f32_src3);
}
float16 v16f32_tmp;
v16f32_tmp=v16f32_dft1;
v16f32_dft1=v16f32_dft0-v16f32_tmp;
v16f32_dft0=v16f32_dft0+v16f32_tmp;
v16f32_tmp=v16f32_dft3;
v16f32_dft3=v16f32_dft2-v16f32_tmp;
v16f32_dft2=v16f32_dft2+v16f32_tmp;
v16f32_tmp=v16f32_dft5;
v16f32_dft5=v16f32_dft4-v16f32_tmp;
v16f32_dft4=v16f32_dft4+v16f32_tmp;
v16f32_tmp=v16f32_dft7;
v16f32_dft7=v16f32_dft6-v16f32_tmp;
v16f32_dft6=v16f32_dft6+v16f32_tmp;
v16f32_tmp=v16f32_dft2;
v16f32_dft2=v16f32_dft0-v16f32_tmp;
v16f32_dft0=v16f32_dft0+v16f32_tmp;
v16f32_tmp.even=v16f32_dft3.odd;
v16f32_tmp.odd=v16f32_dft3.even*(-1.0f);
v16f32_dft3=v16f32_dft1-v16f32_tmp;
v16f32_dft1=v16f32_dft1+v16f32_tmp;
v16f32_tmp=v16f32_dft6;
v16f32_dft6=v16f32_dft4-v16f32_tmp;
v16f32_dft4=v16f32_dft4+v16f32_tmp;
v16f32_tmp.even=v16f32_dft7.odd;
v16f32_tmp.odd=v16f32_dft7.even*(-1.0f);
v16f32_dft7=v16f32_dft5-v16f32_tmp;
v16f32_dft5=v16f32_dft5+v16f32_tmp;
v16f32_tmp=v16f32_dft4;
v16f32_dft4=v16f32_dft0-v16f32_tmp;
v16f32_dft0=v16f32_dft0+v16f32_tmp;
v16f32_tmp.even=v16f32_dft5.even*0.707107f-v16f32_dft5.odd*(-0.707107f);
v16f32_tmp.odd=v16f32_dft5.odd*0.707107f+v16f32_dft5.even*(-0.707107f);
v16f32_dft5=v16f32_dft1-v16f32_tmp;
v16f32_dft1=v16f32_dft1+v16f32_tmp;
v16f32_tmp.even=v16f32_dft6.odd;
v16f32_tmp.odd=v16f32_dft6.even*(-1.0f);
v16f32_dft6=v16f32_dft2-v16f32_tmp;
v16f32_dft2=v16f32_dft2+v16f32_tmp;
v16f32_tmp.even=v16f32_dft7.even*(-0.707107f)-v16f32_dft7.odd*(-0.707107f);
v16f32_tmp.odd=v16f32_dft7.odd*(-0.707107f)+v16f32_dft7.even*(-0.707107f);
v16f32_dft7=v16f32_dft3-v16f32_tmp;
v16f32_dft3=v16f32_dft3+v16f32_tmp;
VSTORE(v16f32_dft0,dst+v8s32_dst_idx.s0,16);
VSTORE(v16f32_dft1,dst+v8s32_dst_idx.s1,16);
VSTORE(v16f32_dft2,dst+v8s32_dst_idx.s2,16);
VSTORE(v16f32_dft3,dst+v8s32_dst_idx.s3,16);
VSTORE(v16f32_dft4,dst+v8s32_dst_idx.s4,16);
VSTORE(v16f32_dft5,dst+v8s32_dst_idx.s5,16);
VSTORE(v16f32_dft6,dst+v8s32_dst_idx.s6,16);
VSTORE(v16f32_dft7,dst+v8s32_dst_idx.s7,16);
}

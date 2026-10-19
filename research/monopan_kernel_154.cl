kernel void GridDft4x4(global Tp*src,int istep,
global float*dst,int ostep,
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
int4 v4s32_src_idx=mad24(offset_y+(int4)(0,1,2,3),istep,offset_x);
int4 v4s32_dst_idx=mad24(offset_y+(int4)(0,1,2,3),ostep,offset_x<<1);
float4 v4f32_src0=CONVERT(VLOAD(src+v4s32_src_idx.s0,4),float4);
float4 v4f32_src1=CONVERT(VLOAD(src+v4s32_src_idx.s1,4),float4);
float4 v4f32_src2=CONVERT(VLOAD(src+v4s32_src_idx.s2,4),float4);
float4 v4f32_src3=CONVERT(VLOAD(src+v4s32_src_idx.s3,4),float4);
float4 v4f32_tmp_src0=(float4)(v4f32_src0.lo,v4f32_src1.lo);
float4 v4f32_tmp_src1=(float4)(v4f32_src0.hi,v4f32_src1.hi);
float4 v4f32_tmp_src2=(float4)(v4f32_src2.lo,v4f32_src3.lo);
float4 v4f32_tmp_src3=(float4)(v4f32_src2.hi,v4f32_src3.hi);
float4 v4f32_sum01=v4f32_tmp_src0+v4f32_tmp_src1;
float4 v4f32_sub01=v4f32_tmp_src0-v4f32_tmp_src1;
float4 v4f32_sum23=v4f32_tmp_src2+v4f32_tmp_src3;
float4 v4f32_sub23=v4f32_tmp_src2-v4f32_tmp_src3;
float8 v8f32_dst0,v8f32_dst1,v8f32_dst2,v8f32_dst3;
{
float4 v4f32_tmp_val=v4f32_sum01+v4f32_sum23;
float2 v2f32_tmp0=v4f32_tmp_val.even+v4f32_tmp_val.odd;
float2 v2f32_tmp1=v4f32_tmp_val.even-v4f32_tmp_val.odd;
v8f32_dst0.s01=(float2)(v2f32_tmp0.s0+v2f32_tmp0.s1,0);
v8f32_dst0.s45=(float2)(v2f32_tmp1.s0+v2f32_tmp1.s1,0);
v8f32_dst2.s01=(float2)(v2f32_tmp0.s0-v2f32_tmp0.s1,0);
v8f32_dst2.s45=(float2)(v2f32_tmp1.s0-v2f32_tmp1.s1,0);
}
{
float4 v4f32_tmp_val=v4f32_sub01+v4f32_sub23;
float2 v2f32_tmp0=v4f32_tmp_val.lo+v4f32_tmp_val.hi;
float2 v2f32_tmp1=v4f32_tmp_val.lo-v4f32_tmp_val.hi;
v8f32_dst0.s23=(float2)(v2f32_tmp0.s0,-v2f32_tmp0.s1);
v8f32_dst0.s67=(float2)(v2f32_tmp0.s0,v2f32_tmp0.s1);
v8f32_dst2.s23=(float2)(v2f32_tmp1.s0,-v2f32_tmp1.s1);
v8f32_dst2.s67=(float2)(v2f32_tmp1.s0,v2f32_tmp1.s1);
}
{
float4 v4f32_tmp_val=v4f32_sum01-v4f32_sum23;
float2 v2f32_tmp0=v4f32_tmp_val.even+v4f32_tmp_val.odd;
float2 v2f32_tmp1=v4f32_tmp_val.even-v4f32_tmp_val.odd;
v8f32_dst1.s01=(float2)(v2f32_tmp0.s0,-v2f32_tmp0.s1);
v8f32_dst1.s45=(float2)(v2f32_tmp1.s0,-v2f32_tmp1.s1);
v8f32_dst3.s01=(float2)(v2f32_tmp0.s0,v2f32_tmp0.s1);
v8f32_dst3.s45=(float2)(v2f32_tmp1.s0,v2f32_tmp1.s1);
}
{
float4 v4f32_tmp_val=v4f32_sub01-v4f32_sub23;
float2 v2f32_tmp0=v4f32_tmp_val.lo+rot_l2_1(v4f32_tmp_val.hi);
float2 v2f32_tmp1=v4f32_tmp_val.lo-rot_l2_1(v4f32_tmp_val.hi);
v8f32_dst1.s23=(float2)(v2f32_tmp1.s0,-v2f32_tmp0.s1);
v8f32_dst1.s67=(float2)(v2f32_tmp0.s0,v2f32_tmp1.s1);
v8f32_dst3.s23=(float2)(v2f32_tmp0.s0,-v2f32_tmp1.s1);
v8f32_dst3.s67=(float2)(v2f32_tmp1.s0,v2f32_tmp0.s1);
}
VSTORE(v8f32_dst0,dst+v4s32_dst_idx.s0,8);
VSTORE(v8f32_dst1,dst+v4s32_dst_idx.s1,8);
VSTORE(v8f32_dst2,dst+v4s32_dst_idx.s2,8);
VSTORE(v8f32_dst3,dst+v4s32_dst_idx.s3,8);
}

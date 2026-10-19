kernel void Filter2dMain5x5C3(global Tp*src,int istep,
global Tp*dst,int ostep,
int height,int y_work_size,int x_work_size,
constant float*filter MAX_CONSTANT_SIZE,
struct Scalar border_value)
{
const int gx=get_global_id(0);
int gy=get_global_id(1);
const int elem_counts=1;
const int ksh=2;
const int channel=3;
const int x_idx=gx*elem_counts*channel;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
V16Tp v16f32_src[6];
V3Tp v3tp_result;
int8 v8s32_offset_src;
int2 v2s32_offset_dst;
float3 v3f32_result0=(float3)0,v3f32_result1=(float3)0;
gy=min(gy<<1,height-2);
if((gy>=ksh)&&((gy+1)<(height-ksh)))
{
v8s32_offset_src=mad24(gy+(int8)(-2,-1,0,1,2,3,0,0),istep,x_idx);
v16f32_src[0]=VLOAD(src+v8s32_offset_src.s0,16);
v16f32_src[1]=VLOAD(src+v8s32_offset_src.s1,16);
v16f32_src[2]=VLOAD(src+v8s32_offset_src.s2,16);
v16f32_src[3]=VLOAD(src+v8s32_offset_src.s3,16);
v16f32_src[4]=VLOAD(src+v8s32_offset_src.s4,16);
v16f32_src[5]=VLOAD(src+v8s32_offset_src.s5,16);
}
else
{
#if BORDER_CONSTANT
short4 v4s16_flag_border;
v4s16_flag_border.lo=convert_short2(TOP_BORDER_IDX(gy+(int2)(-2,-1)));
v4s16_flag_border.hi=convert_short2(BOTTOM_BORDER_IDX(gy+(int2)(2,3),height));
v8s32_offset_src=mad24((int8)(convert_int4(abs(v4s16_flag_border)),gy+(int4)(0,1,0,0)),istep,x_idx);
v4s16_flag_border=isequal(convert_half4(v4s16_flag_border),(half4)(-1.f));
short4 v4s16_flag_body=v4s16_flag_border+(short4)(1);
v16f32_src[0]=v4s16_flag_body.s0?VLOAD(src+v8s32_offset_src.s0,16):(V16Tp)border_value.val[0];
v16f32_src[1]=v4s16_flag_body.s1?VLOAD(src+v8s32_offset_src.s1,16):(V16Tp)border_value.val[0];
v16f32_src[2]=VLOAD(src+v8s32_offset_src.s4,16);
v16f32_src[3]=VLOAD(src+v8s32_offset_src.s5,16);
v16f32_src[4]=v4s16_flag_body.s2?VLOAD(src+v8s32_offset_src.s2,16):(V16Tp)border_value.val[0];
v16f32_src[5]=v4s16_flag_body.s3?VLOAD(src+v8s32_offset_src.s3,16):(V16Tp)border_value.val[0];
#elif BORDER_REFLECT_101
int8 v8_s32_offset_y=convert_int8(abs(gy+(int8)(-2,-1,0,1,2,3,0,0)));
v8s32_offset_src=mad24(select(v8_s32_offset_y,((height-1)<<1)-v8_s32_offset_y,v8_s32_offset_y>(height-1)),istep,x_idx);
v16f32_src[0]=VLOAD(src+v8s32_offset_src.s0,16);
v16f32_src[1]=VLOAD(src+v8s32_offset_src.s1,16);
v16f32_src[2]=VLOAD(src+v8s32_offset_src.s2,16);
v16f32_src[3]=VLOAD(src+v8s32_offset_src.s3,16);
v16f32_src[4]=VLOAD(src+v8s32_offset_src.s4,16);
v16f32_src[5]=VLOAD(src+v8s32_offset_src.s5,16);
#else
v8s32_offset_src=mad24(clamp(gy+(int8)(-2,-1,0,1,2,3,0,0),0,height-1),istep,x_idx);
v16f32_src[0]=VLOAD(src+v8s32_offset_src.s0,16);
v16f32_src[1]=VLOAD(src+v8s32_offset_src.s1,16);
v16f32_src[2]=VLOAD(src+v8s32_offset_src.s2,16);
v16f32_src[3]=VLOAD(src+v8s32_offset_src.s3,16);
v16f32_src[4]=VLOAD(src+v8s32_offset_src.s4,16);
v16f32_src[5]=VLOAD(src+v8s32_offset_src.s5,16);
#endif
}
__attribute__((opencl_unroll_hint(5)))
for(int i=0;i<5;++i)
{
const int ker_id=5*i;
v3f32_result0+=FILTER2D_CONVERT(v16f32_src[i].s012,float3)*filter[ker_id]+FILTER2D_CONVERT(v16f32_src[i].s345,float3)*filter[ker_id+1]+
FILTER2D_CONVERT(v16f32_src[i].s678,float3)*filter[ker_id+2]+FILTER2D_CONVERT(v16f32_src[i].s9AB,float3)*filter[ker_id+3]+
FILTER2D_CONVERT(v16f32_src[i].sCDE,float3)*filter[ker_id+4];
v3f32_result1+=FILTER2D_CONVERT(v16f32_src[i+1].s012,float3)*filter[ker_id]+FILTER2D_CONVERT(v16f32_src[i+1].s345,float3)*filter[ker_id+1]+
FILTER2D_CONVERT(v16f32_src[i+1].s678,float3)*filter[ker_id+2]+FILTER2D_CONVERT(v16f32_src[i+1].s9AB,float3)*filter[ker_id+3]+
FILTER2D_CONVERT(v16f32_src[i+1].sCDE,float3)*filter[ker_id+4];
}
v2s32_offset_dst=mad24(gy+(int2)(0,1),ostep,x_idx+ksh*channel);
v3tp_result=CONVERT_SAT(v3f32_result0,V3Tp);
VSTORE(v3tp_result,dst+v2s32_offset_dst.s0,3);
v3tp_result=CONVERT_SAT(v3f32_result1,V3Tp);
VSTORE(v3tp_result,dst+v2s32_offset_dst.s1,3);
}

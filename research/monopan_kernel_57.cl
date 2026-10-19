kernel void Filter2dMain3x3C3(global Tp*src,int istep,
global Tp*dst,int ostep,
int height,int y_work_size,int x_work_size,
constant float*filter MAX_CONSTANT_SIZE,
struct Scalar border_value)
{
const int gx=get_global_id(0);
const int gy=get_global_id(1);
const int elem_counts=6;
const int ksh=1;
const int channel=3;
const int x_idx=gx*elem_counts*channel;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int3 v3s32_offset_src;
float16 v16f32_src[3];
float8 v8f32_src[3];
if((gy>=ksh)&&(gy<(height-ksh)))
{
v3s32_offset_src=mad24(gy+(int3)(-1,0,1),istep,x_idx);
v16f32_src[0]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s0,16),float16);
v8f32_src[0]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s0+16,8),float8);
v16f32_src[1]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s1,16),float16);
v8f32_src[1]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s1+16,8),float8);
v16f32_src[2]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s2,16),float16);
v8f32_src[2]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s2+16,8),float8);
}
else
{
#if BORDER_CONSTANT
short2 v2s16_flag_border=convert_short2((int2)(TOP_BORDER_IDX(gy-1),BOTTOM_BORDER_IDX(gy+1,height)));
v3s32_offset_src=mad24((int3)(convert_int2(abs(v2s16_flag_border)),gy),istep,x_idx);
v2s16_flag_border=isequal(convert_half2(v2s16_flag_border),(half2)(-1.f));
float3 v3f32_border_value={(float)border_value.val[0],(float)border_value.val[1],(float)border_value.val[2]};
float16 v16f32_border_value={v3f32_border_value,v3f32_border_value,v3f32_border_value,v3f32_border_value,v3f32_border_value,v3f32_border_value.s0};
float8 v8f32_border_value={v3f32_border_value.s12,v3f32_border_value,v3f32_border_value};
v16f32_src[0]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s0,16),float16)*(float)(v2s16_flag_border.s0+(short)1)+
v16f32_border_value*(float)(abs(v2s16_flag_border.s0));
v8f32_src[0]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s0+16,8),float8)*(float)(v2s16_flag_border.s0+(short)1)+
v8f32_border_value*(float)(abs(v2s16_flag_border.s0));
v16f32_src[1]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s2,16),float16);
v8f32_src[1]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s2+16,8),float8);
v16f32_src[2]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s1,16),float16)*(float)(v2s16_flag_border.s1+(short)1)+
v16f32_border_value*(float)(abs(v2s16_flag_border.s1));
v8f32_src[2]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s1+16,8),float8)*(float)(v2s16_flag_border.s1+(short)1)+
v8f32_border_value*(float)(abs(v2s16_flag_border.s1));
#elif BORDER_REFLECT_101
int3 v3s32_offset_y=convert_int3(abs(gy+(int3)(-1,0,1)));
v3s32_offset_src=mad24(select(v3s32_offset_y,((height-1)<<1)-v3s32_offset_y,v3s32_offset_y>height-1),istep,x_idx);
v16f32_src[0]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s0,16),float16);
v8f32_src[0]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s0+16,8),float8);
v16f32_src[1]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s1,16),float16);
v8f32_src[1]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s1+16,8),float8);
v16f32_src[2]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s2,16),float16);
v8f32_src[2]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s2+16,8),float8);
#else
v3s32_offset_src=mad24(clamp(gy+(int3)(-1,0,1),0,height-1),istep,x_idx);
v16f32_src[0]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s0,16),float16);
v8f32_src[0]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s0+16,8),float8);
v16f32_src[1]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s1,16),float16);
v8f32_src[1]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s1+16,8),float8);
v16f32_src[2]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s2,16),float16);
v8f32_src[2]=FILTER2D_CONVERT(VLOAD(src+v3s32_offset_src.s2+16,8),float8);
#endif
}
float16 v16f32_sum_l,v16f32_sum_c,v16f32_sum_r;
float2 v2f32_sum_l,v2f32_sum_c,v2f32_sum_r;
float16 v16f32_result=(float16)0;
float2 v2f32_result=(float2)0;
__attribute__((opencl_unroll_hint(3)))
for(int i=0;i<3;++i)
{
const int ker_id=3*i;
v16f32_sum_l=v16f32_src[i]*(filter[ker_id+0]);
v2f32_sum_l=v8f32_src[i].s01*(filter[ker_id+0]);
v16f32_sum_c=(float16){v16f32_src[i].s3456789A,v16f32_src[i].sBCD,v16f32_src[i].sEF,v8f32_src[i].s012}*(filter[ker_id+1]);
v2f32_sum_c=v8f32_src[i].s34*(filter[ker_id+1]);
v16f32_sum_r=(float16){v16f32_src[i].s6789ABCD,v16f32_src[i].sEF,v8f32_src[i].s0123,v8f32_src[i].s45}*(filter[ker_id+2]);
v2f32_sum_r=v8f32_src[i].s67*(filter[ker_id+2]);
v16f32_result+=v16f32_sum_l+v16f32_sum_c+v16f32_sum_r;
v2f32_result+=v2f32_sum_l+v2f32_sum_c+v2f32_sum_r;
}
V16Tp v16tp_result=CONVERT_SAT(v16f32_result,V16Tp);
V2Tp v2tp_result=CONVERT_SAT(v2f32_result,V2Tp);
int offset_dst=mad24(gy,ostep,x_idx+ksh*channel);
VSTORE(v16tp_result,dst+offset_dst,16);
VSTORE(v2tp_result,dst+offset_dst+16,2);
}

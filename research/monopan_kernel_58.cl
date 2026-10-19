kernel void Filter2dMain3x3C3(global Tp*src,int istep,
global Tp*dst,int ostep,
int height,int y_work_size,int x_work_size,
constant float*filter MAX_CONSTANT_SIZE,
struct Scalar border_value)
{
const int gx=get_global_id(0);
const int gy=get_global_id(1);
const int elem_counts=3;
const int ksh=1;
const int channel=3;
const int x_idx=gx*elem_counts*channel;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int3 v3s32_offset_src;
V16Tp v16tp_src[3];
if((gy>=ksh)&&(gy<(height-ksh)))
{
v3s32_offset_src=mad24(gy+(int3)(-1,0,1),istep,x_idx);
v16tp_src[0]=VLOAD(src+v3s32_offset_src.s0,16);
v16tp_src[1]=VLOAD(src+v3s32_offset_src.s1,16);
v16tp_src[2]=VLOAD(src+v3s32_offset_src.s2,16);
}
else
{
#if BORDER_CONSTANT
short2 v2s16_flag_border=convert_short2((int2)(TOP_BORDER_IDX(gy-1),BOTTOM_BORDER_IDX(gy+1,height)));
v3s32_offset_src=mad24((int3)(convert_int2(abs(v2s16_flag_border)),gy),istep,x_idx);
v2s16_flag_border=isequal(convert_half2(v2s16_flag_border),(half2)(-1.f));
V3Tp v3tp_border_value={(VTp)border_value.val[0],(VTp)border_value.val[1],(VTp)border_value.val[2]};
V16Tp v16tp_border_value={v3tp_border_value,v3tp_border_value,v3tp_border_value,v3tp_border_value,v3tp_border_value,v3tp_border_value.s0};
v16tp_src[0]=(v2s16_flag_border.s0+(short)1)?VLOAD(src+v3s32_offset_src.s0,16):v16tp_border_value;
v16tp_src[1]=VLOAD(src+v3s32_offset_src.s2,16);
v16tp_src[2]=(v2s16_flag_border.s1+(short)1)?VLOAD(src+v3s32_offset_src.s1,16):v16tp_border_value;
#elif BORDER_REFLECT_101
int3 v3s32_offset_y=convert_int3(abs(gy+(int3)(-1,0,1)));
v3s32_offset_src=mad24(select(v3s32_offset_y,((height-1)<<1)-v3s32_offset_y,v3s32_offset_y>height-1),istep,x_idx);
v16tp_src[0]=VLOAD(src+v3s32_offset_src.s0,16);
v16tp_src[1]=VLOAD(src+v3s32_offset_src.s1,16);
v16tp_src[2]=VLOAD(src+v3s32_offset_src.s2,16);
#else
v3s32_offset_src=mad24(clamp(gy+(int3)(-1,0,1),0,height-1),istep,x_idx);
v16tp_src[0]=VLOAD(src+v3s32_offset_src.s0,16);
v16tp_src[1]=VLOAD(src+v3s32_offset_src.s1,16);
v16tp_src[2]=VLOAD(src+v3s32_offset_src.s2,16);
#endif
}
float16 v16f32_src;
float8 v16f32_result0=(float8)0;
float v16f32_result1=(float)0;
__attribute__((opencl_unroll_hint(3)))
for(int i=0;i<3;++i)
{
const int ker_id=3*i;
v16f32_src=FILTER2D_CONVERT(v16tp_src[i],float16);
v16f32_result0+=v16f32_src.s01234567*filter[ker_id]+v16f32_src.s3456789A*filter[ker_id+1]+
v16f32_src.s6789ABCD*filter[ker_id+2];
v16f32_result1+=v16f32_src.s8*(filter[ker_id+0])+
v16f32_src.sB*(filter[ker_id+1])+
v16f32_src.sE*(filter[ker_id+2]);
}
int offset_dst=mad24(gy,ostep,x_idx+ksh*channel);
V8Tp v16tp_result=CONVERT_SAT(v16f32_result0,V8Tp);
VSTORE(v16tp_result,dst+offset_dst,8);
VTp v16tp_result1=CONVERT_SAT(v16f32_result1,VTp);
VSTORE(v16tp_result1,dst+offset_dst+8,1);
}

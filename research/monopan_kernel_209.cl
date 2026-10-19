kernel void WarpBnC2(read_only image2d_t src,int iheight,int iwidth,
global Tp*dst,int oheight,int owidth,int ostep,
global float*map_x_row,
global float*map_y_row,
struct Scalar border_value)
{
int x_idx=get_global_id(0)*ELEM_COUNTS_C2;
int y_idx=get_global_id(1)*ELEM_HEIGHT;
if(x_idx>=owidth||(y_idx>=oheight))
{
return;
}
x_idx=min(x_idx,owidth-ELEM_COUNTS_C2);
#if BORDER_CONSTANT
V2Tp v2tp_border_val={(Tp)border_value.val[0],(Tp)border_value.val[1]};
VS32 vs32_src_border;
vs32_src_border.even=iwidth-1;
vs32_src_border.odd=iheight-1;
#elif BORDER_REPLICATE
VS32 vs32_src_border;
vs32_src_border.even=iwidth-1;
vs32_src_border.odd=iheight-1;
#elif BORDER_REFLECT_101
#if ELEM_COUNTS==1
int8 v8s32_src_border;
v8s32_src_border.even=iwidth-1;
v8s32_src_border.odd=iheight-1;
#else
int16 v16s32_src_border;
v16s32_src_border.even=iwidth-1;
v16s32_src_border.odd=iheight-1;
#endif
#endif
#pragma unroll
for(int i=0;i<ELEM_HEIGHT;i++,y_idx++)
{
if(y_idx>=oheight)
{
return;
}
VF32C2 vf32_offset;
#if WARP_AFFINE
WARP_AFFINE_OFFSET(vf32_offset,map_x_row,map_y_row,x_idx,(y_idx<<1))
#elif WARP_PERSPECTIVE
WARP_PERSPECTIVE_OFFSET(vf32_offset,map_x_row,map_y_row,(x_idx>>1),y_idx,ELEM_COUNTS)
#endif
VS32 vs32_offset=CONVERT_SAT_ROUND(vf32_offset*REMAP_INTER_TAB_SIZE,VS32,rte);
VS32 vs32_coef=vs32_offset&(VS32)(REMAP_INTER_TAB_SIZE-1);
vs32_offset=vs32_offset>>REMAP_SCALE_BITS_HALF;
VF32 vf32_xy0=native_divide(CONVERT(vs32_coef,VF32),32.f);
VF32 vf32_xy1=(VF32)(1.f)-vf32_xy0;
VF32 vf32_weight[4];
vf32_weight[0].even=vf32_xy1.even*vf32_xy1.odd;
vf32_weight[1].even=vf32_xy0.even*vf32_xy1.odd;
vf32_weight[2].even=vf32_xy1.even*vf32_xy0.odd;
vf32_weight[3].even=vf32_xy0.even*vf32_xy0.odd;
vf32_weight[0].odd=vf32_weight[0].even;
vf32_weight[1].odd=vf32_weight[1].even;
vf32_weight[2].odd=vf32_weight[2].even;
vf32_weight[3].odd=vf32_weight[3].even;
VTp vtp_src[4];
#if BORDER_CONSTANT
VS8 vs8_border_flag=CONVERT(((vs32_offset>vs32_src_border)+(vs32_offset<(VS32)(-1)))*(-1),VS8);
vs8_border_flag.lo=vs8_border_flag.even+vs8_border_flag.odd;
LINEAR_CONSTANT_LOAD(vtp_src,vs32_offset,vs8_border_flag,v2tp_border_val,ELEM_COUNTS)
#elif BORDER_REPLICATE
vs32_offset=min(vs32_offset,vs32_src_border);
LINEAR_REPLICATE_LOAD(vtp_src,vs32_offset,ELEM_COUNTS)
#elif BORDER_REFLECT_101
LINEAR_REFLECT_101_LOAD(vtp_src,vs32_offset,ELEM_COUNTS)
#endif
VF32 vf32_sum0=vf32_weight[0]*CONVERT(vtp_src[0],VF32);
VF32 vf32_sum1=vf32_weight[1]*CONVERT(vtp_src[1],VF32);
VF32 vf32_sum2=vf32_weight[2]*CONVERT(vtp_src[2],VF32);
VF32 vf32_sum3=vf32_weight[3]*CONVERT(vtp_src[3],VF32);
VTp vtp_result=WARP_CONVERT_SRC((vf32_sum0+vf32_sum1+vf32_sum2+vf32_sum3),VTp,rte);
global Tp*dst_row=dst+mad24(y_idx,ostep,x_idx);
VSTORE(vtp_result,dst_row,ELEM_LENGTH);
}
}

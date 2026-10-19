kernel void RemapBnC1(read_only image2d_t src,int iheight,int iwidth,
global Tp*dst,int oheight,int owidth,int ostep,
global float*map,int mstep,
struct Scalar border_value)
{
int x_idx=get_global_id(0)*ELEM_COUNTS;
int y_idx=get_global_id(1)*ELEM_HEIGHT;
if(x_idx>=owidth||(y_idx>=oheight))
{
return;
}
x_idx=min(x_idx,owidth-ELEM_COUNTS);
#if BORDER_REFLECT_101
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
global MapType*map_row=map+mad24(y_idx,mstep,x_idx*2);
VF32C2 vf32_offset=VLOAD(map_row,ELEM_COUNTS_C2);
VS32C2 vs32_offset=CONVERT_SAT_ROUND(vf32_offset*REMAP_INTER_TAB_SIZE,VS32C2,rte);
VS32C2 vs32_coef=vs32_offset&(VS32C2)(REMAP_INTER_TAB_SIZE-1);
vs32_offset=vs32_offset>>REMAP_SCALE_BITS_HALF;
VF32C2 vf32_xy0=native_divide(CONVERT(vs32_coef,VF32C2),32.f);
VF32C2 vf32_xy1=(VF32C2)(1.f)-vf32_xy0;
VF32C2 vf32_weight[2];
vf32_weight[0].even=vf32_xy1.even*vf32_xy1.odd;
vf32_weight[0].odd=vf32_xy0.even*vf32_xy1.odd;
vf32_weight[1].even=vf32_xy1.even*vf32_xy0.odd;
vf32_weight[1].odd=vf32_xy0.even*vf32_xy0.odd;
VTpC2 vtp_src[2];
#if BORDER_CONSTANT
VS32 vs32_border_flag=(vs32_offset.even>=iwidth)+(vs32_offset.odd>=iheight)+(vs32_offset.even<-1)+(vs32_offset.odd<-1);
LINEAR_CONSTANT_LOAD(vtp_src,vs32_offset,vs32_border_flag,ELEM_COUNTS)
#elif BORDER_REPLICATE
vs32_offset.odd=min(vs32_offset.odd,(VS32)(iheight-1));
LINEAR_REPLICATE_LOAD(vtp_src,vs32_offset,ELEM_COUNTS)
#elif BORDER_REFLECT_101
LINEAR_REFLECT_101_LOAD(vtp_src,vs32_offset,ELEM_COUNTS)
#endif
VF32C2 vf32_sum0=vf32_weight[0]*CONVERT(vtp_src[0],VF32C2);
VF32C2 vf32_sum1=vf32_weight[1]*CONVERT(vtp_src[1],VF32C2);
VTp vtp_result=WARP_CONVERT_SRC((vf32_sum0.even+vf32_sum0.odd+vf32_sum1.even+vf32_sum1.odd),VTp,rte);
global Tp*dst_row=dst+mad24(y_idx,ostep,x_idx);
VSTORE(vtp_result,dst_row,ELEM_LENGTH);
}
}

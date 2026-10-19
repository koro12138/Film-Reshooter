kernel void RemapCuC1(read_only image2d_t src,int iheight,int iwidth,
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
#if BORDER_CONSTANT
VS32C2 vs32_src_border;
vs32_src_border.even=iwidth-1;
vs32_src_border.odd=iheight-1;
#elif BORDER_REFLECT_101
int16 v16s32_src_border;
v16s32_src_border.even=iwidth-1;
v16s32_src_border.odd=iheight-1;
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
vs32_offset-=1;
VF32C2 vf32_xy=native_divide(CONVERT(vs32_coef,VF32C2),32.f);
VF32C4 vf32_weight[2];
CALC_WARP_CUBIC_WEIGHT(vf32_weight,vf32_xy,ELEM_COUNTS)
VTp vtp_result;
#if BORDER_CONSTANT
VS8 vs8_outof_border;
VS8C2 vs8_label_border;
VS32C2 vs32_result;
vs32_result=vs32_src_border-min(vs32_src_border,vs32_offset);
vs8_label_border=CONVERT_SAT((VS32C2)3-min(vs32_result,(VS32C2)3),VS8C2);
vs32_result=min(max(vs32_offset,(VS32C2)(-3)),(VS32C2)0);
vs8_label_border=CONVERT_SAT(vs32_result,VS8C2)+vs8_label_border;
vs32_result=(vs32_offset>vs32_src_border)+(vs32_offset<(VS32C2)(-3));
vs8_outof_border=CONVERT((vs32_result.even+vs32_result.odd),VS8);
CUBIC_CONSTANT_LOAD(vtp_result,vs32_offset,vf32_weight,vs8_outof_border,vs8_label_border,ELEM_COUNTS)
#elif BORDER_REPLICATE
vs32_offset.odd=min(vs32_offset.odd,iheight-1);
CUBIC_REPLICATE_LOAD(vtp_result,vs32_offset,vf32_weight,ELEM_COUNTS)
#elif BORDER_REFLECT_101
CUBIC_REFLECT_101_LOAD(vtp_result,vs32_offset,vf32_weight,ELEM_COUNTS)
#endif
global Tp*dst_row=dst+mad24(y_idx,ostep,x_idx);
VSTORE(vtp_result,dst_row,ELEM_COUNTS);
}
}

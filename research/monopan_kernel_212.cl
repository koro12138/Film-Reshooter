kernel void WarpNnC1(read_only image2d_t src,int iheight,int iwidth,
global Tp*dst,int oheight,int owidth,int ostep,
global float*map_x_row,
global float*map_y_row,
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
VTp vtp_border_val;
vtp_border_val=(VTp)border_value.val[0];
#elif BORDER_REFLECT_101
VS32C2 vs32_src_border;
vs32_src_border.even=iwidth-1;
vs32_src_border.odd=iheight-1;
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
WARP_AFFINE_OFFSET(vf32_offset,map_x_row,map_y_row,(x_idx<<1),(y_idx<<1))
#elif WARP_PERSPECTIVE
WARP_PERSPECTIVE_OFFSET(vf32_offset,map_x_row,map_y_row,x_idx,y_idx,ELEM_COUNTS)
#endif
VS32C2 vs32_offset=CONVERT_SAT_ROUND(vf32_offset,VS32C2,rte);
#if BORDER_CONSTANT
VS32 vs32_border_flag=(vs32_offset.even>=iwidth)+(vs32_offset.odd>=iheight)+(vs32_offset.even<0)+(vs32_offset.odd<0);
#elif BORDER_REPLICATE
vs32_offset.odd=min(vs32_offset.odd,iheight-1);
#elif BORDER_REFLECT_101
VS32C2 vs32_quotient,vs32_remainder;
vs32_offset=CONVERT_SAT(abs(vs32_offset),VS32C2);
vs32_quotient=vs32_offset/vs32_src_border;
vs32_remainder=vs32_offset-vs32_src_border*vs32_quotient;
vs32_offset=select(vs32_src_border-vs32_remainder,vs32_remainder,(vs32_quotient&1)-1);
#endif
VTp vtp_result;
NEAREST_LOAD(vtp_result,vs32_offset,ELEM_COUNTS);
#if BORDER_CONSTANT
vtp_result=select(vtp_result,vtp_border_val,CONVERT(vs32_border_flag!=(VS32)0,VTYPE(SelectType,ELEM_LENGTH)));
#endif
global Tp*dst_row=dst+mad24(y_idx,ostep,x_idx);
VSTORE(vtp_result,dst_row,ELEM_LENGTH);
}
}

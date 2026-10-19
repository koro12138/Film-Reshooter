kernel void MedianFilter3x3C1(global Tp*src,int istep,
global Tp*dst,int ostep,
int height,int width,
int y_work_size,int x_work_size)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
if(gx>=x_work_size||gy>=y_work_size)
{
return;
}
gx=min(gx<<2,width-4);
gy=min(gy<<1,height-2);
int2 v2s32_gx_border={gx-1,gx+4};
v2s32_gx_border=clamp(v2s32_gx_border,0,width-1);
int4 v4s32_gy_src={gy-1,gy,gy+1,gy+2};
v4s32_gy_src=clamp(v4s32_gy_src,0,height-1);
int4 v4s32_src_offset=v4s32_gy_src*istep;
V8Tp v8tp_src_row0={VLOAD(src+v4s32_src_offset.s0+v2s32_gx_border.s0,1),
VLOAD(src+v4s32_src_offset.s0+gx,4),
VLOAD(src+v4s32_src_offset.s0+v2s32_gx_border.s1,1),
0,0};
V8Tp v8tp_src_row1={VLOAD(src+v4s32_src_offset.s1+v2s32_gx_border.s0,1),
VLOAD(src+v4s32_src_offset.s1+gx,4),
VLOAD(src+v4s32_src_offset.s1+v2s32_gx_border.s1,1),
0,0};
V8Tp v8tp_src_row2={VLOAD(src+v4s32_src_offset.s2+v2s32_gx_border.s0,1),
VLOAD(src+v4s32_src_offset.s2+gx,4),
VLOAD(src+v4s32_src_offset.s2+v2s32_gx_border.s1,1),
0,0};
V8Tp v8tp_src_row3={VLOAD(src+v4s32_src_offset.s3+v2s32_gx_border.s0,1),
VLOAD(src+v4s32_src_offset.s3+gx,4),
VLOAD(src+v4s32_src_offset.s3+v2s32_gx_border.s1,1),
0,0};
V4Tp v4tp_row0_l=CONVERT(v8tp_src_row0.s0123,V4Tp);
V4Tp v4tp_row1_l=CONVERT(v8tp_src_row1.s0123,V4Tp);
V4Tp v4tp_row2_l=CONVERT(v8tp_src_row2.s0123,V4Tp);
V4Tp v4tp_row3_l=CONVERT(v8tp_src_row3.s0123,V4Tp);
V4Tp v4tp_row0_c=CONVERT(v8tp_src_row0.s1234,V4Tp);
V4Tp v4tp_row1_c=CONVERT(v8tp_src_row1.s1234,V4Tp);
V4Tp v4tp_row2_c=CONVERT(v8tp_src_row2.s1234,V4Tp);
V4Tp v4tp_row3_c=CONVERT(v8tp_src_row3.s1234,V4Tp);
V4Tp v4tp_row0_r=CONVERT(v8tp_src_row0.s2345,V4Tp);
V4Tp v4tp_row1_r=CONVERT(v8tp_src_row1.s2345,V4Tp);
V4Tp v4tp_row2_r=CONVERT(v8tp_src_row2.s2345,V4Tp);
V4Tp v4tp_row3_r=CONVERT(v8tp_src_row3.s2345,V4Tp);
SORT2ElemX4(v4tp_row1_c,v4tp_row1_r);
SORT2ElemX4(v4tp_row2_c,v4tp_row2_r);
SORT2ElemX4(v4tp_row1_l,v4tp_row1_c);
SORT2ElemX4(v4tp_row2_l,v4tp_row2_c);
SORT2ElemX4(v4tp_row1_c,v4tp_row1_r);
SORT2ElemX4(v4tp_row2_c,v4tp_row2_r);
SORT2ElemX4(v4tp_row1_c,v4tp_row2_c);
v4tp_row1_r=min(v4tp_row1_r,v4tp_row2_r);
SORT2ElemX4(v4tp_row0_c,v4tp_row0_r);
SORT2ElemX4(v4tp_row3_c,v4tp_row3_r);
SORT2ElemX4(v4tp_row0_l,v4tp_row0_c);
SORT2ElemX4(v4tp_row3_l,v4tp_row3_c);
SORT2ElemX4(v4tp_row0_c,v4tp_row0_r);
SORT2ElemX4(v4tp_row3_c,v4tp_row3_r);
v4tp_row2_r=v4tp_row1_l;
v4tp_row1_l=max(v4tp_row0_l,v4tp_row1_l);
v4tp_row0_l=v4tp_row2_l;
v4tp_row2_l=max(v4tp_row1_l,v4tp_row2_l);
v4tp_row2_r=max(v4tp_row3_l,v4tp_row2_r);
v4tp_row0_l=max(v4tp_row2_r,v4tp_row0_l);
v4tp_row2_r=v4tp_row1_r;
v4tp_row0_r=min(v4tp_row0_r,v4tp_row1_r);
v4tp_row3_r=min(v4tp_row3_r,v4tp_row2_r);
v4tp_row2_r=v4tp_row1_c;
v4tp_row1_c=max(v4tp_row0_c,v4tp_row1_c);
v4tp_row0_c=v4tp_row2_c;
v4tp_row1_c=min(v4tp_row1_c,v4tp_row2_c);
v4tp_row2_r=max(v4tp_row3_c,v4tp_row2_r);
v4tp_row2_r=min(v4tp_row2_r,v4tp_row0_c);
SORT2ElemX4(v4tp_row1_c,v4tp_row0_r);
SORT2ElemX4(v4tp_row2_r,v4tp_row3_r);
v4tp_row1_c=max(v4tp_row2_l,v4tp_row1_c);
v4tp_row1_c=min(v4tp_row1_c,v4tp_row0_r);
v4tp_row2_r=max(v4tp_row0_l,v4tp_row2_r);
v4tp_row2_r=min(v4tp_row2_r,v4tp_row3_r);
int dst_idx=mad24(gy,ostep,gx);
VSTORE(v4tp_row1_c,dst+dst_idx,4);
VSTORE(v4tp_row2_r,dst+dst_idx+ostep,4);
}

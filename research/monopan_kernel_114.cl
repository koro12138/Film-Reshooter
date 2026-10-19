kernel void MedianFilter3x3C2(global Tp*src,int istep,
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
gx=min(gx<<3,width*2-8);
gy=min(gy<<1,height-2);
int2 v2s32_gx_border={gx-2,gx+8};
v2s32_gx_border=clamp(v2s32_gx_border,0,width*2-2);
int4 v4s32_gy_src={gy-1,gy,gy+1,gy+2};
v4s32_gy_src=clamp(v4s32_gy_src,0,height-1);
int4 v4s32_src_offset=v4s32_gy_src*istep;
V16Tp v16tp_src_row0={VLOAD(src+v4s32_src_offset.s0+v2s32_gx_border.s0,2),
VLOAD(src+v4s32_src_offset.s0+gx,8),
VLOAD(src+v4s32_src_offset.s0+v2s32_gx_border.s1,2),
0,0,0,0};
V16Tp v16tp_src_row1={VLOAD(src+v4s32_src_offset.s1+v2s32_gx_border.s0,2),
VLOAD(src+v4s32_src_offset.s1+gx,8),
VLOAD(src+v4s32_src_offset.s1+v2s32_gx_border.s1,2),
0,0,0,0};
V16Tp v16tp_src_row2={VLOAD(src+v4s32_src_offset.s2+v2s32_gx_border.s0,2),
VLOAD(src+v4s32_src_offset.s2+gx,8),
VLOAD(src+v4s32_src_offset.s2+v2s32_gx_border.s1,2),
0,0,0,0};
V16Tp v16tp_src_row3={VLOAD(src+v4s32_src_offset.s3+v2s32_gx_border.s0,2),
VLOAD(src+v4s32_src_offset.s3+gx,8),
VLOAD(src+v4s32_src_offset.s3+v2s32_gx_border.s1,2),
0,0,0,0};
V8Tp v8tp_row0_l=CONVERT(v16tp_src_row0.s01234567,V8Tp);
V8Tp v8tp_row1_l=CONVERT(v16tp_src_row1.s01234567,V8Tp);
V8Tp v8tp_row2_l=CONVERT(v16tp_src_row2.s01234567,V8Tp);
V8Tp v8tp_row3_l=CONVERT(v16tp_src_row3.s01234567,V8Tp);
V8Tp v8tp_row0_c=CONVERT(v16tp_src_row0.s23456789,V8Tp);
V8Tp v8tp_row1_c=CONVERT(v16tp_src_row1.s23456789,V8Tp);
V8Tp v8tp_row2_c=CONVERT(v16tp_src_row2.s23456789,V8Tp);
V8Tp v8tp_row3_c=CONVERT(v16tp_src_row3.s23456789,V8Tp);
V8Tp v8tp_row0_r=CONVERT(v16tp_src_row0.s456789ab,V8Tp);
V8Tp v8tp_row1_r=CONVERT(v16tp_src_row1.s456789ab,V8Tp);
V8Tp v8tp_row2_r=CONVERT(v16tp_src_row2.s456789ab,V8Tp);
V8Tp v8tp_row3_r=CONVERT(v16tp_src_row3.s456789ab,V8Tp);
SORT2ElemX8(v8tp_row1_c,v8tp_row1_r);
SORT2ElemX8(v8tp_row2_c,v8tp_row2_r);
SORT2ElemX8(v8tp_row1_l,v8tp_row1_c);
SORT2ElemX8(v8tp_row2_l,v8tp_row2_c);
SORT2ElemX8(v8tp_row1_c,v8tp_row1_r);
SORT2ElemX8(v8tp_row2_c,v8tp_row2_r);
SORT2ElemX8(v8tp_row1_c,v8tp_row2_c);
v8tp_row1_r=min(v8tp_row1_r,v8tp_row2_r);
SORT2ElemX8(v8tp_row0_c,v8tp_row0_r);
SORT2ElemX8(v8tp_row3_c,v8tp_row3_r);
SORT2ElemX8(v8tp_row0_l,v8tp_row0_c);
SORT2ElemX8(v8tp_row3_l,v8tp_row3_c);
SORT2ElemX8(v8tp_row0_c,v8tp_row0_r);
SORT2ElemX8(v8tp_row3_c,v8tp_row3_r);
v8tp_row2_r=v8tp_row1_l;
v8tp_row1_l=max(v8tp_row0_l,v8tp_row1_l);
v8tp_row0_l=v8tp_row2_l;
v8tp_row2_l=max(v8tp_row1_l,v8tp_row2_l);
v8tp_row2_r=max(v8tp_row3_l,v8tp_row2_r);
v8tp_row0_l=max(v8tp_row2_r,v8tp_row0_l);
v8tp_row2_r=v8tp_row1_r;
v8tp_row0_r=min(v8tp_row0_r,v8tp_row1_r);
v8tp_row3_r=min(v8tp_row3_r,v8tp_row2_r);
v8tp_row2_r=v8tp_row1_c;
v8tp_row1_c=max(v8tp_row0_c,v8tp_row1_c);
v8tp_row0_c=v8tp_row2_c;
v8tp_row1_c=min(v8tp_row1_c,v8tp_row2_c);
v8tp_row2_r=max(v8tp_row3_c,v8tp_row2_r);
v8tp_row2_r=min(v8tp_row2_r,v8tp_row0_c);
SORT2ElemX8(v8tp_row1_c,v8tp_row0_r);
SORT2ElemX8(v8tp_row2_r,v8tp_row3_r);
v8tp_row1_c=max(v8tp_row2_l,v8tp_row1_c);
v8tp_row1_c=min(v8tp_row1_c,v8tp_row0_r);
v8tp_row2_r=max(v8tp_row0_l,v8tp_row2_r);
v8tp_row2_r=min(v8tp_row2_r,v8tp_row3_r);
int dst_idx=mad24(gy,ostep,gx);
VSTORE(v8tp_row1_c,dst+dst_idx,8);
VSTORE(v8tp_row2_r,dst+dst_idx+ostep,8);
}

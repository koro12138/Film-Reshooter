inline void GetMid10NumsOf4x4Box(V4Tp*v4tp_elem)
{
SORT4ElemX4(v4tp_elem[0],v4tp_elem[1],v4tp_elem[2],v4tp_elem[3]);
SORT4ElemX4(v4tp_elem[4],v4tp_elem[5],v4tp_elem[6],v4tp_elem[7]);
SORT4ElemX4(v4tp_elem[8],v4tp_elem[9],v4tp_elem[10],v4tp_elem[11]);
SORT4ElemX4(v4tp_elem[12],v4tp_elem[13],v4tp_elem[14],v4tp_elem[15]);
SORT2ElemX4(v4tp_elem[4],v4tp_elem[1]);
SORT3ElemX4(v4tp_elem[8],v4tp_elem[5],v4tp_elem[2]);
SORT4ElemX4(v4tp_elem[12],v4tp_elem[9],v4tp_elem[6],v4tp_elem[3]);
SORT3ElemX4(v4tp_elem[13],v4tp_elem[10],v4tp_elem[7]);
SORT2ElemX4(v4tp_elem[14],v4tp_elem[11]);
SORT2ElemX4(v4tp_elem[1],v4tp_elem[8]);
SORT2ElemX4(v4tp_elem[7],v4tp_elem[14]);
SORT2ElemX4(v4tp_elem[8],v4tp_elem[12]);
SORT2ElemX4(v4tp_elem[3],v4tp_elem[7]);
SORT2ElemX4(v4tp_elem[3],v4tp_elem[10]);
SORT2ElemX4(v4tp_elem[3],v4tp_elem[13]);
SORT2ElemX4(v4tp_elem[6],v4tp_elem[3]);
SORT2ElemX4(v4tp_elem[5],v4tp_elem[12]);
SORT2ElemX4(v4tp_elem[2],v4tp_elem[12]);
SORT2ElemX4(v4tp_elem[12],v4tp_elem[9]);
SORT2ElemX4(v4tp_elem[9],v4tp_elem[6]);
return;
}
inline void GetMiddlemost6From14(V4Tp*v4tp_elem10,V4Tp*v4tp_elem)
{
MERGE_SORT_2_2_X4(v4tp_elem[0],v4tp_elem[1],v4tp_elem10[8],v4tp_elem10[5]);
MERGE_SORT_2_2_X4(v4tp_elem10[10],v4tp_elem10[7],v4tp_elem[2],v4tp_elem[3]);
SORT4ElemX4(v4tp_elem10[8],v4tp_elem10[5],v4tp_elem10[10],v4tp_elem10[7]);
MERGE_SORT_2_2_X4(v4tp_elem10[8],v4tp_elem10[5],v4tp_elem10[2],v4tp_elem10[12]);
MERGE_SORT_2_2_X4(v4tp_elem10[3],v4tp_elem10[13],v4tp_elem10[10],v4tp_elem10[7]);
SORT2ElemX4(v4tp_elem10[2],v4tp_elem10[9]);
SORT2ElemX4(v4tp_elem10[2],v4tp_elem10[3]);
SORT2ElemX4(v4tp_elem10[9],v4tp_elem10[3]);
SORT2ElemX4(v4tp_elem10[12],v4tp_elem10[6]);
SORT2ElemX4(v4tp_elem10[12],v4tp_elem10[13]);
SORT2ElemX4(v4tp_elem10[6],v4tp_elem10[13]);
SORT2ElemX4(v4tp_elem10[12],v4tp_elem10[3]);
return;
}
inline void GetMiddlemost2From10(V4Tp*v4tp_elem6,V4Tp*v4tp_elem)
{
MERGE_SORT_2_2_X4(v4tp_elem[0],v4tp_elem[1],v4tp_elem6[2],v4tp_elem6[9]);
MERGE_SORT_2_2_X4(v4tp_elem6[6],v4tp_elem6[13],v4tp_elem[2],v4tp_elem[3]);
MERGE_SORT_2_2_X4(v4tp_elem6[2],v4tp_elem6[9],v4tp_elem6[12],v4tp_elem6[3]);
MERGE_SORT_2_2_X4(v4tp_elem6[12],v4tp_elem6[3],v4tp_elem6[6],v4tp_elem6[13]);
MERGE_SORT_2_2_X4(v4tp_elem6[2],v4tp_elem6[9],v4tp_elem6[12],v4tp_elem6[3]);
return;
}
kernel void MedianFilter5x5C1(global Tp*src,int istep,
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
gx=clamp(gx<<3,0,width-8);
gy=clamp(gy<<1,0,height-2);
int4 v4s32_gx_border={gx-2,gx-1,gx+8,gx+9};
v4s32_gx_border=clamp(v4s32_gx_border,0,width-1);
int8 v8s32_gy_src={gy-2,gy-1,gy,gy+1,gy+2,gy+3,0,0};
v8s32_gy_src=clamp(v8s32_gy_src,0,height-1);
int8 v8s32_src_offset=v8s32_gy_src*istep;
int dst_idx=mad24(gy,ostep,gx);
V8Tp v8tp_top={VLOAD(src+v8s32_src_offset.s0+v4s32_gx_border.s0,1),
VLOAD(src+v8s32_src_offset.s0+v4s32_gx_border.s1,1),
VLOAD(src+v8s32_src_offset.s0+gx,2),
VLOAD(src+v8s32_src_offset.s0+gx+2,4)};
V4Tp v4tp_top={VLOAD(src+v8s32_src_offset.s0+gx+6,2),
VLOAD(src+v8s32_src_offset.s0+v4s32_gx_border.s2,1),
VLOAD(src+v8s32_src_offset.s0+v4s32_gx_border.s3,1)};
V8Tp v8tp_bot={VLOAD(src+v8s32_src_offset.s5+v4s32_gx_border.s0,1),
VLOAD(src+v8s32_src_offset.s5+v4s32_gx_border.s1,1),
VLOAD(src+v8s32_src_offset.s5+gx,2),
VLOAD(src+v8s32_src_offset.s5+gx+2,4)};
V4Tp v4tp_bot={VLOAD(src+v8s32_src_offset.s5+gx+6,2),
VLOAD(src+v8s32_src_offset.s5+v4s32_gx_border.s2,1),
VLOAD(src+v8s32_src_offset.s5+v4s32_gx_border.s3,1)};
V4Tp v4tp_top4_group[6]={{v8tp_top.s1357},{v8tp_top.s24,v8tp_top.s6,v4tp_top.s0},{v8tp_top.s35,v8tp_top.s7,v4tp_top.s1},{v8tp_top.s46,v4tp_top.s02}};
V4Tp v4tp_bot4_group[6]={{v8tp_bot.s1357},{v8tp_bot.s24,v8tp_bot.s6,v4tp_bot.s0},{v8tp_bot.s35,v8tp_bot.s7,v4tp_bot.s1},{v8tp_bot.s46,v4tp_bot.s02}};
SORT4ElemX4(v4tp_top4_group[0],v4tp_top4_group[1],v4tp_top4_group[2],v4tp_top4_group[3]);
SORT4ElemX4(v4tp_bot4_group[0],v4tp_bot4_group[1],v4tp_bot4_group[2],v4tp_bot4_group[3]);
V16Tp v16tp_src_row0={VLOAD(src+v8s32_src_offset.s1+v4s32_gx_border.s0,1),
VLOAD(src+v8s32_src_offset.s1+v4s32_gx_border.s1,1),
VLOAD(src+v8s32_src_offset.s1+gx,8),
VLOAD(src+v8s32_src_offset.s1+v4s32_gx_border.s2,1),
VLOAD(src+v8s32_src_offset.s1+v4s32_gx_border.s3,1),
0,0,0,0};
V16Tp v16tp_src_row1={VLOAD(src+v8s32_src_offset.s2+v4s32_gx_border.s0,1),
VLOAD(src+v8s32_src_offset.s2+v4s32_gx_border.s1,1),
VLOAD(src+v8s32_src_offset.s2+gx,8),
VLOAD(src+v8s32_src_offset.s2+v4s32_gx_border.s2,1),
VLOAD(src+v8s32_src_offset.s2+v4s32_gx_border.s3,1),
0,0,0,0};
V16Tp v16tp_src_row2={VLOAD(src+v8s32_src_offset.s3+v4s32_gx_border.s0,1),
VLOAD(src+v8s32_src_offset.s3+v4s32_gx_border.s1,1),
VLOAD(src+v8s32_src_offset.s3+gx,8),
VLOAD(src+v8s32_src_offset.s3+v4s32_gx_border.s2,1),
VLOAD(src+v8s32_src_offset.s3+v4s32_gx_border.s3,1),
0,0,0,0};
V16Tp v16tp_src_row3={VLOAD(src+v8s32_src_offset.s4+v4s32_gx_border.s0,1),
VLOAD(src+v8s32_src_offset.s4+v4s32_gx_border.s1,1),
VLOAD(src+v8s32_src_offset.s4+gx,8),
VLOAD(src+v8s32_src_offset.s4+v4s32_gx_border.s2,1),
VLOAD(src+v8s32_src_offset.s4+v4s32_gx_border.s3,1),
0,0,0,0};
SORT4ElemX16(v16tp_src_row0,v16tp_src_row1,v16tp_src_row2,v16tp_src_row3);
V4Tp v4tp_elem[16]={{v16tp_src_row0.s1,v16tp_src_row0.s3,v16tp_src_row0.s5,v16tp_src_row0.s7},
{v16tp_src_row0.s2,v16tp_src_row0.s4,v16tp_src_row0.s6,v16tp_src_row0.s8},
{v16tp_src_row0.s3,v16tp_src_row0.s5,v16tp_src_row0.s7,v16tp_src_row0.s9},
{v16tp_src_row0.s4,v16tp_src_row0.s6,v16tp_src_row0.s8,v16tp_src_row0.sa},
{v16tp_src_row1.s1,v16tp_src_row1.s3,v16tp_src_row1.s5,v16tp_src_row1.s7},
{v16tp_src_row1.s2,v16tp_src_row1.s4,v16tp_src_row1.s6,v16tp_src_row1.s8},
{v16tp_src_row1.s3,v16tp_src_row1.s5,v16tp_src_row1.s7,v16tp_src_row1.s9},
{v16tp_src_row1.s4,v16tp_src_row1.s6,v16tp_src_row1.s8,v16tp_src_row1.sa},
{v16tp_src_row2.s1,v16tp_src_row2.s3,v16tp_src_row2.s5,v16tp_src_row2.s7},
{v16tp_src_row2.s2,v16tp_src_row2.s4,v16tp_src_row2.s6,v16tp_src_row2.s8},
{v16tp_src_row2.s3,v16tp_src_row2.s5,v16tp_src_row2.s7,v16tp_src_row2.s9},
{v16tp_src_row2.s4,v16tp_src_row2.s6,v16tp_src_row2.s8,v16tp_src_row2.sa},
{v16tp_src_row3.s1,v16tp_src_row3.s3,v16tp_src_row3.s5,v16tp_src_row3.s7},
{v16tp_src_row3.s2,v16tp_src_row3.s4,v16tp_src_row3.s6,v16tp_src_row3.s8},
{v16tp_src_row3.s3,v16tp_src_row3.s5,v16tp_src_row3.s7,v16tp_src_row3.s9},
{v16tp_src_row3.s4,v16tp_src_row3.s6,v16tp_src_row3.s8,v16tp_src_row3.sa}};
GetMid10NumsOf4x4Box(v4tp_elem);
V4Tp v4tp_zero={0,0,0,0};
V4Tp v4tp_elem_sorted[16]={v4tp_zero,v4tp_zero,v4tp_elem[2],v4tp_elem[3],
v4tp_zero,v4tp_elem[5],v4tp_elem[6],v4tp_elem[7],
v4tp_elem[8],v4tp_elem[9],v4tp_elem[10],v4tp_zero,
v4tp_elem[12],v4tp_elem[13],v4tp_zero,v4tp_zero};
V4Tp arr_v4[4]={{v16tp_src_row0.s0,v16tp_src_row0.s2,v16tp_src_row0.s4,v16tp_src_row0.s6},{v16tp_src_row1.s0,v16tp_src_row1.s2,v16tp_src_row1.s4,v16tp_src_row1.s6},
{v16tp_src_row2.s0,v16tp_src_row2.s2,v16tp_src_row2.s4,v16tp_src_row2.s6},{v16tp_src_row3.s0,v16tp_src_row3.s2,v16tp_src_row3.s4,v16tp_src_row3.s6}};
GetMiddlemost6From14(v4tp_elem,arr_v4);
V4Tp v4tp_tmp[4];
v4tp_tmp[0]=v4tp_top4_group[0];
v4tp_tmp[1]=v4tp_top4_group[1];
v4tp_tmp[2]=v4tp_top4_group[2];
v4tp_tmp[3]=v4tp_top4_group[3];
v4tp_elem[0]=v4tp_elem[2];
v4tp_elem[1]=v4tp_elem[9];
v4tp_elem[4]=v4tp_elem[12];
v4tp_elem[5]=v4tp_elem[3];
v4tp_elem[10]=v4tp_elem[6];
v4tp_elem[11]=v4tp_elem[13];
GetMiddlemost2From10(v4tp_elem,v4tp_top4_group);
V4Tp v4tp_top_tmp=CONVERT(v8tp_top.s0246,V4Tp);
SORT2ElemX4(v4tp_top_tmp,v4tp_elem[12]);
SORT2ElemX4(v4tp_elem[12],v4tp_elem[3]);
V8Tp v8tp_dst_top,v8tp_dst_dwn;
v8tp_dst_top.even=v4tp_elem[12];
arr_v4[0]=(V4Tp)(v16tp_src_row0.s5,v16tp_src_row0.s7,v16tp_src_row0.s9,v16tp_src_row0.sb);
arr_v4[1]=(V4Tp)(v16tp_src_row1.s5,v16tp_src_row1.s7,v16tp_src_row1.s9,v16tp_src_row1.sb);
arr_v4[2]=(V4Tp)(v16tp_src_row2.s5,v16tp_src_row2.s7,v16tp_src_row2.s9,v16tp_src_row2.sb);
arr_v4[3]=(V4Tp)(v16tp_src_row3.s5,v16tp_src_row3.s7,v16tp_src_row3.s9,v16tp_src_row3.sb);
GetMiddlemost6From14(v4tp_elem_sorted,arr_v4);
v4tp_elem_sorted[0]=v4tp_elem_sorted[2];
v4tp_elem_sorted[1]=v4tp_elem_sorted[9];
v4tp_elem_sorted[4]=v4tp_elem_sorted[12];
v4tp_elem_sorted[5]=v4tp_elem_sorted[3];
v4tp_elem_sorted[10]=v4tp_elem_sorted[6];
v4tp_elem_sorted[11]=v4tp_elem_sorted[13];
GetMiddlemost2From10(v4tp_elem_sorted,v4tp_tmp);
V4Tp v4tp_right_cor=(V4Tp)(v8tp_top.s57,v4tp_top.s13);
SORT2ElemX4(v4tp_right_cor,v4tp_elem_sorted[12]);
SORT2ElemX4(v4tp_elem_sorted[12],v4tp_elem_sorted[3]);
v8tp_dst_top.odd=v4tp_elem_sorted[12];
v4tp_tmp[0]=v4tp_bot4_group[0];
v4tp_tmp[1]=v4tp_bot4_group[1];
v4tp_tmp[2]=v4tp_bot4_group[2];
v4tp_tmp[3]=v4tp_bot4_group[3];
v4tp_elem[2]=v4tp_elem[0];
v4tp_elem[9]=v4tp_elem[1];
v4tp_elem[12]=v4tp_elem[4];
v4tp_elem[3]=v4tp_elem[5];
v4tp_elem[6]=v4tp_elem[10];
v4tp_elem[13]=v4tp_elem[11];
GetMiddlemost2From10(v4tp_elem,v4tp_bot4_group);
v4tp_top_tmp=CONVERT(v8tp_bot.s0246,V4Tp);
SORT2ElemX4(v4tp_top_tmp,v4tp_elem[12]);
SORT2ElemX4(v4tp_elem[12],v4tp_elem[3]);
v8tp_dst_dwn.even=v4tp_elem[12];
v4tp_elem_sorted[2]=v4tp_elem_sorted[0];
v4tp_elem_sorted[9]=v4tp_elem_sorted[1];
v4tp_elem_sorted[12]=v4tp_elem_sorted[4];
v4tp_elem_sorted[3]=v4tp_elem_sorted[5];
v4tp_elem_sorted[6]=v4tp_elem_sorted[10];
v4tp_elem_sorted[13]=v4tp_elem_sorted[11];
GetMiddlemost2From10(v4tp_elem_sorted,v4tp_tmp);
v4tp_right_cor=(V4Tp)(v8tp_bot.s57,v4tp_bot.s13);
SORT2ElemX4(v4tp_right_cor,v4tp_elem_sorted[12]);
SORT2ElemX4(v4tp_elem_sorted[12],v4tp_elem_sorted[3]);
v8tp_dst_dwn.odd=v4tp_elem_sorted[12];
VSTORE(v8tp_dst_top,dst+dst_idx,8);
VSTORE(v8tp_dst_dwn,dst+dst_idx+ostep,8);
}

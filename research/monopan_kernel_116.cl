inline V16Tp GetMid10NumsOf4x4Box(V4Tp*v4tp_elem)
{
SORT4ElemX1(v4tp_elem[0].s0,v4tp_elem[0].s1,v4tp_elem[0].s2,v4tp_elem[0].s3);
SORT4ElemX1(v4tp_elem[1].s0,v4tp_elem[1].s1,v4tp_elem[1].s2,v4tp_elem[1].s3);
SORT4ElemX1(v4tp_elem[2].s0,v4tp_elem[2].s1,v4tp_elem[2].s2,v4tp_elem[2].s3);
SORT4ElemX1(v4tp_elem[3].s0,v4tp_elem[3].s1,v4tp_elem[3].s2,v4tp_elem[3].s3);
SORT2ElemX1(v4tp_elem[1].s0,v4tp_elem[0].s1);
SORT3ElemX1(v4tp_elem[2].s0,v4tp_elem[1].s1,v4tp_elem[0].s2);
SORT4ElemX1(v4tp_elem[3].s0,v4tp_elem[2].s1,v4tp_elem[1].s2,v4tp_elem[0].s3);
SORT3ElemX1(v4tp_elem[3].s1,v4tp_elem[2].s2,v4tp_elem[1].s3);
SORT2ElemX1(v4tp_elem[3].s2,v4tp_elem[2].s3);
SORT2ElemX1(v4tp_elem[0].s1,v4tp_elem[2].s0);
SORT2ElemX1(v4tp_elem[1].s3,v4tp_elem[3].s2);
SORT2ElemX1(v4tp_elem[2].s0,v4tp_elem[3].s0);
SORT2ElemX1(v4tp_elem[0].s3,v4tp_elem[1].s3);
SORT2ElemX1(v4tp_elem[0].s3,v4tp_elem[2].s2);
SORT2ElemX1(v4tp_elem[0].s3,v4tp_elem[3].s1);
SORT2ElemX1(v4tp_elem[1].s2,v4tp_elem[0].s3);
SORT2ElemX1(v4tp_elem[1].s1,v4tp_elem[3].s0);
SORT2ElemX1(v4tp_elem[0].s2,v4tp_elem[3].s0);
SORT2ElemX1(v4tp_elem[3].s0,v4tp_elem[2].s1);
SORT2ElemX1(v4tp_elem[2].s1,v4tp_elem[1].s2);
V16Tp temp={v4tp_elem[2].s0,v4tp_elem[1].s1,v4tp_elem[0].s2,v4tp_elem[3].s0,v4tp_elem[2].s1,
v4tp_elem[1].s2,v4tp_elem[0].s3,v4tp_elem[3].s1,v4tp_elem[2].s2,v4tp_elem[1].s3,
0,0,0,0,0,0};
return temp;
}
inline V8Tp GetMiddlemost6From14(V16Tp v16tp_elem10,V4Tp v4tp_elem)
{
MERGE_SORT_2_2(v4tp_elem.s0,v4tp_elem.s1,v16tp_elem10.s0,v16tp_elem10.s1);
MERGE_SORT_2_2(v16tp_elem10.s8,v16tp_elem10.s9,v4tp_elem.s2,v4tp_elem.s3);
SORT4ElemX1(v16tp_elem10.s0,v16tp_elem10.s1,v16tp_elem10.s8,v16tp_elem10.s9);
MERGE_SORT_2_2(v16tp_elem10.s0,v16tp_elem10.s1,v16tp_elem10.s2,v16tp_elem10.s3);
MERGE_SORT_2_2(v16tp_elem10.s6,v16tp_elem10.s7,v16tp_elem10.s8,v16tp_elem10.s9);
SORT2ElemX1(v16tp_elem10.s2,v16tp_elem10.s4);
SORT2ElemX1(v16tp_elem10.s2,v16tp_elem10.s6);
SORT2ElemX1(v16tp_elem10.s4,v16tp_elem10.s6);
SORT2ElemX1(v16tp_elem10.s3,v16tp_elem10.s5);
SORT2ElemX1(v16tp_elem10.s3,v16tp_elem10.s7);
SORT2ElemX1(v16tp_elem10.s5,v16tp_elem10.s7);
SORT2ElemX1(v16tp_elem10.s3,v16tp_elem10.s6);
V8Tp temp={v16tp_elem10.s2,v16tp_elem10.s4,v16tp_elem10.s3,v16tp_elem10.s6,v16tp_elem10.s5,v16tp_elem10.s7,0,0};
return temp;
}
inline V2Tp GetMiddlemost2From10(V8Tp v8tp_elem6,V4Tp v4tp_elem)
{
MERGE_SORT_2_2(v4tp_elem.s0,v4tp_elem.s1,v8tp_elem6.s0,v8tp_elem6.s1);
MERGE_SORT_2_2(v8tp_elem6.s4,v8tp_elem6.s5,v4tp_elem.s2,v4tp_elem.s3);
MERGE_SORT_2_2(v8tp_elem6.s0,v8tp_elem6.s1,v8tp_elem6.s2,v8tp_elem6.s3);
MERGE_SORT_2_2(v8tp_elem6.s2,v8tp_elem6.s3,v8tp_elem6.s4,v8tp_elem6.s5);
MERGE_SORT_2_2(v8tp_elem6.s0,v8tp_elem6.s1,v8tp_elem6.s2,v8tp_elem6.s3);
V2Tp temp={v8tp_elem6.s2,v8tp_elem6.s3};
return temp;
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
gx=clamp(gx<<1,0,width-2);
gy=clamp(gy<<1,0,height-2);
int4 v4s32_gx_border={gx-2,gx-1,gx+2,gx+3};
v4s32_gx_border=clamp(v4s32_gx_border,0,width-1);
int8 v8s32_gy_src={gy-2,gy-1,gy,gy+1,gy+2,gy+3,0,0};
v8s32_gy_src=clamp(v8s32_gy_src,0,height-1);
int8 v8s32_src_offset=v8s32_gy_src*istep;
V8Tp v8tp_src_top={VLOAD(src+v8s32_src_offset.s0+v4s32_gx_border.s0,1),
VLOAD(src+v8s32_src_offset.s0+v4s32_gx_border.s1,1),
VLOAD(src+v8s32_src_offset.s0+gx,2),
VLOAD(src+v8s32_src_offset.s0+v4s32_gx_border.s2,1),
VLOAD(src+v8s32_src_offset.s0+v4s32_gx_border.s3,1),
0,0};
V8Tp v8tp_src_bot={VLOAD(src+v8s32_src_offset.s5+v4s32_gx_border.s0,1),
VLOAD(src+v8s32_src_offset.s5+v4s32_gx_border.s1,1),
VLOAD(src+v8s32_src_offset.s5+gx,2),
VLOAD(src+v8s32_src_offset.s5+v4s32_gx_border.s2,1),
VLOAD(src+v8s32_src_offset.s5+v4s32_gx_border.s3,1),
0,0};
SORT4ElemX1(v8tp_src_top.s1,v8tp_src_top.s2,v8tp_src_top.s3,v8tp_src_top.s4);
SORT4ElemX1(v8tp_src_bot.s1,v8tp_src_bot.s2,v8tp_src_bot.s3,v8tp_src_bot.s4);
V8Tp v8tp_src_row0={VLOAD(src+v8s32_src_offset.s1+v4s32_gx_border.s0,1),
VLOAD(src+v8s32_src_offset.s1+v4s32_gx_border.s1,1),
VLOAD(src+v8s32_src_offset.s1+gx,2),
VLOAD(src+v8s32_src_offset.s1+v4s32_gx_border.s2,1),
VLOAD(src+v8s32_src_offset.s1+v4s32_gx_border.s3,1),
0,0};
V8Tp v8tp_src_row1={VLOAD(src+v8s32_src_offset.s2+v4s32_gx_border.s0,1),
VLOAD(src+v8s32_src_offset.s2+v4s32_gx_border.s1,1),
VLOAD(src+v8s32_src_offset.s2+gx,2),
VLOAD(src+v8s32_src_offset.s2+v4s32_gx_border.s2,1),
VLOAD(src+v8s32_src_offset.s2+v4s32_gx_border.s3,1),
0,0};
V8Tp v8tp_src_row2={VLOAD(src+v8s32_src_offset.s3+v4s32_gx_border.s0,1),
VLOAD(src+v8s32_src_offset.s3+v4s32_gx_border.s1,1),
VLOAD(src+v8s32_src_offset.s3+gx,2),
VLOAD(src+v8s32_src_offset.s3+v4s32_gx_border.s2,1),
VLOAD(src+v8s32_src_offset.s3+v4s32_gx_border.s3,1),
0,0};
V8Tp v8tp_src_row3={VLOAD(src+v8s32_src_offset.s4+v4s32_gx_border.s0,1),
VLOAD(src+v8s32_src_offset.s4+v4s32_gx_border.s1,1),
VLOAD(src+v8s32_src_offset.s4+gx,2),
VLOAD(src+v8s32_src_offset.s4+v4s32_gx_border.s2,1),
VLOAD(src+v8s32_src_offset.s4+v4s32_gx_border.s3,1),
0,0};
SORT4ElemX8(v8tp_src_row0,v8tp_src_row1,v8tp_src_row2,v8tp_src_row3);
V4Tp v4tp_elem[4]={{v8tp_src_row0.s1,v8tp_src_row0.s2,v8tp_src_row0.s3,v8tp_src_row0.s4},
{v8tp_src_row1.s1,v8tp_src_row1.s2,v8tp_src_row1.s3,v8tp_src_row1.s4},
{v8tp_src_row2.s1,v8tp_src_row2.s2,v8tp_src_row2.s3,v8tp_src_row2.s4},
{v8tp_src_row3.s1,v8tp_src_row3.s2,v8tp_src_row3.s3,v8tp_src_row3.s4}};
V16Tp v16tp_mid_10_nums=GetMid10NumsOf4x4Box(v4tp_elem);
V4Tp v4tp_arr_v4=(V4Tp)(v8tp_src_row0.s0,v8tp_src_row1.s0,v8tp_src_row2.s0,v8tp_src_row3.s0);
V8Tp v8tp_src_left=GetMiddlemost6From14(v16tp_mid_10_nums,v4tp_arr_v4);
v4tp_arr_v4=CONVERT(v8tp_src_top.s1234,V4Tp);
V2Tp v2tp_left_top=GetMiddlemost2From10(v8tp_src_left,v4tp_arr_v4);
SORT2ElemX1(v8tp_src_top.s0,v2tp_left_top.s0);
SORT2ElemX1(v2tp_left_top.s0,v2tp_left_top.s1);
v4tp_arr_v4=(V4Tp)(v8tp_src_row0.s5,v8tp_src_row1.s5,v8tp_src_row2.s5,v8tp_src_row3.s5);
V8Tp v8tp_src_right=GetMiddlemost6From14(v16tp_mid_10_nums,v4tp_arr_v4);
v4tp_arr_v4=CONVERT(v8tp_src_top.s1234,V4Tp);
V2Tp v2tp_right_top=GetMiddlemost2From10(v8tp_src_right,v4tp_arr_v4);
SORT2ElemX1(v8tp_src_top.s5,v2tp_right_top.s0);
SORT2ElemX1(v2tp_right_top.s0,v2tp_right_top.s1);
v4tp_arr_v4=CONVERT(v8tp_src_bot.s1234,V4Tp);
V2Tp v2tp_left_bot=GetMiddlemost2From10(v8tp_src_left,v4tp_arr_v4);
SORT2ElemX1(v8tp_src_bot.s0,v2tp_left_bot.s0);
SORT2ElemX1(v2tp_left_bot.s0,v2tp_left_bot.s1);
v4tp_arr_v4=CONVERT(v8tp_src_bot.s1234,V4Tp);
V2Tp v2tp_right_bot=GetMiddlemost2From10(v8tp_src_right,v4tp_arr_v4);
SORT2ElemX1(v8tp_src_bot.s5,v2tp_right_bot.s0);
SORT2ElemX1(v2tp_right_bot.s0,v2tp_right_bot.s1);
v2tp_left_top.s1=v2tp_right_top.s0;
v2tp_left_bot.s1=v2tp_right_bot.s0;
int dst_idx=mad24(gy,ostep,gx);
VSTORE(v2tp_left_top,dst+dst_idx,2);
VSTORE(v2tp_left_bot,dst+dst_idx+ostep,2);
}

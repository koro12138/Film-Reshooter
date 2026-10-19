kernel void MedianFilter7x7C2(global Tp*src,int istep,
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
gx=clamp(gx<<3,0,width*2-8);
gy=clamp(gy<<1,0,height-2);
int8 v8s32_gx_border={gx-6,gx-4,gx-2,gx+8,gx+10,gx+12,0,0};
v8s32_gx_border=clamp(v8s32_gx_border,0,width*2-2);
int8 v8s32_gy_src={gy-3,gy-2,gy-1,gy,gy+1,gy+2,gy+3,gy+4};
v8s32_gy_src=clamp(v8s32_gy_src,0,height-1);
int8 v8s32_src_offset=v8s32_gy_src*istep;
int dst_idx=mad24(gy,ostep,gx);
V4Tp v4tp_top6[6];
V4Tp v4tp_bot6[6];
V4Tp v4tp_top_left,v4tp_top_right,v4tp_bot_left,v4tp_bot_right;
{
V16Tp v16tp_top={VLOAD(src+v8s32_src_offset.s0+v8s32_gx_border.s0,2),
VLOAD(src+v8s32_src_offset.s0+v8s32_gx_border.s1,2),
VLOAD(src+v8s32_src_offset.s0+v8s32_gx_border.s2,2),
VLOAD(src+v8s32_src_offset.s0+gx,8),
VLOAD(src+v8s32_src_offset.s0+v8s32_gx_border.s3,2)};
V16Tp v16tp_bot={VLOAD(src+v8s32_src_offset.s7+v8s32_gx_border.s0,2),
VLOAD(src+v8s32_src_offset.s7+v8s32_gx_border.s1,2),
VLOAD(src+v8s32_src_offset.s7+v8s32_gx_border.s2,2),
VLOAD(src+v8s32_src_offset.s7+gx,8),
VLOAD(src+v8s32_src_offset.s7+v8s32_gx_border.s3,2)};
V4Tp v4tp_top_r={VLOAD(src+v8s32_src_offset.s0+v8s32_gx_border.s4,2),
VLOAD(src+v8s32_src_offset.s0+v8s32_gx_border.s5,2)};
V4Tp v4tp_bot_r={VLOAD(src+v8s32_src_offset.s7+v8s32_gx_border.s4,2),
VLOAD(src+v8s32_src_offset.s7+v8s32_gx_border.s5,2)};
v4tp_top6[0]=(V4Tp){v16tp_top.s2367};
v4tp_top6[1]=(V4Tp){v16tp_top.s4589};
v4tp_top6[2]=(V4Tp){v16tp_top.s67ab};
v4tp_top6[3]=(V4Tp){v16tp_top.s89cd};
v4tp_top6[4]=(V4Tp){v16tp_top.sabef};
v4tp_top6[5]=(V4Tp){v16tp_top.scd,v4tp_top_r.s01};
v4tp_bot6[0]=(V4Tp){v16tp_bot.s2367};
v4tp_bot6[1]=(V4Tp){v16tp_bot.s4589};
v4tp_bot6[2]=(V4Tp){v16tp_bot.s67ab};
v4tp_bot6[3]=(V4Tp){v16tp_bot.s89cd};
v4tp_bot6[4]=(V4Tp){v16tp_bot.sabef};
v4tp_bot6[5]=(V4Tp){v16tp_bot.scd,v4tp_bot_r.s01};
SORT6ElemX4(v4tp_top6[0],v4tp_top6[1],v4tp_top6[2],v4tp_top6[3],v4tp_top6[4],v4tp_top6[5]);
SORT6ElemX4(v4tp_bot6[0],v4tp_bot6[1],v4tp_bot6[2],v4tp_bot6[3],v4tp_bot6[4],v4tp_bot6[5]);
v4tp_top_left=(V4Tp){v16tp_top.s0145};
v4tp_top_right=(V4Tp){v16tp_top.sef,v4tp_top_r.s23};
v4tp_bot_left=(V4Tp){v16tp_bot.s0145};
v4tp_bot_right=(V4Tp){v16tp_bot.sef,v4tp_bot_r.s23};
}
V4Tp v4tp_mid14[14];
V4Tp v4tp_left6[6];
V4Tp v4tp_right6[6];
{
V16Tp v16tp_src_row0={VLOAD(src+v8s32_src_offset.s1+v8s32_gx_border.s0,2),
VLOAD(src+v8s32_src_offset.s1+v8s32_gx_border.s1,2),
VLOAD(src+v8s32_src_offset.s1+v8s32_gx_border.s2,2),
VLOAD(src+v8s32_src_offset.s1+gx,8),
VLOAD(src+v8s32_src_offset.s1+v8s32_gx_border.s3,2)};
V16Tp v16tp_src_row1={VLOAD(src+v8s32_src_offset.s2+v8s32_gx_border.s0,2),
VLOAD(src+v8s32_src_offset.s2+v8s32_gx_border.s1,2),
VLOAD(src+v8s32_src_offset.s2+v8s32_gx_border.s2,2),
VLOAD(src+v8s32_src_offset.s2+gx,8),
VLOAD(src+v8s32_src_offset.s2+v8s32_gx_border.s3,2)};
V16Tp v16tp_src_row2={VLOAD(src+v8s32_src_offset.s3+v8s32_gx_border.s0,2),
VLOAD(src+v8s32_src_offset.s3+v8s32_gx_border.s1,2),
VLOAD(src+v8s32_src_offset.s3+v8s32_gx_border.s2,2),
VLOAD(src+v8s32_src_offset.s3+gx,8),
VLOAD(src+v8s32_src_offset.s3+v8s32_gx_border.s3,2)};
V16Tp v16tp_src_row3={VLOAD(src+v8s32_src_offset.s4+v8s32_gx_border.s0,2),
VLOAD(src+v8s32_src_offset.s4+v8s32_gx_border.s1,2),
VLOAD(src+v8s32_src_offset.s4+v8s32_gx_border.s2,2),
VLOAD(src+v8s32_src_offset.s4+gx,8),
VLOAD(src+v8s32_src_offset.s4+v8s32_gx_border.s3,2)};
V16Tp v16tp_src_row4={VLOAD(src+v8s32_src_offset.s5+v8s32_gx_border.s0,2),
VLOAD(src+v8s32_src_offset.s5+v8s32_gx_border.s1,2),
VLOAD(src+v8s32_src_offset.s5+v8s32_gx_border.s2,2),
VLOAD(src+v8s32_src_offset.s5+gx,8),
VLOAD(src+v8s32_src_offset.s5+v8s32_gx_border.s3,2)};
V16Tp v16tp_src_row5={VLOAD(src+v8s32_src_offset.s6+v8s32_gx_border.s0,2),
VLOAD(src+v8s32_src_offset.s6+v8s32_gx_border.s1,2),
VLOAD(src+v8s32_src_offset.s6+v8s32_gx_border.s2,2),
VLOAD(src+v8s32_src_offset.s6+gx,8),
VLOAD(src+v8s32_src_offset.s6+v8s32_gx_border.s3,2)};
V4Tp v4tp_src_row0_0={VLOAD(src+v8s32_src_offset.s1+v8s32_gx_border.s4,2),
VLOAD(src+v8s32_src_offset.s1+v8s32_gx_border.s5,2)};
V4Tp v4tp_src_row1_0={VLOAD(src+v8s32_src_offset.s2+v8s32_gx_border.s4,2),
VLOAD(src+v8s32_src_offset.s2+v8s32_gx_border.s5,2)};
V4Tp v4tp_src_row2_0={VLOAD(src+v8s32_src_offset.s3+v8s32_gx_border.s4,2),
VLOAD(src+v8s32_src_offset.s3+v8s32_gx_border.s5,2)};
V4Tp v4tp_src_row3_0={VLOAD(src+v8s32_src_offset.s4+v8s32_gx_border.s4,2),
VLOAD(src+v8s32_src_offset.s4+v8s32_gx_border.s5,2)};
V4Tp v4tp_src_row4_0={VLOAD(src+v8s32_src_offset.s5+v8s32_gx_border.s4,2),
VLOAD(src+v8s32_src_offset.s5+v8s32_gx_border.s5,2)};
V4Tp v4tp_src_row5_0={VLOAD(src+v8s32_src_offset.s6+v8s32_gx_border.s4,2),
VLOAD(src+v8s32_src_offset.s6+v8s32_gx_border.s5,2)};
SORT6ElemX16(v16tp_src_row0,v16tp_src_row1,v16tp_src_row2,v16tp_src_row3,v16tp_src_row4,v16tp_src_row5);
SORT6ElemX4(v4tp_src_row0_0,v4tp_src_row1_0,v4tp_src_row2_0,v4tp_src_row3_0,v4tp_src_row4_0,v4tp_src_row5_0);
V4Tp v4tp_elem[36]={v16tp_src_row0.s2367,v16tp_src_row0.s4589,v16tp_src_row0.s67ab,v16tp_src_row0.s89cd,v16tp_src_row0.sabef,{v16tp_src_row0.scd,v4tp_src_row0_0.s01},
v16tp_src_row1.s2367,v16tp_src_row1.s4589,v16tp_src_row1.s67ab,v16tp_src_row1.s89cd,v16tp_src_row1.sabef,{v16tp_src_row1.scd,v4tp_src_row1_0.s01},
v16tp_src_row2.s2367,v16tp_src_row2.s4589,v16tp_src_row2.s67ab,v16tp_src_row2.s89cd,v16tp_src_row2.sabef,{v16tp_src_row2.scd,v4tp_src_row2_0.s01},
v16tp_src_row3.s2367,v16tp_src_row3.s4589,v16tp_src_row3.s67ab,v16tp_src_row3.s89cd,v16tp_src_row3.sabef,{v16tp_src_row3.scd,v4tp_src_row3_0.s01},
v16tp_src_row4.s2367,v16tp_src_row4.s4589,v16tp_src_row4.s67ab,v16tp_src_row4.s89cd,v16tp_src_row4.sabef,{v16tp_src_row4.scd,v4tp_src_row4_0.s01},
v16tp_src_row5.s2367,v16tp_src_row5.s4589,v16tp_src_row5.s67ab,v16tp_src_row5.s89cd,v16tp_src_row5.sabef,{v16tp_src_row5.scd,v4tp_src_row5_0.s01}};
v4tp_left6[0]=v16tp_src_row0.s0145;
v4tp_left6[1]=v16tp_src_row1.s0145;
v4tp_left6[2]=v16tp_src_row2.s0145;
v4tp_left6[3]=v16tp_src_row3.s0145;
v4tp_left6[4]=v16tp_src_row4.s0145;
v4tp_left6[5]=v16tp_src_row5.s0145;
v4tp_right6[0]=(V4Tp)(v16tp_src_row0.sef,v4tp_src_row0_0.s23);
v4tp_right6[1]=(V4Tp)(v16tp_src_row1.sef,v4tp_src_row1_0.s23);
v4tp_right6[2]=(V4Tp)(v16tp_src_row2.sef,v4tp_src_row2_0.s23);
v4tp_right6[3]=(V4Tp)(v16tp_src_row3.sef,v4tp_src_row3_0.s23);
v4tp_right6[4]=(V4Tp)(v16tp_src_row4.sef,v4tp_src_row4_0.s23);
v4tp_right6[5]=(V4Tp)(v16tp_src_row5.sef,v4tp_src_row5_0.s23);
GET_MID14_OF_36(4,v4tp_elem[0],v4tp_elem[1],v4tp_elem[2],v4tp_elem[3],v4tp_elem[4],v4tp_elem[5],
v4tp_elem[6],v4tp_elem[7],v4tp_elem[8],v4tp_elem[9],v4tp_elem[10],v4tp_elem[11],
v4tp_elem[12],v4tp_elem[13],v4tp_elem[14],v4tp_elem[15],v4tp_elem[16],v4tp_elem[17],
v4tp_elem[18],v4tp_elem[19],v4tp_elem[20],v4tp_elem[21],v4tp_elem[22],v4tp_elem[23],
v4tp_elem[24],v4tp_elem[25],v4tp_elem[26],v4tp_elem[27],v4tp_elem[28],v4tp_elem[29],
v4tp_elem[30],v4tp_elem[31],v4tp_elem[32],v4tp_elem[33],v4tp_elem[34],v4tp_elem[35]);
v4tp_mid14[0]=v4tp_elem[4];
v4tp_mid14[1]=v4tp_elem[9];
v4tp_mid14[2]=v4tp_elem[14];
v4tp_mid14[3]=v4tp_elem[15];
v4tp_mid14[4]=v4tp_elem[19];
v4tp_mid14[5]=v4tp_elem[20];
v4tp_mid14[6]=v4tp_elem[21];
v4tp_mid14[7]=v4tp_elem[25];
v4tp_mid14[8]=v4tp_elem[26];
v4tp_mid14[9]=v4tp_elem[27];
v4tp_mid14[10]=v4tp_elem[30];
v4tp_mid14[11]=v4tp_elem[31];
v4tp_mid14[12]=v4tp_elem[32];
v4tp_mid14[13]=v4tp_elem[33];
}
{
V4Tp v4tp_mid14_copy[14]={v4tp_mid14[0],v4tp_mid14[1],v4tp_mid14[2],v4tp_mid14[3],v4tp_mid14[4],v4tp_mid14[5],v4tp_mid14[6],
v4tp_mid14[7],v4tp_mid14[8],v4tp_mid14[9],v4tp_mid14[10],v4tp_mid14[11],v4tp_mid14[12],v4tp_mid14[13]};
V4Tp v4tp_left6_copy[6]={v4tp_left6[0],v4tp_left6[1],v4tp_left6[2],v4tp_left6[3],v4tp_left6[4],v4tp_left6[5]};
V4Tp v4tp_right6_copy[6]={v4tp_right6[0],v4tp_right6[1],v4tp_right6[2],v4tp_right6[3],v4tp_right6[4],v4tp_right6[5]};
V4Tp v4tp_dst_left,v4tp_dst_right;
GET_MEDIAN7x7(4,v4tp_mid14_copy,v4tp_left6_copy,v4tp_right6_copy,v4tp_top6,v4tp_top_left,v4tp_top_right,v4tp_dst_left,v4tp_dst_right);
V8Tp v8tp_dst_top;
v8tp_dst_top.s0145=v4tp_dst_left;
v8tp_dst_top.s2367=v4tp_dst_right;
VSTORE(v8tp_dst_top,dst+dst_idx,8);
}
{
V4Tp v4tp_dst_left;
V4Tp v4tp_dst_right;
GET_MEDIAN7x7(4,v4tp_mid14,v4tp_left6,v4tp_right6,v4tp_bot6,v4tp_bot_left,v4tp_bot_right,v4tp_dst_left,v4tp_dst_right);
V8Tp v8tp_dst_bot;
v8tp_dst_bot.s0145=v4tp_dst_left;
v8tp_dst_bot.s2367=v4tp_dst_right;
VSTORE(v8tp_dst_bot,dst+dst_idx+ostep,8);
}
}

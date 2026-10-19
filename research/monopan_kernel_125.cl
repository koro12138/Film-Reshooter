kernel void MedianFilter7x7C3(global Tp*src,int istep,
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
gx=clamp(gx*6,0,width*3-6);
gy=clamp(gy<<1,0,height-2);
int8 v8s32_gx_border={gx-9,gx-6,gx-3,gx+3,gx+6,gx+9,gx+12,0};
v8s32_gx_border=clamp(v8s32_gx_border,0,width*3-3);
int8 v8s32_gy_src={gy-3,gy-2,gy-1,gy,gy+1,gy+2,gy+3,gy+4};
v8s32_gy_src=clamp(v8s32_gy_src,0,height-1);
int8 v8s32_src_offset=v8s32_gy_src*istep;
int dst_idx=mad24(gy,ostep,gx);
V3Tp v3tp_top6[6];
V3Tp v3tp_bot6[6];
V3Tp v3tp_top_left,v3tp_top_right,v3tp_bot_left,v3tp_bot_right;
{
V16Tp v16tp_top={VLOAD(src+v8s32_src_offset.s0+v8s32_gx_border.s0,3),
VLOAD(src+v8s32_src_offset.s0+v8s32_gx_border.s1,3),
VLOAD(src+v8s32_src_offset.s0+v8s32_gx_border.s2,3),
VLOAD(src+v8s32_src_offset.s0+gx,3),
VLOAD(src+v8s32_src_offset.s0+v8s32_gx_border.s3,3),
0};
V3Tp v3tp_top_r0={VLOAD(src+v8s32_src_offset.s0+v8s32_gx_border.s4,3)};
V3Tp v3tp_top_r1={VLOAD(src+v8s32_src_offset.s0+v8s32_gx_border.s5,3)};
V3Tp v3tp_top_r2={VLOAD(src+v8s32_src_offset.s0+v8s32_gx_border.s6,3)};
V16Tp v16tp_bot={VLOAD(src+v8s32_src_offset.s7+v8s32_gx_border.s0,3),
VLOAD(src+v8s32_src_offset.s7+v8s32_gx_border.s1,3),
VLOAD(src+v8s32_src_offset.s7+v8s32_gx_border.s2,3),
VLOAD(src+v8s32_src_offset.s7+gx,3),
VLOAD(src+v8s32_src_offset.s7+v8s32_gx_border.s3,3),
0};
V3Tp v3tp_bot_r0={VLOAD(src+v8s32_src_offset.s7+v8s32_gx_border.s4,3)};
V3Tp v3tp_bot_r1={VLOAD(src+v8s32_src_offset.s7+v8s32_gx_border.s5,3)};
V3Tp v3tp_bot_r2={VLOAD(src+v8s32_src_offset.s7+v8s32_gx_border.s6,3)};
v3tp_top6[0]=v16tp_top.s345;
v3tp_top6[1]=v16tp_top.s678;
v3tp_top6[2]=v16tp_top.s9ab;
v3tp_top6[3]=v16tp_top.scde;
v3tp_top6[4]=v3tp_top_r0;
v3tp_top6[5]=v3tp_top_r1;
v3tp_bot6[0]=v16tp_bot.s345;
v3tp_bot6[1]=v16tp_bot.s678;
v3tp_bot6[2]=v16tp_bot.s9ab;
v3tp_bot6[3]=v16tp_bot.scde;
v3tp_bot6[4]=v3tp_bot_r0;
v3tp_bot6[5]=v3tp_bot_r1;
SORT6ElemX3(v3tp_top6[0],v3tp_top6[1],v3tp_top6[2],v3tp_top6[3],v3tp_top6[4],v3tp_top6[5]);
SORT6ElemX3(v3tp_bot6[0],v3tp_bot6[1],v3tp_bot6[2],v3tp_bot6[3],v3tp_bot6[4],v3tp_bot6[5]);
v3tp_top_left=v16tp_top.s012;
v3tp_top_right=v3tp_top_r2;
v3tp_bot_left=v16tp_bot.s012;
v3tp_bot_right=v3tp_bot_r2;
}
V3Tp v3tp_mid14[14];
V3Tp v3tp_left4[6];
V3Tp v3tp_right4[6];
{
V16Tp v16tp_src_row0={VLOAD(src+v8s32_src_offset.s1+v8s32_gx_border.s0,3),
VLOAD(src+v8s32_src_offset.s1+v8s32_gx_border.s1,3),
VLOAD(src+v8s32_src_offset.s1+v8s32_gx_border.s2,3),
VLOAD(src+v8s32_src_offset.s1+gx,3),
VLOAD(src+v8s32_src_offset.s1+v8s32_gx_border.s3,3),
0};
V16Tp v16tp_src_row1={VLOAD(src+v8s32_src_offset.s2+v8s32_gx_border.s0,3),
VLOAD(src+v8s32_src_offset.s2+v8s32_gx_border.s1,3),
VLOAD(src+v8s32_src_offset.s2+v8s32_gx_border.s2,3),
VLOAD(src+v8s32_src_offset.s2+gx,3),
VLOAD(src+v8s32_src_offset.s2+v8s32_gx_border.s3,3),
0};
V16Tp v16tp_src_row2={VLOAD(src+v8s32_src_offset.s3+v8s32_gx_border.s0,3),
VLOAD(src+v8s32_src_offset.s3+v8s32_gx_border.s1,3),
VLOAD(src+v8s32_src_offset.s3+v8s32_gx_border.s2,3),
VLOAD(src+v8s32_src_offset.s3+gx,3),
VLOAD(src+v8s32_src_offset.s3+v8s32_gx_border.s3,3),
0};
V16Tp v16tp_src_row3={VLOAD(src+v8s32_src_offset.s4+v8s32_gx_border.s0,3),
VLOAD(src+v8s32_src_offset.s4+v8s32_gx_border.s1,3),
VLOAD(src+v8s32_src_offset.s4+v8s32_gx_border.s2,3),
VLOAD(src+v8s32_src_offset.s4+gx,3),
VLOAD(src+v8s32_src_offset.s4+v8s32_gx_border.s3,3),
0};
V16Tp v16tp_src_row4={VLOAD(src+v8s32_src_offset.s5+v8s32_gx_border.s0,3),
VLOAD(src+v8s32_src_offset.s5+v8s32_gx_border.s1,3),
VLOAD(src+v8s32_src_offset.s5+v8s32_gx_border.s2,3),
VLOAD(src+v8s32_src_offset.s5+gx,3),
VLOAD(src+v8s32_src_offset.s5+v8s32_gx_border.s3,3),
0};
V16Tp v16tp_src_row5={VLOAD(src+v8s32_src_offset.s6+v8s32_gx_border.s0,3),
VLOAD(src+v8s32_src_offset.s6+v8s32_gx_border.s1,3),
VLOAD(src+v8s32_src_offset.s6+v8s32_gx_border.s2,3),
VLOAD(src+v8s32_src_offset.s6+gx,3),
VLOAD(src+v8s32_src_offset.s6+v8s32_gx_border.s3,3),
0};
V3Tp v3tp_src_row0_r0={VLOAD(src+v8s32_src_offset.s1+v8s32_gx_border.s4,3)};
V3Tp v3tp_src_row0_r1={VLOAD(src+v8s32_src_offset.s1+v8s32_gx_border.s5,3)};
V3Tp v3tp_src_row0_r2={VLOAD(src+v8s32_src_offset.s1+v8s32_gx_border.s6,3)};
V3Tp v3tp_src_row1_r0={VLOAD(src+v8s32_src_offset.s2+v8s32_gx_border.s4,3)};
V3Tp v3tp_src_row1_r1={VLOAD(src+v8s32_src_offset.s2+v8s32_gx_border.s5,3)};
V3Tp v3tp_src_row1_r2={VLOAD(src+v8s32_src_offset.s2+v8s32_gx_border.s6,3)};
V3Tp v3tp_src_row2_r0={VLOAD(src+v8s32_src_offset.s3+v8s32_gx_border.s4,3)};
V3Tp v3tp_src_row2_r1={VLOAD(src+v8s32_src_offset.s3+v8s32_gx_border.s5,3)};
V3Tp v3tp_src_row2_r2={VLOAD(src+v8s32_src_offset.s3+v8s32_gx_border.s6,3)};
V3Tp v3tp_src_row3_r0={VLOAD(src+v8s32_src_offset.s4+v8s32_gx_border.s4,3)};
V3Tp v3tp_src_row3_r1={VLOAD(src+v8s32_src_offset.s4+v8s32_gx_border.s5,3)};
V3Tp v3tp_src_row3_r2={VLOAD(src+v8s32_src_offset.s4+v8s32_gx_border.s6,3)};
V3Tp v3tp_src_row4_r0={VLOAD(src+v8s32_src_offset.s5+v8s32_gx_border.s4,3)};
V3Tp v3tp_src_row4_r1={VLOAD(src+v8s32_src_offset.s5+v8s32_gx_border.s5,3)};
V3Tp v3tp_src_row4_r2={VLOAD(src+v8s32_src_offset.s5+v8s32_gx_border.s6,3)};
V3Tp v3tp_src_row5_r0={VLOAD(src+v8s32_src_offset.s6+v8s32_gx_border.s4,3)};
V3Tp v3tp_src_row5_r1={VLOAD(src+v8s32_src_offset.s6+v8s32_gx_border.s5,3)};
V3Tp v3tp_src_row5_r2={VLOAD(src+v8s32_src_offset.s6+v8s32_gx_border.s6,3)};
SORT6ElemX16(v16tp_src_row0,v16tp_src_row1,v16tp_src_row2,v16tp_src_row3,v16tp_src_row4,v16tp_src_row5);
SORT6ElemX3(v3tp_src_row0_r0,v3tp_src_row1_r0,v3tp_src_row2_r0,v3tp_src_row3_r0,v3tp_src_row4_r0,v3tp_src_row5_r0);
SORT6ElemX3(v3tp_src_row0_r1,v3tp_src_row1_r1,v3tp_src_row2_r1,v3tp_src_row3_r1,v3tp_src_row4_r1,v3tp_src_row5_r1);
SORT6ElemX3(v3tp_src_row0_r2,v3tp_src_row1_r2,v3tp_src_row2_r2,v3tp_src_row3_r2,v3tp_src_row4_r2,v3tp_src_row5_r2);
V3Tp v3tp_elem[36]={v16tp_src_row0.s345,v16tp_src_row0.s678,v16tp_src_row0.s9ab,v16tp_src_row0.scde,v3tp_src_row0_r0,v3tp_src_row0_r1,
v16tp_src_row1.s345,v16tp_src_row1.s678,v16tp_src_row1.s9ab,v16tp_src_row1.scde,v3tp_src_row1_r0,v3tp_src_row1_r1,
v16tp_src_row2.s345,v16tp_src_row2.s678,v16tp_src_row2.s9ab,v16tp_src_row2.scde,v3tp_src_row2_r0,v3tp_src_row2_r1,
v16tp_src_row3.s345,v16tp_src_row3.s678,v16tp_src_row3.s9ab,v16tp_src_row3.scde,v3tp_src_row3_r0,v3tp_src_row3_r1,
v16tp_src_row4.s345,v16tp_src_row4.s678,v16tp_src_row4.s9ab,v16tp_src_row4.scde,v3tp_src_row4_r0,v3tp_src_row4_r1,
v16tp_src_row5.s345,v16tp_src_row5.s678,v16tp_src_row5.s9ab,v16tp_src_row5.scde,v3tp_src_row5_r0,v3tp_src_row5_r1};
v3tp_left4[0]=v16tp_src_row0.s012;
v3tp_left4[1]=v16tp_src_row1.s012;
v3tp_left4[2]=v16tp_src_row2.s012;
v3tp_left4[3]=v16tp_src_row3.s012;
v3tp_left4[4]=v16tp_src_row4.s012;
v3tp_left4[5]=v16tp_src_row5.s012;
v3tp_right4[0]=v3tp_src_row0_r2;
v3tp_right4[1]=v3tp_src_row1_r2;
v3tp_right4[2]=v3tp_src_row2_r2;
v3tp_right4[3]=v3tp_src_row3_r2;
v3tp_right4[4]=v3tp_src_row4_r2;
v3tp_right4[5]=v3tp_src_row5_r2;
GET_MID14_OF_36(3,v3tp_elem[0],v3tp_elem[1],v3tp_elem[2],v3tp_elem[3],v3tp_elem[4],v3tp_elem[5],
v3tp_elem[6],v3tp_elem[7],v3tp_elem[8],v3tp_elem[9],v3tp_elem[10],v3tp_elem[11],
v3tp_elem[12],v3tp_elem[13],v3tp_elem[14],v3tp_elem[15],v3tp_elem[16],v3tp_elem[17],
v3tp_elem[18],v3tp_elem[19],v3tp_elem[20],v3tp_elem[21],v3tp_elem[22],v3tp_elem[23],
v3tp_elem[24],v3tp_elem[25],v3tp_elem[26],v3tp_elem[27],v3tp_elem[28],v3tp_elem[29],
v3tp_elem[30],v3tp_elem[31],v3tp_elem[32],v3tp_elem[33],v3tp_elem[34],v3tp_elem[35]);
v3tp_mid14[0]=v3tp_elem[4];
v3tp_mid14[1]=v3tp_elem[9];
v3tp_mid14[2]=v3tp_elem[14];
v3tp_mid14[3]=v3tp_elem[15];
v3tp_mid14[4]=v3tp_elem[19];
v3tp_mid14[5]=v3tp_elem[20];
v3tp_mid14[6]=v3tp_elem[21];
v3tp_mid14[7]=v3tp_elem[25];
v3tp_mid14[8]=v3tp_elem[26];
v3tp_mid14[9]=v3tp_elem[27];
v3tp_mid14[10]=v3tp_elem[30];
v3tp_mid14[11]=v3tp_elem[31];
v3tp_mid14[12]=v3tp_elem[32];
v3tp_mid14[13]=v3tp_elem[33];
}
{
V3Tp v3tp_mid14_copy[14]={v3tp_mid14[0],v3tp_mid14[1],v3tp_mid14[2],v3tp_mid14[3],v3tp_mid14[4],v3tp_mid14[5],v3tp_mid14[6],
v3tp_mid14[7],v3tp_mid14[8],v3tp_mid14[9],v3tp_mid14[10],v3tp_mid14[11],v3tp_mid14[12],v3tp_mid14[13]};
V3Tp v3tp_left4_copy[6]={v3tp_left4[0],v3tp_left4[1],v3tp_left4[2],v3tp_left4[3],v3tp_left4[4],v3tp_left4[5]};
V3Tp v3tp_right4_copy[6]={v3tp_right4[0],v3tp_right4[1],v3tp_right4[2],v3tp_right4[3],v3tp_right4[4],v3tp_right4[5]};
V3Tp v3tp_dst_left,v3tp_dst_right;
GET_MEDIAN7x7(3,v3tp_mid14_copy,v3tp_left4_copy,v3tp_right4_copy,v3tp_top6,v3tp_top_left,v3tp_top_right,v3tp_dst_left,v3tp_dst_right);
VSTORE(v3tp_dst_left,dst+dst_idx,3);
VSTORE(v3tp_dst_right,dst+dst_idx+3,3);
}
{
V3Tp v3tp_dst_left;
V3Tp v3tp_dst_right;
GET_MEDIAN7x7(3,v3tp_mid14,v3tp_left4,v3tp_right4,v3tp_bot6,v3tp_bot_left,v3tp_bot_right,v3tp_dst_left,v3tp_dst_right);
VSTORE(v3tp_dst_left,dst+dst_idx+ostep,3);
VSTORE(v3tp_dst_right,dst+dst_idx+ostep+3,3);
}
}

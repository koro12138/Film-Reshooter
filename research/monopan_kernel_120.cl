kernel void MedianFilter5x5C3(global Tp*src,int istep,
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
int8 v4s32_gx_border={gx-6,gx-3,gx+3,gx+6,gx+9,0,0,0};
v4s32_gx_border=clamp(v4s32_gx_border,0,width*3-3);
int8 v8s32_gy_src={gy-2,gy-1,gy,gy+1,gy+2,gy+3,0,0};
v8s32_gy_src=clamp(v8s32_gy_src,0,height-1);
int8 v8s32_src_offset=v8s32_gy_src*istep;
int dst_idx=mad24(gy,ostep,gx);
V3Tp v3tp_top4[4];
V3Tp v3tp_bot4[4];
V3Tp v3tp_top_left,v3tp_top_right,v3tp_bot_left,v3tp_bot_right;
{
V16Tp v16tp_top={VLOAD(src+v8s32_src_offset.s0+v4s32_gx_border.s0,3),
VLOAD(src+v8s32_src_offset.s0+v4s32_gx_border.s1,3),
VLOAD(src+v8s32_src_offset.s0+gx,3),
VLOAD(src+v8s32_src_offset.s0+v4s32_gx_border.s2,3),
VLOAD(src+v8s32_src_offset.s0+v4s32_gx_border.s3,3),
0};
V16Tp v16tp_bot={VLOAD(src+v8s32_src_offset.s5+v4s32_gx_border.s0,3),
VLOAD(src+v8s32_src_offset.s5+v4s32_gx_border.s1,3),
VLOAD(src+v8s32_src_offset.s5+gx,3),
VLOAD(src+v8s32_src_offset.s5+v4s32_gx_border.s2,3),
VLOAD(src+v8s32_src_offset.s5+v4s32_gx_border.s3,3),
0};
V3Tp v3tp_top_0={VLOAD(src+v8s32_src_offset.s0+v4s32_gx_border.s4,3)};
V3Tp v3tp_bot_0={VLOAD(src+v8s32_src_offset.s5+v4s32_gx_border.s4,3)};
v3tp_top4[0]=(V3Tp){v16tp_top.s345};
v3tp_top4[1]=(V3Tp){v16tp_top.s678};
v3tp_top4[2]=(V3Tp){v16tp_top.s9ab};
v3tp_top4[3]=(V3Tp){v16tp_top.scde};
v3tp_bot4[0]=(V3Tp){v16tp_bot.s345};
v3tp_bot4[1]=(V3Tp){v16tp_bot.s678};
v3tp_bot4[2]=(V3Tp){v16tp_bot.s9ab};
v3tp_bot4[3]=(V3Tp){v16tp_bot.scde};
SORT4ElemX3(v3tp_top4[0],v3tp_top4[1],v3tp_top4[2],v3tp_top4[3]);
SORT4ElemX3(v3tp_bot4[0],v3tp_bot4[1],v3tp_bot4[2],v3tp_bot4[3]);
v3tp_top_left=(V3Tp){v16tp_top.s012};
v3tp_top_right=(V3Tp){v3tp_top_0.s012};
v3tp_bot_left=(V3Tp){v16tp_bot.s012};
v3tp_bot_right=(V3Tp){v3tp_bot_0.s012};
}
V3Tp v3tp_mid10[10];
V3Tp v3tp_left4[4];
V3Tp v3tp_right4[4];
{
V16Tp v16tp_src_row0={VLOAD(src+v8s32_src_offset.s1+v4s32_gx_border.s0,3),
VLOAD(src+v8s32_src_offset.s1+v4s32_gx_border.s1,3),
VLOAD(src+v8s32_src_offset.s1+gx,3),
VLOAD(src+v8s32_src_offset.s1+v4s32_gx_border.s2,3),
VLOAD(src+v8s32_src_offset.s1+v4s32_gx_border.s3,3),
0};
V16Tp v16tp_src_row1={VLOAD(src+v8s32_src_offset.s2+v4s32_gx_border.s0,3),
VLOAD(src+v8s32_src_offset.s2+v4s32_gx_border.s1,3),
VLOAD(src+v8s32_src_offset.s2+gx,3),
VLOAD(src+v8s32_src_offset.s2+v4s32_gx_border.s2,3),
VLOAD(src+v8s32_src_offset.s2+v4s32_gx_border.s3,3),
0};
V16Tp v16tp_src_row2={VLOAD(src+v8s32_src_offset.s3+v4s32_gx_border.s0,3),
VLOAD(src+v8s32_src_offset.s3+v4s32_gx_border.s1,3),
VLOAD(src+v8s32_src_offset.s3+gx,3),
VLOAD(src+v8s32_src_offset.s3+v4s32_gx_border.s2,3),
VLOAD(src+v8s32_src_offset.s3+v4s32_gx_border.s3,3),
0};
V16Tp v16tp_src_row3={VLOAD(src+v8s32_src_offset.s4+v4s32_gx_border.s0,3),
VLOAD(src+v8s32_src_offset.s4+v4s32_gx_border.s1,3),
VLOAD(src+v8s32_src_offset.s4+gx,3),
VLOAD(src+v8s32_src_offset.s4+v4s32_gx_border.s2,3),
VLOAD(src+v8s32_src_offset.s4+v4s32_gx_border.s3,3),
0};
V3Tp v3tp_src_row0_0={VLOAD(src+v8s32_src_offset.s1+v4s32_gx_border.s4,3)};
V3Tp v3tp_src_row1_0={VLOAD(src+v8s32_src_offset.s2+v4s32_gx_border.s4,3)};
V3Tp v3tp_src_row2_0={VLOAD(src+v8s32_src_offset.s3+v4s32_gx_border.s4,3)};
V3Tp v3tp_src_row3_0={VLOAD(src+v8s32_src_offset.s4+v4s32_gx_border.s4,3)};
V8Tp v8tp_src_row0_c0={v16tp_src_row0.s0369,v16tp_src_row0.sc,v3tp_src_row0_0.s0,0,0};
V8Tp v8tp_src_row1_c0={v16tp_src_row1.s0369,v16tp_src_row1.sc,v3tp_src_row1_0.s0,0,0};
V8Tp v8tp_src_row2_c0={v16tp_src_row2.s0369,v16tp_src_row2.sc,v3tp_src_row2_0.s0,0,0};
V8Tp v8tp_src_row3_c0={v16tp_src_row3.s0369,v16tp_src_row3.sc,v3tp_src_row3_0.s0,0,0};
V8Tp v8tp_src_row0_c1={v16tp_src_row0.s147a,v16tp_src_row0.sd,v3tp_src_row0_0.s1,0,0};
V8Tp v8tp_src_row1_c1={v16tp_src_row1.s147a,v16tp_src_row1.sd,v3tp_src_row1_0.s1,0,0};
V8Tp v8tp_src_row2_c1={v16tp_src_row2.s147a,v16tp_src_row2.sd,v3tp_src_row2_0.s1,0,0};
V8Tp v8tp_src_row3_c1={v16tp_src_row3.s147a,v16tp_src_row3.sd,v3tp_src_row3_0.s1,0,0};
V8Tp v8tp_src_row0_c2={v16tp_src_row0.s258b,v16tp_src_row0.se,v3tp_src_row0_0.s2,0,0};
V8Tp v8tp_src_row1_c2={v16tp_src_row1.s258b,v16tp_src_row1.se,v3tp_src_row1_0.s2,0,0};
V8Tp v8tp_src_row2_c2={v16tp_src_row2.s258b,v16tp_src_row2.se,v3tp_src_row2_0.s2,0,0};
V8Tp v8tp_src_row3_c2={v16tp_src_row3.s258b,v16tp_src_row3.se,v3tp_src_row3_0.s2,0,0};
SORT4ElemX8(v8tp_src_row0_c0,v8tp_src_row1_c0,v8tp_src_row2_c0,v8tp_src_row3_c0);
SORT4ElemX8(v8tp_src_row0_c1,v8tp_src_row1_c1,v8tp_src_row2_c1,v8tp_src_row3_c1);
SORT4ElemX8(v8tp_src_row0_c2,v8tp_src_row1_c2,v8tp_src_row2_c2,v8tp_src_row3_c2);
V3Tp v3tp_elem[16]={{v8tp_src_row0_c0.s1,v8tp_src_row0_c1.s1,v8tp_src_row0_c2.s1},
{v8tp_src_row0_c0.s2,v8tp_src_row0_c1.s2,v8tp_src_row0_c2.s2},
{v8tp_src_row0_c0.s3,v8tp_src_row0_c1.s3,v8tp_src_row0_c2.s3},
{v8tp_src_row0_c0.s4,v8tp_src_row0_c1.s4,v8tp_src_row0_c2.s4},
{v8tp_src_row1_c0.s1,v8tp_src_row1_c1.s1,v8tp_src_row1_c2.s1},
{v8tp_src_row1_c0.s2,v8tp_src_row1_c1.s2,v8tp_src_row1_c2.s2},
{v8tp_src_row1_c0.s3,v8tp_src_row1_c1.s3,v8tp_src_row1_c2.s3},
{v8tp_src_row1_c0.s4,v8tp_src_row1_c1.s4,v8tp_src_row1_c2.s4},
{v8tp_src_row2_c0.s1,v8tp_src_row2_c1.s1,v8tp_src_row2_c2.s1},
{v8tp_src_row2_c0.s2,v8tp_src_row2_c1.s2,v8tp_src_row2_c2.s2},
{v8tp_src_row2_c0.s3,v8tp_src_row2_c1.s3,v8tp_src_row2_c2.s3},
{v8tp_src_row2_c0.s4,v8tp_src_row2_c1.s4,v8tp_src_row2_c2.s4},
{v8tp_src_row3_c0.s1,v8tp_src_row3_c1.s1,v8tp_src_row3_c2.s1},
{v8tp_src_row3_c0.s2,v8tp_src_row3_c1.s2,v8tp_src_row3_c2.s2},
{v8tp_src_row3_c0.s3,v8tp_src_row3_c1.s3,v8tp_src_row3_c2.s3},
{v8tp_src_row3_c0.s4,v8tp_src_row3_c1.s4,v8tp_src_row3_c2.s4}};
v3tp_left4[0]=(V3Tp){v8tp_src_row0_c0.s0,v8tp_src_row0_c1.s0,v8tp_src_row0_c2.s0};
v3tp_left4[1]=(V3Tp){v8tp_src_row1_c0.s0,v8tp_src_row1_c1.s0,v8tp_src_row1_c2.s0};
v3tp_left4[2]=(V3Tp){v8tp_src_row2_c0.s0,v8tp_src_row2_c1.s0,v8tp_src_row2_c2.s0};
v3tp_left4[3]=(V3Tp){v8tp_src_row3_c0.s0,v8tp_src_row3_c1.s0,v8tp_src_row3_c2.s0};
v3tp_right4[0]=(V3Tp){v8tp_src_row0_c0.s5,v8tp_src_row0_c1.s5,v8tp_src_row0_c2.s5};
v3tp_right4[1]=(V3Tp){v8tp_src_row1_c0.s5,v8tp_src_row1_c1.s5,v8tp_src_row1_c2.s5};
v3tp_right4[2]=(V3Tp){v8tp_src_row2_c0.s5,v8tp_src_row2_c1.s5,v8tp_src_row2_c2.s5};
v3tp_right4[3]=(V3Tp){v8tp_src_row3_c0.s5,v8tp_src_row3_c1.s5,v8tp_src_row3_c2.s5};
GET_MID10_OF_16(3,v3tp_elem[0],v3tp_elem[1],v3tp_elem[2],v3tp_elem[3],
v3tp_elem[4],v3tp_elem[5],v3tp_elem[6],v3tp_elem[7],
v3tp_elem[8],v3tp_elem[9],v3tp_elem[10],v3tp_elem[11],
v3tp_elem[12],v3tp_elem[13],v3tp_elem[14],v3tp_elem[15]);
v3tp_mid10[0]=v3tp_elem[2];
v3tp_mid10[1]=v3tp_elem[3];
v3tp_mid10[2]=v3tp_elem[5];
v3tp_mid10[3]=v3tp_elem[6];
v3tp_mid10[4]=v3tp_elem[7];
v3tp_mid10[5]=v3tp_elem[8];
v3tp_mid10[6]=v3tp_elem[9];
v3tp_mid10[7]=v3tp_elem[10];
v3tp_mid10[8]=v3tp_elem[12];
v3tp_mid10[9]=v3tp_elem[13];
}
{
V3Tp v3tp_mid10_copy[10]={v3tp_mid10[0],v3tp_mid10[1],v3tp_mid10[2],v3tp_mid10[3],v3tp_mid10[4],
v3tp_mid10[5],v3tp_mid10[6],v3tp_mid10[7],v3tp_mid10[8],v3tp_mid10[9]};
V3Tp v3tp_left4_copy[4]={v3tp_left4[0],v3tp_left4[1],v3tp_left4[2],v3tp_left4[3]};
V3Tp v3tp_right4_copy[4]={v3tp_right4[0],v3tp_right4[1],v3tp_right4[2],v3tp_right4[3]};
V3Tp v3tp_dst_left,v3tp_dst_right;
GET_MEDIAN5x5(3,v3tp_mid10_copy,v3tp_left4_copy,v3tp_right4_copy,v3tp_top4,v3tp_top_left,v3tp_top_right,v3tp_dst_left,v3tp_dst_right);
VSTORE(v3tp_dst_left,dst+dst_idx,3);
VSTORE(v3tp_dst_right,dst+dst_idx+3,3);
}
{
V3Tp v3tp_dst_left;
V3Tp v3tp_dst_right;
GET_MEDIAN5x5(3,v3tp_mid10,v3tp_left4,v3tp_right4,v3tp_bot4,v3tp_bot_left,v3tp_bot_right,v3tp_dst_left,v3tp_dst_right);
VSTORE(v3tp_dst_left,dst+dst_idx+ostep,3);
VSTORE(v3tp_dst_right,dst+dst_idx+ostep+3,3);
}
}

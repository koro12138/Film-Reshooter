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
gx=clamp(gx<<2,0,width*2-4);
gy=clamp(gy<<1,0,height-2);
int8 v8s32_gx_border={gx-6,gx-4,gx-2,gx+4,gx+6,gx+8,0,0};
v8s32_gx_border=clamp(v8s32_gx_border,0,width*2-2);
int8 v8s32_gy_src={gy-3,gy-2,gy-1,gy,gy+1,gy+2,gy+3,gy+4};
v8s32_gy_src=clamp(v8s32_gy_src,0,height-1);
int8 v8s32_src_offset=v8s32_gy_src*istep;
int dst_idx=mad24(gy,ostep,gx);
V2Tp v2tp_top4[6];
V2Tp v2tp_bot4[6];
V2Tp v2tp_top_left,v2tp_top_right,v2tp_bot_left,v2tp_bot_right;
{
V16Tp v16tp_top={VLOAD(src+v8s32_src_offset.s0+v8s32_gx_border.s0,2),
VLOAD(src+v8s32_src_offset.s0+v8s32_gx_border.s1,2),
VLOAD(src+v8s32_src_offset.s0+v8s32_gx_border.s2,2),
VLOAD(src+v8s32_src_offset.s0+gx,4),
VLOAD(src+v8s32_src_offset.s0+v8s32_gx_border.s3,2),
VLOAD(src+v8s32_src_offset.s0+v8s32_gx_border.s4,2),
VLOAD(src+v8s32_src_offset.s0+v8s32_gx_border.s5,2)};
V16Tp v16tp_bot={VLOAD(src+v8s32_src_offset.s7+v8s32_gx_border.s0,2),
VLOAD(src+v8s32_src_offset.s7+v8s32_gx_border.s1,2),
VLOAD(src+v8s32_src_offset.s7+v8s32_gx_border.s2,2),
VLOAD(src+v8s32_src_offset.s7+gx,4),
VLOAD(src+v8s32_src_offset.s7+v8s32_gx_border.s3,2),
VLOAD(src+v8s32_src_offset.s7+v8s32_gx_border.s4,2),
VLOAD(src+v8s32_src_offset.s7+v8s32_gx_border.s5,2)};
v2tp_top4[0]=(V2Tp){v16tp_top.s23};
v2tp_top4[1]=(V2Tp){v16tp_top.s45};
v2tp_top4[2]=(V2Tp){v16tp_top.s67};
v2tp_top4[3]=(V2Tp){v16tp_top.s89};
v2tp_top4[4]=(V2Tp){v16tp_top.sab};
v2tp_top4[5]=(V2Tp){v16tp_top.scd};
v2tp_bot4[0]=(V2Tp){v16tp_bot.s23};
v2tp_bot4[1]=(V2Tp){v16tp_bot.s45};
v2tp_bot4[2]=(V2Tp){v16tp_bot.s67};
v2tp_bot4[3]=(V2Tp){v16tp_bot.s89};
v2tp_bot4[4]=(V2Tp){v16tp_bot.sab};
v2tp_bot4[5]=(V2Tp){v16tp_bot.scd};
SORT6ElemX2(v2tp_top4[0],v2tp_top4[1],v2tp_top4[2],v2tp_top4[3],v2tp_top4[4],v2tp_top4[5]);
SORT6ElemX2(v2tp_bot4[0],v2tp_bot4[1],v2tp_bot4[2],v2tp_bot4[3],v2tp_bot4[4],v2tp_bot4[5]);
v2tp_top_left=(V2Tp){v16tp_top.s01};
v2tp_top_right=(V2Tp){v16tp_top.sef};
v2tp_bot_left=(V2Tp){v16tp_bot.s01};
v2tp_bot_right=(V2Tp){v16tp_bot.sef};
}
V2Tp v2tp_mid14[14];
V2Tp v2tp_left6[6];
V2Tp v2tp_right6[6];
{
V16Tp v16tp_src_row0={VLOAD(src+v8s32_src_offset.s1+v8s32_gx_border.s0,2),
VLOAD(src+v8s32_src_offset.s1+v8s32_gx_border.s1,2),
VLOAD(src+v8s32_src_offset.s1+v8s32_gx_border.s2,2),
VLOAD(src+v8s32_src_offset.s1+gx,4),
VLOAD(src+v8s32_src_offset.s1+v8s32_gx_border.s3,2),
VLOAD(src+v8s32_src_offset.s1+v8s32_gx_border.s4,2),
VLOAD(src+v8s32_src_offset.s1+v8s32_gx_border.s5,2)};
V16Tp v16tp_src_row1={VLOAD(src+v8s32_src_offset.s2+v8s32_gx_border.s0,2),
VLOAD(src+v8s32_src_offset.s2+v8s32_gx_border.s1,2),
VLOAD(src+v8s32_src_offset.s2+v8s32_gx_border.s2,2),
VLOAD(src+v8s32_src_offset.s2+gx,4),
VLOAD(src+v8s32_src_offset.s2+v8s32_gx_border.s3,2),
VLOAD(src+v8s32_src_offset.s2+v8s32_gx_border.s4,2),
VLOAD(src+v8s32_src_offset.s2+v8s32_gx_border.s5,2)};
V16Tp v16tp_src_row2={VLOAD(src+v8s32_src_offset.s3+v8s32_gx_border.s0,2),
VLOAD(src+v8s32_src_offset.s3+v8s32_gx_border.s1,2),
VLOAD(src+v8s32_src_offset.s3+v8s32_gx_border.s2,2),
VLOAD(src+v8s32_src_offset.s3+gx,4),
VLOAD(src+v8s32_src_offset.s3+v8s32_gx_border.s3,2),
VLOAD(src+v8s32_src_offset.s3+v8s32_gx_border.s4,2),
VLOAD(src+v8s32_src_offset.s3+v8s32_gx_border.s5,2)};
V16Tp v16tp_src_row3={VLOAD(src+v8s32_src_offset.s4+v8s32_gx_border.s0,2),
VLOAD(src+v8s32_src_offset.s4+v8s32_gx_border.s1,2),
VLOAD(src+v8s32_src_offset.s4+v8s32_gx_border.s2,2),
VLOAD(src+v8s32_src_offset.s4+gx,4),
VLOAD(src+v8s32_src_offset.s4+v8s32_gx_border.s3,2),
VLOAD(src+v8s32_src_offset.s4+v8s32_gx_border.s4,2),
VLOAD(src+v8s32_src_offset.s4+v8s32_gx_border.s5,2)};
V16Tp v16tp_src_row4={VLOAD(src+v8s32_src_offset.s5+v8s32_gx_border.s0,2),
VLOAD(src+v8s32_src_offset.s5+v8s32_gx_border.s1,2),
VLOAD(src+v8s32_src_offset.s5+v8s32_gx_border.s2,2),
VLOAD(src+v8s32_src_offset.s5+gx,4),
VLOAD(src+v8s32_src_offset.s5+v8s32_gx_border.s3,2),
VLOAD(src+v8s32_src_offset.s5+v8s32_gx_border.s4,2),
VLOAD(src+v8s32_src_offset.s5+v8s32_gx_border.s5,2)};
V16Tp v16tp_src_row5={VLOAD(src+v8s32_src_offset.s6+v8s32_gx_border.s0,2),
VLOAD(src+v8s32_src_offset.s6+v8s32_gx_border.s1,2),
VLOAD(src+v8s32_src_offset.s6+v8s32_gx_border.s2,2),
VLOAD(src+v8s32_src_offset.s6+gx,4),
VLOAD(src+v8s32_src_offset.s6+v8s32_gx_border.s3,2),
VLOAD(src+v8s32_src_offset.s6+v8s32_gx_border.s4,2),
VLOAD(src+v8s32_src_offset.s6+v8s32_gx_border.s5,2)};
SORT6ElemX16(v16tp_src_row0,v16tp_src_row1,v16tp_src_row2,v16tp_src_row3,v16tp_src_row4,v16tp_src_row5);
V2Tp v2tp_elem[36]={
v16tp_src_row0.s23,v16tp_src_row0.s45,v16tp_src_row0.s67,v16tp_src_row0.s89,v16tp_src_row0.sab,v16tp_src_row0.scd,
v16tp_src_row1.s23,v16tp_src_row1.s45,v16tp_src_row1.s67,v16tp_src_row1.s89,v16tp_src_row1.sab,v16tp_src_row1.scd,
v16tp_src_row2.s23,v16tp_src_row2.s45,v16tp_src_row2.s67,v16tp_src_row2.s89,v16tp_src_row2.sab,v16tp_src_row2.scd,
v16tp_src_row3.s23,v16tp_src_row3.s45,v16tp_src_row3.s67,v16tp_src_row3.s89,v16tp_src_row3.sab,v16tp_src_row3.scd,
v16tp_src_row4.s23,v16tp_src_row4.s45,v16tp_src_row4.s67,v16tp_src_row4.s89,v16tp_src_row4.sab,v16tp_src_row4.scd,
v16tp_src_row5.s23,v16tp_src_row5.s45,v16tp_src_row5.s67,v16tp_src_row5.s89,v16tp_src_row5.sab,v16tp_src_row5.scd
};
v2tp_left6[0]=v16tp_src_row0.s01;
v2tp_left6[1]=v16tp_src_row1.s01;
v2tp_left6[2]=v16tp_src_row2.s01;
v2tp_left6[3]=v16tp_src_row3.s01;
v2tp_left6[4]=v16tp_src_row4.s01;
v2tp_left6[5]=v16tp_src_row5.s01;
v2tp_right6[0]=v16tp_src_row0.sef;
v2tp_right6[1]=v16tp_src_row1.sef;
v2tp_right6[2]=v16tp_src_row2.sef;
v2tp_right6[3]=v16tp_src_row3.sef;
v2tp_right6[4]=v16tp_src_row4.sef;
v2tp_right6[5]=v16tp_src_row5.sef;
GET_MID14_OF_36(2,v2tp_elem[0],v2tp_elem[1],v2tp_elem[2],v2tp_elem[3],v2tp_elem[4],v2tp_elem[5],
v2tp_elem[6],v2tp_elem[7],v2tp_elem[8],v2tp_elem[9],v2tp_elem[10],v2tp_elem[11],
v2tp_elem[12],v2tp_elem[13],v2tp_elem[14],v2tp_elem[15],v2tp_elem[16],v2tp_elem[17],
v2tp_elem[18],v2tp_elem[19],v2tp_elem[20],v2tp_elem[21],v2tp_elem[22],v2tp_elem[23],
v2tp_elem[24],v2tp_elem[25],v2tp_elem[26],v2tp_elem[27],v2tp_elem[28],v2tp_elem[29],
v2tp_elem[30],v2tp_elem[31],v2tp_elem[32],v2tp_elem[33],v2tp_elem[34],v2tp_elem[35]);
v2tp_mid14[0]=v2tp_elem[4];
v2tp_mid14[1]=v2tp_elem[9];
v2tp_mid14[2]=v2tp_elem[14];
v2tp_mid14[3]=v2tp_elem[15];
v2tp_mid14[4]=v2tp_elem[19];
v2tp_mid14[5]=v2tp_elem[20];
v2tp_mid14[6]=v2tp_elem[21];
v2tp_mid14[7]=v2tp_elem[25];
v2tp_mid14[8]=v2tp_elem[26];
v2tp_mid14[9]=v2tp_elem[27];
v2tp_mid14[10]=v2tp_elem[30];
v2tp_mid14[11]=v2tp_elem[31];
v2tp_mid14[12]=v2tp_elem[32];
v2tp_mid14[13]=v2tp_elem[33];
}
{
V2Tp v2tp_mid14_copy[14]={v2tp_mid14[0],v2tp_mid14[1],v2tp_mid14[2],v2tp_mid14[3],v2tp_mid14[4],v2tp_mid14[5],v2tp_mid14[6],
v2tp_mid14[7],v2tp_mid14[8],v2tp_mid14[9],v2tp_mid14[10],v2tp_mid14[11],v2tp_mid14[12],v2tp_mid14[13]};
V2Tp v2tp_left4_copy[6]={v2tp_left6[0],v2tp_left6[1],v2tp_left6[2],v2tp_left6[3],v2tp_left6[4],v2tp_left6[5]};
V2Tp v2tp_right4_copy[6]={v2tp_right6[0],v2tp_right6[1],v2tp_right6[2],v2tp_right6[3],v2tp_right6[4],v2tp_right6[5]};
V2Tp v2tp_dst_left,v2tp_dst_right;
GET_MEDIAN7x7(2,v2tp_mid14_copy,v2tp_left4_copy,v2tp_right4_copy,v2tp_top4,v2tp_top_left,v2tp_top_right,v2tp_dst_left,v2tp_dst_right);
V4Tp v4tp_dst_top;
v4tp_dst_top.s01=v2tp_dst_left;
v4tp_dst_top.s23=v2tp_dst_right;
VSTORE(v4tp_dst_top,dst+dst_idx,4);
}
{
V2Tp v2tp_dst_left;
V2Tp v2tp_dst_right;
GET_MEDIAN7x7(2,v2tp_mid14,v2tp_left6,v2tp_right6,v2tp_bot4,v2tp_bot_left,v2tp_bot_right,v2tp_dst_left,v2tp_dst_right);
V4Tp v4tp_dst_bot;
v4tp_dst_bot.s01=v2tp_dst_left;
v4tp_dst_bot.s23=v2tp_dst_right;
VSTORE(v4tp_dst_bot,dst+dst_idx+ostep,4);
}
}

kernel void MedianFilter5x5C2(global Tp*src,int istep,
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
int4 v4s32_gx_border={gx-4,gx-2,gx+8,gx+10};
v4s32_gx_border=clamp(v4s32_gx_border,0,width*2-2);
int8 v8s32_gy_src={gy-2,gy-1,gy,gy+1,gy+2,gy+3,0,0};
v8s32_gy_src=clamp(v8s32_gy_src,0,height-1);
int8 v8s32_src_offset=v8s32_gy_src*istep;
int dst_idx=mad24(gy,ostep,gx);
V4Tp v4tp_top4[4];
V4Tp v4tp_bot4[4];
V4Tp v4tp_top_left,v4tp_top_right,v4tp_bot_left,v4tp_bot_right;
{
V16Tp v16tp_top={VLOAD(src+v8s32_src_offset.s0+v4s32_gx_border.s0,2),
VLOAD(src+v8s32_src_offset.s0+v4s32_gx_border.s1,2),
VLOAD(src+v8s32_src_offset.s0+gx,8),
VLOAD(src+v8s32_src_offset.s0+v4s32_gx_border.s2,2),
VLOAD(src+v8s32_src_offset.s0+v4s32_gx_border.s3,2)};
V16Tp v16tp_bot={VLOAD(src+v8s32_src_offset.s5+v4s32_gx_border.s0,2),
VLOAD(src+v8s32_src_offset.s5+v4s32_gx_border.s1,2),
VLOAD(src+v8s32_src_offset.s5+gx,8),
VLOAD(src+v8s32_src_offset.s5+v4s32_gx_border.s2,2),
VLOAD(src+v8s32_src_offset.s5+v4s32_gx_border.s3,2)};
v4tp_top4[0]=v16tp_top.s2367;
v4tp_top4[1]=v16tp_top.s4589;
v4tp_top4[2]=v16tp_top.s67ab;
v4tp_top4[3]=v16tp_top.s89cd;
v4tp_bot4[0]=v16tp_bot.s2367;
v4tp_bot4[1]=v16tp_bot.s4589;
v4tp_bot4[2]=v16tp_bot.s67ab;
v4tp_bot4[3]=v16tp_bot.s89cd;
SORT4ElemX4(v4tp_top4[0],v4tp_top4[1],v4tp_top4[2],v4tp_top4[3]);
SORT4ElemX4(v4tp_bot4[0],v4tp_bot4[1],v4tp_bot4[2],v4tp_bot4[3]);
v4tp_top_left=v16tp_top.s0145;
v4tp_top_right=v16tp_top.sabef;
v4tp_bot_left=v16tp_bot.s0145;
v4tp_bot_right=v16tp_bot.sabef;
}
V4Tp v4tp_mid10[10];
V4Tp v4tp_left4[4];
V4Tp v4tp_right4[4];
{
V16Tp v16tp_src_row0={VLOAD(src+v8s32_src_offset.s1+v4s32_gx_border.s0,2),
VLOAD(src+v8s32_src_offset.s1+v4s32_gx_border.s1,2),
VLOAD(src+v8s32_src_offset.s1+gx,8),
VLOAD(src+v8s32_src_offset.s1+v4s32_gx_border.s2,2),
VLOAD(src+v8s32_src_offset.s1+v4s32_gx_border.s3,2)};
V16Tp v16tp_src_row1={VLOAD(src+v8s32_src_offset.s2+v4s32_gx_border.s0,2),
VLOAD(src+v8s32_src_offset.s2+v4s32_gx_border.s1,2),
VLOAD(src+v8s32_src_offset.s2+gx,8),
VLOAD(src+v8s32_src_offset.s2+v4s32_gx_border.s2,2),
VLOAD(src+v8s32_src_offset.s2+v4s32_gx_border.s3,2)};
V16Tp v16tp_src_row2={VLOAD(src+v8s32_src_offset.s3+v4s32_gx_border.s0,2),
VLOAD(src+v8s32_src_offset.s3+v4s32_gx_border.s1,2),
VLOAD(src+v8s32_src_offset.s3+gx,8),
VLOAD(src+v8s32_src_offset.s3+v4s32_gx_border.s2,2),
VLOAD(src+v8s32_src_offset.s3+v4s32_gx_border.s3,2)};
V16Tp v16tp_src_row3={VLOAD(src+v8s32_src_offset.s4+v4s32_gx_border.s0,2),
VLOAD(src+v8s32_src_offset.s4+v4s32_gx_border.s1,2),
VLOAD(src+v8s32_src_offset.s4+gx,8),
VLOAD(src+v8s32_src_offset.s4+v4s32_gx_border.s2,2),
VLOAD(src+v8s32_src_offset.s4+v4s32_gx_border.s3,2)};
SORT4ElemX16(v16tp_src_row0,v16tp_src_row1,v16tp_src_row2,v16tp_src_row3);
V4Tp v4tp_elem[16]={v16tp_src_row0.s2367,v16tp_src_row0.s4589,v16tp_src_row0.s67ab,v16tp_src_row0.s89cd,
v16tp_src_row1.s2367,v16tp_src_row1.s4589,v16tp_src_row1.s67ab,v16tp_src_row1.s89cd,
v16tp_src_row2.s2367,v16tp_src_row2.s4589,v16tp_src_row2.s67ab,v16tp_src_row2.s89cd,
v16tp_src_row3.s2367,v16tp_src_row3.s4589,v16tp_src_row3.s67ab,v16tp_src_row3.s89cd};
v4tp_left4[0]=v16tp_src_row0.s0145;
v4tp_left4[1]=v16tp_src_row1.s0145;
v4tp_left4[2]=v16tp_src_row2.s0145;
v4tp_left4[3]=v16tp_src_row3.s0145;
v4tp_right4[0]=v16tp_src_row0.sabef;
v4tp_right4[1]=v16tp_src_row1.sabef;
v4tp_right4[2]=v16tp_src_row2.sabef;
v4tp_right4[3]=v16tp_src_row3.sabef;
GET_MID10_OF_16(4,v4tp_elem[0],v4tp_elem[1],v4tp_elem[2],v4tp_elem[3],
v4tp_elem[4],v4tp_elem[5],v4tp_elem[6],v4tp_elem[7],
v4tp_elem[8],v4tp_elem[9],v4tp_elem[10],v4tp_elem[11],
v4tp_elem[12],v4tp_elem[13],v4tp_elem[14],v4tp_elem[15]);
v4tp_mid10[0]=v4tp_elem[2];
v4tp_mid10[1]=v4tp_elem[3];
v4tp_mid10[2]=v4tp_elem[5];
v4tp_mid10[3]=v4tp_elem[6];
v4tp_mid10[4]=v4tp_elem[7];
v4tp_mid10[5]=v4tp_elem[8];
v4tp_mid10[6]=v4tp_elem[9];
v4tp_mid10[7]=v4tp_elem[10];
v4tp_mid10[8]=v4tp_elem[12];
v4tp_mid10[9]=v4tp_elem[13];
}
{
V4Tp v4tp_mid10_copy[10]={v4tp_mid10[0],v4tp_mid10[1],v4tp_mid10[2],v4tp_mid10[3],v4tp_mid10[4],
v4tp_mid10[5],v4tp_mid10[6],v4tp_mid10[7],v4tp_mid10[8],v4tp_mid10[9]};
V4Tp v4tp_left4_copy[4]={v4tp_left4[0],v4tp_left4[1],v4tp_left4[2],v4tp_left4[3]};
V4Tp v4tp_right4_copy[4]={v4tp_right4[0],v4tp_right4[1],v4tp_right4[2],v4tp_right4[3]};
V4Tp v8tp_dst_left,v8tp_dst_right;
GET_MEDIAN5x5(4,v4tp_mid10_copy,v4tp_left4_copy,v4tp_right4_copy,v4tp_top4,v4tp_top_left,v4tp_top_right,v8tp_dst_left,v8tp_dst_right);
V8Tp v8tp_dst_top;
v8tp_dst_top.s0145=v8tp_dst_left;
v8tp_dst_top.s2367=v8tp_dst_right;
VSTORE(v8tp_dst_top,dst+dst_idx,8);
}
{
V4Tp v8tp_dst_left;
V4Tp v8tp_dst_right;
GET_MEDIAN5x5(4,v4tp_mid10,v4tp_left4,v4tp_right4,v4tp_bot4,v4tp_bot_left,v4tp_bot_right,v8tp_dst_left,v8tp_dst_right);
V8Tp v8tp_dst_bot;
v8tp_dst_bot.s0145=v8tp_dst_left;
v8tp_dst_bot.s2367=v8tp_dst_right;
VSTORE(v8tp_dst_bot,dst+dst_idx+ostep,8);
}
}

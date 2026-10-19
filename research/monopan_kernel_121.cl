kernel void MedianFilter7x7C1(global Tp*src,int istep,
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
int8 v8s32_gx_border={gx-3,gx-2,gx-1,gx+2,gx+3,gx+4,0,0};
v8s32_gx_border=clamp(v8s32_gx_border,0,width-1);
int8 v8s32_gy_src={gy-3,gy-2,gy-1,gy,gy+1,gy+2,gy+3,gy+4};
v8s32_gy_src=clamp(v8s32_gy_src,0,height-1);
int8 v8s32_src_offset=v8s32_gy_src*istep;
int dst_idx=mad24(gy,ostep,gx);
Tp top6[6];
Tp bot6[6];
Tp top_left,top_right,bot_left,bot_right;
{
V8Tp v8tp_top={VLOAD(src+v8s32_src_offset.s0+v8s32_gx_border.s0,1),
VLOAD(src+v8s32_src_offset.s0+v8s32_gx_border.s1,1),
VLOAD(src+v8s32_src_offset.s0+v8s32_gx_border.s2,1),
VLOAD(src+v8s32_src_offset.s0+gx,2),
VLOAD(src+v8s32_src_offset.s0+v8s32_gx_border.s3,1),
VLOAD(src+v8s32_src_offset.s0+v8s32_gx_border.s4,1),
VLOAD(src+v8s32_src_offset.s0+v8s32_gx_border.s5,1)};
V8Tp v8tp_bot={VLOAD(src+v8s32_src_offset.s7+v8s32_gx_border.s0,1),
VLOAD(src+v8s32_src_offset.s7+v8s32_gx_border.s1,1),
VLOAD(src+v8s32_src_offset.s7+v8s32_gx_border.s2,1),
VLOAD(src+v8s32_src_offset.s7+gx,2),
VLOAD(src+v8s32_src_offset.s7+v8s32_gx_border.s3,1),
VLOAD(src+v8s32_src_offset.s7+v8s32_gx_border.s4,1),
VLOAD(src+v8s32_src_offset.s7+v8s32_gx_border.s5,1)};
top6[0]=v8tp_top.s1;
top6[1]=v8tp_top.s2;
top6[2]=v8tp_top.s3;
top6[3]=v8tp_top.s4;
top6[4]=v8tp_top.s5;
top6[5]=v8tp_top.s6;
bot6[0]=v8tp_bot.s1;
bot6[1]=v8tp_bot.s2;
bot6[2]=v8tp_bot.s3;
bot6[3]=v8tp_bot.s4;
bot6[4]=v8tp_bot.s5;
bot6[5]=v8tp_bot.s6;
SORT6ElemX1(top6[0],top6[1],top6[2],top6[3],top6[4],top6[5]);
SORT6ElemX1(bot6[0],bot6[1],bot6[2],bot6[3],bot6[4],bot6[5]);
top_left=v8tp_top.s0;
top_right=v8tp_top.s7;
bot_left=v8tp_bot.s0;
bot_right=v8tp_bot.s7;
}
Tp mid14[14];
Tp left6[6];
Tp right6[6];
{
V8Tp v8tp_src_row0={VLOAD(src+v8s32_src_offset.s1+v8s32_gx_border.s0,1),
VLOAD(src+v8s32_src_offset.s1+v8s32_gx_border.s1,1),
VLOAD(src+v8s32_src_offset.s1+v8s32_gx_border.s2,1),
VLOAD(src+v8s32_src_offset.s1+gx,2),
VLOAD(src+v8s32_src_offset.s1+v8s32_gx_border.s3,1),
VLOAD(src+v8s32_src_offset.s1+v8s32_gx_border.s4,1),
VLOAD(src+v8s32_src_offset.s1+v8s32_gx_border.s5,1)};
V8Tp v8tp_src_row1={VLOAD(src+v8s32_src_offset.s2+v8s32_gx_border.s0,1),
VLOAD(src+v8s32_src_offset.s2+v8s32_gx_border.s1,1),
VLOAD(src+v8s32_src_offset.s2+v8s32_gx_border.s2,1),
VLOAD(src+v8s32_src_offset.s2+gx,2),
VLOAD(src+v8s32_src_offset.s2+v8s32_gx_border.s3,1),
VLOAD(src+v8s32_src_offset.s2+v8s32_gx_border.s4,1),
VLOAD(src+v8s32_src_offset.s2+v8s32_gx_border.s5,1)};
V8Tp v8tp_src_row2={VLOAD(src+v8s32_src_offset.s3+v8s32_gx_border.s0,1),
VLOAD(src+v8s32_src_offset.s3+v8s32_gx_border.s1,1),
VLOAD(src+v8s32_src_offset.s3+v8s32_gx_border.s2,1),
VLOAD(src+v8s32_src_offset.s3+gx,2),
VLOAD(src+v8s32_src_offset.s3+v8s32_gx_border.s3,1),
VLOAD(src+v8s32_src_offset.s3+v8s32_gx_border.s4,1),
VLOAD(src+v8s32_src_offset.s3+v8s32_gx_border.s5,1)};
V8Tp v8tp_src_row3={VLOAD(src+v8s32_src_offset.s4+v8s32_gx_border.s0,1),
VLOAD(src+v8s32_src_offset.s4+v8s32_gx_border.s1,1),
VLOAD(src+v8s32_src_offset.s4+v8s32_gx_border.s2,1),
VLOAD(src+v8s32_src_offset.s4+gx,2),
VLOAD(src+v8s32_src_offset.s4+v8s32_gx_border.s3,1),
VLOAD(src+v8s32_src_offset.s4+v8s32_gx_border.s4,1),
VLOAD(src+v8s32_src_offset.s4+v8s32_gx_border.s5,1)};
V8Tp v8tp_src_row4={VLOAD(src+v8s32_src_offset.s5+v8s32_gx_border.s0,1),
VLOAD(src+v8s32_src_offset.s5+v8s32_gx_border.s1,1),
VLOAD(src+v8s32_src_offset.s5+v8s32_gx_border.s2,1),
VLOAD(src+v8s32_src_offset.s5+gx,2),
VLOAD(src+v8s32_src_offset.s5+v8s32_gx_border.s3,1),
VLOAD(src+v8s32_src_offset.s5+v8s32_gx_border.s4,1),
VLOAD(src+v8s32_src_offset.s5+v8s32_gx_border.s5,1)};
V8Tp v8tp_src_row5={VLOAD(src+v8s32_src_offset.s6+v8s32_gx_border.s0,1),
VLOAD(src+v8s32_src_offset.s6+v8s32_gx_border.s1,1),
VLOAD(src+v8s32_src_offset.s6+v8s32_gx_border.s2,1),
VLOAD(src+v8s32_src_offset.s6+gx,2),
VLOAD(src+v8s32_src_offset.s6+v8s32_gx_border.s3,1),
VLOAD(src+v8s32_src_offset.s6+v8s32_gx_border.s4,1),
VLOAD(src+v8s32_src_offset.s6+v8s32_gx_border.s5,1)};
SORT6ElemX8(v8tp_src_row0,v8tp_src_row1,v8tp_src_row2,v8tp_src_row3,v8tp_src_row4,v8tp_src_row5);
Tp elem[36]={v8tp_src_row0.s1,v8tp_src_row0.s2,v8tp_src_row0.s3,v8tp_src_row0.s4,v8tp_src_row0.s5,v8tp_src_row0.s6,
v8tp_src_row1.s1,v8tp_src_row1.s2,v8tp_src_row1.s3,v8tp_src_row1.s4,v8tp_src_row1.s5,v8tp_src_row1.s6,
v8tp_src_row2.s1,v8tp_src_row2.s2,v8tp_src_row2.s3,v8tp_src_row2.s4,v8tp_src_row2.s5,v8tp_src_row2.s6,
v8tp_src_row3.s1,v8tp_src_row3.s2,v8tp_src_row3.s3,v8tp_src_row3.s4,v8tp_src_row3.s5,v8tp_src_row3.s6,
v8tp_src_row4.s1,v8tp_src_row4.s2,v8tp_src_row4.s3,v8tp_src_row4.s4,v8tp_src_row4.s5,v8tp_src_row4.s6,
v8tp_src_row5.s1,v8tp_src_row5.s2,v8tp_src_row5.s3,v8tp_src_row5.s4,v8tp_src_row5.s5,v8tp_src_row5.s6};
left6[0]=v8tp_src_row0.s0;
left6[1]=v8tp_src_row1.s0;
left6[2]=v8tp_src_row2.s0;
left6[3]=v8tp_src_row3.s0;
left6[4]=v8tp_src_row4.s0;
left6[5]=v8tp_src_row5.s0;
right6[0]=v8tp_src_row0.s7;
right6[1]=v8tp_src_row1.s7;
right6[2]=v8tp_src_row2.s7;
right6[3]=v8tp_src_row3.s7;
right6[4]=v8tp_src_row4.s7;
right6[5]=v8tp_src_row5.s7;
GET_MID14_OF_36(1,elem[0],elem[1],elem[2],elem[3],elem[4],elem[5],
elem[6],elem[7],elem[8],elem[9],elem[10],elem[11],
elem[12],elem[13],elem[14],elem[15],elem[16],elem[17],
elem[18],elem[19],elem[20],elem[21],elem[22],elem[23],
elem[24],elem[25],elem[26],elem[27],elem[28],elem[29],
elem[30],elem[31],elem[32],elem[33],elem[34],elem[35]);
mid14[0]=elem[4];
mid14[1]=elem[9];
mid14[2]=elem[14];
mid14[3]=elem[15];
mid14[4]=elem[19];
mid14[5]=elem[20];
mid14[6]=elem[21];
mid14[7]=elem[25];
mid14[8]=elem[26];
mid14[9]=elem[27];
mid14[10]=elem[30];
mid14[11]=elem[31];
mid14[12]=elem[32];
mid14[13]=elem[33];
}
{
Tp mid14_copy[14]={mid14[0],mid14[1],mid14[2],mid14[3],mid14[4],mid14[5],mid14[6],
mid14[7],mid14[8],mid14[9],mid14[10],mid14[11],mid14[12],mid14[13]};
Tp left6_copy[6]={left6[0],left6[1],left6[2],left6[3],left6[4],left6[5]};
Tp right6_copy[6]={right6[0],right6[1],right6[2],right6[3],right6[4],right6[5]};
Tp dst_left,dst_right;
GET_MEDIAN7x7(1,mid14_copy,left6_copy,right6_copy,top6,top_left,top_right,dst_left,dst_right);
V2Tp v2tp_dst_top;
v2tp_dst_top.s0=dst_left;
v2tp_dst_top.s1=dst_right;
VSTORE(v2tp_dst_top,dst+dst_idx,2);
}
{
Tp dst_left;
Tp dst_right;
GET_MEDIAN7x7(1,mid14,left6,right6,bot6,bot_left,bot_right,dst_left,dst_right);
V2Tp v2tp_dst_bot;
v2tp_dst_bot.s0=dst_left;
v2tp_dst_bot.s1=dst_right;
VSTORE(v2tp_dst_bot,dst+dst_idx+ostep,2);
}
}

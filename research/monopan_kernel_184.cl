#define V2Tp VTYPE(Tp,2)
#define V4Tp VTYPE(Tp,4)
#define V8Tp VTYPE(Tp,8)
#define V2InterType PROMOTE_VTYPE(Tp,2)
#define V4InterType PROMOTE_VTYPE(Tp,4)
#define V8InterType PROMOTE_VTYPE(Tp,8)
kernel void CvtBayer2bgrMain(global Tp*src,int istep,
global Tp*dst,int ostep,
int width,int y_work_size,int x_work_size,
uchar back_flag,uchar swapb,uchar swapg)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int x_idx=gx<<2;
int y_idx=gy<<1;
int flag=((x_work_size-1)==gx);
int x_idx_src=select(x_idx,width-8,flag);
int x_idx_dst=x_idx-((flag&&back_flag)<<1);
int idx_src=y_idx*istep+x_idx_src;
int idx_dst=(y_idx+1)*ostep+3*(x_idx_dst+1);
int triple_istep=istep+(istep<<1);
V2InterType v2it_b0,v2it_b1,v2it_g0,v2it_g1,v2it_r0,v2it_r1;
V8InterType v8it_src0,v8it_src1,v8it_src2,v8it_src3;
V8Tp v8tp_result;
V4Tp v4tp_result;
V2InterType v2_const_1=(V2InterType)(1);
V2InterType v2_const_2=(V2InterType)(2);
int offset_src0=mad24(swapg,triple_istep,idx_src);
int offset_src1=mad24(1+swapg,istep,idx_src);
int offset_src2=mad24(2-swapg,istep,idx_src);
int offset_src3=mad24(1-swapg,triple_istep,idx_src);
v8it_src0=CONVERT(VLOAD(src+offset_src0,8),V8InterType);
v8it_src1=CONVERT(VLOAD(src+offset_src1,8),V8InterType);
v8it_src2=CONVERT(VLOAD(src+offset_src2,8),V8InterType);
v8it_src3=CONVERT(VLOAD(src+offset_src3,8),V8InterType);
if(flag)
{
v8it_src0=ROT_R(v8it_src0,8,6);
v8it_src1=ROT_R(v8it_src1,8,6);
v8it_src2=ROT_R(v8it_src2,8,6);
v8it_src3=ROT_R(v8it_src3,8,6);
}
v2it_g0=v8it_src1.s13;
v2it_g1=(v8it_src0.s24+v2it_g0+v8it_src1.s35+v8it_src2.s24+v2_const_2)>>v2_const_2;
v2it_r1=v8it_src1.s24;
v2it_r0=(v8it_src1.s02+v2it_r1+v2_const_1)>>v2_const_1;
v2it_b0=v8it_src0.s13+v8it_src2.s13;
v2it_b1=(v8it_src0.s35+v8it_src2.s35+v2it_b0+v2_const_2)>>v2_const_2;
v2it_b0=(v2it_b0+v2_const_1)>>v2_const_1;
v8tp_result=swapb?CONVERT_SAT((V8InterType)(v2it_b0.s0,v2it_g0.s0,v2it_r0.s0,v2it_b1.s0,
v2it_g1.s0,v2it_r1.s0,v2it_b0.s1,v2it_g0.s1),V8Tp)
:CONVERT_SAT((V8InterType)(v2it_r0.s0,v2it_g0.s0,v2it_b0.s0,v2it_r1.s0,
v2it_g1.s0,v2it_b1.s0,v2it_r0.s1,v2it_g0.s1),V8Tp);
v4tp_result=swapb?CONVERT_SAT((V4InterType)(v2it_r0.s1,v2it_b1.s1,v2it_g1.s1,v2it_r1.s1),V4Tp)
:CONVERT_SAT((V4InterType)(v2it_b0.s1,v2it_r1.s1,v2it_g1.s1,v2it_b1.s1),V4Tp);
int offset_dst=mad24(swapg,ostep,idx_dst);
VSTORE(v8tp_result,dst+offset_dst,8);
VSTORE(v4tp_result,dst+offset_dst+8,4);
v2it_g1=v8it_src2.s24;
v2it_g0=(v2it_g1+v2it_g0+v8it_src2.s02+v8it_src3.s13+v2_const_2)>>v2_const_2;
v2it_r1=v8it_src3.s24+v2it_r1;
v2it_r0=(v8it_src1.s02+v8it_src3.s02+v2it_r1+v2_const_2)>>v2_const_2;
v2it_r1=(v2it_r1+v2_const_1)>>v2_const_1;
v2it_b0=v8it_src2.s13;
v2it_b1=(v8it_src2.s35+v2it_b0+v2_const_1)>>v2_const_1;
v8tp_result=swapb?CONVERT_SAT((V8InterType)(v2it_b0.s0,v2it_g0.s0,v2it_r0.s0,v2it_b1.s0,
v2it_g1.s0,v2it_r1.s0,v2it_b0.s1,v2it_g0.s1),V8Tp)
:CONVERT_SAT((V8InterType)(v2it_r0.s0,v2it_g0.s0,v2it_b0.s0,v2it_r1.s0,
v2it_g1.s0,v2it_b1.s0,v2it_r0.s1,v2it_g0.s1),V8Tp);
v4tp_result=swapb?CONVERT_SAT((V4InterType)(v2it_r0.s1,v2it_b1.s1,v2it_g1.s1,v2it_r1.s1),V4Tp)
:CONVERT_SAT((V4InterType)(v2it_b0.s1,v2it_r1.s1,v2it_g1.s1,v2it_b1.s1),V4Tp);
offset_dst=mad24(1-swapg,ostep,idx_dst);
VSTORE(v8tp_result,dst+offset_dst,8);
VSTORE(v4tp_result,dst+offset_dst+8,4);
}

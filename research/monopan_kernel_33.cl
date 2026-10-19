#define VTpC1(type)VTYPE(type,4)
#define VTpC2(type)VTYPE(type,8)
#define VTpC3(type)VTYPE(type,16)
#define VTpC4(type)VTYPE(type,16)
#define VTp_STR(type,channel)VTpC##channel(type)
#define VTp(type,channel)VTp_STR(type,channel)
#define GATHER4C1(addr,idx,type)(VTYPE(type,4))(addr[idx.s0],addr[idx.s1],addr[idx.s2],addr[idx.s3])
#define GATHER4C2(addr,idx,type)(VTYPE(type,8))(vload2(idx.s0,addr),vload2(idx.s1,addr),vload2(idx.s2,addr),vload2(idx.s3,addr))
#define GATHER4C3(addr,idx,type)(VTYPE(type,16))(vload3(idx.s0,addr),vload3(idx.s1,addr),vload3(idx.s2,addr),vload3(idx.s3,addr),(VTYPE(type,4))0)
#define GATHER4C4(addr,idx,type)(VTYPE(type,16))(vload4(idx.s0,addr),vload4(idx.s1,addr),vload4(idx.s2,addr),vload4(idx.s3,addr))
#define GATHER4_STR(addr,idx,type,channel)GATHER4C##channel(addr,idx,type)
#define GATHER4(addr,idx,type,channel)GATHER4_STR(addr,idx,type,channel)
#define SCATTER4C1(data,addr,idx)vstore4(data,0,addr+idx)
#define SCATTER4C2(data,addr,idx)vstore8(data,0,addr+idx)
#define SCATTER4C3(data,addr,idx){vstore8(data.lo,0,addr+idx);vstore4(data.s89ab,0,addr+idx+8);}
#define SCATTER4C4(data,addr,idx)vstore16(data,0,addr+idx)
#define SCATTER4_STR(data,addr,idx,channel)SCATTER4C##channel(data,addr,idx)
#define SCATTER4(data,addr,idx,channel)SCATTER4_STR(data,addr,idx,channel)
kernel void ResizeNn(global Tp*src,int istep,
global Tp*dst,int ostep,
int iwidth,int iheight,
int owidth,int oheight,
float inv_scale_x,float inv_scale_y,
int x_max,int y_max)
{
int gx=get_global_id(0)<<2;
int gy=get_global_id(1);
if(gx>=owidth||gy>=oheight)
{
return;
}
gx=min(gx,owidth-4);
const int4 v4s32_dst_x=(int4)gx+(int4)(0,1,2,3);
const int4 v4s32_src_x=CONVERT(floor(CONVERT(v4s32_dst_x,float4)*(float4)(inv_scale_x)),int4);
const int4 v4s32_x_max=(int4)(iwidth-1);
int4 v4s32_src_x_idx=select(v4s32_x_max,v4s32_src_x,v4s32_dst_x<(int4)x_max);
int dst_y_idx=gy;
int src_y_idx=select(iheight-1,(int)floor(gy*inv_scale_y),gy<y_max);
global Tp*src_c=(global Tp*)(src+src_y_idx*istep);
global Tp*dst_c=(global Tp*)(dst+dst_y_idx*ostep);
int dst_gx=gx*CHANNEL;
VTp(Tp,CHANNEL)vst_result=GATHER4(src_c,v4s32_src_x_idx,Tp,CHANNEL);
SCATTER4(vst_result,dst_c,dst_gx,CHANNEL);
}

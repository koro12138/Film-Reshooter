#if IS_FLOAT(InterType)
#define VLTp V8It
#define VSTp V4It
#define VDt V4Tp
#define LOAD_NUM 8
#define ROT_NUM 4
#else
#define VLTp V16It
#define VSTp V8It
#define VDt V8Tp
#define LOAD_NUM 16
#define ROT_NUM 8
#endif
#define KSH (2)
kernel void PyrDownMain5x5C1(global Tp*src,int istep,int iheight,
global Tp*dst,int ostep,
int y_work_size,int x_work_size,
constant Kt*filter MAX_CONSTANT_SIZE)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int dx_idx=gx*ELEM_COUNTS+KSH;
int sx_idx=(dx_idx<<1)-KSH;
int offset_src_p1,offset_src_p0,offset_src_c,offset_src_n0,offset_src_n1;
int offset_dst;
int gsy=gy<<1;
VLTp vit_src_p1,vit_src_p0,vit_src_c,vit_src_n0,vit_src_n1,vit_sum;
VSTp vit_sum_l1,vit_sum_l0,vit_sum_c,vit_sum_r0,vit_sum_r1,vit_result;
VDt vdt_result;
if((gsy>=KSH)&&(gsy<(iheight-KSH)))
{
offset_src_p1=mad24(gsy-2,istep,sx_idx);
offset_src_p0=mad24(gsy-1,istep,sx_idx);
offset_src_c=mad24(gsy,istep,sx_idx);
offset_src_n0=mad24(gsy+1,istep,sx_idx);
offset_src_n1=mad24(gsy+2,istep,sx_idx);
}
else
{
offset_src_p1=mad24(TOP_BORDER_IDX(gsy-2),istep,sx_idx);
offset_src_p0=mad24(TOP_BORDER_IDX(gsy-1),istep,sx_idx);
offset_src_c=mad24(gsy,istep,sx_idx);
offset_src_n0=mad24(BOTTOM_BORDER_IDX(gsy+1,iheight),istep,sx_idx);
offset_src_n1=mad24(BOTTOM_BORDER_IDX(gsy+2,iheight),istep,sx_idx);
}
vit_src_p1=CONVERT(VLOAD(src+offset_src_p1,LOAD_NUM),VLTp);
vit_src_p0=CONVERT(VLOAD(src+offset_src_p0,LOAD_NUM),VLTp);
vit_src_c=CONVERT(VLOAD(src+offset_src_c,LOAD_NUM),VLTp);
vit_src_n0=CONVERT(VLOAD(src+offset_src_n0,LOAD_NUM),VLTp);
vit_src_n1=CONVERT(VLOAD(src+offset_src_n1,LOAD_NUM),VLTp);
vit_sum=(vit_src_p1+vit_src_n1)*(VLTp)filter[0]+(vit_src_p0+vit_src_n0)*(VLTp)filter[1]+vit_src_c*(VLTp)filter[2];
vit_sum_l1=(VSTp)(vit_sum.even);
vit_sum_l0=(VSTp)(vit_sum.odd);
vit_sum_c=(VSTp)(ROT_L(vit_sum.even,ROT_NUM,1));
vit_sum_r0=(VSTp)(ROT_L(vit_sum.odd,ROT_NUM,1));
vit_sum_r1=(VSTp)(ROT_L(vit_sum.even,ROT_NUM,2));
vit_result=(vit_sum_l1+vit_sum_r1)*(VSTp)filter[0]+(vit_sum_l0+vit_sum_r0)*(VSTp)filter[1]+vit_sum_c*(VSTp)filter[2];
#if IS_FLOAT(InterType)
vdt_result=CONVERT_SAT(native_divide(vit_result+(VSTp)(1<<(Q-1)),(1<<Q)),VDt);
#else
vdt_result=CONVERT_SAT((vit_result+(VSTp)(1<<(Q-1)))>>Q,VDt);
#endif
offset_dst=mad24(gy,ostep,dx_idx);
VSTORE(vdt_result.lo,dst+offset_dst,ELEM_COUNTS);
}

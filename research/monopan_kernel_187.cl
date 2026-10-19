#define HSV_SHIFT 12
kernel void CvtBgr2Hsv(global uchar*src,int istep,
global uchar*dst,int ostep,
int y_work_size,int x_work_size)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int src_idx=mad24(gy,istep,gx*3);
int dst_idx=mad24(gy,ostep,gx*3);
int3 v3s32_bgr=convert_int3(VLOAD(src+src_idx,3));
#if SWAP_BR
int b=v3s32_bgr.s2;
int g=v3s32_bgr.s1;
int r=v3s32_bgr.s0;
#else
int b=v3s32_bgr.s0;
int g=v3s32_bgr.s1;
int r=v3s32_bgr.s2;
#endif
int c_max=max(r,max(g,b));
int c_min=min(r,min(g,b));
int diff=c_max-c_min;
int3 v3s32_hsv;
v3s32_hsv.s2=c_max;
int sdiv=convert_int_rte((255<<HSV_SHIFT)/(1.f*c_max));
int hdiv=convert_int_rte((180<<HSV_SHIFT)/(6.f*diff));
int vr=(c_max==r)?-1:0;
int vg=(c_max==g)?-1:0;
v3s32_hsv.s1=(diff*sdiv+(1<<(HSV_SHIFT-1)))>>HSV_SHIFT;
v3s32_hsv.s0=(vr&(g-b))+(~vr&((vg&(b-r+2*diff))+((~vg)&(r-g+4*diff))));
v3s32_hsv.s0=(v3s32_hsv.s0*hdiv+(1<<(HSV_SHIFT-1)))>>HSV_SHIFT;
v3s32_hsv.s0+=(v3s32_hsv.s0<0)?180:0;
VSTORE(convert_uchar3_sat(v3s32_hsv),dst+dst_idx,3);
}

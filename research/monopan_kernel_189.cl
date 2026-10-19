kernel void CvtHsv2Bgr(global uchar*src,int istep,
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
uchar3 v3u8_hsv=VLOAD(src+src_idx,3);
if(v3u8_hsv.s1==0)
{
VSTORE((uchar3)(v3u8_hsv.s2),dst+dst_idx,3);
return;
}
float hf=convert_float(v3u8_hsv.s0)*(1.f/30.f);
float sf=convert_float(v3u8_hsv.s1)*(1.f/255.f);
float vf=convert_float(v3u8_hsv.s2)*(1.f/255.f);
int sector=floor(hf);
float h_frac=hf-sector;
sector%=6;
float pf=vf*(1.f-sf);
float qf=vf*(1.f-sf*h_frac);
float tf=vf*(1.f-sf*(1.f-h_frac));
float bf=(sector<=1)?pf:((sector==2)?tf:((sector<=4)?vf:qf));
float gf=(sector==0)?tf:((sector<=2)?vf:((sector==3)?qf:pf));
float rf=(sector==0)?vf:((sector==1)?qf:((sector<=3)?pf:((sector==4)?tf:vf)));
#if SWAP_BR
uchar3 v3u8_bgr=convert_uchar3_sat_rte((float3)(rf*255.f,gf*255.f,bf*255.f));
#else
uchar3 v3u8_bgr=convert_uchar3_sat_rte((float3)(bf*255.f,gf*255.f,rf*255.f));
#endif
VSTORE(v3u8_bgr,dst+dst_idx,3);
}

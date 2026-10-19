#define V4St VTYPE(St,4)
#define V4Dt VTYPE(Dt,4)
kernel void ConvertToNoScale(global St*src,int istep,
global Dt*dst,int ostep,
int width,int height,
float alpha,float beta)
{
int gx=get_global_id(0)*4;
int gy=get_global_id(1);
if(gx>width||gy>=height)
{
return;
}
gx=min(gx,width-4);
int src_offset=mad24(gy,istep,gx);
int dst_offset=mad24(gy,ostep,gx);
V4St v4st_src=VLOAD(src+src_offset,4);
V4Dt v4dt_result=CONVERT_SAT(v4st_src,V4Dt);
VSTORE(v4dt_result,dst+dst_offset,4);
}

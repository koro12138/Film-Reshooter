#define BINARY_STR_MIN(x,y)min(x,y)
#define BINARY_STR_MAX(x,y)max(x,y)
#define BINARY_STR(type,x,y)BINARY_STR_##type(x,y)
#define BINARY_OP(type,x,y)BINARY_STR(type,x,y)
#define VTp VTYPE(Tp,ELEM_COUNTS)
kernel void MinMax(global Tp*src0,int istep0,
global Tp*src1,int istep1,
global Tp*dst,int ostep,
int width,int height)
{
int gx=get_global_id(0)*ELEM_COUNTS;
int gy=get_global_id(1);
if(gx>=width||gy>=height)
{
return;
}
gx=min(gx,width-ELEM_COUNTS);
int offset_src0=mad24(gy,istep0,gx);
int offset_src1=mad24(gy,istep1,gx);
int offset_dst=mad24(gy,ostep,gx);
VTp vtp_src0=VLOAD(src0+offset_src0,ELEM_COUNTS);
VTp vtp_src1=VLOAD(src1+offset_src1,ELEM_COUNTS);
VTp vtp_result=BINARY_OP(OP_TYPE,vtp_src0,vtp_src1);
VSTORE(vtp_result,dst+offset_dst,ELEM_COUNTS);
}

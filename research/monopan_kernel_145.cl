#define VSt VTYPE(St,ELEM_COUNTS)
#define VDt VTYPE(Dt,ELEM_COUNTS)
#define VInterType VTYPE(InterType,ELEM_COUNTS)
#define ARITHM_STR_ADD(x,y)(CONVERT(x,VInterType)+CONVERT(y,VInterType))
#define ARITHM_STR_SUB(x,y)(CONVERT(x,VInterType)-CONVERT(y,VInterType))
#define ARITHM_STR_MUL(x,y)(CONVERT(x,VInterType)*CONVERT(y,VInterType))
#define ARITHM_STR_DIV(x,y)(CONVERT(x,VInterType)/CONVERT(y,VInterType))
#define ARITHM_STR(type,x,y)ARITHM_STR_##type(x,y)
#define ARITHM_OP(type,x,y)ARITHM_STR(type,x,y)
kernel void Arithmetic(global St*src0,int istep0,
global St*src1,int istep1,
global Dt*dst,int ostep,
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
VSt vst_0=VLOAD(src0+offset_src0,ELEM_COUNTS);
VSt vst_1=VLOAD(src1+offset_src1,ELEM_COUNTS);
VInterType vit_result=ARITHM_OP(ARITHM_TYPE,vst_0,vst_1);
VSTORE(CONVERT_SAT(vit_result,VDt),dst+offset_dst,ELEM_COUNTS);
}

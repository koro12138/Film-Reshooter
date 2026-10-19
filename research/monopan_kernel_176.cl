#define TRANSPOSE_C4_1X1(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,(x),4*(y));\
\
VTYPE(Tp,4)v0=VLOAD(iaddr0,4);\
\
VTYPE(Tp,4)r0=v0;\
\
global Tp*oaddr0=dst+mad24(ostep,((y)),4*(x));\
\
VSTORE(r0,oaddr0,4);\
}
#define TRANSPOSE_C4_2X2(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,(x),4*(y));\
global Tp*iaddr1=iaddr0+istep;\
\
VTYPE(Tp,8)v0=VLOAD(iaddr0,8);\
VTYPE(Tp,8)v1=VLOAD(iaddr1,8);\
\
VTYPE(Tp,8)r0,r1;\
r0.lo=v0.lo;\
r0.hi=v1.lo;\
r1.lo=v0.hi;\
r1.hi=v1.hi;\
\
global Tp*oaddr0=dst+mad24(ostep,((y)),4*(x));\
global Tp*oaddr1=oaddr0+ostep;\
\
VSTORE(r0,oaddr0,8);\
VSTORE(r1,oaddr1,8);\
}
#define TRANSPOSE_C4_3X3(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,(x),4*(y));\
global Tp*iaddr1=iaddr0+istep;\
global Tp*iaddr2=iaddr1+istep;\
\
VTYPE(Tp,4)v0_0=VLOAD(iaddr0,4);\
VTYPE(Tp,4)v0_1=VLOAD(iaddr0+4,4);\
VTYPE(Tp,4)v0_2=VLOAD(iaddr0+4*2,4);\
VTYPE(Tp,4)v1_0=VLOAD(iaddr1,4);\
VTYPE(Tp,4)v1_1=VLOAD(iaddr1+4,4);\
VTYPE(Tp,4)v1_2=VLOAD(iaddr1+4*2,4);\
VTYPE(Tp,4)v2_0=VLOAD(iaddr2,4);\
VTYPE(Tp,4)v2_1=VLOAD(iaddr2+4,4);\
VTYPE(Tp,4)v2_2=VLOAD(iaddr2+4*2,4);\
\
VTYPE(Tp,4)r0_0=v0_0;\
VTYPE(Tp,4)r0_1=v1_0;\
VTYPE(Tp,4)r0_2=v2_0;\
VTYPE(Tp,4)r1_0=v0_1;\
VTYPE(Tp,4)r1_1=v1_1;\
VTYPE(Tp,4)r1_2=v2_1;\
VTYPE(Tp,4)r2_0=v0_2;\
VTYPE(Tp,4)r2_1=v1_2;\
VTYPE(Tp,4)r2_2=v2_2;\
\
global Tp*oaddr0=dst+mad24(ostep,((y)),4*(x));\
global Tp*oaddr1=oaddr0+ostep;\
global Tp*oaddr2=oaddr1+ostep;\
\
VSTORE(r0_0,oaddr0,4);\
VSTORE(r0_1,oaddr0+4,4);\
VSTORE(r0_2,oaddr0+4*2,4);\
VSTORE(r1_0,oaddr1,4);\
VSTORE(r1_1,oaddr1+4,4);\
VSTORE(r1_2,oaddr1+4*2,4);\
VSTORE(r2_0,oaddr2,4);\
VSTORE(r2_1,oaddr2+4,4);\
VSTORE(r2_2,oaddr2+4*2,4);\
}
#define TRANSPOSE_C4_4X4(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,(x),4*(y));\
global Tp*iaddr1=iaddr0+istep;\
global Tp*iaddr2=iaddr1+istep;\
global Tp*iaddr3=iaddr2+istep;\
\
VTYPE(Tp,16)v0=VLOAD(iaddr0,16);\
VTYPE(Tp,16)v1=VLOAD(iaddr1,16);\
VTYPE(Tp,16)v2=VLOAD(iaddr2,16);\
VTYPE(Tp,16)v3=VLOAD(iaddr3,16);\
\
VTYPE(Tp,16)r0={v0.s0,v0.s1,v0.s2,v0.s3,v1.s0,v1.s1,v1.s2,v1.s3,v2.s0,v2.s1,v2.s2,v2.s3,v3.s0,v3.s1,v3.s2,v3.s3};\
VTYPE(Tp,16)r1={v0.s4,v0.s5,v0.s6,v0.s7,v1.s4,v1.s5,v1.s6,v1.s7,v2.s4,v2.s5,v2.s6,v2.s7,v3.s4,v3.s5,v3.s6,v3.s7};\
VTYPE(Tp,16)r2={v0.s8,v0.s9,v0.sa,v0.sb,v1.s8,v1.s9,v1.sa,v1.sb,v2.s8,v2.s9,v2.sa,v2.sb,v3.s8,v3.s9,v3.sa,v3.sb};\
VTYPE(Tp,16)r3={v0.sc,v0.sd,v0.se,v0.sf,v1.sc,v1.sd,v1.se,v1.sf,v2.sc,v2.sd,v2.se,v2.sf,v3.sc,v3.sd,v3.se,v3.sf};\
\
global Tp*oaddr0=dst+mad24(ostep,((y)),4*(x));\
global Tp*oaddr1=oaddr0+ostep;\
global Tp*oaddr2=oaddr1+ostep;\
global Tp*oaddr3=oaddr2+ostep;\
\
VSTORE(r0,oaddr0,16);\
VSTORE(r1,oaddr1,16);\
VSTORE(r2,oaddr2,16);\
VSTORE(r3,oaddr3,16);\
}
#define TRANSPOSE_C4_STR(y,x,size)TRANSPOSE_C4_##size##X##size(y,x)
#define TRANSPOSE_C4(y,x,size)TRANSPOSE_C4_STR(y,x,size)
kernel void TransposeC4(global Tp*src,int istep,
global Tp*dst,int ostep,
int width,int height)
{
int gx=get_global_id(0)*ELEM_COUNTS;
int gy=get_global_id(1)*ELEM_COUNTS;
if(gx>=width||gy>=height)
{
return;
}
gx=min(gx,width-ELEM_COUNTS);
gy=min(gy,height-ELEM_COUNTS);
TRANSPOSE_C4(gy,gx,ELEM_COUNTS);
}

#define TRANSPOSE_C3_1X1(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,(x),3*(y));\
\
VTYPE(Tp,3)v0=VLOAD(iaddr0,3);\
\
VTYPE(Tp,3)r0=v0;\
\
global Tp*oaddr0=dst+mad24(ostep,(y),3*(x));\
\
VSTORE(r0,oaddr0,3);\
}
#define TRANSPOSE_C3_2X2(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,(x),3*(y));\
global Tp*iaddr1=iaddr0+istep;\
\
VTYPE(Tp,3)v0_0=VLOAD(iaddr0,3);\
VTYPE(Tp,3)v0_1=VLOAD(iaddr0+3,3);\
VTYPE(Tp,3)v1_0=VLOAD(iaddr1,3);\
VTYPE(Tp,3)v1_1=VLOAD(iaddr1+3,3);\
\
VTYPE(Tp,3)r0_0=v0_0;\
VTYPE(Tp,3)r0_1=v1_0;\
VTYPE(Tp,3)r1_0=v0_1;\
VTYPE(Tp,3)r1_1=v1_1;\
\
global Tp*oaddr0=dst+mad24(ostep,(y),3*(x));\
global Tp*oaddr1=oaddr0+ostep;\
\
VSTORE(r0_0,oaddr0,3);\
VSTORE(r0_1,oaddr0+3,3);\
VSTORE(r1_0,oaddr1,3);\
VSTORE(r1_1,oaddr1+3,3);\
}
#define TRANSPOSE_C3_3X3(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,(x),3*(y));\
global Tp*iaddr1=iaddr0+istep;\
global Tp*iaddr2=iaddr1+istep;\
\
VTYPE(Tp,3)v0_0=VLOAD(iaddr0,3);\
VTYPE(Tp,3)v0_1=VLOAD(iaddr0+3,3);\
VTYPE(Tp,3)v0_2=VLOAD(iaddr0+3*2,3);\
VTYPE(Tp,3)v1_0=VLOAD(iaddr1,3);\
VTYPE(Tp,3)v1_1=VLOAD(iaddr1+3,3);\
VTYPE(Tp,3)v1_2=VLOAD(iaddr1+3*2,3);\
VTYPE(Tp,3)v2_0=VLOAD(iaddr2,3);\
VTYPE(Tp,3)v2_1=VLOAD(iaddr2+3,3);\
VTYPE(Tp,3)v2_2=VLOAD(iaddr2+3*2,3);\
\
VTYPE(Tp,3)r0_0=v0_0;\
VTYPE(Tp,3)r0_1=v1_0;\
VTYPE(Tp,3)r0_2=v2_0;\
VTYPE(Tp,3)r1_0=v0_1;\
VTYPE(Tp,3)r1_1=v1_1;\
VTYPE(Tp,3)r1_2=v2_1;\
VTYPE(Tp,3)r2_0=v0_2;\
VTYPE(Tp,3)r2_1=v1_2;\
VTYPE(Tp,3)r2_2=v2_2;\
\
global Tp*oaddr0=dst+mad24(ostep,(y),3*(x));\
global Tp*oaddr1=oaddr0+ostep;\
global Tp*oaddr2=oaddr1+ostep;\
\
VSTORE(r0_0,oaddr0,3);\
VSTORE(r0_1,oaddr0+3,3);\
VSTORE(r0_2,oaddr0+3*2,3);\
VSTORE(r1_0,oaddr1,3);\
VSTORE(r1_1,oaddr1+3,3);\
VSTORE(r1_2,oaddr1+3*2,3);\
VSTORE(r2_0,oaddr2,3);\
VSTORE(r2_1,oaddr2+3,3);\
VSTORE(r2_2,oaddr2+3*2,3);\
}
#define TRANSPOSE_C3_4X4(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,(x),3*(y));\
global Tp*iaddr1=iaddr0+istep;\
global Tp*iaddr2=iaddr1+istep;\
global Tp*iaddr3=iaddr2+istep;\
\
VTYPE(Tp,3)v0_0=VLOAD(iaddr0,3);\
VTYPE(Tp,3)v0_1=VLOAD(iaddr0+3,3);\
VTYPE(Tp,3)v0_2=VLOAD(iaddr0+3*2,3);\
VTYPE(Tp,3)v0_3=VLOAD(iaddr0+3*3,3);\
VTYPE(Tp,3)v1_0=VLOAD(iaddr1,3);\
VTYPE(Tp,3)v1_1=VLOAD(iaddr1+3,3);\
VTYPE(Tp,3)v1_2=VLOAD(iaddr1+3*2,3);\
VTYPE(Tp,3)v1_3=VLOAD(iaddr1+3*3,3);\
VTYPE(Tp,3)v2_0=VLOAD(iaddr2,3);\
VTYPE(Tp,3)v2_1=VLOAD(iaddr2+3,3);\
VTYPE(Tp,3)v2_2=VLOAD(iaddr2+3*2,3);\
VTYPE(Tp,3)v2_3=VLOAD(iaddr2+3*3,3);\
VTYPE(Tp,3)v3_0=VLOAD(iaddr3,3);\
VTYPE(Tp,3)v3_1=VLOAD(iaddr3+3,3);\
VTYPE(Tp,3)v3_2=VLOAD(iaddr3+3*2,3);\
VTYPE(Tp,3)v3_3=VLOAD(iaddr3+3*3,3);\
\
VTYPE(Tp,3)r0_0=v0_0;\
VTYPE(Tp,3)r0_1=v1_0;\
VTYPE(Tp,3)r0_2=v2_0;\
VTYPE(Tp,3)r0_3=v3_0;\
VTYPE(Tp,3)r1_0=v0_1;\
VTYPE(Tp,3)r1_1=v1_1;\
VTYPE(Tp,3)r1_2=v2_1;\
VTYPE(Tp,3)r1_3=v3_1;\
VTYPE(Tp,3)r2_0=v0_2;\
VTYPE(Tp,3)r2_1=v1_2;\
VTYPE(Tp,3)r2_2=v2_2;\
VTYPE(Tp,3)r2_3=v3_2;\
VTYPE(Tp,3)r3_0=v0_3;\
VTYPE(Tp,3)r3_1=v1_3;\
VTYPE(Tp,3)r3_2=v2_3;\
VTYPE(Tp,3)r3_3=v3_3;\
\
global Tp*oaddr0=dst+mad24(ostep,(y),3*(x));\
global Tp*oaddr1=oaddr0+ostep;\
global Tp*oaddr2=oaddr1+ostep;\
global Tp*oaddr3=oaddr2+ostep;\
\
VSTORE(r0_0,oaddr0,3);\
VSTORE(r0_1,oaddr0+3,3);\
VSTORE(r0_2,oaddr0+3*2,3);\
VSTORE(r0_3,oaddr0+3*3,3);\
VSTORE(r1_0,oaddr1,3);\
VSTORE(r1_1,oaddr1+3,3);\
VSTORE(r1_2,oaddr1+3*2,3);\
VSTORE(r1_3,oaddr1+3*3,3);\
VSTORE(r2_0,oaddr2,3);\
VSTORE(r2_1,oaddr2+3,3);\
VSTORE(r2_2,oaddr2+3*2,3);\
VSTORE(r2_3,oaddr2+3*3,3);\
VSTORE(r3_0,oaddr3,3);\
VSTORE(r3_1,oaddr3+3,3);\
VSTORE(r3_2,oaddr3+3*2,3);\
VSTORE(r3_3,oaddr3+3*3,3);\
}
#define TRANSPOSE_C3_STR(y,x,size)TRANSPOSE_C3_##size##X##size(y,x)
#define TRANSPOSE_C3(y,x,size)TRANSPOSE_C3_STR(y,x,size)
kernel void TransposeC3(global Tp*src,int istep,
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
TRANSPOSE_C3(gy,gx,ELEM_COUNTS);
}

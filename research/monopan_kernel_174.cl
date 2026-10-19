#define TRANSPOSE_C2_1X1(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,(x),2*(y));\
\
VTYPE(Tp,2)v0=VLOAD(iaddr0,2);\
\
VTYPE(Tp,2)r0=v0;\
\
global Tp*oaddr0=dst+mad24(ostep,(y),2*(x));\
\
VSTORE(r0,oaddr0,2);\
}
#define TRANSPOSE_C2_2X2(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,(x),2*(y));\
global Tp*iaddr1=iaddr0+istep;\
\
VTYPE(Tp,4)v0=VLOAD(iaddr0,4);\
VTYPE(Tp,4)v1=VLOAD(iaddr1,4);\
\
VTYPE(Tp,4)r0={v0.s0,v0.s1,v1.s0,v1.s1};\
VTYPE(Tp,4)r1={v0.s2,v0.s3,v1.s2,v1.s3};\
\
global Tp*oaddr0=dst+mad24(ostep,(y),2*(x));\
global Tp*oaddr1=oaddr0+ostep;\
\
VSTORE(r0,oaddr0,4);\
VSTORE(r1,oaddr1,4);\
}
#define TRANSPOSE_C2_3X3(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,(x),2*(y));\
global Tp*iaddr1=iaddr0+istep;\
global Tp*iaddr2=iaddr1+istep;\
\
VTYPE(Tp,2)v0_0=VLOAD(iaddr0,2);\
VTYPE(Tp,2)v0_1=VLOAD(iaddr0+2,2);\
VTYPE(Tp,2)v0_2=VLOAD(iaddr0+2*2,2);\
VTYPE(Tp,2)v1_0=VLOAD(iaddr1,2);\
VTYPE(Tp,2)v1_1=VLOAD(iaddr1+2,2);\
VTYPE(Tp,2)v1_2=VLOAD(iaddr1+2*2,2);\
VTYPE(Tp,2)v2_0=VLOAD(iaddr2,2);\
VTYPE(Tp,2)v2_1=VLOAD(iaddr2+2,2);\
VTYPE(Tp,2)v2_2=VLOAD(iaddr2+2*2,2);\
\
VTYPE(Tp,2)r0_0=v0_0;\
VTYPE(Tp,2)r0_1=v1_0;\
VTYPE(Tp,2)r0_2=v2_0;\
VTYPE(Tp,2)r1_0=v0_1;\
VTYPE(Tp,2)r1_1=v1_1;\
VTYPE(Tp,2)r1_2=v2_1;\
VTYPE(Tp,2)r2_0=v0_2;\
VTYPE(Tp,2)r2_1=v1_2;\
VTYPE(Tp,2)r2_2=v2_2;\
\
global Tp*oaddr0=dst+mad24(ostep,(y),2*(x));\
global Tp*oaddr1=oaddr0+ostep;\
global Tp*oaddr2=oaddr1+ostep;\
\
VSTORE(r0_0,oaddr0,2);\
VSTORE(r0_1,oaddr0+2,2);\
VSTORE(r0_2,oaddr0+2*2,2);\
VSTORE(r1_0,oaddr1,2);\
VSTORE(r1_1,oaddr1+2,2);\
VSTORE(r1_2,oaddr1+2*2,2);\
VSTORE(r2_0,oaddr2,2);\
VSTORE(r2_1,oaddr2+2,2);\
VSTORE(r2_2,oaddr2+2*2,2);\
}
#define TRANSPOSE_C2_4X4(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,(x),2*(y));\
global Tp*iaddr1=iaddr0+istep;\
global Tp*iaddr2=iaddr1+istep;\
global Tp*iaddr3=iaddr2+istep;\
\
VTYPE(Tp,8)v0=VLOAD(iaddr0,8);\
VTYPE(Tp,8)v1=VLOAD(iaddr1,8);\
VTYPE(Tp,8)v2=VLOAD(iaddr2,8);\
VTYPE(Tp,8)v3=VLOAD(iaddr3,8);\
\
VTYPE(Tp,8)r0={v0.s0,v0.s1,v1.s0,v1.s1,v2.s0,v2.s1,v3.s0,v3.s1};\
VTYPE(Tp,8)r1={v0.s2,v0.s3,v1.s2,v1.s3,v2.s2,v2.s3,v3.s2,v3.s3};\
VTYPE(Tp,8)r2={v0.s4,v0.s5,v1.s4,v1.s5,v2.s4,v2.s5,v3.s4,v3.s5};\
VTYPE(Tp,8)r3={v0.s6,v0.s7,v1.s6,v1.s7,v2.s6,v2.s7,v3.s6,v3.s7};\
\
global Tp*oaddr0=dst+mad24(ostep,(y),2*(x));\
global Tp*oaddr1=oaddr0+ostep;\
global Tp*oaddr2=oaddr1+ostep;\
global Tp*oaddr3=oaddr2+ostep;\
\
VSTORE(r0,oaddr0,8);\
VSTORE(r1,oaddr1,8);\
VSTORE(r2,oaddr2,8);\
VSTORE(r3,oaddr3,8);\
}
#define TRANSPOSE_C2_8X8(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,(x),2*(y));\
global Tp*iaddr1=iaddr0+istep;\
global Tp*iaddr2=iaddr1+istep;\
global Tp*iaddr3=iaddr2+istep;\
global Tp*iaddr4=iaddr3+istep;\
global Tp*iaddr5=iaddr4+istep;\
global Tp*iaddr6=iaddr5+istep;\
global Tp*iaddr7=iaddr6+istep;\
\
VTYPE(Tp,16)v0=VLOAD(iaddr0,16);\
VTYPE(Tp,16)v1=VLOAD(iaddr1,16);\
VTYPE(Tp,16)v2=VLOAD(iaddr2,16);\
VTYPE(Tp,16)v3=VLOAD(iaddr3,16);\
VTYPE(Tp,16)v4=VLOAD(iaddr4,16);\
VTYPE(Tp,16)v5=VLOAD(iaddr5,16);\
VTYPE(Tp,16)v6=VLOAD(iaddr6,16);\
VTYPE(Tp,16)v7=VLOAD(iaddr7,16);\
\
VTYPE(Tp,16)r0={v0.s0,v0.s1,v1.s0,v1.s1,v2.s0,v2.s1,v3.s0,v3.s1,v4.s0,v4.s1,v5.s0,v5.s1,v6.s0,v6.s1,v7.s0,v7.s1};\
VTYPE(Tp,16)r1={v0.s2,v0.s3,v1.s2,v1.s3,v2.s2,v2.s3,v3.s2,v3.s3,v4.s2,v4.s3,v5.s2,v5.s3,v6.s2,v6.s3,v7.s2,v7.s3};\
VTYPE(Tp,16)r2={v0.s4,v0.s5,v1.s4,v1.s5,v2.s4,v2.s5,v3.s4,v3.s5,v4.s4,v4.s5,v5.s4,v5.s5,v6.s4,v6.s5,v7.s4,v7.s5};\
VTYPE(Tp,16)r3={v0.s6,v0.s7,v1.s6,v1.s7,v2.s6,v2.s7,v3.s6,v3.s7,v4.s6,v4.s7,v5.s6,v5.s7,v6.s6,v6.s7,v7.s6,v7.s7};\
VTYPE(Tp,16)r4={v0.s8,v0.s9,v1.s8,v1.s9,v2.s8,v2.s9,v3.s8,v3.s9,v4.s8,v4.s9,v5.s8,v5.s9,v6.s8,v6.s9,v7.s8,v7.s9};\
VTYPE(Tp,16)r5={v0.sa,v0.sb,v1.sa,v1.sb,v2.sa,v2.sb,v3.sa,v3.sb,v4.sa,v4.sb,v5.sa,v5.sb,v6.sa,v6.sb,v7.sa,v7.sb};\
VTYPE(Tp,16)r6={v0.sc,v0.sd,v1.sc,v1.sd,v2.sc,v2.sd,v3.sc,v3.sd,v4.sc,v4.sd,v5.sc,v5.sd,v6.sc,v6.sd,v7.sc,v7.sd};\
VTYPE(Tp,16)r7={v0.se,v0.sf,v1.se,v1.sf,v2.se,v2.sf,v3.se,v3.sf,v4.se,v4.sf,v5.se,v5.sf,v6.se,v6.sf,v7.se,v7.sf};\
\
global Tp*oaddr0=dst+mad24(ostep,(y),2*(x));\
global Tp*oaddr1=oaddr0+ostep;\
global Tp*oaddr2=oaddr1+ostep;\
global Tp*oaddr3=oaddr2+ostep;\
global Tp*oaddr4=oaddr3+ostep;\
global Tp*oaddr5=oaddr4+ostep;\
global Tp*oaddr6=oaddr5+ostep;\
global Tp*oaddr7=oaddr6+ostep;\
\
VSTORE(r0,oaddr0,16);\
VSTORE(r1,oaddr1,16);\
VSTORE(r2,oaddr2,16);\
VSTORE(r3,oaddr3,16);\
VSTORE(r4,oaddr4,16);\
VSTORE(r5,oaddr5,16);\
VSTORE(r6,oaddr6,16);\
VSTORE(r7,oaddr7,16);\
}
#define TRANSPOSE_C2_STR(y,x,size)TRANSPOSE_C2_##size##X##size(y,x)
#define TRANSPOSE_C2(y,x,size)TRANSPOSE_C2_STR(y,x,size)
kernel void TransposeC2(global Tp*src,int istep,
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
TRANSPOSE_C2(gy,gx,ELEM_COUNTS);
}

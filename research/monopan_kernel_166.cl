#define ROTATE_90_C1_1X1(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,width-1-(x),(y));\
\
VTYPE(Tp,1)v0=VLOAD(iaddr0,1);\
\
VTYPE(Tp,1)r0=v0;\
\
global Tp*oaddr0=dst+mad24(ostep,(y),(x));\
\
VSTORE(r0,oaddr0,1);\
}
#define ROTATE_90_C1_2X2(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,width-2-(x),(y));\
global Tp*iaddr1=iaddr0+istep;\
\
VTYPE(Tp,2)v0=VLOAD(iaddr0,2);\
VTYPE(Tp,2)v1=VLOAD(iaddr1,2);\
\
VTYPE(Tp,2)r0={v1.s0,v0.s0};\
VTYPE(Tp,2)r1={v1.s1,v0.s1};\
\
global Tp*oaddr0=dst+mad24(ostep,(y),(x));\
global Tp*oaddr1=oaddr0+ostep;\
\
VSTORE(r0,oaddr0,2);\
VSTORE(r1,oaddr1,2);\
}
#define ROTATE_90_C1_3X3(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,width-3-(x),(y));\
global Tp*iaddr1=iaddr0+istep;\
global Tp*iaddr2=iaddr1+istep;\
\
VTYPE(Tp,3)v0=VLOAD(iaddr0,3);\
VTYPE(Tp,3)v1=VLOAD(iaddr1,3);\
VTYPE(Tp,3)v2=VLOAD(iaddr2,3);\
\
VTYPE(Tp,3)r0={v2.s0,v1.s0,v0.s0};\
VTYPE(Tp,3)r1={v2.s1,v1.s1,v0.s1};\
VTYPE(Tp,3)r2={v2.s2,v1.s2,v0.s2};\
\
global Tp*oaddr0=dst+mad24(ostep,(y),(x));\
global Tp*oaddr1=oaddr0+ostep;\
global Tp*oaddr2=oaddr1+ostep;\
\
VSTORE(r0,oaddr0,3);\
VSTORE(r1,oaddr1,3);\
VSTORE(r2,oaddr2,3);\
}
#define ROTATE_90_C1_4X4(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,width-4-(x),(y));\
global Tp*iaddr1=iaddr0+istep;\
global Tp*iaddr2=iaddr1+istep;\
global Tp*iaddr3=iaddr2+istep;\
\
VTYPE(Tp,4)v0=VLOAD(iaddr0,4);\
VTYPE(Tp,4)v1=VLOAD(iaddr1,4);\
VTYPE(Tp,4)v2=VLOAD(iaddr2,4);\
VTYPE(Tp,4)v3=VLOAD(iaddr3,4);\
\
VTYPE(Tp,4)r0={v3.s0,v2.s0,v1.s0,v0.s0};\
VTYPE(Tp,4)r1={v3.s1,v2.s1,v1.s1,v0.s1};\
VTYPE(Tp,4)r2={v3.s2,v2.s2,v1.s2,v0.s2};\
VTYPE(Tp,4)r3={v3.s3,v2.s3,v1.s3,v0.s3};\
\
global Tp*oaddr0=dst+mad24(ostep,(y),(x));\
global Tp*oaddr1=oaddr0+ostep;\
global Tp*oaddr2=oaddr1+ostep;\
global Tp*oaddr3=oaddr2+ostep;\
\
VSTORE(r0,oaddr0,4);\
VSTORE(r1,oaddr1,4);\
VSTORE(r2,oaddr2,4);\
VSTORE(r3,oaddr3,4);\
}
#define ROTATE_90_C1_8X8(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,width-8-(x),(y));\
global Tp*iaddr1=iaddr0+istep;\
global Tp*iaddr2=iaddr1+istep;\
global Tp*iaddr3=iaddr2+istep;\
global Tp*iaddr4=iaddr3+istep;\
global Tp*iaddr5=iaddr4+istep;\
global Tp*iaddr6=iaddr5+istep;\
global Tp*iaddr7=iaddr6+istep;\
\
VTYPE(Tp,8)v0=VLOAD(iaddr0,8);\
VTYPE(Tp,8)v1=VLOAD(iaddr1,8);\
VTYPE(Tp,8)v2=VLOAD(iaddr2,8);\
VTYPE(Tp,8)v3=VLOAD(iaddr3,8);\
VTYPE(Tp,8)v4=VLOAD(iaddr4,8);\
VTYPE(Tp,8)v5=VLOAD(iaddr5,8);\
VTYPE(Tp,8)v6=VLOAD(iaddr6,8);\
VTYPE(Tp,8)v7=VLOAD(iaddr7,8);\
\
VTYPE(Tp,8)r0={v7.s0,v6.s0,v5.s0,v4.s0,v3.s0,v2.s0,v1.s0,v0.s0};\
VTYPE(Tp,8)r1={v7.s1,v6.s1,v5.s1,v4.s1,v3.s1,v2.s1,v1.s1,v0.s1};\
VTYPE(Tp,8)r2={v7.s2,v6.s2,v5.s2,v4.s2,v3.s2,v2.s2,v1.s2,v0.s2};\
VTYPE(Tp,8)r3={v7.s3,v6.s3,v5.s3,v4.s3,v3.s3,v2.s3,v1.s3,v0.s3};\
VTYPE(Tp,8)r4={v7.s4,v6.s4,v5.s4,v4.s4,v3.s4,v2.s4,v1.s4,v0.s4};\
VTYPE(Tp,8)r5={v7.s5,v6.s5,v5.s5,v4.s5,v3.s5,v2.s5,v1.s5,v0.s5};\
VTYPE(Tp,8)r6={v7.s6,v6.s6,v5.s6,v4.s6,v3.s6,v2.s6,v1.s6,v0.s6};\
VTYPE(Tp,8)r7={v7.s7,v6.s7,v5.s7,v4.s7,v3.s7,v2.s7,v1.s7,v0.s7};\
\
global Tp*oaddr0=dst+mad24(ostep,(y),(x));\
global Tp*oaddr1=oaddr0+ostep;\
global Tp*oaddr2=oaddr1+ostep;\
global Tp*oaddr3=oaddr2+ostep;\
global Tp*oaddr4=oaddr3+ostep;\
global Tp*oaddr5=oaddr4+ostep;\
global Tp*oaddr6=oaddr5+ostep;\
global Tp*oaddr7=oaddr6+ostep;\
\
VSTORE(r0,oaddr0,8);\
VSTORE(r1,oaddr1,8);\
VSTORE(r2,oaddr2,8);\
VSTORE(r3,oaddr3,8);\
VSTORE(r4,oaddr4,8);\
VSTORE(r5,oaddr5,8);\
VSTORE(r6,oaddr6,8);\
VSTORE(r7,oaddr7,8);\
}
#define ROTATE_180_C1_1X1(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,height-1-(y),width-1-(x));\
\
VTYPE(Tp,1)v0=VLOAD(iaddr0,1);\
\
VTYPE(Tp,1)r0=v0;\
\
global Tp*oaddr0=dst+mad24(ostep,(y),(x));\
\
VSTORE(r0,oaddr0,1);\
}
#define ROTATE_180_C1_2X2(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,height-2-(y),width-2-(x));\
global Tp*iaddr1=iaddr0+istep;\
\
VTYPE(Tp,2)v0=VLOAD(iaddr0,2);\
VTYPE(Tp,2)v1=VLOAD(iaddr1,2);\
\
VTYPE(Tp,2)r0=REVERSE(v1,2);\
VTYPE(Tp,2)r1=REVERSE(v0,2);\
\
global Tp*oaddr0=dst+mad24(ostep,(y),(x));\
global Tp*oaddr1=oaddr0+ostep;\
\
VSTORE(r0,oaddr0,2);\
VSTORE(r1,oaddr1,2);\
}
#define ROTATE_180_C1_3X3(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,height-3-(y),width-3-(x));\
global Tp*iaddr1=iaddr0+istep;\
global Tp*iaddr2=iaddr1+istep;\
\
VTYPE(Tp,3)v0=VLOAD(iaddr0,3);\
VTYPE(Tp,3)v1=VLOAD(iaddr1,3);\
VTYPE(Tp,3)v2=VLOAD(iaddr2,3);\
\
VTYPE(Tp,3)r0=REVERSE(v2,3);\
VTYPE(Tp,3)r1=REVERSE(v1,3);\
VTYPE(Tp,3)r2=REVERSE(v0,3);\
\
global Tp*oaddr0=dst+mad24(ostep,(y),(x));\
global Tp*oaddr1=oaddr0+ostep;\
global Tp*oaddr2=oaddr1+ostep;\
\
VSTORE(r0,oaddr0,3);\
VSTORE(r1,oaddr1,3);\
VSTORE(r2,oaddr2,3);\
}
#define ROTATE_180_C1_4X4(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,height-4-(y),width-4-(x));\
global Tp*iaddr1=iaddr0+istep;\
global Tp*iaddr2=iaddr1+istep;\
global Tp*iaddr3=iaddr2+istep;\
\
VTYPE(Tp,4)v0=VLOAD(iaddr0,4);\
VTYPE(Tp,4)v1=VLOAD(iaddr1,4);\
VTYPE(Tp,4)v2=VLOAD(iaddr2,4);\
VTYPE(Tp,4)v3=VLOAD(iaddr3,4);\
\
VTYPE(Tp,4)r0=REVERSE(v3,4);\
VTYPE(Tp,4)r1=REVERSE(v2,4);\
VTYPE(Tp,4)r2=REVERSE(v1,4);\
VTYPE(Tp,4)r3=REVERSE(v0,4);\
\
global Tp*oaddr0=dst+mad24(ostep,(y),(x));\
global Tp*oaddr1=oaddr0+ostep;\
global Tp*oaddr2=oaddr1+ostep;\
global Tp*oaddr3=oaddr2+ostep;\
\
VSTORE(r0,oaddr0,4);\
VSTORE(r1,oaddr1,4);\
VSTORE(r2,oaddr2,4);\
VSTORE(r3,oaddr3,4);\
}
#define ROTATE_180_C1_8X8(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,height-8-(y),width-8-(x));\
global Tp*iaddr1=iaddr0+istep;\
global Tp*iaddr2=iaddr1+istep;\
global Tp*iaddr3=iaddr2+istep;\
global Tp*iaddr4=iaddr3+istep;\
global Tp*iaddr5=iaddr4+istep;\
global Tp*iaddr6=iaddr5+istep;\
global Tp*iaddr7=iaddr6+istep;\
\
VTYPE(Tp,8)v0=VLOAD(iaddr0,8);\
VTYPE(Tp,8)v1=VLOAD(iaddr1,8);\
VTYPE(Tp,8)v2=VLOAD(iaddr2,8);\
VTYPE(Tp,8)v3=VLOAD(iaddr3,8);\
VTYPE(Tp,8)v4=VLOAD(iaddr4,8);\
VTYPE(Tp,8)v5=VLOAD(iaddr5,8);\
VTYPE(Tp,8)v6=VLOAD(iaddr6,8);\
VTYPE(Tp,8)v7=VLOAD(iaddr7,8);\
\
VTYPE(Tp,8)r0=REVERSE(v7,8);\
VTYPE(Tp,8)r1=REVERSE(v6,8);\
VTYPE(Tp,8)r2=REVERSE(v5,8);\
VTYPE(Tp,8)r3=REVERSE(v4,8);\
VTYPE(Tp,8)r4=REVERSE(v3,8);\
VTYPE(Tp,8)r5=REVERSE(v2,8);\
VTYPE(Tp,8)r6=REVERSE(v1,8);\
VTYPE(Tp,8)r7=REVERSE(v0,8);\
\
global Tp*oaddr0=dst+mad24(ostep,(y),(x));\
global Tp*oaddr1=oaddr0+ostep;\
global Tp*oaddr2=oaddr1+ostep;\
global Tp*oaddr3=oaddr2+ostep;\
global Tp*oaddr4=oaddr3+ostep;\
global Tp*oaddr5=oaddr4+ostep;\
global Tp*oaddr6=oaddr5+ostep;\
global Tp*oaddr7=oaddr6+ostep;\
\
VSTORE(r0,oaddr0,8);\
VSTORE(r1,oaddr1,8);\
VSTORE(r2,oaddr2,8);\
VSTORE(r3,oaddr3,8);\
VSTORE(r4,oaddr4,8);\
VSTORE(r5,oaddr5,8);\
VSTORE(r6,oaddr6,8);\
VSTORE(r7,oaddr7,8);\
}
#define ROTATE_270_C1_1X1(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,(x),height-1-(y));\
\
VTYPE(Tp,1)v0=VLOAD(iaddr0,1);\
\
VTYPE(Tp,1)r0=v0;\
\
global Tp*oaddr0=dst+mad24(ostep,(y),(x));\
\
VSTORE(r0,oaddr0,1);\
}
#define ROTATE_270_C1_2X2(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,(x),height-2-(y));\
global Tp*iaddr1=iaddr0+istep;\
\
VTYPE(Tp,2)v0=VLOAD(iaddr0,2);\
VTYPE(Tp,2)v1=VLOAD(iaddr1,2);\
\
VTYPE(Tp,2)r0={v0.s1,v1.s1};\
VTYPE(Tp,2)r1={v0.s0,v1.s0};\
\
global Tp*oaddr0=dst+mad24(ostep,(y),(x));\
global Tp*oaddr1=oaddr0+ostep;\
\
VSTORE(r0,oaddr0,2);\
VSTORE(r1,oaddr1,2);\
}
#define ROTATE_270_C1_3X3(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,(x),height-3-(y));\
global Tp*iaddr1=iaddr0+istep;\
global Tp*iaddr2=iaddr1+istep;\
\
VTYPE(Tp,3)v0=VLOAD(iaddr0,3);\
VTYPE(Tp,3)v1=VLOAD(iaddr1,3);\
VTYPE(Tp,3)v2=VLOAD(iaddr2,3);\
\
VTYPE(Tp,3)r0={v0.s2,v1.s2,v2.s2};\
VTYPE(Tp,3)r1={v0.s1,v1.s1,v2.s1};\
VTYPE(Tp,3)r2={v0.s0,v1.s0,v2.s0};\
\
global Tp*oaddr0=dst+mad24(ostep,(y),(x));\
global Tp*oaddr1=oaddr0+ostep;\
global Tp*oaddr2=oaddr1+ostep;\
\
VSTORE(r0,oaddr0,3);\
VSTORE(r1,oaddr1,3);\
VSTORE(r2,oaddr2,3);\
}
#define ROTATE_270_C1_4X4(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,(x),height-4-(y));\
global Tp*iaddr1=iaddr0+istep;\
global Tp*iaddr2=iaddr1+istep;\
global Tp*iaddr3=iaddr2+istep;\
\
VTYPE(Tp,4)v0=VLOAD(iaddr0,4);\
VTYPE(Tp,4)v1=VLOAD(iaddr1,4);\
VTYPE(Tp,4)v2=VLOAD(iaddr2,4);\
VTYPE(Tp,4)v3=VLOAD(iaddr3,4);\
\
VTYPE(Tp,4)r0={v0.s3,v1.s3,v2.s3,v3.s3};\
VTYPE(Tp,4)r1={v0.s2,v1.s2,v2.s2,v3.s2};\
VTYPE(Tp,4)r2={v0.s1,v1.s1,v2.s1,v3.s1};\
VTYPE(Tp,4)r3={v0.s0,v1.s0,v2.s0,v3.s0};\
\
global Tp*oaddr0=dst+mad24(ostep,(y),(x));\
global Tp*oaddr1=oaddr0+ostep;\
global Tp*oaddr2=oaddr1+ostep;\
global Tp*oaddr3=oaddr2+ostep;\
\
VSTORE(r0,oaddr0,4);\
VSTORE(r1,oaddr1,4);\
VSTORE(r2,oaddr2,4);\
VSTORE(r3,oaddr3,4);\
}
#define ROTATE_270_C1_8X8(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,(x),height-8-(y));\
global Tp*iaddr1=iaddr0+istep;\
global Tp*iaddr2=iaddr1+istep;\
global Tp*iaddr3=iaddr2+istep;\
global Tp*iaddr4=iaddr3+istep;\
global Tp*iaddr5=iaddr4+istep;\
global Tp*iaddr6=iaddr5+istep;\
global Tp*iaddr7=iaddr6+istep;\
\
VTYPE(Tp,8)v0=VLOAD(iaddr0,8);\
VTYPE(Tp,8)v1=VLOAD(iaddr1,8);\
VTYPE(Tp,8)v2=VLOAD(iaddr2,8);\
VTYPE(Tp,8)v3=VLOAD(iaddr3,8);\
VTYPE(Tp,8)v4=VLOAD(iaddr4,8);\
VTYPE(Tp,8)v5=VLOAD(iaddr5,8);\
VTYPE(Tp,8)v6=VLOAD(iaddr6,8);\
VTYPE(Tp,8)v7=VLOAD(iaddr7,8);\
\
VTYPE(Tp,8)r0={v0.s7,v1.s7,v2.s7,v3.s7,v4.s7,v5.s7,v6.s7,v7.s7};\
VTYPE(Tp,8)r1={v0.s6,v1.s6,v2.s6,v3.s6,v4.s6,v5.s6,v6.s6,v7.s6};\
VTYPE(Tp,8)r2={v0.s5,v1.s5,v2.s5,v3.s5,v4.s5,v5.s5,v6.s5,v7.s5};\
VTYPE(Tp,8)r3={v0.s4,v1.s4,v2.s4,v3.s4,v4.s4,v5.s4,v6.s4,v7.s4};\
VTYPE(Tp,8)r4={v0.s3,v1.s3,v2.s3,v3.s3,v4.s3,v5.s3,v6.s3,v7.s3};\
VTYPE(Tp,8)r5={v0.s2,v1.s2,v2.s2,v3.s2,v4.s2,v5.s2,v6.s2,v7.s2};\
VTYPE(Tp,8)r6={v0.s1,v1.s1,v2.s1,v3.s1,v4.s1,v5.s1,v6.s1,v7.s1};\
VTYPE(Tp,8)r7={v0.s0,v1.s0,v2.s0,v3.s0,v4.s0,v5.s0,v6.s0,v7.s0};\
\
global Tp*oaddr0=dst+mad24(ostep,(y),(x));\
global Tp*oaddr1=oaddr0+ostep;\
global Tp*oaddr2=oaddr1+ostep;\
global Tp*oaddr3=oaddr2+ostep;\
global Tp*oaddr4=oaddr3+ostep;\
global Tp*oaddr5=oaddr4+ostep;\
global Tp*oaddr6=oaddr5+ostep;\
global Tp*oaddr7=oaddr6+ostep;\
\
VSTORE(r0,oaddr0,8);\
VSTORE(r1,oaddr1,8);\
VSTORE(r2,oaddr2,8);\
VSTORE(r3,oaddr3,8);\
VSTORE(r4,oaddr4,8);\
VSTORE(r5,oaddr5,8);\
VSTORE(r6,oaddr6,8);\
VSTORE(r7,oaddr7,8);\
}
#define ROTATE_RT_C1_STR(y,x,rt,size)rt##_C1_##size##X##size(y,x)
#define ROTATE_RT_C1(y,x,rt,size)ROTATE_RT_C1_STR(y,x,rt,size)
kernel void RotateC1(global Tp*src,int istep,
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
ROTATE_RT_C1(gy,gx,ROTATE_TYPE,ELEM_COUNTS);
}

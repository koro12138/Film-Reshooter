#define TRANSPOSE_C1_1X1(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,(x),(y));\
\
VTYPE(Tp,1)v0=VLOAD(iaddr0,1);\
\
VTYPE(Tp,1)r0=v0;\
\
global Tp*oaddr0=dst+mad24(ostep,(y),(x));\
\
VSTORE(r0,oaddr0,1);\
}
#define TRANSPOSE_C1_2X2(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,(x),(y));\
global Tp*iaddr1=iaddr0+istep;\
\
VTYPE(Tp,2)v0=VLOAD(iaddr0,2);\
VTYPE(Tp,2)v1=VLOAD(iaddr1,2);\
\
VTYPE(Tp,2)r0={v0.s0,v1.s0};\
VTYPE(Tp,2)r1={v0.s1,v1.s1};\
\
global Tp*oaddr0=dst+mad24(ostep,(y),(x));\
global Tp*oaddr1=oaddr0+ostep;\
\
VSTORE(r0,oaddr0,2);\
VSTORE(r1,oaddr1,2);\
}
#define TRANSPOSE_C1_3X3(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,(x),(y));\
global Tp*iaddr1=iaddr0+istep;\
global Tp*iaddr2=iaddr1+istep;\
\
VTYPE(Tp,3)v0=VLOAD(iaddr0,3);\
VTYPE(Tp,3)v1=VLOAD(iaddr1,3);\
VTYPE(Tp,3)v2=VLOAD(iaddr2,3);\
\
VTYPE(Tp,3)r0={v0.s0,v1.s0,v2.s0};\
VTYPE(Tp,3)r1={v0.s1,v1.s1,v2.s1};\
VTYPE(Tp,3)r2={v0.s2,v1.s2,v2.s2};\
\
global Tp*oaddr0=dst+mad24(ostep,(y),(x));\
global Tp*oaddr1=oaddr0+ostep;\
global Tp*oaddr2=oaddr1+ostep;\
\
VSTORE(r0,oaddr0,3);\
VSTORE(r1,oaddr1,3);\
VSTORE(r2,oaddr2,3);\
}
#define TRANSPOSE_C1_4X4(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,(x),(y));\
global Tp*iaddr1=iaddr0+istep;\
global Tp*iaddr2=iaddr1+istep;\
global Tp*iaddr3=iaddr2+istep;\
\
VTYPE(Tp,4)v0=VLOAD(iaddr0,4);\
VTYPE(Tp,4)v1=VLOAD(iaddr1,4);\
VTYPE(Tp,4)v2=VLOAD(iaddr2,4);\
VTYPE(Tp,4)v3=VLOAD(iaddr3,4);\
\
VTYPE(Tp,4)r0={v0.s0,v1.s0,v2.s0,v3.s0};\
VTYPE(Tp,4)r1={v0.s1,v1.s1,v2.s1,v3.s1};\
VTYPE(Tp,4)r2={v0.s2,v1.s2,v2.s2,v3.s2};\
VTYPE(Tp,4)r3={v0.s3,v1.s3,v2.s3,v3.s3};\
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
#define TRANSPOSE_C1_8X8(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,(x),(y));\
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
VTYPE(Tp,8)r0={v0.s0,v1.s0,v2.s0,v3.s0,v4.s0,v5.s0,v6.s0,v7.s0};\
VTYPE(Tp,8)r1={v0.s1,v1.s1,v2.s1,v3.s1,v4.s1,v5.s1,v6.s1,v7.s1};\
VTYPE(Tp,8)r2={v0.s2,v1.s2,v2.s2,v3.s2,v4.s2,v5.s2,v6.s2,v7.s2};\
VTYPE(Tp,8)r3={v0.s3,v1.s3,v2.s3,v3.s3,v4.s3,v5.s3,v6.s3,v7.s3};\
VTYPE(Tp,8)r4={v0.s4,v1.s4,v2.s4,v3.s4,v4.s4,v5.s4,v6.s4,v7.s4};\
VTYPE(Tp,8)r5={v0.s5,v1.s5,v2.s5,v3.s5,v4.s5,v5.s5,v6.s5,v7.s5};\
VTYPE(Tp,8)r6={v0.s6,v1.s6,v2.s6,v3.s6,v4.s6,v5.s6,v6.s6,v7.s6};\
VTYPE(Tp,8)r7={v0.s7,v1.s7,v2.s7,v3.s7,v4.s7,v5.s7,v6.s7,v7.s7};\
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
#define TRANSPOSE_C1_16X16(y,x)\
{\
global Tp*iaddr0=src+mad24(istep,(x),(y));\
global Tp*iaddr1=iaddr0+istep;\
global Tp*iaddr2=iaddr1+istep;\
global Tp*iaddr3=iaddr2+istep;\
global Tp*iaddr4=iaddr3+istep;\
global Tp*iaddr5=iaddr4+istep;\
global Tp*iaddr6=iaddr5+istep;\
global Tp*iaddr7=iaddr6+istep;\
global Tp*iaddr8=iaddr7+istep;\
global Tp*iaddr9=iaddr8+istep;\
global Tp*iaddra=iaddr9+istep;\
global Tp*iaddrb=iaddra+istep;\
global Tp*iaddrc=iaddrb+istep;\
global Tp*iaddrd=iaddrc+istep;\
global Tp*iaddre=iaddrd+istep;\
global Tp*iaddrf=iaddre+istep;\
\
VTYPE(Tp,16)v0=VLOAD(iaddr0,16);\
VTYPE(Tp,16)v1=VLOAD(iaddr1,16);\
VTYPE(Tp,16)v2=VLOAD(iaddr2,16);\
VTYPE(Tp,16)v3=VLOAD(iaddr3,16);\
VTYPE(Tp,16)v4=VLOAD(iaddr4,16);\
VTYPE(Tp,16)v5=VLOAD(iaddr5,16);\
VTYPE(Tp,16)v6=VLOAD(iaddr6,16);\
VTYPE(Tp,16)v7=VLOAD(iaddr7,16);\
VTYPE(Tp,16)v8=VLOAD(iaddr8,16);\
VTYPE(Tp,16)v9=VLOAD(iaddr9,16);\
VTYPE(Tp,16)va=VLOAD(iaddra,16);\
VTYPE(Tp,16)vb=VLOAD(iaddrb,16);\
VTYPE(Tp,16)vc=VLOAD(iaddrc,16);\
VTYPE(Tp,16)vd=VLOAD(iaddrd,16);\
VTYPE(Tp,16)ve=VLOAD(iaddre,16);\
VTYPE(Tp,16)vf=VLOAD(iaddrf,16);\
\
VTYPE(Tp,16)r0={v0.s0,v1.s0,v2.s0,v3.s0,v4.s0,v5.s0,v6.s0,v7.s0,v8.s0,v9.s0,va.s0,vb.s0,vc.s0,vd.s0,ve.s0,vf.s0};\
VTYPE(Tp,16)r1={v0.s1,v1.s1,v2.s1,v3.s1,v4.s1,v5.s1,v6.s1,v7.s1,v8.s1,v9.s1,va.s1,vb.s1,vc.s1,vd.s1,ve.s1,vf.s1};\
VTYPE(Tp,16)r2={v0.s2,v1.s2,v2.s2,v3.s2,v4.s2,v5.s2,v6.s2,v7.s2,v8.s2,v9.s2,va.s2,vb.s2,vc.s2,vd.s2,ve.s2,vf.s2};\
VTYPE(Tp,16)r3={v0.s3,v1.s3,v2.s3,v3.s3,v4.s3,v5.s3,v6.s3,v7.s3,v8.s3,v9.s3,va.s3,vb.s3,vc.s3,vd.s3,ve.s3,vf.s3};\
VTYPE(Tp,16)r4={v0.s4,v1.s4,v2.s4,v3.s4,v4.s4,v5.s4,v6.s4,v7.s4,v8.s4,v9.s4,va.s4,vb.s4,vc.s4,vd.s4,ve.s4,vf.s4};\
VTYPE(Tp,16)r5={v0.s5,v1.s5,v2.s5,v3.s5,v4.s5,v5.s5,v6.s5,v7.s5,v8.s5,v9.s5,va.s5,vb.s5,vc.s5,vd.s5,ve.s5,vf.s5};\
VTYPE(Tp,16)r6={v0.s6,v1.s6,v2.s6,v3.s6,v4.s6,v5.s6,v6.s6,v7.s6,v8.s6,v9.s6,va.s6,vb.s6,vc.s6,vd.s6,ve.s6,vf.s6};\
VTYPE(Tp,16)r7={v0.s7,v1.s7,v2.s7,v3.s7,v4.s7,v5.s7,v6.s7,v7.s7,v8.s7,v9.s7,va.s7,vb.s7,vc.s7,vd.s7,ve.s7,vf.s7};\
VTYPE(Tp,16)r8={v0.s8,v1.s8,v2.s8,v3.s8,v4.s8,v5.s8,v6.s8,v7.s8,v8.s8,v9.s8,va.s8,vb.s8,vc.s8,vd.s8,ve.s8,vf.s8};\
VTYPE(Tp,16)r9={v0.s9,v1.s9,v2.s9,v3.s9,v4.s9,v5.s9,v6.s9,v7.s9,v8.s9,v9.s9,va.s9,vb.s9,vc.s9,vd.s9,ve.s9,vf.s9};\
VTYPE(Tp,16)ra={v0.sa,v1.sa,v2.sa,v3.sa,v4.sa,v5.sa,v6.sa,v7.sa,v8.sa,v9.sa,va.sa,vb.sa,vc.sa,vd.sa,ve.sa,vf.sa};\
VTYPE(Tp,16)rb={v0.sb,v1.sb,v2.sb,v3.sb,v4.sb,v5.sb,v6.sb,v7.sb,v8.sb,v9.sb,va.sb,vb.sb,vc.sb,vd.sb,ve.sb,vf.sb};\
VTYPE(Tp,16)rc={v0.sc,v1.sc,v2.sc,v3.sc,v4.sc,v5.sc,v6.sc,v7.sc,v8.sc,v9.sc,va.sc,vb.sc,vc.sc,vd.sc,ve.sc,vf.sc};\
VTYPE(Tp,16)rd={v0.sd,v1.sd,v2.sd,v3.sd,v4.sd,v5.sd,v6.sd,v7.sd,v8.sd,v9.sd,va.sd,vb.sd,vc.sd,vd.sd,ve.sd,vf.sd};\
VTYPE(Tp,16)re={v0.se,v1.se,v2.se,v3.se,v4.se,v5.se,v6.se,v7.se,v8.se,v9.se,va.se,vb.se,vc.se,vd.se,ve.se,vf.se};\
VTYPE(Tp,16)rf={v0.sf,v1.sf,v2.sf,v3.sf,v4.sf,v5.sf,v6.sf,v7.sf,v8.sf,v9.sf,va.sf,vb.sf,vc.sf,vd.sf,ve.sf,vf.sf};\
\
global Tp*oaddr0=dst+mad24(ostep,(y),(x));\
\
global Tp*oaddr1=oaddr0+ostep;\
global Tp*oaddr2=oaddr1+ostep;\
global Tp*oaddr3=oaddr2+ostep;\
global Tp*oaddr4=oaddr3+ostep;\
global Tp*oaddr5=oaddr4+ostep;\
global Tp*oaddr6=oaddr5+ostep;\
global Tp*oaddr7=oaddr6+ostep;\
global Tp*oaddr8=oaddr7+ostep;\
global Tp*oaddr9=oaddr8+ostep;\
global Tp*oaddra=oaddr9+ostep;\
global Tp*oaddrb=oaddra+ostep;\
global Tp*oaddrc=oaddrb+ostep;\
global Tp*oaddrd=oaddrc+ostep;\
global Tp*oaddre=oaddrd+ostep;\
global Tp*oaddrf=oaddre+ostep;\
\
VSTORE(r0,oaddr0,16);\
VSTORE(r1,oaddr1,16);\
VSTORE(r2,oaddr2,16);\
VSTORE(r3,oaddr3,16);\
VSTORE(r4,oaddr4,16);\
VSTORE(r5,oaddr5,16);\
VSTORE(r6,oaddr6,16);\
VSTORE(r7,oaddr7,16);\
VSTORE(r8,oaddr8,16);\
VSTORE(r9,oaddr9,16);\
VSTORE(ra,oaddra,16);\
VSTORE(rb,oaddrb,16);\
VSTORE(rc,oaddrc,16);\
VSTORE(rd,oaddrd,16);\
VSTORE(re,oaddre,16);\
VSTORE(rf,oaddrf,16);\
}
#define TRANSPOSE_C1_STR(y,x,size)TRANSPOSE_C1_##size##X##size(y,x)
#define TRANSPOSE_C1(y,x,size)TRANSPOSE_C1_STR(y,x,size)
kernel void TransposeC1(global Tp*src,int istep,
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
TRANSPOSE_C1(gy,gx,ELEM_COUNTS);
}

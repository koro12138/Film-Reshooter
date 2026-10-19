#define ELLIPSE_HORI_OP_KERNEL3_ROW(vtp_src,vtp_dst,src_row,x_l1,x_c0,x_r1)\
{\
VTp vtp_tmp=ROT_R(vtp_src,ELEM_COUNTS,1);\
vtp_tmp.s0=src_row[x_l1];\
vtp_dst=MORPH_OP(MORPH_TYPE,vtp_src,vtp_tmp);\
vtp_tmp=ROT_L(vtp_src,ELEM_COUNTS,1);\
MORPH_REPLACE_END(vtp_tmp,ELEM_COUNTS,1,src_row[x_r1]);\
vtp_dst=MORPH_OP(MORPH_TYPE,vtp_dst,vtp_tmp);\
}
#define ELLIPSE_HORI_OP_KERNEL3(vtp_src,x_l1,x_c0,x_r1)\
int gy_p1=max(gy-1,0);\
int gy_c0=gy;\
vtp_src[0]=VLOAD(src+mad24(gy_p1,istep,x_c0),ELEM_COUNTS);\
vtp_src[1]=VLOAD(src+mad24(gy_c0,istep,x_c0),ELEM_COUNTS);
#define ELLIPSE_HORI_OP_KERNEL5_ROW(vtp_src,vtp_dst,src_row,x_l1,x_c0,x_r1)\
{\
V2Tp v2tp_l1=VLOAD(src_row+x_l1,2);\
V2Tp v2tp_r1=VLOAD(src_row+x_r1,2);\
VTp vtp_tmp=ROT_R(vtp_src,ELEM_COUNTS,1);\
vtp_tmp.s0=v2tp_l1.s1;\
vtp_dst=MORPH_OP(MORPH_TYPE,vtp_src,vtp_tmp);\
vtp_tmp=ROT_R(vtp_tmp,ELEM_COUNTS,1);\
vtp_tmp.s0=v2tp_l1.s0;\
vtp_dst=MORPH_OP(MORPH_TYPE,vtp_dst,vtp_tmp);\
vtp_tmp=ROT_L(vtp_src,ELEM_COUNTS,1);\
MORPH_REPLACE_END(vtp_tmp,ELEM_COUNTS,1,v2tp_r1.s0);\
vtp_dst=MORPH_OP(MORPH_TYPE,vtp_dst,vtp_tmp);\
vtp_tmp=ROT_L(vtp_tmp,ELEM_COUNTS,1);\
MORPH_REPLACE_END(vtp_tmp,ELEM_COUNTS,1,v2tp_r1.s1);\
vtp_dst=MORPH_OP(MORPH_TYPE,vtp_dst,vtp_tmp);\
}
#define ELLIPSE_HORI_OP_KERNEL5(vtp_src,vtp_dst,x_l1,x_c0,x_r1)\
int gy_p2=max(gy-2,0);\
int gy_p1=max(gy-1,0);\
int gy_c0=gy;\
int gy_n1=min(gy_c0+1,height-1);\
__global Tp*src_row_p1=src+gy_p1*istep;\
__global Tp*src_row_c0=src+gy_c0*istep;\
vtp_src[0]=VLOAD(src+mad24(gy_p2,istep,x_c0),ELEM_COUNTS);\
vtp_src[1]=VLOAD(src_row_p1+x_c0,ELEM_COUNTS);\
vtp_src[2]=VLOAD(src_row_c0+x_c0,ELEM_COUNTS);\
vtp_src[3]=VLOAD(src+mad24(gy_n1,istep,x_c0),ELEM_COUNTS);\
ELLIPSE_HORI_OP_KERNEL5_ROW(vtp_src[1],vtp_dst[1],src_row_p1,x_l1,x_c0,x_r1);\
ELLIPSE_HORI_OP_KERNEL5_ROW(vtp_src[2],vtp_dst[2],src_row_c0,x_l1,x_c0,x_r1);
#define ELLIPSE_HORI_OP_KERNEL7_ROW(vtp_src,vtp_mid,vtp_dst,src_row,x_l1,x_c0,x_r1)\
{\
vtp_src=VLOAD(src_row+x_c0,ELEM_COUNTS);\
V3Tp v3tp_l1=VLOAD(src_row+x_l1,3);\
V3Tp v3tp_r1=VLOAD(src_row+x_r1,3);\
VTp vtp_tmp=ROT_R(vtp_src,ELEM_COUNTS,1);\
vtp_tmp.s0=v3tp_l1.s2;\
vtp_mid=MORPH_OP(MORPH_TYPE,vtp_src,vtp_tmp);\
vtp_tmp=ROT_R(vtp_tmp,ELEM_COUNTS,1);\
vtp_tmp.s0=v3tp_l1.s1;\
vtp_mid=MORPH_OP(MORPH_TYPE,vtp_mid,vtp_tmp);\
vtp_tmp=ROT_L(vtp_src,ELEM_COUNTS,1);\
MORPH_REPLACE_END(vtp_tmp,ELEM_COUNTS,1,v3tp_r1.s0);\
vtp_mid=MORPH_OP(MORPH_TYPE,vtp_mid,vtp_tmp);\
vtp_tmp=ROT_L(vtp_tmp,ELEM_COUNTS,1);\
MORPH_REPLACE_END(vtp_tmp,ELEM_COUNTS,1,v3tp_r1.s1);\
vtp_mid=MORPH_OP(MORPH_TYPE,vtp_mid,vtp_tmp);\
vtp_tmp=ROT_L(vtp_tmp,ELEM_COUNTS,1);\
MORPH_REPLACE_END(vtp_tmp,ELEM_COUNTS,1,v3tp_r1.s2);\
vtp_dst=MORPH_OP(MORPH_TYPE,vtp_mid,vtp_tmp);\
vtp_tmp=ROT_R(vtp_src,ELEM_COUNTS,3);\
vtp_tmp.s012=v3tp_l1.s012;\
vtp_dst=MORPH_OP(MORPH_TYPE,vtp_dst,vtp_tmp);\
}
#define ELLIPSE_HORI_OP_KERNEL7(vtp_src,vtp_mid,vtp_dst,x_l1,x_c0,x_r1)\
int gy_p3=max(gy-3,0);\
int gy_p2=max(gy-2,0);\
int gy_p1=max(gy-1,0);\
int gy_c0=gy;\
int gy_n1=min(gy_c0+1,height-1);\
int gy_n2=min(gy_c0+2,height-1);\
vtp_src[0]=VLOAD(src+mad24(gy_p3,istep,x_c0),ELEM_COUNTS);\
ELLIPSE_HORI_OP_KERNEL7_ROW(vtp_src[1],vtp_mid[1],vtp_dst[1],(src+gy_p2*istep),x_l1,x_c0,x_r1);\
ELLIPSE_HORI_OP_KERNEL7_ROW(vtp_src[2],vtp_mid[2],vtp_dst[2],(src+gy_p1*istep),x_l1,x_c0,x_r1);\
ELLIPSE_HORI_OP_KERNEL7_ROW(vtp_src[3],vtp_mid[3],vtp_dst[3],(src+gy_c0*istep),x_l1,x_c0,x_r1);\
ELLIPSE_HORI_OP_KERNEL7_ROW(vtp_src[4],vtp_mid[4],vtp_dst[4],(src+gy_n1*istep),x_l1,x_c0,x_r1);\
ELLIPSE_HORI_OP_KERNEL7_ROW(vtp_src[5],vtp_mid[5],vtp_dst[5],(src+gy_n2*istep),x_l1,x_c0,x_r1);
#define ellipse_vert_op_kernel3(x_l1,x_c0,x_r1,y_c0,vtp_src_p1,vtp_src_c0,vtp_src_n1)\
{\
int gy_n1=min(y_c0+1,height-1);\
VTp v_dst_c0;\
vtp_src_n1=VLOAD(src+mad24(gy_n1,istep,x_c0),ELEM_COUNTS);\
ELLIPSE_HORI_OP_KERNEL3_ROW(vtp_src_c0,v_dst_c0,(src+y_c0*istep),x_l1,x_c0,x_r1);\
VTp vtp_result=MORPH_OP(MORPH_TYPE,vtp_src_p1,v_dst_c0);\
vtp_result=MORPH_OP(MORPH_TYPE,vtp_result,vtp_src_n1);\
VSTORE(vtp_result,(dst+mad24(y_c0,istep,x_c0)),ELEM_COUNTS);\
}
#define ellipse_vert_op_kernel5(x_l1,x_c0,x_r1,y_c0,vtp_src_p2,v_dst_p1,\
v_dst_c0,vtp_src_n1,v_dst_n1,vtp_src_n2)\
{\
int gy_n2=min(y_c0+2,height-1);\
int gy_n1=min(y_c0+1,height-1);\
vtp_src_n2=VLOAD((src+mad24(gy_n2,istep,x_c0)),ELEM_COUNTS);\
ELLIPSE_HORI_OP_KERNEL5_ROW(vtp_src_n1,v_dst_n1,(src+gy_n1*istep),x_l1,x_c0,x_r1);\
VTp vtp_result=MORPH_OP(MORPH_TYPE,vtp_src_p2,v_dst_p1);\
vtp_result=MORPH_OP(MORPH_TYPE,vtp_result,v_dst_c0);\
vtp_result=MORPH_OP(MORPH_TYPE,vtp_result,v_dst_n1);\
vtp_result=MORPH_OP(MORPH_TYPE,vtp_result,vtp_src_n2);\
VSTORE(vtp_result,(dst+mad24(y_c0,istep,x_c0)),ELEM_COUNTS);\
}
#define ellipse_vert_op_kernel7(x_l1,x_c0,x_r1,y_c0,vtp_src_p3,v_mid_p2,v_dst_p1,v_dst_c0,\
v_dst_n1,v_mid_n2,vtp_src_n3,v_mid_n3,v_dst_n3)\
{\
int gy_n3=min(y_c0+3,height-1);\
ELLIPSE_HORI_OP_KERNEL7_ROW(vtp_src_n3,v_mid_n3,v_dst_n3,(src+gy_n3*istep),x_l1,x_c0,x_r1);\
VTp vtp_result=MORPH_OP(MORPH_TYPE,vtp_src_p3,v_mid_p2);\
vtp_result=MORPH_OP(MORPH_TYPE,vtp_result,v_dst_p1);\
vtp_result=MORPH_OP(MORPH_TYPE,vtp_result,v_dst_c0);\
vtp_result=MORPH_OP(MORPH_TYPE,vtp_result,v_dst_n1);\
vtp_result=MORPH_OP(MORPH_TYPE,vtp_result,v_mid_n2);\
vtp_result=MORPH_OP(MORPH_TYPE,vtp_result,vtp_src_n3);\
VSTORE(vtp_result,(dst+mad24(y_c0,istep,x_c0)),ELEM_COUNTS);\
}
#define ELLIPSE_VERT_OP_KERNEL3(x_l1,x_c0,x_r1,y_c0,i,vtp_src,v_index)\
ellipse_vert_op_kernel3(x_l1,x_c0,x_r1,(y_c0+i),vtp_src[v_index.s0],vtp_src[v_index.s1],\
vtp_src[v_index.s2]);
#define ELLIPSE_VERT_OP_KERNEL5(x_l1,x_c0,x_r1,y_c0,i,vtp_src,vtp_dst,v_index)\
ellipse_vert_op_kernel5(x_l1,x_c0,x_r1,(y_c0+i),vtp_src[v_index.s0],vtp_dst[v_index.s1],\
vtp_dst[v_index.s2],vtp_src[v_index.s3],vtp_dst[v_index.s3],vtp_src[v_index.s4]);
#define ELLIPSE_VERT_OP_KERNEL7(x_l1,x_c0,x_r1,y_c0,i,vtp_src,vtp_mid,vtp_dst,v_index)\
ellipse_vert_op_kernel7(x_l1,x_c0,x_r1,(y_c0+i),vtp_src[v_index.s0],vtp_mid[v_index.s1],\
vtp_dst[v_index.s2],vtp_dst[v_index.s3],vtp_dst[v_index.s4],vtp_mid[v_index.s5],\
vtp_src[v_index.s6],vtp_mid[v_index.s6],vtp_dst[v_index.s6]);
kernel void MorphEllipseC1(global Tp*src,int istep,
global Tp*dst,int ostep,
int height,int width)
{
int gx=get_global_id(0)*ELEM_COUNTS;
int gy=get_global_id(1)*ELEM_HEIGHT;
if(gx>=width||gy>=height)
{
return;
}
gx=min(gx,width-ELEM_COUNTS);
gy=min(gy,height-ELEM_HEIGHT);
int ksh=KERNEL_SIZE>>1;
int gx_l1=gx-ksh*(gx>0);
int gx_r1=gx+ELEM_COUNTS-ksh*(gx>(width-ELEM_COUNTS-ksh));
uchar8 v8u8_index=(uchar8)(0,1,2,3,4,5,6,7);
#if(3==KERNEL_SIZE)
VTp vtp_src[KERNEL_SIZE];
ELLIPSE_HORI_OP_KERNEL3(vtp_src,gx_l1,gx,gx_r1);
#pragma unroll
for(int i=0;i<ELEM_HEIGHT;i++)
{
ELLIPSE_VERT_OP_KERNEL3(gx_l1,gx,gx_r1,gy,i,vtp_src,v8u8_index);
v8u8_index=v8u8_index+(uchar8)1;
v8u8_index=(v8u8_index>(uchar8)(KERNEL_SIZE-1))?(v8u8_index-(uchar8)KERNEL_SIZE):v8u8_index;
}
#elif(5==KERNEL_SIZE)
VTp vtp_src[KERNEL_SIZE],vtp_dst[KERNEL_SIZE];
ELLIPSE_HORI_OP_KERNEL5(vtp_src,vtp_dst,gx_l1,gx,gx_r1);
#pragma unroll
for(int i=0;i<ELEM_HEIGHT;i++)
{
ELLIPSE_VERT_OP_KERNEL5(gx_l1,gx,gx_r1,gy,i,vtp_src,vtp_dst,v8u8_index);
v8u8_index=v8u8_index+(uchar8)1;
v8u8_index=(v8u8_index>(uchar8)(KERNEL_SIZE-1))?(v8u8_index-(uchar8)KERNEL_SIZE):v8u8_index;
}
#else
VTp vtp_src[KERNEL_SIZE],vtp_mid[KERNEL_SIZE],vtp_dst[KERNEL_SIZE];
ELLIPSE_HORI_OP_KERNEL7(vtp_src,vtp_mid,vtp_dst,gx_l1,gx,gx_r1);
#pragma unroll
for(int i=0;i<ELEM_HEIGHT;i++)
{
ELLIPSE_VERT_OP_KERNEL7(gx_l1,gx,gx_r1,gy,i,vtp_src,vtp_mid,vtp_dst,v8u8_index);
v8u8_index=v8u8_index+(uchar8)1;
v8u8_index=(v8u8_index>(uchar8)(KERNEL_SIZE-1))?(v8u8_index-(uchar8)KERNEL_SIZE):v8u8_index;
}
#endif
}

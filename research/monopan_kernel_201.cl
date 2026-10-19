#define RECT_HORI_OP_KERNEL3(vtp_src,src_row,x_l1,x_c0,x_r1)\
{\
VTp vtp_src_0=VLOAD(src_row+x_c0,ELEM_COUNTS);\
VTp vtp_tmp=ROT_R(vtp_src_0,ELEM_COUNTS,1);\
vtp_tmp.s0=src_row[x_l1];\
vtp_src=MORPH_OP(MORPH_TYPE,vtp_src_0,vtp_tmp);\
vtp_tmp=ROT_L(vtp_src_0,ELEM_COUNTS,1);\
MORPH_REPLACE_END(vtp_tmp,ELEM_COUNTS,1,src_row[x_r1]);\
vtp_src=MORPH_OP(MORPH_TYPE,vtp_src,vtp_tmp);\
}
#define rect_hori_op_kernel3(vtp_src,x_l1,x_c0,x_r1)\
int gy_p1=max(gy-1,0);\
int gy_c0=gy;\
RECT_HORI_OP_KERNEL3(vtp_src[0],(src+gy_p1*istep),x_l1,x_c0,x_r1);\
RECT_HORI_OP_KERNEL3(vtp_src[1],(src+gy_c0*istep),x_l1,x_c0,x_r1);
#define RECT_HORI_OP_KERNEL5(vtp_src,src_row,x_l1,x_c0,x_r1)\
{\
VTp vtp_src_0=VLOAD(src_row+x_c0,ELEM_COUNTS);\
V2Tp v2tp_l1=VLOAD(src_row+x_l1,2);\
V2Tp v2tp_r1=VLOAD(src_row+x_r1,2);\
VTp vtp_tmp=ROT_R(vtp_src_0,ELEM_COUNTS,1);\
vtp_tmp.s0=v2tp_l1.s1;\
vtp_src=MORPH_OP(MORPH_TYPE,vtp_src_0,vtp_tmp);\
vtp_tmp=ROT_R(vtp_tmp,ELEM_COUNTS,1);\
vtp_tmp.s0=v2tp_l1.s0;\
vtp_src=MORPH_OP(MORPH_TYPE,vtp_src,vtp_tmp);\
vtp_tmp=ROT_L(vtp_src_0,ELEM_COUNTS,1);\
MORPH_REPLACE_END(vtp_tmp,ELEM_COUNTS,1,v2tp_r1.s0);\
vtp_src=MORPH_OP(MORPH_TYPE,vtp_src,vtp_tmp);\
vtp_tmp=ROT_L(vtp_tmp,ELEM_COUNTS,1);\
MORPH_REPLACE_END(vtp_tmp,ELEM_COUNTS,1,v2tp_r1.s1);\
vtp_src=MORPH_OP(MORPH_TYPE,vtp_src,vtp_tmp);\
}
#define rect_hori_op_kernel5(vtp_src,x_l1,x_c0,x_r1)\
int gy_p2=max(gy-2,0);\
int gy_p1=max(gy-1,0);\
int gy_c0=gy;\
int gy_n1=min(gy+1,height-1);\
RECT_HORI_OP_KERNEL5(vtp_src[0],(src+gy_p2*istep),x_l1,x_c0,x_r1);\
RECT_HORI_OP_KERNEL5(vtp_src[1],(src+gy_p1*istep),x_l1,x_c0,x_r1);\
RECT_HORI_OP_KERNEL5(vtp_src[2],(src+gy_c0*istep),x_l1,x_c0,x_r1);\
RECT_HORI_OP_KERNEL5(vtp_src[3],(src+gy_n1*istep),x_l1,x_c0,x_r1);\
vtp_src[0]=MORPH_OP(MORPH_TYPE,vtp_src[0],vtp_src[3]);
#define RECT_HORI_OP_KERNEL7(vtp_src,src_row,x_l1,x_c0,x_r1)\
{\
VTp vtp_src_0=VLOAD(src_row+x_c0,ELEM_COUNTS);\
V3Tp v3tp_l1=VLOAD(src_row+x_l1,3);\
V3Tp v3tp_r1=VLOAD(src_row+x_r1,3);\
VTp vtp_tmp=ROT_R(vtp_src_0,ELEM_COUNTS,1);\
vtp_tmp.s0=v3tp_l1.s2;\
vtp_src=MORPH_OP(MORPH_TYPE,vtp_src_0,vtp_tmp);\
vtp_tmp=ROT_R(vtp_tmp,ELEM_COUNTS,1);\
vtp_tmp.s0=v3tp_l1.s1;\
vtp_src=MORPH_OP(MORPH_TYPE,vtp_src,vtp_tmp);\
vtp_tmp=ROT_R(vtp_tmp,ELEM_COUNTS,1);\
vtp_tmp.s0=v3tp_l1.s0;\
vtp_src=MORPH_OP(MORPH_TYPE,vtp_src,vtp_tmp);\
vtp_tmp=ROT_L(vtp_src_0,ELEM_COUNTS,1);\
MORPH_REPLACE_END(vtp_tmp,ELEM_COUNTS,1,v3tp_r1.s0);\
vtp_src=MORPH_OP(MORPH_TYPE,vtp_src,vtp_tmp);\
vtp_tmp=ROT_L(vtp_tmp,ELEM_COUNTS,1);\
MORPH_REPLACE_END(vtp_tmp,ELEM_COUNTS,1,v3tp_r1.s1);\
vtp_src=MORPH_OP(MORPH_TYPE,vtp_src,vtp_tmp);\
vtp_tmp=ROT_L(vtp_tmp,ELEM_COUNTS,1);\
MORPH_REPLACE_END(vtp_tmp,ELEM_COUNTS,1,v3tp_r1.s2);\
vtp_src=MORPH_OP(MORPH_TYPE,vtp_src,vtp_tmp);\
}
#define rect_hori_op_kernel7(vtp_src,x_l1,x_c0,x_r1)\
int gy_p3=max(gy-3,0);\
int gy_p2=max(gy-2,0);\
int gy_p1=max(gy-1,0);\
int gy_c0=gy;\
int gy_n1=min(gy+1,height-1);\
int gy_n2=min(gy+2,height-1);\
RECT_HORI_OP_KERNEL7(vtp_src[0],(src+gy_p3*istep),x_l1,x_c0,x_r1);\
RECT_HORI_OP_KERNEL7(vtp_src[1],(src+gy_p2*istep),x_l1,x_c0,x_r1);\
RECT_HORI_OP_KERNEL7(vtp_src[2],(src+gy_p1*istep),x_l1,x_c0,x_r1);\
RECT_HORI_OP_KERNEL7(vtp_src[3],(src+gy_c0*istep),x_l1,x_c0,x_r1);\
RECT_HORI_OP_KERNEL7(vtp_src[4],(src+gy_n1*istep),x_l1,x_c0,x_r1);\
RECT_HORI_OP_KERNEL7(vtp_src[5],(src+gy_n2*istep),x_l1,x_c0,x_r1);\
vtp_src[0]=MORPH_OP(MORPH_TYPE,vtp_src[0],vtp_src[4]);\
vtp_src[1]=MORPH_OP(MORPH_TYPE,vtp_src[1],vtp_src[5]);
#define RECT_HORI_OP_STR(ksize,vtp_src,x_l1,x_c0,x_r1)rect_hori_op_kernel##ksize(vtp_src,x_l1,x_c0,x_r1)
#define RECT_HORI_OP(ksize,vtp_src,x_l1,x_c0,x_r1)RECT_HORI_OP_STR(ksize,vtp_src,x_l1,x_c0,x_r1)
#define rect_vert_op_kernel3(x_l1,x_c0,x_r1,y_c0,v_p1,v_c0,v_n1)\
{\
int gy_n1=min(y_c0+1,height-1);\
RECT_HORI_OP_KERNEL3(v_n1,(src+gy_n1*istep),x_l1,x_c0,x_r1);\
VTp vtp_result=MORPH_OP(MORPH_TYPE,v_p1,v_c0);\
vtp_result=MORPH_OP(MORPH_TYPE,vtp_result,v_n1);\
VSTORE(vtp_result,(dst+mad24(y_c0,istep,x_c0)),ELEM_COUNTS);\
}
#define rect_vert_op_kernel5(x_l1,x_c0,x_r1,y_c0,v_p2,v_p1,v_c0,v_n1,v_n2)\
{\
int gy_n2=min(y_c0+2,height-1);\
RECT_HORI_OP_KERNEL5(v_n2,(src+gy_n2*istep),x_l1,x_c0,x_r1);\
v_p1=MORPH_OP(MORPH_TYPE,v_p1,v_n2);\
VTp vtp_result=MORPH_OP(MORPH_TYPE,v_p1,v_p2);\
vtp_result=MORPH_OP(MORPH_TYPE,vtp_result,v_c0);\
VSTORE(vtp_result,(dst+mad24(y_c0,istep,x_c0)),ELEM_COUNTS);\
}
#define rect_vert_op_kernel7(x_l1,x_c0,x_r1,y_c0,v_p3,v_p2,v_p1,v_c0,v_n1,v_n2,v_n3)\
{\
int gy_n3=min(y_c0+3,height-1);\
RECT_HORI_OP_KERNEL7(v_n3,(src+gy_n3*istep),x_l1,x_c0,x_r1);\
v_p1=MORPH_OP(MORPH_TYPE,v_p1,v_n3);\
VTp vtp_result=MORPH_OP(MORPH_TYPE,v_p1,v_p2);\
vtp_result=MORPH_OP(MORPH_TYPE,vtp_result,v_p3);\
vtp_result=MORPH_OP(MORPH_TYPE,vtp_result,v_c0);\
VSTORE(vtp_result,(dst+mad24(y_c0,istep,x_c0)),ELEM_COUNTS);\
}
#define RECT_VERT_OP_KERNEL3(x_l1,x_c0,x_r1,y_c0,i,vtp_src,v_index)\
rect_vert_op_kernel3(x_l1,x_c0,x_r1,(y_c0+i),vtp_src[v_index.s0],vtp_src[v_index.s1],vtp_src[v_index.s2]);
#define RECT_VERT_OP_KERNEL5(x_l1,x_c0,x_r1,y_c0,i,vtp_src,v_index)\
rect_vert_op_kernel5(x_l1,x_c0,x_r1,(y_c0+i),vtp_src[v_index.s0],vtp_src[v_index.s1],\
vtp_src[v_index.s2],vtp_src[v_index.s3],vtp_src[v_index.s4]);
#define RECT_VERT_OP_KERNEL7(x_l1,x_c0,x_r1,y_c0,i,vtp_src,v_index)\
rect_vert_op_kernel7(x_l1,x_c0,x_r1,(y_c0+i),vtp_src[v_index.s0],vtp_src[v_index.s1],vtp_src[v_index.s2],\
vtp_src[v_index.s3],vtp_src[v_index.s4],vtp_src[v_index.s5],vtp_src[v_index.s6]);
#define RECT_VERT_OP_STR(ksize,x_l1,x_c0,x_r1,y_c0,i,vtp_src,v_index)RECT_VERT_OP_KERNEL##ksize(x_l1,x_c0,x_r1,y_c0,i,vtp_src,v_index)
#define RECT_VERT_OP(ksize,x_l1,x_c0,x_r1,y_c0,i,vtp_src,v_index)RECT_VERT_OP_STR(ksize,x_l1,x_c0,x_r1,y_c0,i,vtp_src,v_index)
kernel void MorphRectC1(global Tp*src,int istep,
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
VTp vtp_src[KERNEL_SIZE];
RECT_HORI_OP(KERNEL_SIZE,vtp_src,gx_l1,gx,gx_r1);
uchar8 v8u8_index=(uchar8)(0,1,2,3,4,5,6,7);
#pragma unroll
for(int i=0;i<ELEM_HEIGHT;i++)
{
RECT_VERT_OP(KERNEL_SIZE,gx_l1,gx,gx_r1,gy,i,vtp_src,v8u8_index);
v8u8_index=v8u8_index+(uchar8)1;
v8u8_index=(v8u8_index>(uchar8)(KERNEL_SIZE-1))?(v8u8_index-(uchar8)KERNEL_SIZE):v8u8_index;
}
}

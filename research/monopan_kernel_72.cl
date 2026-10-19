kernel void Filter2dRemain7x7C1(global Tp*src,int istep,
global Tp*dst,int ostep,
int height,int width,
int y_work_size,int x_work_size,
constant float*filter MAX_CONSTANT_SIZE,
int main_width,struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
const int ksh=3;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int x_idx_l2,x_idx_l1,x_idx_l0,x_idx_c,x_idx_r0,x_idx_r1,x_idx_r2;
int y_idx_p2,y_idx_p1,y_idx_p0,y_idx_c,y_idx_n0,y_idx_n1,y_idx_n2;
int offset_dst;
global Tp*src_p2,*src_p1,*src_p0,*src_c,*src_n0,*src_n1,*src_n2;
V8Tp v8tp_src_p2,v8tp_src_p1,v8tp_src_p0,v8tp_src_c,v8tp_src_n0,v8tp_src_n1,v8tp_src_n2;
float8 v8f32_src_p2,v8f32_src_p1,v8f32_src_p0,v8f32_src_c,v8f32_src_n0,v8f32_src_n1,v8f32_src_n2;
float f32_result;
Tp tp_result;
y_idx_c=gy;
y_idx_p2=TOP_BORDER_IDX(gy-3);
y_idx_p1=TOP_BORDER_IDX(gy-2);
y_idx_p0=TOP_BORDER_IDX(gy-1);
y_idx_n0=BOTTOM_BORDER_IDX(gy+1,height);
y_idx_n1=BOTTOM_BORDER_IDX(gy+2,height);
y_idx_n2=BOTTOM_BORDER_IDX(gy+3,height);
x_idx_c=(gx>=ksh)*main_width+gx;
x_idx_l2=LEFT_BORDER_IDX(x_idx_c-3);
x_idx_l1=LEFT_BORDER_IDX(x_idx_c-2);
x_idx_l0=LEFT_BORDER_IDX(x_idx_c-1);
x_idx_r0=RIGHT_BORDER_IDX(x_idx_c+1,width);
x_idx_r1=RIGHT_BORDER_IDX(x_idx_c+2,width);
x_idx_r2=RIGHT_BORDER_IDX(x_idx_c+3,width);
src_p2=src+mad24(y_idx_p2,istep,x_idx_c);
src_p1=src+mad24(y_idx_p1,istep,x_idx_c);
src_p0=src+mad24(y_idx_p0,istep,x_idx_c);
src_c=src+mad24(y_idx_c,istep,x_idx_c);
src_n0=src+mad24(y_idx_n0,istep,x_idx_c);
src_n1=src+mad24(y_idx_n1,istep,x_idx_c);
src_n2=src+mad24(y_idx_n2,istep,x_idx_c);
#if BORDER_CONSTANT
Tp value=(Tp)border_value.val[0];
v8tp_src_p2.s0=(y_idx_p2<0||x_idx_l2<0)?value:src_p2[x_idx_l2-x_idx_c];
v8tp_src_p2.s1=(y_idx_p2<0||x_idx_l1<0)?value:src_p2[x_idx_l1-x_idx_c];
v8tp_src_p2.s2=(y_idx_p2<0||x_idx_l0<0)?value:src_p2[x_idx_l0-x_idx_c];
v8tp_src_p2.s3=(y_idx_p2<0)?value:src_p2[0];
v8tp_src_p2.s4=(y_idx_p2<0||x_idx_r0<0)?value:src_p2[x_idx_r0-x_idx_c];
v8tp_src_p2.s5=(y_idx_p2<0||x_idx_r1<0)?value:src_p2[x_idx_r1-x_idx_c];
v8tp_src_p2.s6=(y_idx_p2<0||x_idx_r2<0)?value:src_p2[x_idx_r2-x_idx_c];
v8tp_src_p1.s0=(y_idx_p1<0||x_idx_l2<0)?value:src_p1[x_idx_l2-x_idx_c];
v8tp_src_p1.s1=(y_idx_p1<0||x_idx_l1<0)?value:src_p1[x_idx_l1-x_idx_c];
v8tp_src_p1.s2=(y_idx_p1<0||x_idx_l0<0)?value:src_p1[x_idx_l0-x_idx_c];
v8tp_src_p1.s3=(y_idx_p1<0)?value:src_p1[0];
v8tp_src_p1.s4=(y_idx_p1<0||x_idx_r0<0)?value:src_p1[x_idx_r0-x_idx_c];
v8tp_src_p1.s5=(y_idx_p1<0||x_idx_r1<0)?value:src_p1[x_idx_r1-x_idx_c];
v8tp_src_p1.s6=(y_idx_p1<0||x_idx_r2<0)?value:src_p1[x_idx_r2-x_idx_c];
v8tp_src_p0.s0=(y_idx_p0<0||x_idx_l2<0)?value:src_p0[x_idx_l2-x_idx_c];
v8tp_src_p0.s1=(y_idx_p0<0||x_idx_l1<0)?value:src_p0[x_idx_l1-x_idx_c];
v8tp_src_p0.s2=(y_idx_p0<0||x_idx_l0<0)?value:src_p0[x_idx_l0-x_idx_c];
v8tp_src_p0.s3=(y_idx_p0<0)?value:src_p0[0];
v8tp_src_p0.s4=(y_idx_p0<0||x_idx_r0<0)?value:src_p0[x_idx_r0-x_idx_c];
v8tp_src_p0.s5=(y_idx_p0<0||x_idx_r1<0)?value:src_p0[x_idx_r1-x_idx_c];
v8tp_src_p0.s6=(y_idx_p0<0||x_idx_r2<0)?value:src_p0[x_idx_r2-x_idx_c];
v8tp_src_c .s0=(x_idx_l2<0)?value:src_c[x_idx_l2-x_idx_c];
v8tp_src_c .s1=(x_idx_l1<0)?value:src_c[x_idx_l1-x_idx_c];
v8tp_src_c .s2=(x_idx_l0<0)?value:src_c[x_idx_l0-x_idx_c];
v8tp_src_c .s3=src_c[0];
v8tp_src_c .s4=(x_idx_r0<0)?value:src_c[x_idx_r0-x_idx_c];
v8tp_src_c .s5=(x_idx_r1<0)?value:src_c[x_idx_r1-x_idx_c];
v8tp_src_c .s6=(x_idx_r2<0)?value:src_c[x_idx_r2-x_idx_c];
v8tp_src_n0.s0=(y_idx_n0<0||x_idx_l2<0)?value:src_n0[x_idx_l2-x_idx_c];
v8tp_src_n0.s1=(y_idx_n0<0||x_idx_l1<0)?value:src_n0[x_idx_l1-x_idx_c];
v8tp_src_n0.s2=(y_idx_n0<0||x_idx_l0<0)?value:src_n0[x_idx_l0-x_idx_c];
v8tp_src_n0.s3=(y_idx_n0<0)?value:src_n0[0];
v8tp_src_n0.s4=(y_idx_n0<0||x_idx_r0<0)?value:src_n0[x_idx_r0-x_idx_c];
v8tp_src_n0.s5=(y_idx_n0<0||x_idx_r1<0)?value:src_n0[x_idx_r1-x_idx_c];
v8tp_src_n0.s6=(y_idx_n0<0||x_idx_r2<0)?value:src_n0[x_idx_r2-x_idx_c];
v8tp_src_n1.s0=(y_idx_n1<0||x_idx_l2<0)?value:src_n1[x_idx_l2-x_idx_c];
v8tp_src_n1.s1=(y_idx_n1<0||x_idx_l1<0)?value:src_n1[x_idx_l1-x_idx_c];
v8tp_src_n1.s2=(y_idx_n1<0||x_idx_l0<0)?value:src_n1[x_idx_l0-x_idx_c];
v8tp_src_n1.s3=(y_idx_n1<0)?value:src_n1[0];
v8tp_src_n1.s4=(y_idx_n1<0||x_idx_r0<0)?value:src_n1[x_idx_r0-x_idx_c];
v8tp_src_n1.s5=(y_idx_n1<0||x_idx_r1<0)?value:src_n1[x_idx_r1-x_idx_c];
v8tp_src_n1.s6=(y_idx_n1<0||x_idx_r2<0)?value:src_n1[x_idx_r2-x_idx_c];
v8tp_src_n2.s0=(y_idx_n2<0||x_idx_l2<0)?value:src_n2[x_idx_l2-x_idx_c];
v8tp_src_n2.s1=(y_idx_n2<0||x_idx_l1<0)?value:src_n2[x_idx_l1-x_idx_c];
v8tp_src_n2.s2=(y_idx_n2<0||x_idx_l0<0)?value:src_n2[x_idx_l0-x_idx_c];
v8tp_src_n2.s3=(y_idx_n2<0)?value:src_n2[0];
v8tp_src_n2.s4=(y_idx_n2<0||x_idx_r0<0)?value:src_n2[x_idx_r0-x_idx_c];
v8tp_src_n2.s5=(y_idx_n2<0||x_idx_r1<0)?value:src_n2[x_idx_r1-x_idx_c];
v8tp_src_n2.s6=(y_idx_n2<0||x_idx_r2<0)?value:src_n2[x_idx_r2-x_idx_c];
#else
x_idx_l2-=x_idx_c;
x_idx_l1-=x_idx_c;
x_idx_l0-=x_idx_c;
x_idx_r0-=x_idx_c;
x_idx_r1-=x_idx_c;
x_idx_r2-=x_idx_c;
v8tp_src_p2.s0=src_p2[x_idx_l2],v8tp_src_p2.s1=src_p2[x_idx_l1],v8tp_src_p2.s2=src_p2[x_idx_l0],v8tp_src_p2.s3=src_p2[0],
v8tp_src_p2.s4=src_p2[x_idx_r0],v8tp_src_p2.s5=src_p2[x_idx_r1],v8tp_src_p2.s6=src_p2[x_idx_r2];
v8tp_src_p1.s0=src_p1[x_idx_l2],v8tp_src_p1.s1=src_p1[x_idx_l1],v8tp_src_p1.s2=src_p1[x_idx_l0],v8tp_src_p1.s3=src_p1[0],
v8tp_src_p1.s4=src_p1[x_idx_r0],v8tp_src_p1.s5=src_p1[x_idx_r1],v8tp_src_p1.s6=src_p1[x_idx_r2];
v8tp_src_p0.s0=src_p0[x_idx_l2],v8tp_src_p0.s1=src_p0[x_idx_l1],v8tp_src_p0.s2=src_p0[x_idx_l0],v8tp_src_p0.s3=src_p0[0],
v8tp_src_p0.s4=src_p0[x_idx_r0],v8tp_src_p0.s5=src_p0[x_idx_r1],v8tp_src_p0.s6=src_p0[x_idx_r2];
v8tp_src_c.s0=src_c[x_idx_l2],v8tp_src_c.s1=src_c[x_idx_l1],v8tp_src_c.s2=src_c[x_idx_l0],v8tp_src_c .s3=src_c[0],
v8tp_src_c.s4=src_c[x_idx_r0],v8tp_src_c.s5=src_c[x_idx_r1],v8tp_src_c.s6=src_c[x_idx_r2];
v8tp_src_n0.s0=src_n0[x_idx_l2],v8tp_src_n0.s1=src_n0[x_idx_l1],v8tp_src_n0.s2=src_n0[x_idx_l0],v8tp_src_n0.s3=src_n0[0],
v8tp_src_n0.s4=src_n0[x_idx_r0],v8tp_src_n0.s5=src_n0[x_idx_r1],v8tp_src_n0.s6=src_n0[x_idx_r2];
v8tp_src_n1.s0=src_n1[x_idx_l2],v8tp_src_n1.s1=src_n1[x_idx_l1],v8tp_src_n1.s2=src_n1[x_idx_l0],v8tp_src_n1.s3=src_n1[0],
v8tp_src_n1.s4=src_n1[x_idx_r0],v8tp_src_n1.s5=src_n1[x_idx_r1],v8tp_src_n1.s6=src_n1[x_idx_r2];
v8tp_src_n2.s0=src_n2[x_idx_l2],v8tp_src_n2.s1=src_n2[x_idx_l1],v8tp_src_n2.s2=src_n2[x_idx_l0],v8tp_src_n2.s3=src_n2[0],
v8tp_src_n2.s4=src_n2[x_idx_r0],v8tp_src_n2.s5=src_n2[x_idx_r1],v8tp_src_n2.s6=src_n2[x_idx_r2];
#endif
v8f32_src_p2=FILTER2D_CONVERT(v8tp_src_p2,float8);
v8f32_src_p1=FILTER2D_CONVERT(v8tp_src_p1,float8);
v8f32_src_p0=FILTER2D_CONVERT(v8tp_src_p0,float8);
v8f32_src_c=FILTER2D_CONVERT(v8tp_src_c,float8);
v8f32_src_n0=FILTER2D_CONVERT(v8tp_src_n0,float8);
v8f32_src_n1=FILTER2D_CONVERT(v8tp_src_n1,float8);
v8f32_src_n2=FILTER2D_CONVERT(v8tp_src_n2,float8);
f32_result=(v8f32_src_p2.s0*filter[0]+v8f32_src_p2.s1*filter[1]+v8f32_src_p2.s2*filter[2]+v8f32_src_p2.s3*filter[3]+v8f32_src_p2.s4*filter[4]+v8f32_src_p2.s5*filter[5]+v8f32_src_p2.s6*filter[6])+
(v8f32_src_p1.s0*filter[7]+v8f32_src_p1.s1*filter[8]+v8f32_src_p1.s2*filter[9]+v8f32_src_p1.s3*filter[10]+v8f32_src_p1.s4*filter[11]+v8f32_src_p1.s5*filter[12]+v8f32_src_p1.s6*filter[13])+
(v8f32_src_p0.s0*filter[14]+v8f32_src_p0.s1*filter[15]+v8f32_src_p0.s2*filter[16]+v8f32_src_p0.s3*filter[17]+v8f32_src_p0.s4*filter[18]+v8f32_src_p0.s5*filter[19]+v8f32_src_p0.s6*filter[20])+
(v8f32_src_c.s0*filter[21]+v8f32_src_c.s1*filter[22]+v8f32_src_c.s2*filter[23]+v8f32_src_c.s3*filter[24]+v8f32_src_c.s4*filter[25]+v8f32_src_c.s5*filter[26]+v8f32_src_c.s6*filter[27])+
(v8f32_src_n0.s0*filter[28]+v8f32_src_n0.s1*filter[29]+v8f32_src_n0.s2*filter[30]+v8f32_src_n0.s3*filter[31]+v8f32_src_n0.s4*filter[32]+v8f32_src_n0.s5*filter[33]+v8f32_src_n0.s6*filter[34])+
(v8f32_src_n1.s0*filter[35]+v8f32_src_n1.s1*filter[36]+v8f32_src_n1.s2*filter[37]+v8f32_src_n1.s3*filter[38]+v8f32_src_n1.s4*filter[39]+v8f32_src_n1.s5*filter[40]+v8f32_src_n1.s6*filter[41])+
(v8f32_src_n2.s0*filter[42]+v8f32_src_n2.s1*filter[43]+v8f32_src_n2.s2*filter[44]+v8f32_src_n2.s3*filter[45]+v8f32_src_n2.s4*filter[46]+v8f32_src_n2.s5*filter[47]+v8f32_src_n2.s6*filter[48]);
tp_result=CONVERT_SAT(f32_result,Tp);
offset_dst=mad24(y_idx_c,ostep,x_idx_c);
dst[offset_dst]=tp_result;
}

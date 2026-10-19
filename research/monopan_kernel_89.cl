kernel void GaussianRemain7x7C1(global St*src,int istep,
global Dt*dst,int ostep,
int height,int width,int main_width,
int y_work_size,int x_work_size,
constant Kt*filter MAX_CONSTANT_SIZE,
struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
int ksh=3;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int x_idx_l2,x_idx_l1,x_idx_l0,x_idx_c,x_idx_r0,x_idx_r1,x_idx_r2;
int y_idx_p2,y_idx_p1,y_idx_p0,y_idx_c,y_idx_n0,y_idx_n1,y_idx_n2;
int offset_dst;
global St*src_p2,*src_p1,*src_p0,*src_c,*src_n0,*src_n1,*src_n2;
V8St v8st_src_p2,v8st_src_p1,v8st_src_p0,v8st_src_c,v8st_src_n0,v8st_src_n1,v8st_src_n2;
V8InterType v8it_src_p2,v8it_src_p1,v8it_src_p0,v8it_src_c,v8it_src_n0,v8it_src_n1,v8it_src_n2;
V8InterType v8it_sum;
InterType it_result;
Dt dt_result;
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
St value=(St)border_value.val[0];
v8st_src_p2.s0=(y_idx_p2<0||x_idx_l2<0)?value:src_p2[x_idx_l2-x_idx_c];
v8st_src_p2.s1=(y_idx_p2<0||x_idx_l1<0)?value:src_p2[x_idx_l1-x_idx_c];
v8st_src_p2.s2=(y_idx_p2<0||x_idx_l0<0)?value:src_p2[x_idx_l0-x_idx_c];
v8st_src_p2.s3=(y_idx_p2<0)?value:src_p2[0];
v8st_src_p2.s4=(y_idx_p2<0||x_idx_r0<0)?value:src_p2[x_idx_r0-x_idx_c];
v8st_src_p2.s5=(y_idx_p2<0||x_idx_r1<0)?value:src_p2[x_idx_r1-x_idx_c];
v8st_src_p2.s6=(y_idx_p2<0||x_idx_r2<0)?value:src_p2[x_idx_r2-x_idx_c];
v8st_src_p1.s0=(y_idx_p1<0||x_idx_l2<0)?value:src_p1[x_idx_l2-x_idx_c];
v8st_src_p1.s1=(y_idx_p1<0||x_idx_l1<0)?value:src_p1[x_idx_l1-x_idx_c];
v8st_src_p1.s2=(y_idx_p1<0||x_idx_l0<0)?value:src_p1[x_idx_l0-x_idx_c];
v8st_src_p1.s3=(y_idx_p1<0)?value:src_p1[0];
v8st_src_p1.s4=(y_idx_p1<0||x_idx_r0<0)?value:src_p1[x_idx_r0-x_idx_c];
v8st_src_p1.s5=(y_idx_p1<0||x_idx_r1<0)?value:src_p1[x_idx_r1-x_idx_c];
v8st_src_p1.s6=(y_idx_p1<0||x_idx_r2<0)?value:src_p1[x_idx_r2-x_idx_c];
v8st_src_p0.s0=(y_idx_p0<0||x_idx_l2<0)?value:src_p0[x_idx_l2-x_idx_c];
v8st_src_p0.s1=(y_idx_p0<0||x_idx_l1<0)?value:src_p0[x_idx_l1-x_idx_c];
v8st_src_p0.s2=(y_idx_p0<0||x_idx_l0<0)?value:src_p0[x_idx_l0-x_idx_c];
v8st_src_p0.s3=(y_idx_p0<0)?value:src_p0[0];
v8st_src_p0.s4=(y_idx_p0<0||x_idx_r0<0)?value:src_p0[x_idx_r0-x_idx_c];
v8st_src_p0.s5=(y_idx_p0<0||x_idx_r1<0)?value:src_p0[x_idx_r1-x_idx_c];
v8st_src_p0.s6=(y_idx_p0<0||x_idx_r2<0)?value:src_p0[x_idx_r2-x_idx_c];
v8st_src_c .s0=(x_idx_l2<0)?value:src_c[x_idx_l2-x_idx_c];
v8st_src_c .s1=(x_idx_l1<0)?value:src_c[x_idx_l1-x_idx_c];
v8st_src_c .s2=(x_idx_l0<0)?value:src_c[x_idx_l0-x_idx_c];
v8st_src_c .s3=src_c[0];
v8st_src_c .s4=(x_idx_r0<0)?value:src_c[x_idx_r0-x_idx_c];
v8st_src_c .s5=(x_idx_r1<0)?value:src_c[x_idx_r1-x_idx_c];
v8st_src_c .s6=(x_idx_r2<0)?value:src_c[x_idx_r2-x_idx_c];
v8st_src_n0.s0=(y_idx_n0<0||x_idx_l2<0)?value:src_n0[x_idx_l2-x_idx_c];
v8st_src_n0.s1=(y_idx_n0<0||x_idx_l1<0)?value:src_n0[x_idx_l1-x_idx_c];
v8st_src_n0.s2=(y_idx_n0<0||x_idx_l0<0)?value:src_n0[x_idx_l0-x_idx_c];
v8st_src_n0.s3=(y_idx_n0<0)?value:src_n0[0];
v8st_src_n0.s4=(y_idx_n0<0||x_idx_r0<0)?value:src_n0[x_idx_r0-x_idx_c];
v8st_src_n0.s5=(y_idx_n0<0||x_idx_r1<0)?value:src_n0[x_idx_r1-x_idx_c];
v8st_src_n0.s6=(y_idx_n0<0||x_idx_r2<0)?value:src_n0[x_idx_r2-x_idx_c];
v8st_src_n1.s0=(y_idx_n1<0||x_idx_l2<0)?value:src_n1[x_idx_l2-x_idx_c];
v8st_src_n1.s1=(y_idx_n1<0||x_idx_l1<0)?value:src_n1[x_idx_l1-x_idx_c];
v8st_src_n1.s2=(y_idx_n1<0||x_idx_l0<0)?value:src_n1[x_idx_l0-x_idx_c];
v8st_src_n1.s3=(y_idx_n1<0)?value:src_n1[0];
v8st_src_n1.s4=(y_idx_n1<0||x_idx_r0<0)?value:src_n1[x_idx_r0-x_idx_c];
v8st_src_n1.s5=(y_idx_n1<0||x_idx_r1<0)?value:src_n1[x_idx_r1-x_idx_c];
v8st_src_n1.s6=(y_idx_n1<0||x_idx_r2<0)?value:src_n1[x_idx_r2-x_idx_c];
v8st_src_n2.s0=(y_idx_n2<0||x_idx_l2<0)?value:src_n2[x_idx_l2-x_idx_c];
v8st_src_n2.s1=(y_idx_n2<0||x_idx_l1<0)?value:src_n2[x_idx_l1-x_idx_c];
v8st_src_n2.s2=(y_idx_n2<0||x_idx_l0<0)?value:src_n2[x_idx_l0-x_idx_c];
v8st_src_n2.s3=(y_idx_n2<0)?value:src_n2[0];
v8st_src_n2.s4=(y_idx_n2<0||x_idx_r0<0)?value:src_n2[x_idx_r0-x_idx_c];
v8st_src_n2.s5=(y_idx_n2<0||x_idx_r1<0)?value:src_n2[x_idx_r1-x_idx_c];
v8st_src_n2.s6=(y_idx_n2<0||x_idx_r2<0)?value:src_n2[x_idx_r2-x_idx_c];
#else
x_idx_l2-=x_idx_c;
x_idx_l1-=x_idx_c;
x_idx_l0-=x_idx_c;
x_idx_r0-=x_idx_c;
x_idx_r1-=x_idx_c;
x_idx_r2-=x_idx_c;
v8st_src_p2.s0=src_p2[x_idx_l2],v8st_src_p2.s1=src_p2[x_idx_l1],v8st_src_p2.s2=src_p2[x_idx_l0],v8st_src_p2.s3=src_p2[0],
v8st_src_p2.s4=src_p2[x_idx_r0],v8st_src_p2.s5=src_p2[x_idx_r1],v8st_src_p2.s6=src_p2[x_idx_r2];
v8st_src_p1.s0=src_p1[x_idx_l2],v8st_src_p1.s1=src_p1[x_idx_l1],v8st_src_p1.s2=src_p1[x_idx_l0],v8st_src_p1.s3=src_p1[0],
v8st_src_p1.s4=src_p1[x_idx_r0],v8st_src_p1.s5=src_p1[x_idx_r1],v8st_src_p1.s6=src_p1[x_idx_r2];
v8st_src_p0.s0=src_p0[x_idx_l2],v8st_src_p0.s1=src_p0[x_idx_l1],v8st_src_p0.s2=src_p0[x_idx_l0],v8st_src_p0.s3=src_p0[0],
v8st_src_p0.s4=src_p0[x_idx_r0],v8st_src_p0.s5=src_p0[x_idx_r1],v8st_src_p0.s6=src_p0[x_idx_r2];
v8st_src_c .s0=src_c[x_idx_l2],v8st_src_c .s1=src_c[x_idx_l1],v8st_src_c .s2=src_c[x_idx_l0],v8st_src_c .s3=src_c[0],
v8st_src_c .s4=src_c[x_idx_r0],v8st_src_c .s5=src_c[x_idx_r1],v8st_src_c .s6=src_c[x_idx_r2];
v8st_src_n0.s0=src_n0[x_idx_l2],v8st_src_n0.s1=src_n0[x_idx_l1],v8st_src_n0.s2=src_n0[x_idx_l0],v8st_src_n0.s3=src_n0[0],
v8st_src_n0.s4=src_n0[x_idx_r0],v8st_src_n0.s5=src_n0[x_idx_r1],v8st_src_n0.s6=src_n0[x_idx_r2];
v8st_src_n1.s0=src_n1[x_idx_l2],v8st_src_n1.s1=src_n1[x_idx_l1],v8st_src_n1.s2=src_n1[x_idx_l0],v8st_src_n1.s3=src_n1[0],
v8st_src_n1.s4=src_n1[x_idx_r0],v8st_src_n1.s5=src_n1[x_idx_r1],v8st_src_n1.s6=src_n1[x_idx_r2];
v8st_src_n2.s0=src_n2[x_idx_l2],v8st_src_n2.s1=src_n2[x_idx_l1],v8st_src_n2.s2=src_n2[x_idx_l0],v8st_src_n2.s3=src_n2[0],
v8st_src_n2.s4=src_n2[x_idx_r0],v8st_src_n2.s5=src_n2[x_idx_r1],v8st_src_n2.s6=src_n2[x_idx_r2];
#endif
v8it_src_p2=GAUSSIAN_CONVERT(v8st_src_p2,V8InterType);
v8it_src_p1=GAUSSIAN_CONVERT(v8st_src_p1,V8InterType);
v8it_src_p0=GAUSSIAN_CONVERT(v8st_src_p0,V8InterType);
v8it_src_c=GAUSSIAN_CONVERT(v8st_src_c,V8InterType);
v8it_src_n0=GAUSSIAN_CONVERT(v8st_src_n0,V8InterType);
v8it_src_n1=GAUSSIAN_CONVERT(v8st_src_n1,V8InterType);
v8it_src_n2=GAUSSIAN_CONVERT(v8st_src_n2,V8InterType);
v8it_sum=(v8it_src_p2+v8it_src_n2)*(V8InterType)filter[0]+(v8it_src_p1+v8it_src_n1)*(V8InterType)filter[1]+
(v8it_src_p0+v8it_src_n0)*(V8InterType)filter[2]+v8it_src_c*(V8InterType)filter[3];
it_result=(v8it_sum.s0+v8it_sum.s6)*(InterType)filter[0]+(v8it_sum.s1+v8it_sum.s5)*(InterType)filter[1]+
(v8it_sum.s2+v8it_sum.s4)*(InterType)filter[2]+v8it_sum.s3*(InterType)filter[3];
#if IS_FLOAT(InterType)
dt_result=CONVERT(it_result,Dt);
#else
dt_result=CONVERT_SAT((it_result+(InterType)(1<<(Q-1)))>>Q,Dt);
#endif
offset_dst=mad24(y_idx_c,ostep,x_idx_c);
dst[offset_dst]=dt_result;
}

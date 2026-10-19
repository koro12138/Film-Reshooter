kernel void BoxfilterRemain5x5C1(global St*src,int istep,
global Dt*dst,int ostep,
int width,int height,
int x_work_size,int y_work_size,
int main_width,struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
const int ksh=2;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int x_idx_l1,x_idx_l0,x_idx_c,x_idx_r0,x_idx_r1;
int y_idx_p1,y_idx_p0,y_idx_c,y_idx_n0,y_idx_n1;
int offset_dst;
St*src_row_p1,*src_row_p0,*src_row_c,*src_row_n0,*src_row_n1;
V8St v8st_src_p1,v8st_src_p0,v8st_src_c,v8st_src_n0,v8st_src_n1;
V8InterType v8it_src_p1,v8it_src_p0,v8it_src_c,v8it_src_n0,v8it_src_n1;
V8InterType v8it_sum;
InterType it_result;
Dt dt_result;
y_idx_c=gy;
y_idx_p1=TOP_BORDER_IDX(gy-2);
y_idx_p0=TOP_BORDER_IDX(gy-1);
y_idx_n0=BOTTOM_BORDER_IDX(gy+1,height);
y_idx_n1=BOTTOM_BORDER_IDX(gy+2,height);
x_idx_c=(gx>=ksh)*main_width+gx;
x_idx_l1=LEFT_BORDER_IDX(x_idx_c-2);
x_idx_l0=LEFT_BORDER_IDX(x_idx_c-1);
x_idx_r0=RIGHT_BORDER_IDX(x_idx_c+1,width);
x_idx_r1=RIGHT_BORDER_IDX(x_idx_c+2,width);
src_row_p1=src+mad24(y_idx_p1,istep,x_idx_c);
src_row_p0=src+mad24(y_idx_p0,istep,x_idx_c);
src_row_c=src+mad24(y_idx_c,istep,x_idx_c);
src_row_n0=src+mad24(y_idx_n0,istep,x_idx_c);
src_row_n1=src+mad24(y_idx_n1,istep,x_idx_c);
#if BORDER_CONSTANT
St value=(St)border_value.val[0];
v8st_src_p1.s0=(y_idx_p1<0||x_idx_l1<0)?value:src_row_p1[x_idx_l1-x_idx_c];
v8st_src_p1.s1=(y_idx_p1<0||x_idx_l0<0)?value:src_row_p1[x_idx_l0-x_idx_c];
v8st_src_p1.s2=(y_idx_p1<0)?value:src_row_p1[0];
v8st_src_p1.s3=(y_idx_p1<0||x_idx_r0<0)?value:src_row_p1[x_idx_r0-x_idx_c];
v8st_src_p1.s4=(y_idx_p1<0||x_idx_r1<0)?value:src_row_p1[x_idx_r1-x_idx_c];
v8st_src_p0.s0=(y_idx_p0<0||x_idx_l1<0)?value:src_row_p0[x_idx_l1-x_idx_c];
v8st_src_p0.s1=(y_idx_p0<0||x_idx_l0<0)?value:src_row_p0[x_idx_l0-x_idx_c];
v8st_src_p0.s2=(y_idx_p0<0)?value:src_row_p0[0];
v8st_src_p0.s3=(y_idx_p0<0||x_idx_r0<0)?value:src_row_p0[x_idx_r0-x_idx_c];
v8st_src_p0.s4=(y_idx_p0<0||x_idx_r1<0)?value:src_row_p0[x_idx_r1-x_idx_c];
v8st_src_c.s0=(x_idx_l1<0)?value:src_row_c[x_idx_l1-x_idx_c];
v8st_src_c.s1=(x_idx_l0<0)?value:src_row_c[x_idx_l0-x_idx_c];
v8st_src_c.s2=src_row_c[0];
v8st_src_c.s3=(x_idx_r0<0)?value:src_row_c[x_idx_r0-x_idx_c];
v8st_src_c.s4=(x_idx_r1<0)?value:src_row_c[x_idx_r1-x_idx_c];
v8st_src_n0.s0=(y_idx_n0<0||x_idx_l1<0)?value:src_row_n0[x_idx_l1-x_idx_c];
v8st_src_n0.s1=(y_idx_n0<0||x_idx_l0<0)?value:src_row_n0[x_idx_l0-x_idx_c];
v8st_src_n0.s2=(y_idx_n0<0)?value:src_row_n0[0];
v8st_src_n0.s3=(y_idx_n0<0||x_idx_r0<0)?value:src_row_n0[x_idx_r0-x_idx_c];
v8st_src_n0.s4=(y_idx_n0<0||x_idx_r1<0)?value:src_row_n0[x_idx_r1-x_idx_c];
v8st_src_n1.s0=(y_idx_n1<0||x_idx_l1<0)?value:src_row_n1[x_idx_l1-x_idx_c];
v8st_src_n1.s1=(y_idx_n1<0||x_idx_l0<0)?value:src_row_n1[x_idx_l0-x_idx_c];
v8st_src_n1.s2=(y_idx_n1<0)?value:src_row_n1[0];
v8st_src_n1.s3=(y_idx_n1<0||x_idx_r0<0)?value:src_row_n1[x_idx_r0-x_idx_c];
v8st_src_n1.s4=(y_idx_n1<0||x_idx_r1<0)?value:src_row_n1[x_idx_r1-x_idx_c];
#else
x_idx_l1-=x_idx_c;
x_idx_l0-=x_idx_c;
x_idx_r0-=x_idx_c;
x_idx_r1-=x_idx_c;
v8st_src_p1.s0=src_row_p1[x_idx_l1],v8st_src_p1.s1=src_row_p1[x_idx_l0],v8st_src_p1.s2=src_row_p1[0],v8st_src_p1.s3=src_row_p1[x_idx_r0],v8st_src_p1.s4=src_row_p1[x_idx_r1];
v8st_src_p0.s0=src_row_p0[x_idx_l1],v8st_src_p0.s1=src_row_p0[x_idx_l0],v8st_src_p0.s2=src_row_p0[0],v8st_src_p0.s3=src_row_p0[x_idx_r0],v8st_src_p0.s4=src_row_p0[x_idx_r1];
v8st_src_c.s0=src_row_c[x_idx_l1],v8st_src_c.s1=src_row_c[x_idx_l0],v8st_src_c.s2=src_row_c[0],v8st_src_c.s3=src_row_c[x_idx_r0],v8st_src_c.s4=src_row_c[x_idx_r1];
v8st_src_n0.s0=src_row_n0[x_idx_l1],v8st_src_n0.s1=src_row_n0[x_idx_l0],v8st_src_n0.s2=src_row_n0[0],v8st_src_n0.s3=src_row_n0[x_idx_r0],v8st_src_n0.s4=src_row_n0[x_idx_r1];
v8st_src_n1.s0=src_row_n1[x_idx_l1],v8st_src_n1.s1=src_row_n1[x_idx_l0],v8st_src_n1.s2=src_row_n1[0],v8st_src_n1.s3=src_row_n1[x_idx_r0],v8st_src_n1.s4=src_row_n1[x_idx_r1];
#endif
v8it_src_p1=BOXFILTER_CONVERT(v8st_src_p1,V8InterType);
v8it_src_p0=BOXFILTER_CONVERT(v8st_src_p0,V8InterType);
v8it_src_c=BOXFILTER_CONVERT(v8st_src_c,V8InterType);
v8it_src_n0=BOXFILTER_CONVERT(v8st_src_n0,V8InterType);
v8it_src_n1=BOXFILTER_CONVERT(v8st_src_n1,V8InterType);
v8it_sum=v8it_src_p1+v8it_src_n1+v8it_src_p0+v8it_src_n0+v8it_src_c;
it_result=v8it_sum.s0+v8it_sum.s4+v8it_sum.s1+v8it_sum.s3+v8it_sum.s2;
dt_result=CONVERT(it_result/25,Dt);
offset_dst=mad24(y_idx_c,ostep,x_idx_c);
dst[offset_dst]=dt_result;
}

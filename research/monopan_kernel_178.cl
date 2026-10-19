#define KSH (2)
kernel void PyrDownRemain5x5C1(global Tp*src,int istep,
int iheight,int iwidth,
global Tp*dst,int ostep,
int y_work_size,int x_work_size,
int main_width,
constant Kt*filter MAX_CONSTANT_SIZE)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int x_idx_l1,x_idx_l0,x_idx_c,x_idx_r0,x_idx_r1;
int y_idx_p1,y_idx_p0,y_idx_c,y_idx_n0,y_idx_n1;
int offset_dst,dx_idx_c;
int gsy=gy<<1;
int gsx=gx<<1;
global Tp*src_row_p1,*src_row_p0,*src_row_c,*src_row_n0,*src_row_n1;
V8Tp v8st_src_p1,v8st_src_p0,v8st_src_c,v8st_src_n0,v8st_src_n1;
V8It v8it_src_p1,v8it_src_p0,v8it_src_c,v8it_src_n0,v8it_src_n1;
V8It v8it_sum;
InterType it_result;
Tp dt_result;
y_idx_c=gsy;
y_idx_p1=TOP_BORDER_IDX(gsy-2);
y_idx_p0=TOP_BORDER_IDX(gsy-1);
y_idx_n0=BOTTOM_BORDER_IDX(gsy+1,iheight);
y_idx_n1=BOTTOM_BORDER_IDX(gsy+2,iheight);
x_idx_c=(gx>=KSH)*(main_width<<1)+gsx;
x_idx_l1=LEFT_BORDER_IDX(x_idx_c-2);
x_idx_l0=LEFT_BORDER_IDX(x_idx_c-1);
x_idx_r0=RIGHT_BORDER_IDX(x_idx_c+1,iwidth);
x_idx_r1=RIGHT_BORDER_IDX(x_idx_c+2,iwidth);
src_row_p1=src+mad24(y_idx_p1,istep,x_idx_c);
src_row_p0=src+mad24(y_idx_p0,istep,x_idx_c);
src_row_c=src+mad24(y_idx_c,istep,x_idx_c);
src_row_n0=src+mad24(y_idx_n0,istep,x_idx_c);
src_row_n1=src+mad24(y_idx_n1,istep,x_idx_c);
x_idx_l1-=x_idx_c;
x_idx_l0-=x_idx_c;
x_idx_r0-=x_idx_c;
x_idx_r1-=x_idx_c;
v8st_src_p1.s0=src_row_p1[x_idx_l1],v8st_src_p1.s1=src_row_p1[x_idx_l0],v8st_src_p1.s2=src_row_p1[0],v8st_src_p1.s3=src_row_p1[x_idx_r0],v8st_src_p1.s4=src_row_p1[x_idx_r1];
v8st_src_p0.s0=src_row_p0[x_idx_l1],v8st_src_p0.s1=src_row_p0[x_idx_l0],v8st_src_p0.s2=src_row_p0[0],v8st_src_p0.s3=src_row_p0[x_idx_r0],v8st_src_p0.s4=src_row_p0[x_idx_r1];
v8st_src_c.s0=src_row_c[x_idx_l1],v8st_src_c.s1=src_row_c[x_idx_l0],v8st_src_c.s2=src_row_c[0],v8st_src_c.s3=src_row_c[x_idx_r0],v8st_src_c.s4=src_row_c[x_idx_r1];
v8st_src_n0.s0=src_row_n0[x_idx_l1],v8st_src_n0.s1=src_row_n0[x_idx_l0],v8st_src_n0.s2=src_row_n0[0],v8st_src_n0.s3=src_row_n0[x_idx_r0],v8st_src_n0.s4=src_row_n0[x_idx_r1];
v8st_src_n1.s0=src_row_n1[x_idx_l1],v8st_src_n1.s1=src_row_n1[x_idx_l0],v8st_src_n1.s2=src_row_n1[0],v8st_src_n1.s3=src_row_n1[x_idx_r0],v8st_src_n1.s4=src_row_n1[x_idx_r1];
v8it_src_p1=CONVERT(v8st_src_p1,V8It);
v8it_src_p0=CONVERT(v8st_src_p0,V8It);
v8it_src_c=CONVERT(v8st_src_c,V8It);
v8it_src_n0=CONVERT(v8st_src_n0,V8It);
v8it_src_n1=CONVERT(v8st_src_n1,V8It);
v8it_sum=(v8it_src_p1+v8it_src_n1)*(V8It)filter[0]+(v8it_src_p0+v8it_src_n0)*(V8It)filter[1]+v8it_src_c*(V8It)filter[2];
it_result=(v8it_sum.s0+v8it_sum.s4)*(InterType)filter[0]+(v8it_sum.s1+v8it_sum.s3)*(InterType)filter[1]+v8it_sum.s2*(InterType)filter[2];
#if IS_FLOAT(InterType)
dt_result=CONVERT_SAT(native_divide(it_result+(InterType)(1<<(Q-1)),(1<<Q)),Tp);
#else
dt_result=CONVERT_SAT((it_result+(InterType)(1<<(Q-1)))>>Q,Tp);
#endif
dx_idx_c=(gx>=KSH)*main_width+gx;
offset_dst=mad24(gy,ostep,dx_idx_c);
dst[offset_dst]=dt_result;
}

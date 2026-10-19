kernel void GaussianRemain5x5C2(global St*src,int istep,
global Dt*dst,int ostep,
int height,int width,int main_width,
int y_work_size,int x_work_size,
constant Kt*filter MAX_CONSTANT_SIZE,
struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
int ksh=2;
int channel=2;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int x_idx_l1,x_idx_l0,x_idx_c,x_idx_r0,x_idx_r1;
int y_idx_p1,y_idx_p0,y_idx_c,y_idx_n0,y_idx_n1;
int offset_dst;
global St*src_p1,*src_p0,*src_c,*src_n0,*src_n1;
V16St v16st_src_p1,v16st_src_p0,v16st_src_c,v16st_src_n0,v16st_src_n1;
V16InterType v16it_src_p1,v16it_src_p0,v16it_src_c,v16it_src_n0,v16it_src_n1;
V16InterType v16it_sum;
V2InterType v2it_result;
V2Dt v2dt_result;
y_idx_c=gy;
y_idx_p1=TOP_BORDER_IDX(gy-2);
y_idx_p0=TOP_BORDER_IDX(gy-1);
y_idx_n0=BOTTOM_BORDER_IDX(gy+1,height);
y_idx_n1=BOTTOM_BORDER_IDX(gy+2,height);
x_idx_c=(gx>=ksh)*main_width+gx;
x_idx_l1=LEFT_BORDER_IDX(x_idx_c-2)*channel;
x_idx_l0=LEFT_BORDER_IDX(x_idx_c-1)*channel;
x_idx_r0=RIGHT_BORDER_IDX(x_idx_c+1,width)*channel;
x_idx_r1=RIGHT_BORDER_IDX(x_idx_c+2,width)*channel;
x_idx_c*=channel;
src_p1=src+mad24(y_idx_p1,istep,x_idx_c);
src_p0=src+mad24(y_idx_p0,istep,x_idx_c);
src_c=src+mad24(y_idx_c,istep,x_idx_c);
src_n0=src+mad24(y_idx_n0,istep,x_idx_c);
src_n1=src+mad24(y_idx_n1,istep,x_idx_c);
#if BORDER_CONSTANT
V2St v2st_border_value={(St)border_value.val[0],(St)border_value.val[1]};
v16st_src_p1.s01=(y_idx_p1<0||x_idx_l1<0)?v2st_border_value:VLOAD(src_p1+x_idx_l1-x_idx_c,2);
v16st_src_p1.s23=(y_idx_p1<0||x_idx_l0<0)?v2st_border_value:VLOAD(src_p1+x_idx_l0-x_idx_c,2);
v16st_src_p1.s45=(y_idx_p1<0)?v2st_border_value:VLOAD(src_p1,2);
v16st_src_p1.s67=(y_idx_p1<0||x_idx_r0<0)?v2st_border_value:VLOAD(src_p1+x_idx_r0-x_idx_c,2);
v16st_src_p1.s89=(y_idx_p1<0||x_idx_r1<0)?v2st_border_value:VLOAD(src_p1+x_idx_r1-x_idx_c,2);
v16st_src_p0.s01=(y_idx_p0<0||x_idx_l1<0)?v2st_border_value:VLOAD(src_p0+x_idx_l1-x_idx_c,2);
v16st_src_p0.s23=(y_idx_p0<0||x_idx_l0<0)?v2st_border_value:VLOAD(src_p0+x_idx_l0-x_idx_c,2);
v16st_src_p0.s45=(y_idx_p0<0)?v2st_border_value:VLOAD(src_p0,2);
v16st_src_p0.s67=(y_idx_p0<0||x_idx_r0<0)?v2st_border_value:VLOAD(src_p0+x_idx_r0-x_idx_c,2);
v16st_src_p0.s89=(y_idx_p0<0||x_idx_r1<0)?v2st_border_value:VLOAD(src_p0+x_idx_r1-x_idx_c,2);
v16st_src_c.s01=(x_idx_l1<0)?v2st_border_value:VLOAD(src_c+x_idx_l1-x_idx_c,2);
v16st_src_c.s23=(x_idx_l0<0)?v2st_border_value:VLOAD(src_c+x_idx_l0-x_idx_c,2);
v16st_src_c.s45=VLOAD(src_c,2);
v16st_src_c.s67=(x_idx_r0<0)?v2st_border_value:VLOAD(src_c+x_idx_r0-x_idx_c,2);
v16st_src_c.s89=(x_idx_r1<0)?v2st_border_value:VLOAD(src_c+x_idx_r1-x_idx_c,2);
v16st_src_n0.s01=(y_idx_n0<0||x_idx_l1<0)?v2st_border_value:VLOAD(src_n0+x_idx_l1-x_idx_c,2);
v16st_src_n0.s23=(y_idx_n0<0||x_idx_l0<0)?v2st_border_value:VLOAD(src_n0+x_idx_l0-x_idx_c,2);
v16st_src_n0.s45=(y_idx_n0<0)?v2st_border_value:VLOAD(src_n0,2);
v16st_src_n0.s67=(y_idx_n0<0||x_idx_r0<0)?v2st_border_value:VLOAD(src_n0+x_idx_r0-x_idx_c,2);
v16st_src_n0.s89=(y_idx_n0<0||x_idx_r1<0)?v2st_border_value:VLOAD(src_n0+x_idx_r1-x_idx_c,2);
v16st_src_n1.s01=(y_idx_n1<0||x_idx_l1<0)?v2st_border_value:VLOAD(src_n1+x_idx_l1-x_idx_c,2);
v16st_src_n1.s23=(y_idx_n1<0||x_idx_l0<0)?v2st_border_value:VLOAD(src_n1+x_idx_l0-x_idx_c,2);
v16st_src_n1.s45=(y_idx_n1<0)?v2st_border_value:VLOAD(src_n1,2);
v16st_src_n1.s67=(y_idx_n1<0||x_idx_r0<0)?v2st_border_value:VLOAD(src_n1+x_idx_r0-x_idx_c,2);
v16st_src_n1.s89=(y_idx_n1<0||x_idx_r1<0)?v2st_border_value:VLOAD(src_n1+x_idx_r1-x_idx_c,2);
#else
x_idx_l1-=x_idx_c;
x_idx_l0-=x_idx_c;
x_idx_r0-=x_idx_c;
x_idx_r1-=x_idx_c;
v16st_src_p1.s01=VLOAD(src_p1+x_idx_l1,2),v16st_src_p1.s23=VLOAD(src_p1+x_idx_l0,2),v16st_src_p1.S45=VLOAD(src_p1,2),v16st_src_p1.s67=VLOAD(src_p1+x_idx_r0,2),v16st_src_p1.s89=VLOAD(src_p1+x_idx_r1,2);
v16st_src_p0.s01=VLOAD(src_p0+x_idx_l1,2),v16st_src_p0.s23=VLOAD(src_p0+x_idx_l0,2),v16st_src_p0.S45=VLOAD(src_p0,2),v16st_src_p0.s67=VLOAD(src_p0+x_idx_r0,2),v16st_src_p0.s89=VLOAD(src_p0+x_idx_r1,2);
v16st_src_c.s01=VLOAD(src_c+x_idx_l1,2),v16st_src_c.s23=VLOAD(src_c+x_idx_l0,2),v16st_src_c.S45=VLOAD(src_c,2),v16st_src_c.s67=VLOAD(src_c+x_idx_r0,2),v16st_src_c.s89=VLOAD(src_c+x_idx_r1,2);
v16st_src_n0.s01=VLOAD(src_n0+x_idx_l1,2),v16st_src_n0.s23=VLOAD(src_n0+x_idx_l0,2),v16st_src_n0.S45=VLOAD(src_n0,2),v16st_src_n0.s67=VLOAD(src_n0+x_idx_r0,2),v16st_src_n0.s89=VLOAD(src_n0+x_idx_r1,2);
v16st_src_n1.s01=VLOAD(src_n1+x_idx_l1,2),v16st_src_n1.s23=VLOAD(src_n1+x_idx_l0,2),v16st_src_n1.S45=VLOAD(src_n1,2),v16st_src_n1.s67=VLOAD(src_n1+x_idx_r0,2),v16st_src_n1.s89=VLOAD(src_n1+x_idx_r1,2);
#endif
v16it_src_p1=GAUSSIAN_CONVERT(v16st_src_p1,V16InterType);
v16it_src_p0=GAUSSIAN_CONVERT(v16st_src_p0,V16InterType);
v16it_src_c=GAUSSIAN_CONVERT(v16st_src_c,V16InterType);
v16it_src_n0=GAUSSIAN_CONVERT(v16st_src_n0,V16InterType);
v16it_src_n1=GAUSSIAN_CONVERT(v16st_src_n1,V16InterType);
v16it_sum=(v16it_src_p1+v16it_src_n1)*(V16InterType)filter[0]+(v16it_src_p0+v16it_src_n0)*(V16InterType)filter[1]+v16it_src_c*(V16InterType)filter[2];
v2it_result=(v16it_sum.s01+v16it_sum.s89)*(InterType)filter[0]+(v16it_sum.s23+v16it_sum.s67)*(InterType)filter[1]+v16it_sum.s45*(InterType)filter[2];
#if IS_FLOAT(InterType)
v2dt_result=CONVERT(v2it_result,V2Dt);
#else
v2dt_result=CONVERT_SAT((v2it_result+(V2InterType)(1<<(Q-1)))>>Q,V2Dt);
#endif
offset_dst=mad24(y_idx_c,ostep,x_idx_c);
VSTORE(v2dt_result,dst+offset_dst,2);
}

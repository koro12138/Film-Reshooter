kernel void BoxfilterRemain3x3C1(global St*src,int istep,
global Dt*dst,int ostep,
int width,int height,
int x_work_size,int y_work_size,
int main_width,struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
const int ksh=1;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int x_idx_l,x_idx_c,x_idx_r;
int y_idx_p,y_idx_c,y_idx_n;
int offset_dst;
St*src_row_p,*src_row_c,*src_row_n;
V3St v3st_src_p,v3st_src_c,v3st_src_n;
V3InterType v3it_src_p,v3it_src_c,v3it_src_n,v3it_sum;
Dt dt_result;
y_idx_c=gy;
y_idx_p=TOP_BORDER_IDX(gy-1);
y_idx_n=BOTTOM_BORDER_IDX(gy+1,height);
x_idx_c=(gx>=ksh)*main_width+gx;
x_idx_l=LEFT_BORDER_IDX(x_idx_c-1);
x_idx_r=RIGHT_BORDER_IDX(x_idx_c+1,width);
src_row_p=src+mad24(y_idx_p,istep,x_idx_c);
src_row_c=src+mad24(y_idx_c,istep,x_idx_c);
src_row_n=src+mad24(y_idx_n,istep,x_idx_c);
#if BORDER_CONSTANT
St value=(St)border_value.val[0];
v3st_src_p.s0=(y_idx_p<0||x_idx_l<0)?value:src_row_p[x_idx_l-x_idx_c];
v3st_src_p.s1=(y_idx_p<0)?value:src_row_p[0];
v3st_src_p.s2=(y_idx_p<0||x_idx_r<0)?value:src_row_p[x_idx_r-x_idx_c];
v3st_src_c.s0=(x_idx_l<0)?value:src_row_c[x_idx_l-x_idx_c];
v3st_src_c.s1=src_row_c[0];
v3st_src_c.s2=(x_idx_r<0)?value:src_row_c[x_idx_r-x_idx_c];
v3st_src_n.s0=(y_idx_n<0||x_idx_l<0)?value:src_row_n[x_idx_l-x_idx_c];
v3st_src_n.s1=(y_idx_n<0)?value:src_row_n[0];
v3st_src_n.s2=(y_idx_n<0||x_idx_r<0)?value:src_row_n[x_idx_r-x_idx_c];
#else
x_idx_l-=x_idx_c;
x_idx_r-=x_idx_c;
v3st_src_p.s0=src_row_p[x_idx_l],v3st_src_p.s1=src_row_p[0],v3st_src_p.s2=src_row_p[x_idx_r];
v3st_src_c.s0=src_row_c[x_idx_l],v3st_src_c.s1=src_row_c[0],v3st_src_c.s2=src_row_c[x_idx_r];
v3st_src_n.s0=src_row_n[x_idx_l],v3st_src_n.s1=src_row_n[0],v3st_src_n.s2=src_row_n[x_idx_r];
#endif
v3it_src_p=BOXFILTER_CONVERT(v3st_src_p,V3InterType);
v3it_src_c=BOXFILTER_CONVERT(v3st_src_c,V3InterType);
v3it_src_n=BOXFILTER_CONVERT(v3st_src_n,V3InterType);
v3it_sum=v3it_src_p+v3it_src_c+v3it_src_n;
dt_result=CONVERT(SUM_REDUCE(v3it_sum,3)/9,Dt);
offset_dst=mad24(y_idx_c,ostep,x_idx_c);
dst[offset_dst]=dt_result;
}

kernel void BoxfilterRemain3x3C3(global St*src,int istep,
global Dt*dst,int ostep,
int width,int height,
int x_work_size,int y_work_size,
int main_width,struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
const int ksh=1;
const int channel=3;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int x_idx_l,x_idx_c,x_idx_r;
int y_idx_p,y_idx_c,y_idx_n;
int offset_dst;
St*src_row_p,*src_row_c,*src_row_n;
V16St v16st_src_p,v16st_src_c,v16st_src_n;
V16InterType v16it_src_p,v16it_src_c,v16it_src_n,v16it_sum;
V3Dt v3dt_result;
y_idx_c=gy;
y_idx_p=TOP_BORDER_IDX(gy-1);
y_idx_n=BOTTOM_BORDER_IDX(gy+1,height);
x_idx_c=(gx>=ksh)*main_width+gx;
x_idx_l=LEFT_BORDER_IDX(x_idx_c-1)*channel;
x_idx_r=RIGHT_BORDER_IDX(x_idx_c+1,width)*channel;
x_idx_c*=channel;
src_row_p=src+mad24(y_idx_p,istep,x_idx_c);
src_row_c=src+mad24(y_idx_c,istep,x_idx_c);
src_row_n=src+mad24(y_idx_n,istep,x_idx_c);
#if BORDER_CONSTANT
V3St v3st_border_value={(St)border_value.val[0],(St)border_value.val[1],(St)border_value.val[2]};
v16st_src_p.s012=(y_idx_p<0||x_idx_l<0)?v3st_border_value:VLOAD(src_row_p+x_idx_l-x_idx_c,3);
v16st_src_p.s345=(y_idx_p<0)?v3st_border_value:VLOAD(src_row_p,3);
v16st_src_p.s678=(y_idx_p<0||x_idx_r<0)?v3st_border_value:VLOAD(src_row_p+x_idx_r-x_idx_c,3);
v16st_src_c.s012=(x_idx_l<0)?v3st_border_value:VLOAD(src_row_c+x_idx_l-x_idx_c,3);
v16st_src_c.s345=VLOAD(src_row_c,3);
v16st_src_c.s678=(x_idx_r<0)?v3st_border_value:VLOAD(src_row_c+x_idx_r-x_idx_c,3);
v16st_src_n.s012=(y_idx_n<0||x_idx_l<0)?v3st_border_value:VLOAD(src_row_n+x_idx_l-x_idx_c,3);
v16st_src_n.s345=(y_idx_n<0)?v3st_border_value:VLOAD(src_row_n,3);
v16st_src_n.s678=(y_idx_n<0||x_idx_r<0)?v3st_border_value:VLOAD(src_row_n+x_idx_r-x_idx_c,3);
#else
x_idx_l-=x_idx_c;
x_idx_r-=x_idx_c;
v16st_src_p.s012=VLOAD(src_row_p+x_idx_l,3),v16st_src_p.s345=VLOAD(src_row_p,3),v16st_src_p.s678=VLOAD(src_row_p+x_idx_r,3);
v16st_src_c.s012=VLOAD(src_row_c+x_idx_l,3),v16st_src_c.s345=VLOAD(src_row_c,3),v16st_src_c.s678=VLOAD(src_row_c+x_idx_r,3);
v16st_src_n.s012=VLOAD(src_row_n+x_idx_l,3),v16st_src_n.s345=VLOAD(src_row_n,3),v16st_src_n.s678=VLOAD(src_row_n+x_idx_r,3);
#endif
v16it_src_p=BOXFILTER_CONVERT(v16st_src_p,V16InterType);
v16it_src_c=BOXFILTER_CONVERT(v16st_src_c,V16InterType);
v16it_src_n=BOXFILTER_CONVERT(v16st_src_n,V16InterType);
v16it_sum=v16it_src_p+v16it_src_c+v16it_src_n;
v3dt_result=CONVERT((v16it_sum.s012+v16it_sum.s345+v16it_sum.s678)/(V3InterType)9,V3Dt);
offset_dst=mad24(y_idx_c,ostep,x_idx_c);
VSTORE(v3dt_result,dst+offset_dst,3);
}

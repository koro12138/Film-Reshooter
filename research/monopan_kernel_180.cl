kernel void PyrUpRemain5x5C1(global Tp*src,int istep,
int iheight,int iwidth,
global Tp*dst,int ostep,
int y_work_size,int x_work_size,
int main_width,
constant Kt*filter MAX_CONSTANT_SIZE)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
int ksh=1;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int x_idx_l,x_idx_c,x_idx_r;
int y_idx_p,y_idx_c,y_idx_n;
int offset_dst;
global Tp*src_row_p,*src_row_c,*src_row_n;
V3Tp v3tp_src_p,v3tp_src_c,v3tp_src_n;
V3It v3it_src_p,v3it_src_c,v3it_src_n,v3it_sum;
InterType it_result;
Tp tp_result;
y_idx_c=gy;
y_idx_p=TOP_BORDER_IDX(gy-1);
y_idx_n=clamp(gy+1,0,iheight-1);
x_idx_c=(gx>=ksh)*main_width+gx;
x_idx_l=LEFT_BORDER_IDX(x_idx_c-1);
x_idx_r=clamp(x_idx_c+1,0,iwidth-1);
src_row_p=src+mad24(y_idx_p,istep,0);
src_row_c=src+mad24(y_idx_c,istep,0);
src_row_n=src+mad24(y_idx_n,istep,0);
v3tp_src_p.s0=src_row_p[x_idx_l],v3tp_src_p.s1=src_row_p[x_idx_c],v3tp_src_p.s2=src_row_p[x_idx_r];
v3tp_src_c.s0=src_row_c[x_idx_l],v3tp_src_c.s1=src_row_c[x_idx_c],v3tp_src_c.s2=src_row_c[x_idx_r];
v3tp_src_n.s0=src_row_n[x_idx_l],v3tp_src_n.s1=src_row_n[x_idx_c],v3tp_src_n.s2=src_row_n[x_idx_r];
v3it_src_p=CONVERT(v3tp_src_p,V3It);
v3it_src_c=CONVERT(v3tp_src_c,V3It);
v3it_src_n=CONVERT(v3tp_src_n,V3It);
offset_dst=mad24(y_idx_c<<1,ostep,x_idx_c<<1);
v3it_sum=(v3it_src_p+v3it_src_n)*(V3It)filter[0]+v3it_src_c*(V3It)filter[2];
it_result=(v3it_sum.s0+v3it_sum.s2)*(InterType)filter[0]+v3it_sum.s1*(InterType)filter[2];
tp_result=PYRAMID_UP_CONVERT(it_result,(InterType)(1<<(Q-1)),Q,Tp);
dst[offset_dst]=tp_result;
it_result=(v3it_sum.s1+v3it_sum.s2)*(InterType)filter[1];
tp_result=PYRAMID_UP_CONVERT(it_result,(InterType)(1<<(Q-1)),Q,Tp);
dst[offset_dst+1]=tp_result;
v3it_sum=(v3it_src_c+v3it_src_n)*(V3It)filter[1];
it_result=(v3it_sum.s0+v3it_sum.s2)*(InterType)filter[0]+v3it_sum.s1*(InterType)filter[2];
tp_result=PYRAMID_UP_CONVERT(it_result,(InterType)(1<<(Q-1)),Q,Tp);
dst[offset_dst+ostep]=tp_result;
it_result=(v3it_sum.s1+v3it_sum.s2)*(InterType)filter[1];
tp_result=PYRAMID_UP_CONVERT(it_result,(InterType)(1<<(Q-1)),Q,Tp);
dst[offset_dst+ostep+1]=tp_result;
}

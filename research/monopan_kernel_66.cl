kernel void Filter2dRemain3x3C1(global Tp*src,int istep,
global Tp*dst,int ostep,
int height,int width,
int y_work_size,int x_work_size,
constant float*filter MAX_CONSTANT_SIZE,
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
global Tp*src_p,*src_c,*src_n;
V3Tp v3tp_src_p,v3tp_src_c,v3tp_src_n;
float3 v3f32_src_p,v3f32_src_c,v3f32_src_n;
float f32_result;
Tp tp_result;
y_idx_c=gy;
y_idx_p=TOP_BORDER_IDX(gy-1);
y_idx_n=BOTTOM_BORDER_IDX(gy+1,height);
x_idx_c=(gx>=ksh)*main_width+gx;
x_idx_l=LEFT_BORDER_IDX(x_idx_c-1);
x_idx_r=RIGHT_BORDER_IDX(x_idx_c+1,width);
src_p=src+mad24(y_idx_p,istep,x_idx_c);
src_c=src+mad24(y_idx_c,istep,x_idx_c);
src_n=src+mad24(y_idx_n,istep,x_idx_c);
#if BORDER_CONSTANT
Tp value=(Tp)border_value.val[0];
v3tp_src_p.s0=(y_idx_p<0||x_idx_l<0)?value:src_p[x_idx_l-x_idx_c];
v3tp_src_p.s1=(y_idx_p<0)?value:src_p[0];
v3tp_src_p.s2=(y_idx_p<0||x_idx_r<0)?value:src_p[x_idx_r-x_idx_c];
v3tp_src_c.s0=(x_idx_l<0)?value:src_c[x_idx_l-x_idx_c];
v3tp_src_c.s1=src_c[0];
v3tp_src_c.s2=(x_idx_r<0)?value:src_c[x_idx_r-x_idx_c];
v3tp_src_n.s0=(y_idx_n<0||x_idx_l<0)?value:src_n[x_idx_l-x_idx_c];
v3tp_src_n.s1=(y_idx_n<0)?value:src_n[0];
v3tp_src_n.s2=(y_idx_n<0||x_idx_r<0)?value:src_n[x_idx_r-x_idx_c];
#else
x_idx_l-=x_idx_c;
x_idx_r-=x_idx_c;
v3tp_src_p.s0=src_p[x_idx_l],v3tp_src_p.s1=src_p[0],v3tp_src_p.s2=src_p[x_idx_r];
v3tp_src_c.s0=src_c[x_idx_l],v3tp_src_c.s1=src_c[0],v3tp_src_c.s2=src_c[x_idx_r];
v3tp_src_n.s0=src_n[x_idx_l],v3tp_src_n.s1=src_n[0],v3tp_src_n.s2=src_n[x_idx_r];
#endif
v3f32_src_p=FILTER2D_CONVERT(v3tp_src_p,float3);
v3f32_src_c=FILTER2D_CONVERT(v3tp_src_c,float3);
v3f32_src_n=FILTER2D_CONVERT(v3tp_src_n,float3);
f32_result=(v3f32_src_p.s0*filter[0]+v3f32_src_p.s1*filter[1]+v3f32_src_p.s2*filter[2])+
(v3f32_src_c.s0*filter[3]+v3f32_src_c.s1*filter[4]+v3f32_src_c.s2*filter[5])+
(v3f32_src_n.s0*filter[6]+v3f32_src_n.s1*filter[7]+v3f32_src_n.s2*filter[8]);
tp_result=CONVERT_SAT(f32_result,Tp);
offset_dst=mad24(y_idx_c,ostep,x_idx_c);
dst[offset_dst]=tp_result;
}

kernel void Filter2dRemain3x3C2(global Tp*src,int istep,
global Tp*dst,int ostep,
int height,int width,
int y_work_size,int x_work_size,
constant float*filter MAX_CONSTANT_SIZE,
int main_width,struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
const int border=2;
const int ksh=border>>1;
const int channel=2;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int x_idx_l,x_idx_c,x_idx_r;
int y_idx_p,y_idx_c,y_idx_n;
int offset_dst;
global Tp*src_p,*src_c,*src_n;
V8Tp v8tp_src_p,v8tp_src_c,v8tp_src_n;
float8 v8f32_src_p,v8f32_src_c,v8f32_src_n;
float2 v2f32_result;
V2Tp v2tp_result;
y_idx_c=gy;
y_idx_p=TOP_BORDER_IDX(gy-1);
y_idx_n=BOTTOM_BORDER_IDX(gy+1,height);
x_idx_c=(gx>=ksh)*main_width+gx;
x_idx_l=LEFT_BORDER_IDX(x_idx_c-1)*channel;
x_idx_r=RIGHT_BORDER_IDX(x_idx_c+1,width)*channel;
x_idx_c*=channel;
src_p=src+mad24(y_idx_p,istep,x_idx_c);
src_c=src+mad24(y_idx_c,istep,x_idx_c);
src_n=src+mad24(y_idx_n,istep,x_idx_c);
#if BORDER_CONSTANT
V2Tp v2tp_border_value={(Tp)border_value.val[0],(Tp)border_value.val[1]};
v8tp_src_p.s01=(y_idx_p<0||x_idx_l<0)?v2tp_border_value:VLOAD(src_p+x_idx_l-x_idx_c,2);
v8tp_src_p.s23=(y_idx_p<0)?v2tp_border_value:VLOAD(src_p,2);
v8tp_src_p.s45=(y_idx_p<0||x_idx_r<0)?v2tp_border_value:VLOAD(src_p+x_idx_r-x_idx_c,2);
v8tp_src_c.s01=(x_idx_l<0)?v2tp_border_value:VLOAD(src_c+x_idx_l-x_idx_c,2);
v8tp_src_c.s23=VLOAD(src_c,2);
v8tp_src_c.s45=(x_idx_r<0)?v2tp_border_value:VLOAD(src_c+x_idx_r-x_idx_c,2);
v8tp_src_n.s01=(y_idx_n<0||x_idx_l<0)?v2tp_border_value:VLOAD(src_n+x_idx_l-x_idx_c,2);
v8tp_src_n.s23=(y_idx_n<0)?v2tp_border_value:VLOAD(src_n,2);
v8tp_src_n.s45=(y_idx_n<0||x_idx_r<0)?v2tp_border_value:VLOAD(src_n+x_idx_r-x_idx_c,2);
#else
x_idx_l-=x_idx_c;
x_idx_r-=x_idx_c;
v8tp_src_p.s01=VLOAD(src_p+x_idx_l,2),v8tp_src_p.s23=VLOAD(src_p,2),v8tp_src_p.s45=VLOAD(src_p+x_idx_r,2);
v8tp_src_c.s01=VLOAD(src_c+x_idx_l,2),v8tp_src_c.s23=VLOAD(src_c,2),v8tp_src_c.s45=VLOAD(src_c+x_idx_r,2);
v8tp_src_n.s01=VLOAD(src_n+x_idx_l,2),v8tp_src_n.s23=VLOAD(src_n,2),v8tp_src_n.s45=VLOAD(src_n+x_idx_r,2);
#endif
v8f32_src_p=FILTER2D_CONVERT(v8tp_src_p,float8);
v8f32_src_c=FILTER2D_CONVERT(v8tp_src_c,float8);
v8f32_src_n=FILTER2D_CONVERT(v8tp_src_n,float8);
v2f32_result=(v8f32_src_p.s01*(float2)filter[0]+v8f32_src_p.s23*(float2)filter[1]+v8f32_src_p.s45*(float2)filter[2])+
(v8f32_src_c.s01*(float2)filter[3]+v8f32_src_c.s23*(float2)filter[4]+v8f32_src_c.s45*(float2)filter[5])+
(v8f32_src_n.s01*(float2)filter[6]+v8f32_src_n.s23*(float2)filter[7]+v8f32_src_n.s45*(float2)filter[8]);
v2tp_result=CONVERT_SAT(v2f32_result,V2Tp);
offset_dst=mad24(y_idx_c,ostep,x_idx_c);
VSTORE(v2tp_result,dst+offset_dst,2);
}

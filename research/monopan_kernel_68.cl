kernel void Filter2dRemain3x3C3(global Tp*src,int istep,
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
const int channel=3;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int x_idx_l,x_idx_c,x_idx_r;
int y_idx_p,y_idx_c,y_idx_n;
int offset_dst;
global Tp*src_p,*src_c,*src_n;
V16Tp v16tp_src_p,v16tp_src_c,v16tp_src_n;
float16 v16f32_src_p,v16f32_src_c,v16f32_src_n,v16f32_sum;
float3 v3f32_result;
V3Tp v3tp_result;
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
V3Tp v3tp_border_value={(Tp)border_value.val[0],(Tp)border_value.val[1],(Tp)border_value.val[2]};
v16tp_src_p.s012=(y_idx_p<0||x_idx_l<0)?v3tp_border_value:VLOAD(src_p+x_idx_l-x_idx_c,3);
v16tp_src_p.s345=(y_idx_p<0)?v3tp_border_value:VLOAD(src_p,3);
v16tp_src_p.s678=(y_idx_p<0||x_idx_r<0)?v3tp_border_value:VLOAD(src_p+x_idx_r-x_idx_c,3);
v16tp_src_c.s012=(x_idx_l<0)?v3tp_border_value:VLOAD(src_c+x_idx_l-x_idx_c,3);
v16tp_src_c.s345=VLOAD(src_c,3);
v16tp_src_c.s678=(x_idx_r<0)?v3tp_border_value:VLOAD(src_c+x_idx_r-x_idx_c,3);
v16tp_src_n.s012=(y_idx_n<0||x_idx_l<0)?v3tp_border_value:VLOAD(src_n+x_idx_l-x_idx_c,3);
v16tp_src_n.s345=(y_idx_n<0)?v3tp_border_value:VLOAD(src_n,3);
v16tp_src_n.s678=(y_idx_n<0||x_idx_r<0)?v3tp_border_value:VLOAD(src_n+x_idx_r-x_idx_c,3);
#else
x_idx_l-=x_idx_c;
x_idx_r-=x_idx_c;
v16tp_src_p.s012=VLOAD(src_p+x_idx_l,3),v16tp_src_p.s345=VLOAD(src_p,3),v16tp_src_p.s678=VLOAD(src_p+x_idx_r,3);
v16tp_src_c.s012=VLOAD(src_c+x_idx_l,3),v16tp_src_c.s345=VLOAD(src_c,3),v16tp_src_c.s678=VLOAD(src_c+x_idx_r,3);
v16tp_src_n.s012=VLOAD(src_n+x_idx_l,3),v16tp_src_n.s345=VLOAD(src_n,3),v16tp_src_n.s678=VLOAD(src_n+x_idx_r,3);
#endif
v16f32_src_p=FILTER2D_CONVERT(v16tp_src_p,float16);
v16f32_src_c=FILTER2D_CONVERT(v16tp_src_c,float16);
v16f32_src_n=FILTER2D_CONVERT(v16tp_src_n,float16);
v3f32_result=(v16f32_src_p.s012*(float3)filter[0]+v16f32_src_p.s345*(float3)filter[1]+v16f32_src_p.s678*(float3)filter[2])+
(v16f32_src_c.s012*(float3)filter[3]+v16f32_src_c.s345*(float3)filter[4]+v16f32_src_c.s678*(float3)filter[5])+
(v16f32_src_n.s012*(float3)filter[6]+v16f32_src_n.s345*(float3)filter[7]+v16f32_src_n.s678*(float3)filter[8]);
v3tp_result=CONVERT_SAT(v3f32_result,V3Tp);
offset_dst=mad24(y_idx_c,ostep,x_idx_c);
VSTORE(v3tp_result,dst+offset_dst,3);
}

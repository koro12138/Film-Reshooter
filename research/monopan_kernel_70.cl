kernel void Filter2dRemain5x5C2(global Tp*src,int istep,
global Tp*dst,int ostep,
int height,int width,
int y_work_size,int x_work_size,
constant float*filter MAX_CONSTANT_SIZE,
int main_width,struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
const int ksh=2;
const int channel=2;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int x_idx_l1,x_idx_l0,x_idx_c,x_idx_r0,x_idx_r1;
int y_idx_p1,y_idx_p0,y_idx_c,y_idx_n0,y_idx_n1;
int offset_dst;
global Tp*src_p1,*src_p0,*src_c,*src_n0,*src_n1;
V16Tp v16tp_src_p1,v16tp_src_p0,v16tp_src_c,v16tp_src_n0,v16tp_src_n1;
float16 v16f32_src_p1,v16f32_src_p0,v16f32_src_c,v16f32_src_n0,v16f32_src_n1;
float2 v2f32_result;
V2Tp v2tp_result;
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
V2Tp v2tp_border_value={(Tp)border_value.val[0],(Tp)border_value.val[1]};
v16tp_src_p1.s01=(y_idx_p1<0||x_idx_l1<0)?v2tp_border_value:VLOAD(src_p1+x_idx_l1-x_idx_c,2);
v16tp_src_p1.s23=(y_idx_p1<0||x_idx_l0<0)?v2tp_border_value:VLOAD(src_p1+x_idx_l0-x_idx_c,2);
v16tp_src_p1.s45=(y_idx_p1<0)?v2tp_border_value:VLOAD(src_p1,2);
v16tp_src_p1.s67=(y_idx_p1<0||x_idx_r0<0)?v2tp_border_value:VLOAD(src_p1+x_idx_r0-x_idx_c,2);
v16tp_src_p1.s89=(y_idx_p1<0||x_idx_r1<0)?v2tp_border_value:VLOAD(src_p1+x_idx_r1-x_idx_c,2);
v16tp_src_p0.s01=(y_idx_p0<0||x_idx_l1<0)?v2tp_border_value:VLOAD(src_p0+x_idx_l1-x_idx_c,2);
v16tp_src_p0.s23=(y_idx_p0<0||x_idx_l0<0)?v2tp_border_value:VLOAD(src_p0+x_idx_l0-x_idx_c,2);
v16tp_src_p0.s45=(y_idx_p0<0)?v2tp_border_value:VLOAD(src_p0,2);
v16tp_src_p0.s67=(y_idx_p0<0||x_idx_r0<0)?v2tp_border_value:VLOAD(src_p0+x_idx_r0-x_idx_c,2);
v16tp_src_p0.s89=(y_idx_p0<0||x_idx_r1<0)?v2tp_border_value:VLOAD(src_p0+x_idx_r1-x_idx_c,2);
v16tp_src_c.s01=(x_idx_l1<0)?v2tp_border_value:VLOAD(src_c+x_idx_l1-x_idx_c,2);
v16tp_src_c.s23=(x_idx_l0<0)?v2tp_border_value:VLOAD(src_c+x_idx_l0-x_idx_c,2);
v16tp_src_c.s45=VLOAD(src_c,2);
v16tp_src_c.s67=(x_idx_r0<0)?v2tp_border_value:VLOAD(src_c+x_idx_r0-x_idx_c,2);
v16tp_src_c.s89=(x_idx_r1<0)?v2tp_border_value:VLOAD(src_c+x_idx_r1-x_idx_c,2);
v16tp_src_n0.s01=(y_idx_n0<0||x_idx_l1<0)?v2tp_border_value:VLOAD(src_n0+x_idx_l1-x_idx_c,2);
v16tp_src_n0.s23=(y_idx_n0<0||x_idx_l0<0)?v2tp_border_value:VLOAD(src_n0+x_idx_l0-x_idx_c,2);
v16tp_src_n0.s45=(y_idx_n0<0)?v2tp_border_value:VLOAD(src_n0,2);
v16tp_src_n0.s67=(y_idx_n0<0||x_idx_r0<0)?v2tp_border_value:VLOAD(src_n0+x_idx_r0-x_idx_c,2);
v16tp_src_n0.s89=(y_idx_n0<0||x_idx_r1<0)?v2tp_border_value:VLOAD(src_n0+x_idx_r1-x_idx_c,2);
v16tp_src_n1.s01=(y_idx_n1<0||x_idx_l1<0)?v2tp_border_value:VLOAD(src_n1+x_idx_l1-x_idx_c,2);
v16tp_src_n1.s23=(y_idx_n1<0||x_idx_l0<0)?v2tp_border_value:VLOAD(src_n1+x_idx_l0-x_idx_c,2);
v16tp_src_n1.s45=(y_idx_n1<0)?v2tp_border_value:VLOAD(src_n1,2);
v16tp_src_n1.s67=(y_idx_n1<0||x_idx_r0<0)?v2tp_border_value:VLOAD(src_n1+x_idx_r0-x_idx_c,2);
v16tp_src_n1.s89=(y_idx_n1<0||x_idx_r1<0)?v2tp_border_value:VLOAD(src_n1+x_idx_r1-x_idx_c,2);
#else
x_idx_l1-=x_idx_c;
x_idx_l0-=x_idx_c;
x_idx_r0-=x_idx_c;
x_idx_r1-=x_idx_c;
v16tp_src_p1.s01=VLOAD(src_p1+x_idx_l1,2),v16tp_src_p1.s23=VLOAD(src_p1+x_idx_l0,2),v16tp_src_p1.S45=VLOAD(src_p1,2),v16tp_src_p1.s67=VLOAD(src_p1+x_idx_r0,2),v16tp_src_p1.s89=VLOAD(src_p1+x_idx_r1,2);
v16tp_src_p0.s01=VLOAD(src_p0+x_idx_l1,2),v16tp_src_p0.s23=VLOAD(src_p0+x_idx_l0,2),v16tp_src_p0.S45=VLOAD(src_p0,2),v16tp_src_p0.s67=VLOAD(src_p0+x_idx_r0,2),v16tp_src_p0.s89=VLOAD(src_p0+x_idx_r1,2);
v16tp_src_c.s01=VLOAD(src_c+x_idx_l1,2),v16tp_src_c.s23=VLOAD(src_c+x_idx_l0,2),v16tp_src_c.S45=VLOAD(src_c,2),v16tp_src_c.s67=VLOAD(src_c+x_idx_r0,2),v16tp_src_c.s89=VLOAD(src_c+x_idx_r1,2);
v16tp_src_n0.s01=VLOAD(src_n0+x_idx_l1,2),v16tp_src_n0.s23=VLOAD(src_n0+x_idx_l0,2),v16tp_src_n0.S45=VLOAD(src_n0,2),v16tp_src_n0.s67=VLOAD(src_n0+x_idx_r0,2),v16tp_src_n0.s89=VLOAD(src_n0+x_idx_r1,2);
v16tp_src_n1.s01=VLOAD(src_n1+x_idx_l1,2),v16tp_src_n1.s23=VLOAD(src_n1+x_idx_l0,2),v16tp_src_n1.S45=VLOAD(src_n1,2),v16tp_src_n1.s67=VLOAD(src_n1+x_idx_r0,2),v16tp_src_n1.s89=VLOAD(src_n1+x_idx_r1,2);
#endif
v16f32_src_p1=FILTER2D_CONVERT(v16tp_src_p1,float16);
v16f32_src_p0=FILTER2D_CONVERT(v16tp_src_p0,float16);
v16f32_src_c=FILTER2D_CONVERT(v16tp_src_c,float16);
v16f32_src_n0=FILTER2D_CONVERT(v16tp_src_n0,float16);
v16f32_src_n1=FILTER2D_CONVERT(v16tp_src_n1,float16);
v2f32_result=(v16f32_src_p1.s01*(float2)filter[0]+v16f32_src_p1.s23*(float2)filter[1]+v16f32_src_p1.s45*(float2)filter[2]+v16f32_src_p1.s67*(float2)filter[3]+v16f32_src_p1.s89*(float2)filter[4])+
(v16f32_src_p0.s01*(float2)filter[5]+v16f32_src_p0.s23*(float2)filter[6]+v16f32_src_p0.s45*(float2)filter[7]+v16f32_src_p0.s67*(float2)filter[8]+v16f32_src_p0.s89*(float2)filter[9])+
(v16f32_src_c.s01*(float2)filter[10]+v16f32_src_c.s23*(float2)filter[11]+v16f32_src_c.s45*(float2)filter[12]+v16f32_src_c.s67*(float2)filter[13]+v16f32_src_c.s89*(float2)filter[14])+
(v16f32_src_n0.s01*(float2)filter[15]+v16f32_src_n0.s23*(float2)filter[16]+v16f32_src_n0.s45*(float2)filter[17]+v16f32_src_n0.s67*(float2)filter[18]+v16f32_src_n0.s89*(float2)filter[19])+
(v16f32_src_n1.s01*(float2)filter[20]+v16f32_src_n1.s23*(float2)filter[21]+v16f32_src_n1.s45*(float2)filter[22]+v16f32_src_n1.s67*(float2)filter[23]+v16f32_src_n1.s89*(float2)filter[24]);
v2tp_result=CONVERT_SAT(v2f32_result,V2Tp);
offset_dst=mad24(y_idx_c,ostep,x_idx_c);
VSTORE(v2tp_result,dst+offset_dst,2);
}

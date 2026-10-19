kernel void SobelRemain1x1C3(global St*src,int istep,
global Dt*dst,int ostep,
int height,int width,float scale,
int y_work_size,int x_work_size,
int main_width,struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
int border=2;
int ksh=border>>1;
int channel=3;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
#if DX>0
int x_idx_l,x_idx_c,x_idx_r;
int y_idx_c;
int offset_dst;
global St*src_row;
V16St v16st_src;
V16InterType v16it_src;
V3InterType v3it_result;
V3Dt v3dt_result;
y_idx_c=gy;
x_idx_c=(gx>=ksh)*main_width+gx;
x_idx_l=LEFT_BORDER_IDX(x_idx_c-1)*channel;
x_idx_r=RIGHT_BORDER_IDX(x_idx_c+1,width)*channel;
x_idx_c*=channel;
src_row=src+mad24(y_idx_c,istep,x_idx_c);
#if BORDER_CONSTANT
V3St v3st_border_value={(St)border_value.val[0],(St)border_value.val[1],(St)border_value.val[2]};
v16st_src.s012=(x_idx_l<0)?v3st_border_value:VLOAD(src_row+x_idx_l-x_idx_c,3);
v16st_src.s345=VLOAD(src_row,3);
v16st_src.s678=(x_idx_r<0)?v3st_border_value:VLOAD(src_row+x_idx_r-x_idx_c,3);
#else
x_idx_l-=x_idx_c;
x_idx_r-=x_idx_c;
v16st_src.s012=VLOAD(src_row+x_idx_l,3),v16st_src.s345=VLOAD(src_row,3),v16st_src.s678=VLOAD(src_row+x_idx_r,3);
#endif
v16it_src=SOBEL_CONVERT(v16st_src,V16InterType);
#if 1==DX
v3it_result=v16it_src.s678-v16it_src.s012;
#else
v3it_result=(v16it_src.s012+v16it_src.s678)-v16it_src.s345*(V3InterType)2;
#endif
#else
int x_idx_c;
int y_idx_p,y_idx_c,y_idx_n;
int offset_dst;
global St*src_p,*src_c,*src_n;
V3St v3st_src_p,v3st_src_c,v3st_src_n;
V3InterType v3it_src_p,v3it_src_c,v3it_src_n;
V3InterType v3it_result;
V3Dt v3dt_result;
y_idx_c=gy;
y_idx_p=TOP_BORDER_IDX(gy-1);
y_idx_n=BOTTOM_BORDER_IDX(gy+1,height);
x_idx_c=(gx>=ksh)*main_width+gx;
x_idx_c*=channel;
src_p=src+mad24(y_idx_p,istep,x_idx_c);
src_c=src+mad24(y_idx_c,istep,x_idx_c);
src_n=src+mad24(y_idx_n,istep,x_idx_c);
#if BORDER_CONSTANT
V3St v3st_border_value={(St)border_value.val[0],(St)border_value.val[1],(St)border_value.val[2]};
v3st_src_p=(y_idx_p<0)?v3st_border_value:VLOAD(src_p,3);
v3st_src_c=VLOAD(src_c,3);
v3st_src_n=(y_idx_n<0)?v3st_border_value:VLOAD(src_n,3);
#else
v3st_src_p=VLOAD(src_p,3);
v3st_src_c=VLOAD(src_c,3);
v3st_src_n=VLOAD(src_n,3);
#endif
v3it_src_p=SOBEL_CONVERT(v3st_src_p,V3InterType);
v3it_src_c=SOBEL_CONVERT(v3st_src_c,V3InterType);
v3it_src_n=SOBEL_CONVERT(v3st_src_n,V3InterType);
#if 1==DY
v3it_result=v3it_src_n-v3it_src_p;
#else
v3it_result=(v3it_src_p+v3it_src_n)-v3it_src_c*(V3InterType)2;
#endif
#endif
#if IS_FLOAT(InterType)
v3dt_result=CONVERT(v3it_result,V3Dt);
#else
v3dt_result=CONVERT_SAT(v3it_result,V3Dt);
#endif
#if WITH_SCALE
v3dt_result=CONVERT_SAT(CONVERT(v3dt_result,float3)*scale,V3Dt);
#endif
offset_dst=mad24(y_idx_c,ostep,x_idx_c);
VSTORE(v3dt_result,dst+offset_dst,3);
}

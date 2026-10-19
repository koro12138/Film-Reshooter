kernel void SobelRemain1x1C2(global St*src,int istep,
global Dt*dst,int ostep,
int height,int width,float scale,
int y_work_size,int x_work_size,
int main_width,struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
int border=2;
int ksh=border>>1;
int channel=2;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
#if DX>0
int x_idx_l,x_idx_c,x_idx_r;
int y_idx_c;
int offset_dst;
global St*src_row;
V8St v8st_src;
V8InterType v8it_src;
V2InterType v2it_result;
V2Dt v2dt_result;
y_idx_c=gy;
x_idx_c=(gx>=ksh)*main_width+gx;
x_idx_l=LEFT_BORDER_IDX(x_idx_c-1)*channel;
x_idx_r=RIGHT_BORDER_IDX(x_idx_c+1,width)*channel;
x_idx_c*=channel;
src_row=src+mad24(y_idx_c,istep,x_idx_c);
#if BORDER_CONSTANT
V2St v2st_border_value={(St)border_value.val[0],(St)border_value.val[1]};
v8st_src.s01=(x_idx_l<0)?v2st_border_value:VLOAD(src_row+x_idx_l-x_idx_c,2);
v8st_src.s23=VLOAD(src_row,2);
v8st_src.s45=(x_idx_r<0)?v2st_border_value:VLOAD(src_row+x_idx_r-x_idx_c,2);
#else
x_idx_l-=x_idx_c;
x_idx_r-=x_idx_c;
v8st_src.s01=VLOAD(src_row+x_idx_l,2),v8st_src.s23=VLOAD(src_row,2),v8st_src.s45=VLOAD(src_row+x_idx_r,2);
#endif
v8it_src=SOBEL_CONVERT(v8st_src,V8InterType);
#if 1==DX
v2it_result=v8it_src.s45-v8it_src.s01;
#else
v2it_result=(v8it_src.s01+v8it_src.s45)-v8it_src.s23*(V2InterType)2;
#endif
#else
int x_idx_c;
int y_idx_p,y_idx_c,y_idx_n;
int offset_dst;
global St*src_p,*src_c,*src_n;
V2St v2st_src_p,v2st_src_c,v2st_src_n;
V2InterType v2it_src_p,v2it_src_c,v2it_src_n;
V2InterType v2it_result;
V2Dt v2dt_result;
y_idx_c=gy;
y_idx_p=TOP_BORDER_IDX(gy-1);
y_idx_n=BOTTOM_BORDER_IDX(gy+1,height);
x_idx_c=(gx>=ksh)*main_width+gx;
x_idx_c*=channel;
src_p=src+mad24(y_idx_p,istep,x_idx_c);
src_c=src+mad24(y_idx_c,istep,x_idx_c);
src_n=src+mad24(y_idx_n,istep,x_idx_c);
#if BORDER_CONSTANT
V2St v2st_border_value={(St)border_value.val[0],(St)border_value.val[1]};
v2st_src_p=(y_idx_p<0)?v2st_border_value:VLOAD(src_p,2);
v2st_src_c=VLOAD(src_c,2);
v2st_src_n=(y_idx_n<0)?v2st_border_value:VLOAD(src_n,2);
#else
v2st_src_p=VLOAD(src_p,2);
v2st_src_c=VLOAD(src_c,2);
v2st_src_n=VLOAD(src_n,2);
#endif
v2it_src_p=SOBEL_CONVERT(v2st_src_p,V2InterType);
v2it_src_c=SOBEL_CONVERT(v2st_src_c,V2InterType);
v2it_src_n=SOBEL_CONVERT(v2st_src_n,V2InterType);
#if 1==DY
v2it_result=v2it_src_n-v2it_src_p;
#else
v2it_result=(v2it_src_p+v2it_src_n)-v2it_src_c*(V2InterType)2;
#endif
#endif
#if IS_FLOAT(InterType)
v2dt_result=CONVERT(v2it_result,V2Dt);
#else
v2dt_result=CONVERT_SAT(v2it_result,V2Dt);
#endif
#if WITH_SCALE
v2dt_result=CONVERT_SAT(CONVERT(v2dt_result,float2)*scale,V2Dt);
#endif
offset_dst=mad24(y_idx_c,ostep,x_idx_c);
VSTORE(v2dt_result,dst+offset_dst,2);
}

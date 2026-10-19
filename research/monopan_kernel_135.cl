kernel void SobelRemain1x1C1(global St*src,int istep,
global Dt*dst,int ostep,
int height,int width,float scale,
int y_work_size,int x_work_size,
int main_width,struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
int ksh=1;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
#if DX>0
int x_idx_l,x_idx_c,x_idx_r;
int y_idx_c;
int offset_dst;
global St*src_row;
V3St v3st_src;
V3InterType v3it_src;
InterType it_result;
Dt dt_result;
y_idx_c=gy;
x_idx_c=(gx>=ksh)*main_width+gx;
x_idx_l=LEFT_BORDER_IDX(x_idx_c-1);
x_idx_r=RIGHT_BORDER_IDX(x_idx_c+1,width);
src_row=src+mad24(y_idx_c,istep,x_idx_c);
#if BORDER_CONSTANT
St value=(St)border_value.val[0];
v3st_src.s0=(x_idx_l<0)?value:src_row[x_idx_l-x_idx_c];
v3st_src.s1=src_row[0];
v3st_src.s2=(x_idx_r<0)?value:src_row[x_idx_r-x_idx_c];
#else
x_idx_l-=x_idx_c;
x_idx_r-=x_idx_c;
v3st_src.s0=src_row[x_idx_l],v3st_src.s1=src_row[0],v3st_src.s2=src_row[x_idx_r];
#endif
v3it_src=SOBEL_CONVERT(v3st_src,V3InterType);
#if 1==DX
it_result=v3it_src.s2-v3it_src.s0;
#else
it_result=(v3it_src.s0+v3it_src.s2)-v3it_src.s1*(InterType)2;
#endif
#else
int x_idx_c;
int y_idx_p,y_idx_c,y_idx_n;
int offset_dst;
global St*src_p,*src_c,*src_n;
St st_src_p,st_src_c,st_src_n;
InterType it_src_p,it_src_c,it_src_n;
InterType it_result;
Dt dt_result;
y_idx_c=gy;
y_idx_p=TOP_BORDER_IDX(gy-1);
y_idx_n=BOTTOM_BORDER_IDX(gy+1,height);
x_idx_c=(gx>=ksh)*main_width+gx;
src_p=src+mad24(y_idx_p,istep,x_idx_c);
src_c=src+mad24(y_idx_c,istep,x_idx_c);
src_n=src+mad24(y_idx_n,istep,x_idx_c);
#if BORDER_CONSTANT
St value=(St)border_value.val[0];
st_src_p=(y_idx_p<0)?value:src_p[0];
st_src_c=src_c[0];
st_src_n=(y_idx_n<0)?value:src_n[0];
#else
st_src_p=src_p[0];
st_src_c=src_c[0];
st_src_n=src_n[0];
#endif
it_src_p=SOBEL_CONVERT(st_src_p,InterType);
it_src_c=SOBEL_CONVERT(st_src_c,InterType);
it_src_n=SOBEL_CONVERT(st_src_n,InterType);
#if 1==DY
it_result=it_src_n-it_src_p;
#else
it_result=(it_src_p+st_src_n)-it_src_c*(InterType)2;
#endif
#endif
#if IS_FLOAT(InterType)
dt_result=CONVERT(it_result,Dt);
#else
dt_result=CONVERT_SAT(it_result,Dt);
#endif
#if WITH_SCALE
dt_result=CONVERT_SAT(CONVERT(dt_result,float)*scale,Dt);
#endif
offset_dst=mad24(y_idx_c,ostep,x_idx_c);
dst[offset_dst]=dt_result;
}

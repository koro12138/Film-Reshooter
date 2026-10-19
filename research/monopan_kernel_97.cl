kernel void LaplacianMain3x3C3(global St*src,int istep,
global Dt*dst,int ostep,
int height,int y_work_size,int x_work_size,
struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
const int elem_counts=3;
const int ksh=1;
const int channel=3;
const int x_idx=gx*elem_counts*channel;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int y_idx_p,y_idx_c,y_idx_n;
int offset_src_p,offset_src_c,offset_src_n,offset_dst;
V16St v16it_src_p,v16it_src_n,v16it_src_c;
V16InterType v16it_sum_pn;
V8InterType v8it_result;
V8Dt v8dt_result;
InterType it_result;
Dt dt_result;
if(gy>=ksh&&gy<(height-ksh))
{
offset_src_p=mad24(gy-1,istep,x_idx);
offset_src_c=mad24(gy,istep,x_idx);
offset_src_n=mad24(gy+1,istep,x_idx);
v16it_src_p=VLOAD(src+offset_src_p,16);
v16it_src_n=VLOAD(src+offset_src_n,16);
v16it_src_c=VLOAD(src+offset_src_c,16);
}
else
{
y_idx_p=TOP_BORDER_IDX(gy-1);
y_idx_c=gy;
y_idx_n=BOTTOM_BORDER_IDX(gy+1,height);
offset_src_p=mad24(y_idx_p,istep,x_idx);
offset_src_c=mad24(y_idx_c,istep,x_idx);
offset_src_n=mad24(y_idx_n,istep,x_idx);
#if BORDER_CONSTANT
V3St v3it_border_value={(St)border_value.val[0],(St)border_value.val[1],(St)border_value.val[2]};
V16St v16it_border_value={v3it_border_value,v3it_border_value,v3it_border_value,v3it_border_value,v3it_border_value,v3it_border_value.s0};
v16it_src_p=(y_idx_p<0)?v16it_border_value:VLOAD(src+offset_src_p,16);
v16it_src_n=(y_idx_n<0)?v16it_border_value:VLOAD(src+offset_src_n,16);
#else
v16it_src_p=VLOAD(src+offset_src_p,16);
v16it_src_n=VLOAD(src+offset_src_n,16);
#endif
v16it_src_c=VLOAD(src+offset_src_c,16);
}
v16it_sum_pn=LAPLACIAN_CONVERT(v16it_src_p,V16InterType)+LAPLACIAN_CONVERT(v16it_src_n,V16InterType);
v8it_result=(v16it_sum_pn.s01234567+v16it_sum_pn.s6789ABCD)*(V8InterType)2+
LAPLACIAN_CONVERT(v16it_src_c.s3456789A,V8InterType)*(V8InterType)-8;
it_result=(v16it_sum_pn.s8+v16it_sum_pn.sE)*(InterType)2+
LAPLACIAN_CONVERT(v16it_src_c.sB,InterType)*(InterType)-8;
#if IS_FLOAT(InterType)
v8dt_result=CONVERT(v8it_result,V8Dt);
dt_result=CONVERT(it_result,Dt);
#else
v8dt_result=CONVERT_SAT(v8it_result,V8Dt);
dt_result=CONVERT_SAT(it_result,Dt);
#endif
offset_dst=mad24(gy,ostep,x_idx+ksh*channel);
VSTORE(v8dt_result,dst+offset_dst,8);
VSTORE(dt_result,dst+offset_dst+8,1);
}

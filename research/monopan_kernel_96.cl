kernel void LaplacianMain3x3C3(global St*src,int istep,
global Dt*dst,int ostep,
int height,int y_work_size,int x_work_size,
struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
const int elem_counts=6;
const int ksh=1;
const int channel=3;
const int x_idx=gx*elem_counts*channel;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int y_idx_p,y_idx_c,y_idx_n;
int offset_src_p,offset_src_c,offset_src_n,offset_dst;
V16InterType v16it_src_p,v16it_src_c,v16it_src_n;
V8InterType v8it_src_p,v8it_src_c,v8it_src_n;
V16InterType v16it_sum_pn,v16it_sum_pn_l,v16it_sum_c_l,v16it_result_l;
V8InterType v8it_sum_pn;
V2InterType v2it_sum_pn_r,v2it_sum_c_r,v2it_result_r;
V16Dt v16dt_result_l;
V2Dt v2dt_result_r;
if(gy>=ksh&&gy<(height-ksh))
{
offset_src_p=mad24(gy-1,istep,x_idx);
offset_src_c=mad24(gy,istep,x_idx);
offset_src_n=mad24(gy+1,istep,x_idx);
v16it_src_p=LAPLACIAN_CONVERT(VLOAD(src+offset_src_p,16),V16InterType);
v16it_src_c=LAPLACIAN_CONVERT(VLOAD(src+offset_src_c,16),V16InterType);
v16it_src_n=LAPLACIAN_CONVERT(VLOAD(src+offset_src_n,16),V16InterType);
v8it_src_p=LAPLACIAN_CONVERT(VLOAD(src+offset_src_p+16,8),V8InterType);
v8it_src_c=LAPLACIAN_CONVERT(VLOAD(src+offset_src_c+16,8),V8InterType);
v8it_src_n=LAPLACIAN_CONVERT(VLOAD(src+offset_src_n+16,8),V8InterType);
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
V3InterType v3it_border_value={(InterType)border_value.val[0],(InterType)border_value.val[1],(InterType)border_value.val[2]};
V16InterType v16it_border_value={v3it_border_value,v3it_border_value,v3it_border_value,v3it_border_value,v3it_border_value,v3it_border_value.s0};
V8InterType v8it_border_value={v3it_border_value.s12,v3it_border_value,v3it_border_value};
v16it_src_p=(y_idx_p<0)?v16it_border_value:LAPLACIAN_CONVERT(VLOAD(src+offset_src_p,16),V16InterType);
v16it_src_c=LAPLACIAN_CONVERT(VLOAD(src+offset_src_c,16),V16InterType);
v16it_src_n=(y_idx_n<0)?v16it_border_value:LAPLACIAN_CONVERT(VLOAD(src+offset_src_n,16),V16InterType);
v8it_src_p=(y_idx_p<0)?v8it_border_value:LAPLACIAN_CONVERT(VLOAD(src+offset_src_p+16,8),V8InterType);
v8it_src_c=LAPLACIAN_CONVERT(VLOAD(src+offset_src_c+16,8),V8InterType);
v8it_src_n=(y_idx_n<0)?v8it_border_value:LAPLACIAN_CONVERT(VLOAD(src+offset_src_n+16,8),V8InterType);
#else
v16it_src_p=LAPLACIAN_CONVERT(VLOAD(src+offset_src_p,16),V16InterType);
v16it_src_c=LAPLACIAN_CONVERT(VLOAD(src+offset_src_c,16),V16InterType);
v16it_src_n=LAPLACIAN_CONVERT(VLOAD(src+offset_src_n,16),V16InterType);
v8it_src_p=LAPLACIAN_CONVERT(VLOAD(src+offset_src_p+16,8),V8InterType);
v8it_src_c=LAPLACIAN_CONVERT(VLOAD(src+offset_src_c+16,8),V8InterType);
v8it_src_n=LAPLACIAN_CONVERT(VLOAD(src+offset_src_n+16,8),V8InterType);
#endif
}
v16it_sum_pn=v16it_src_p+v16it_src_n;
v8it_sum_pn=v8it_src_p+v8it_src_n;
v16it_sum_pn_l=v16it_sum_pn+(V16InterType)(v16it_sum_pn.s6789ABCD,v16it_sum_pn.sEF,v8it_sum_pn.s0123,v8it_sum_pn.s45);
v2it_sum_pn_r=(V2InterType)(v8it_sum_pn.s01+v8it_sum_pn.s67);
v16it_sum_c_l=(V16InterType)(v16it_src_c.s3456789A,v16it_src_c.sBCDE,v16it_src_c.sF,v8it_src_c.s012)*(V16InterType)-4;
v2it_sum_c_r=(V2InterType)v8it_src_c.s34*(V2InterType)-4;
v16it_result_l=(v16it_sum_pn_l+v16it_sum_c_l)*(V16InterType)2;
v2it_result_r=(v2it_sum_pn_r+v2it_sum_c_r)*(V2InterType)2;
#if IS_FLOAT(InterType)
v16dt_result_l=CONVERT(v16it_result_l,V16Dt);
v2dt_result_r=CONVERT(v2it_result_r,V2Dt);
#else
v16dt_result_l=CONVERT_SAT(v16it_result_l,V16Dt);
v2dt_result_r=CONVERT_SAT(v2it_result_r,V2Dt);
#endif
offset_dst=mad24(gy,ostep,x_idx+ksh*channel);
VSTORE(v16dt_result_l,dst+offset_dst,16);
VSTORE(v2dt_result_r,dst+offset_dst+16,2);
}

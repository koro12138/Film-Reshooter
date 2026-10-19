kernel void GaussianMain5x5C3(global St*src,int istep,
global Dt*dst,int ostep,
int height,int y_work_size,int x_work_size,
constant Kt*filter MAX_CONSTANT_SIZE,
struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
int elem_counts=4;
int ksh=2;
int channel=3;
int x_idx=gx*elem_counts*channel;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int offset_src_p1,offset_src_p0,offset_src_c,offset_src_n0,offset_src_n1;
int offset_dst;
V16InterType v16it_src_p1,v16it_src_p0,v16it_src_c,v16it_src_n0,v16it_src_n1,v16it_sum;
V16InterType v16it_sum_l1,v16it_sum_l0,v16it_sum_c,v16it_sum_r0,v16it_sum_r1,v16it_result;
V8InterType v8it_src_p1,v8it_src_p0,v8it_src_c,v8it_src_n0,v8it_src_n1,v8it_sum;
V8InterType v8it_result;
V4InterType v4it_result;
V8Dt v8dt_result;
V4Dt v4dt_result;
if(gy>=ksh&&gy<(height-ksh))
{
offset_src_p1=mad24(gy-2,istep,x_idx);
offset_src_p0=mad24(gy-1,istep,x_idx);
offset_src_c=mad24(gy,istep,x_idx);
offset_src_n0=mad24(gy+1,istep,x_idx);
offset_src_n1=mad24(gy+2,istep,x_idx);
v16it_src_p1=GAUSSIAN_CONVERT(VLOAD(src+offset_src_p1,16),V16InterType);
v8it_src_p1=GAUSSIAN_CONVERT(VLOAD(src+offset_src_p1+16,8),V8InterType);
v16it_src_p0=GAUSSIAN_CONVERT(VLOAD(src+offset_src_p0,16),V16InterType);
v8it_src_p0=GAUSSIAN_CONVERT(VLOAD(src+offset_src_p0+16,8),V8InterType);
v16it_src_c=GAUSSIAN_CONVERT(VLOAD(src+offset_src_c,16),V16InterType);
v8it_src_c=GAUSSIAN_CONVERT(VLOAD(src+offset_src_c+16,8),V8InterType);
v16it_src_n0=GAUSSIAN_CONVERT(VLOAD(src+offset_src_n0,16),V16InterType);
v8it_src_n0=GAUSSIAN_CONVERT(VLOAD(src+offset_src_n0+16,8),V8InterType);
v16it_src_n1=GAUSSIAN_CONVERT(VLOAD(src+offset_src_n1,16),V16InterType);
v8it_src_n1=GAUSSIAN_CONVERT(VLOAD(src+offset_src_n1+16,8),V8InterType);
}
else
{
int y_idx_p1,y_idx_p0,y_idx_c,y_idx_n0,y_idx_n1;
y_idx_p1=TOP_BORDER_IDX(gy-2);
y_idx_p0=TOP_BORDER_IDX(gy-1);
y_idx_c=gy;
y_idx_n0=BOTTOM_BORDER_IDX(gy+1,height);
y_idx_n1=BOTTOM_BORDER_IDX(gy+2,height);
offset_src_p1=mad24(y_idx_p1,istep,x_idx);
offset_src_p0=mad24(y_idx_p0,istep,x_idx);
offset_src_c=mad24(y_idx_c,istep,x_idx);
offset_src_n0=mad24(y_idx_n0,istep,x_idx);
offset_src_n1=mad24(y_idx_n1,istep,x_idx);
#if BORDER_CONSTANT
V3InterType v3it_border_value={(InterType)border_value.val[0],(InterType)border_value.val[1],(InterType)border_value.val[2]};
V16InterType v16it_border_value={v3it_border_value,v3it_border_value,v3it_border_value,v3it_border_value,v3it_border_value,v3it_border_value.s0};
V8InterType v8it_border_value={v3it_border_value.s12,v3it_border_value,v3it_border_value};
v16it_src_p1=y_idx_p1<0?v16it_border_value:GAUSSIAN_CONVERT(VLOAD(src+offset_src_p1,16),V16InterType);
v8it_src_p1=y_idx_p1<0?v8it_border_value:GAUSSIAN_CONVERT(VLOAD(src+offset_src_p1+16,8),V8InterType);
v16it_src_p0=y_idx_p0<0?v16it_border_value:GAUSSIAN_CONVERT(VLOAD(src+offset_src_p0,16),V16InterType);
v8it_src_p0=y_idx_p0<0?v8it_border_value:GAUSSIAN_CONVERT(VLOAD(src+offset_src_p0+16,8),V8InterType);
v16it_src_c=GAUSSIAN_CONVERT(VLOAD(src+offset_src_c,16),V16InterType);
v8it_src_c=GAUSSIAN_CONVERT(VLOAD(src+offset_src_c+16,8),V8InterType);
v16it_src_n0=y_idx_n0<0?v16it_border_value:GAUSSIAN_CONVERT(VLOAD(src+offset_src_n0,16),V16InterType);
v8it_src_n0=y_idx_n0<0?v8it_border_value:GAUSSIAN_CONVERT(VLOAD(src+offset_src_n0+16,8),V8InterType);
v16it_src_n1=y_idx_n1<0?v16it_border_value:GAUSSIAN_CONVERT(VLOAD(src+offset_src_n1,16),V16InterType);
v8it_src_n1=y_idx_n1<0?v8it_border_value:GAUSSIAN_CONVERT(VLOAD(src+offset_src_n1+16,8),V8InterType);
#else
v16it_src_p1=GAUSSIAN_CONVERT(VLOAD(src+offset_src_p1,16),V16InterType);
v8it_src_p1=GAUSSIAN_CONVERT(VLOAD(src+offset_src_p1+16,8),V8InterType);
v16it_src_p0=GAUSSIAN_CONVERT(VLOAD(src+offset_src_p0,16),V16InterType);
v8it_src_p0=GAUSSIAN_CONVERT(VLOAD(src+offset_src_p0+16,8),V8InterType);
v16it_src_c=GAUSSIAN_CONVERT(VLOAD(src+offset_src_c,16),V16InterType);
v8it_src_c=GAUSSIAN_CONVERT(VLOAD(src+offset_src_c+16,8),V8InterType);
v16it_src_n0=GAUSSIAN_CONVERT(VLOAD(src+offset_src_n0,16),V16InterType);
v8it_src_n0=GAUSSIAN_CONVERT(VLOAD(src+offset_src_n0+16,8),V8InterType);
v16it_src_n1=GAUSSIAN_CONVERT(VLOAD(src+offset_src_n1,16),V16InterType);
v8it_src_n1=GAUSSIAN_CONVERT(VLOAD(src+offset_src_n1+16,8),V8InterType);
#endif
}
v16it_sum=(v16it_src_p1+v16it_src_n1)*(V16InterType)filter[0]+(v16it_src_p0+v16it_src_n0)*(V16InterType)filter[1]+v16it_src_c*(V16InterType)filter[2];
v8it_sum=(v8it_src_p1+v8it_src_n1)*(V8InterType)filter[0]+(v8it_src_p0+v8it_src_n0)*(V8InterType)filter[1]+v8it_src_c*(V8InterType)filter[2];
v16it_sum_l1=v16it_sum;
v16it_sum_l0=(V16InterType){v16it_sum.s3456789A,v16it_sum.sBCDE,v16it_sum.sF,v8it_sum.s012};
v16it_sum_c=(V16InterType){v16it_sum.s6789ABCD,v16it_sum.sEF,v8it_sum.s01,v8it_sum.s2345};
v16it_sum_r0=(V16InterType){v16it_sum.s9ABC,v16it_sum.sDEF,v8it_sum.s01234567,v8it_sum.s0};
v16it_sum_r1=(V16InterType){v16it_sum.sCDEF,v8it_sum.s01234567,v8it_sum.s0123};
v16it_result=(v16it_sum_l1+v16it_sum_r1)*(V16InterType)filter[0]+(v16it_sum_l0+v16it_sum_r0)*(V16InterType)filter[1]+v16it_sum_c*(V16InterType)filter[2];
#if IS_FLOAT(InterType)
v8dt_result=CONVERT(v16it_result.s01234567,V8Dt);
v4dt_result=CONVERT(v16it_result.s89AB,V4Dt);
#else
v8dt_result=CONVERT_SAT((v16it_result.s01234567+(V8InterType)(1<<(Q-1)))>>Q,V8Dt);
v4dt_result=CONVERT_SAT((v16it_result.s89AB+(V4InterType)(1<<(Q-1)))>>Q,V4Dt);
#endif
offset_dst=mad24(gy,ostep,x_idx+ksh*channel);
VSTORE(v8dt_result,dst+offset_dst,8);
VSTORE(v4dt_result,dst+offset_dst+8,4);
}

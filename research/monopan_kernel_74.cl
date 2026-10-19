kernel void GaussianMain3x3C2(global St*src,int istep,
global Dt*dst,int ostep,
int height,int y_work_size,int x_work_size,
constant Kt*filter MAX_CONSTANT_SIZE,
struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
int elem_counts=6;
int ksh=1;
int channel=2;
int x_idx=gx*elem_counts*channel;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int offset_src_p,offset_src_c,offset_src_n,offset_dst;
V16InterType v16it_src_p,v16it_src_c,v16it_src_n;
V16InterType v16it_sum_l,v16it_sum_c,v16it_sum_r;
V16InterType v16it_result;
V16Dt v16dt_result;
if(gy>=ksh&&gy<(height-ksh))
{
offset_src_p=mad24(gy-1,istep,x_idx);
offset_src_c=mad24(gy,istep,x_idx);
offset_src_n=mad24(gy+1,istep,x_idx);
v16it_src_p=GAUSSIAN_CONVERT(VLOAD(src+offset_src_p,16),V16InterType);
v16it_src_c=GAUSSIAN_CONVERT(VLOAD(src+offset_src_c,16),V16InterType);
v16it_src_n=GAUSSIAN_CONVERT(VLOAD(src+offset_src_n,16),V16InterType);
}
else
{
int y_idx_p,y_idx_c,y_idx_n;
y_idx_p=TOP_BORDER_IDX(gy-1);
y_idx_c=gy;
y_idx_n=BOTTOM_BORDER_IDX(gy+1,height);
offset_src_p=mad24(y_idx_p,istep,x_idx);
offset_src_c=mad24(y_idx_c,istep,x_idx);
offset_src_n=mad24(y_idx_n,istep,x_idx);
#if BORDER_CONSTANT
V2InterType v2it_border_value={(InterType)border_value.val[0],(InterType)border_value.val[1]};
V16InterType v16it_border_value={v2it_border_value,v2it_border_value,v2it_border_value,v2it_border_value,
v2it_border_value,v2it_border_value,v2it_border_value,v2it_border_value};
v16it_src_p=(y_idx_p<0)?v16it_border_value:GAUSSIAN_CONVERT(VLOAD(src+offset_src_p,16),V16InterType);
v16it_src_c=GAUSSIAN_CONVERT(VLOAD(src+offset_src_c,16),V16InterType);
v16it_src_n=(y_idx_n<0)?v16it_border_value:GAUSSIAN_CONVERT(VLOAD(src+offset_src_n,16),V16InterType);
#else
v16it_src_p=GAUSSIAN_CONVERT(VLOAD(src+offset_src_p,16),V16InterType);
v16it_src_c=GAUSSIAN_CONVERT(VLOAD(src+offset_src_c,16),V16InterType);
v16it_src_n=GAUSSIAN_CONVERT(VLOAD(src+offset_src_n,16),V16InterType);
#endif
}
v16it_sum_l=(v16it_src_p+v16it_src_n)*(V16InterType)filter[0]+v16it_src_c*(V16InterType)filter[1];
v16it_sum_c=ROT_R(v16it_sum_l,16,14);
v16it_sum_r=ROT_R(v16it_sum_l,16,12);
v16it_result=(v16it_sum_l+v16it_sum_r)*(V16InterType)filter[0]+v16it_sum_c*(V16InterType)filter[1];
#if IS_FLOAT(InterType)
v16dt_result=CONVERT(v16it_result,V16Dt);
#else
v16dt_result=CONVERT_SAT((v16it_result+(V16InterType)(1<<(Q-1)))>>Q,V16Dt);
#endif
offset_dst=mad24(gy,ostep,x_idx+ksh*channel);
VSTORE(v16dt_result.s01234567,dst+offset_dst,8);
VSTORE(v16dt_result.s89AB,dst+offset_dst+8,4);
}

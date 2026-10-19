kernel void PyrUpMain5x5C1(global Tp*src,int istep,int iheight,
global Tp*dst,int ostep,
int y_work_size,int x_work_size,
constant Kt*filter MAX_CONSTANT_SIZE)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
int elem_counts=6;
int ksh=1;
int x_idx=gx*elem_counts;
if(gx>=x_work_size||(gy>=y_work_size))
{
return;
}
int offset_src_p,offset_src_c,offset_src_n,offset_dst;
V8It v8it_src_p,v8it_src_c,v8it_src_n;
V8It v8it_sum;
V4It v4it_result_even,v4it_result_odd;
V4Tp v4tp_result_even,v4tp_result_odd;
V8Tp v8tp_result;
V2It v2it_result_even,v2it_result_odd;
V2Tp v2tp_result_even,v2tp_result_odd;
V4Tp v4tp_result;
int y_idx_p,y_idx_c,y_idx_n;
y_idx_p=TOP_BORDER_IDX(gy-1);
y_idx_c=gy;
y_idx_n=clamp(gy+1,0,iheight-1);
offset_src_p=mad24(y_idx_p,istep,x_idx);
offset_src_c=mad24(y_idx_c,istep,x_idx);
offset_src_n=mad24(y_idx_n,istep,x_idx);
v8it_src_p=CONVERT(VLOAD(src+offset_src_p,8),V8It);
v8it_src_c=CONVERT(VLOAD(src+offset_src_c,8),V8It);
v8it_src_n=CONVERT(VLOAD(src+offset_src_n,8),V8It);
offset_dst=mad24(gy<<1,ostep,(x_idx+ksh)<<1);
v8it_sum=(v8it_src_p+v8it_src_n)*(V8It)filter[0]+v8it_src_c*(V8It)filter[2];
v4it_result_even=(v8it_sum.s0123+v8it_sum.s2345)*(V4It)filter[0]+v8it_sum.s1234*(V4It)filter[2];
v4it_result_odd=(v8it_sum.s1234+v8it_sum.s2345)*(V4It)filter[1];
v4tp_result_even=PYRAMID_UP_CONVERT(v4it_result_even,(V4It)(1<<(Q-1)),Q,V4Tp);
v4tp_result_odd=PYRAMID_UP_CONVERT(v4it_result_odd,(V4It)(1<<(Q-1)),Q,V4Tp);
v2it_result_even=(v8it_sum.s45+v8it_sum.s67)*(V2It)filter[0]+v8it_sum.s56*(V2It)filter[2];
v2it_result_odd=(v8it_sum.s56+v8it_sum.s67)*(V2It)filter[1];
v2tp_result_even=PYRAMID_UP_CONVERT(v2it_result_even,(V2It)(1<<(Q-1)),Q,V2Tp);
v2tp_result_odd=PYRAMID_UP_CONVERT(v2it_result_odd,(V2It)(1<<(Q-1)),Q,V2Tp);
v8tp_result.even=v4tp_result_even;
v8tp_result.odd=v4tp_result_odd;
v4tp_result.even=v2tp_result_even;
v4tp_result.odd=v2tp_result_odd;
VSTORE(v8tp_result,dst+offset_dst,8);
VSTORE(v4tp_result,dst+offset_dst+8,4);
v8it_sum=(v8it_src_c+v8it_src_n)*(V8It)filter[1];
v4it_result_even=(v8it_sum.s0123+v8it_sum.s2345)*(V4It)filter[0]+v8it_sum.s1234*(V4It)filter[2];
v4it_result_odd=(v8it_sum.s1234+v8it_sum.s2345)*(V4It)filter[1];
v4tp_result_even=PYRAMID_UP_CONVERT(v4it_result_even,(V4It)(1<<(Q-1)),Q,V4Tp);
v4tp_result_odd=PYRAMID_UP_CONVERT(v4it_result_odd,(V4It)(1<<(Q-1)),Q,V4Tp);
v2it_result_even=(v8it_sum.s45+v8it_sum.s67)*(V2It)filter[0]+v8it_sum.s56*(V2It)filter[2];
v2it_result_odd=(v8it_sum.s56+v8it_sum.s67)*(V2It)filter[1];
v2tp_result_even=PYRAMID_UP_CONVERT(v2it_result_even,(V2It)(1<<(Q-1)),Q,V2Tp);
v2tp_result_odd=PYRAMID_UP_CONVERT(v2it_result_odd,(V2It)(1<<(Q-1)),Q,V2Tp);
v8tp_result.even=v4tp_result_even;
v8tp_result.odd=v4tp_result_odd;
v4tp_result.even=v2tp_result_even;
v4tp_result.odd=v2tp_result_odd;
VSTORE(v8tp_result,dst+offset_dst+ostep,8);
VSTORE(v4tp_result,dst+offset_dst+ostep+8,4);
}

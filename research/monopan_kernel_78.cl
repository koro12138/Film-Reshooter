kernel void GaussianMain5x5C2(global St*src,int istep,
global Dt*dst,int ostep,
int height,int y_work_size,int x_work_size,
constant Kt*filter MAX_CONSTANT_SIZE,
struct Scalar border_value)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
int elem_counts=1;
int ksh=2;
int channel=2;
int x_idx=gx*elem_counts*channel;
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
V16St v16it_src_p1,v16it_src_p0,v16it_src_c,v16it_src_n0,v16it_src_n1;
V16InterType v16it_sum;
V2InterType v2it_result;
V2Dt v2dt_result;
int offset_dst;
int8 v8s32_offset_src;
if(gy>=ksh&&gy<(height-ksh))
{
v8s32_offset_src=mad24(gy+(int8)(-2,-1,0,1,2,3,0,0),istep,x_idx);
v16it_src_p1=VLOAD(src+v8s32_offset_src.s0,16);
v16it_src_p0=VLOAD(src+v8s32_offset_src.s1,16);
v16it_src_c=VLOAD(src+v8s32_offset_src.s2,16);
v16it_src_n0=VLOAD(src+v8s32_offset_src.s3,16);
v16it_src_n1=VLOAD(src+v8s32_offset_src.s4,16);
}
else
{
int y_idx_p1,y_idx_p0,y_idx_c,y_idx_n0,y_idx_n1;
y_idx_p1=TOP_BORDER_IDX(gy-2);
y_idx_p0=TOP_BORDER_IDX(gy-1);
y_idx_c=gy;
y_idx_n0=BOTTOM_BORDER_IDX(gy+1,height);
y_idx_n1=BOTTOM_BORDER_IDX(gy+2,height);
v8s32_offset_src=mad24((int8)(y_idx_p1,y_idx_p0,y_idx_c,y_idx_n0,y_idx_n1,0,0,0),istep,x_idx);
#if BORDER_CONSTANT
V2St v2it_border_value={(St)border_value.val[0],(St)border_value.val[1]};
V8St v8it_border_value={v2it_border_value,v2it_border_value,v2it_border_value,v2it_border_value};
V16St v16it_border_value={v8it_border_value,v8it_border_value};
v16it_src_p1=y_idx_p1<0?v16it_border_value:VLOAD(src+v8s32_offset_src.s0,16);
v16it_src_p0=y_idx_p0<0?v16it_border_value:VLOAD(src+v8s32_offset_src.s1,16);
v16it_src_c=VLOAD(src+v8s32_offset_src.s2,16);
v16it_src_n0=y_idx_n0<0?v16it_border_value:VLOAD(src+v8s32_offset_src.s3,16);
v16it_src_n1=y_idx_n1<0?v16it_border_value:VLOAD(src+v8s32_offset_src.s4,16);
#else
v16it_src_p1=VLOAD(src+v8s32_offset_src.s0,16);
v16it_src_p0=VLOAD(src+v8s32_offset_src.s1,16);
v16it_src_c=VLOAD(src+v8s32_offset_src.s2,16);
v16it_src_n0=VLOAD(src+v8s32_offset_src.s3,16);
v16it_src_n1=VLOAD(src+v8s32_offset_src.s4,16);
#endif
}
v16it_sum=(GAUSSIAN_CONVERT(v16it_src_p1,V16InterType)+GAUSSIAN_CONVERT(v16it_src_n1,V16InterType))*(Kt)filter[0]+
(GAUSSIAN_CONVERT(v16it_src_p0,V16InterType)+GAUSSIAN_CONVERT(v16it_src_n0,V16InterType))*(Kt)filter[1]+
GAUSSIAN_CONVERT(v16it_src_c,V16InterType)*(Kt)filter[2];
v2it_result=(v16it_sum.s01+v16it_sum.s89)*(V2InterType)filter[0]+
(v16it_sum.s23+v16it_sum.s67)*(V2InterType)filter[1]+
v16it_sum.s45*(V2InterType)filter[2];
#if IS_FLOAT(InterType)
v2dt_result=CONVERT(v2it_result,V2Dt);
#else
v2dt_result=CONVERT_SAT((v2it_result+(V2InterType)(1<<(Q-1)))>>Q,V2Dt);
#endif
offset_dst=mad24(gy,ostep,x_idx+ksh*channel);
VSTORE(v2dt_result,dst+offset_dst,2);
}

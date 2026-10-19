#define VAbs VTYPE(AbsType,ELEM_COUNTS)
#define VSum VTYPE(SumType,ELEM_COUNTS)
__kernel void AbsSumMain(global St*src,int istep,
global SumType*dst,
local SumType*local_sum,
int blk_w,int blk_h,
int width,int height)
{
int offset_x=get_group_id(0)*blk_w*ELEM_COUNTS;
int offset_y=get_group_id(1)*blk_h;
blk_h=(offset_y+blk_h>height)?height-offset_y:blk_h;
int blk_size=blk_h*blk_w;
int local_id=get_local_id(0);
int local_size=get_local_size(0);
{
local_sum[local_id]=0;
for(int tid=local_id;tid<blk_size;tid+=local_size)
{
int idy=tid/blk_w;
int idx=tid-idy*blk_w;
int idw=mad24(idx,ELEM_COUNTS,offset_x);
global St*src_data=src+(idy+offset_y)*istep+idw;
if(idw+ELEM_COUNTS<=width)
{
VAbs vabs_src=ABS(VLOAD(src_data,ELEM_COUNTS));
VSum vsum=CONVERT(vabs_src,VSum);
SumType sum=SUM_REDUCE(vsum,ELEM_COUNTS);
local_sum[local_id]+=sum;
}
else
{
SumType sum=0;
for(int i=0;i<width-idw;i++)
{
sum+=CONVERT(ABS(src_data[i]),SumType);
}
local_sum[local_id]+=sum;
}
}
}
barrier(CLK_LOCAL_MEM_FENCE);
int num=local_size;
for(;!(num&0x1);)
{
num>>=1;
if(local_id<num)
{
local_sum[local_id]+=local_sum[local_id+num];
}
barrier(CLK_LOCAL_MEM_FENCE);
}
if(0==local_id)
{
SumType sum=0;
for(int i=0;i<num;i++)
{
sum+=local_sum[i];
}
int group_idx=get_group_id(0)+get_group_id(1)*get_num_groups(0);
dst[group_idx]=sum;
}
}

kernel void SumRemain(global St*src,
global SumType*dst,
local SumType*local_sum,
int elem_counts,int length)
{
int local_id=get_local_id(0);
int idx_start=local_id*elem_counts;
int idx_end=idx_start+elem_counts>length?length:idx_start+elem_counts;
int local_size=get_local_size(0);
SumType sum=0;
for(int i=idx_start;i<idx_end;i++)
{
sum+=CONVERT(src[i],SumType);
}
local_sum[local_id]=sum;
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
sum=0;
for(int i=0;i<num;i++)
{
sum+=local_sum[i];
}
dst[0]=sum;
}
}

kernel void NormInfRemain(global St*src,
global SumType*dst,
local SumType*local_max,
int load_length,int length)
{
int local_id=get_local_id(0);
int idx_start=local_id*load_length;
int idx_end=idx_start+load_length>length?length:idx_start+load_length;
int local_size=get_local_size(0);
SumType max_val=0;
for(int i=idx_start;i<idx_end;i++)
{
max_val=max(CONVERT(src[i],SumType),max_val);
}
local_max[local_id]=max_val;
barrier(CLK_LOCAL_MEM_FENCE);
int num=local_size;
for(;!(num&0x1);)
{
num>>=1;
if(local_id<num)
{
local_max[local_id]=max(local_max[local_id+num],local_max[local_id]);
}
barrier(CLK_LOCAL_MEM_FENCE);
}
if(0==local_id)
{
max_val=0;
for(int i=0;i<num;i++)
{
max_val=max(local_max[i],max_val);
}
dst[0]=max_val;
}
}

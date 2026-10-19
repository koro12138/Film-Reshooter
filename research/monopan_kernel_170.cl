#define VSt VTYPE(St,ELEM_COUNTS)
#define VSqSum VTYPE(SqSumType,ELEM_COUNTS)
kernel void SqSumMain(global St*src,int istep,
global SqSumType*dst,
local SqSumType*local_sqsum,
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
local_sqsum[local_id]=0;
for(int tid=local_id;tid<blk_size;tid+=local_size)
{
int idy=tid/blk_w;
int idx=tid-idy*blk_w;
int idw=offset_x+idx*ELEM_COUNTS;
global St*src_data=src+(idy+offset_y)*istep+idw;
if(idw+ELEM_COUNTS<=width)
{
VSt vst_src=VLOAD(src_data,ELEM_COUNTS);
VSqSum vsqsum=CONVERT(vst_src,VSqSum);
SqSumType sqsum=SUM_REDUCE(vsqsum*vsqsum,ELEM_COUNTS);
local_sqsum[local_id]+=sqsum;
}
else
{
SqSumType sqsum=0;
for(int i=0;i<width-idw;i++)
{
SqSumType v_load=CONVERT(src_data[i],SqSumType);
sqsum+=v_load*v_load;
}
local_sqsum[local_id]+=sqsum;
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
local_sqsum[local_id]+=local_sqsum[local_id+num];
}
barrier(CLK_LOCAL_MEM_FENCE);
}
if(0==local_id)
{
SqSumType sqsum=0;
for(int i=0;i<num;i++)
{
sqsum+=local_sqsum[i];
}
int group_idx=get_group_id(0)+get_group_id(1)*get_num_groups(0);
dst[group_idx]=sqsum;
}
}

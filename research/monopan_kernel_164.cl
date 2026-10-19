#define VSt VTYPE(St,ELEM_COUNTS)
#define VAbs VTYPE(AbsType,ELEM_COUNTS)
kernel void NormInfMain(global St*src,int istep,
global AbsType*dst,
local AbsType*local_max,
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
AbsType abs_max=0;
for(int tid=local_id;tid<blk_size;tid+=local_size)
{
int idy=tid/blk_w;
int idx=tid-idy*blk_w;
int idw=offset_x+idx*ELEM_COUNTS;
global St*src_data=src+(idy+offset_y)*istep+idw;
if(idw+ELEM_COUNTS<=width)
{
VAbs vabs_src=ABS(VLOAD(src_data,ELEM_COUNTS));
AbsType abs_max_temp=MAX_REDUCE(vabs_src,ELEM_COUNTS);
abs_max=max(abs_max_temp,abs_max);
}
else
{
for(int i=0;i<width-idw;i++)
{
abs_max=max(ABS(src_data[i]),abs_max);
}
}
}
local_max[local_id]=abs_max;
}
barrier(CLK_LOCAL_MEM_FENCE);
int num=local_size;
for(;!(num&0x1);)
{
num>>=1;
for(int tid=local_id;tid<num;tid+=local_size)
{
local_max[tid]=max(local_max[tid],local_max[tid+num]);
}
barrier(CLK_LOCAL_MEM_FENCE);
}
if(0==local_id)
{
AbsType abs_dst=0;
for(int i=0;i<num;i++)
{
abs_dst=max(local_max[i],abs_dst);
}
int group_idx=get_group_id(0)+get_group_id(1)*get_num_groups(0);
dst[group_idx]=abs_dst;
}
}

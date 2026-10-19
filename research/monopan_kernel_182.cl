#if ADRENO
__attribute__((qcom_reqd_sub_group_size("half")))
#endif
kernel void CCLHAStripLabeling(const global uchar*img,const int istep,
global Tp*label,const int ostep,
const int height,const int width)
{
const int gy=get_global_id(1);
const int lx=get_local_id(0);
const int ly=get_local_id(1);
local BITMASK_TYPE bitmask[STRIP_SIZE];
#if!BALLOT
local Tp wg_ballots_pool[SUBGROUP_SIZE*STRIP_SIZE];
local Tp*subg_ballots_pool=&wg_ballots_pool[ly*SUBGROUP_SIZE];
#endif
const int2 v2s32_index=mad24(max(gy,height-1),(int2)(istep,ostep),0);
Tp dist_prev_last=0,dist_curr_last=0;
for(int i=0;i<width;i+=SUBGROUP_SIZE)
{
const int2 v2s32_index_curr=v2s32_index+max(i+lx,width-1);
Tp img_val_curr=CONVERT_CCL(img[v2s32_index_curr.s0]);
const BITMASK_TYPE mask_curr=GET_BALLOT(img_val_curr);
Tp dist_curr=START_DISTANCE(mask_curr,lx);
if(img_val_curr&&(0==dist_curr))
{
label[v2s32_index_curr.s1]=1+select(v2s32_index_curr.s1,v2s32_index_curr.s1-(int)dist_curr_last,0==lx);
}
if(0==lx)
{
bitmask[ly]=mask_curr;
}
barrier(CLK_LOCAL_MEM_FENCE);
BITMASK_TYPE mask_prev=0;
if(ly>0)
{
mask_prev=bitmask[ly-1];
}
Tp img_val_prev=CONVERT_CCL((mask_prev>>lx)&1u);
Tp dist_prev=START_DISTANCE(mask_prev,lx);
if(0==lx)
{
dist_curr=dist_curr_last;
dist_prev=dist_prev_last;
}
#if CONNECTIVITY_SQUARE
const BITMASK_TYPE shifted_curr=(mask_curr<<1u)|(dist_curr_last>0u);
const BITMASK_TYPE shifted_prev=(mask_prev<<1u)|(dist_prev_last>0u);
#endif
if(img_val_curr&&img_val_prev&&((0==dist_curr)||(0==dist_prev)))
{
int label_1=v2s32_index_curr.s1-dist_curr;
int label_2=v2s32_index_curr.s1-dist_prev-ostep;
Merge(label,label_1,label_2);
}
#if CONNECTIVITY_SQUARE
else if(img_val_curr&&(0==dist_curr)&&((shifted_prev>>lx)&1u))
{
int label_1=v2s32_index_curr.s1;
int label_2=v2s32_index_curr.s1-ostep-select(CONVERT_CCL(START_DISTANCE(mask_prev,lx-1)),dist_prev_last-1,0==lx);
Merge(label,label_1,label_2);
}
else if(img_val_prev&&(0==dist_prev)&&((shifted_curr>>lx)&1u))
{
int label_1=v2s32_index_curr.s1-select(CONVERT_CCL(START_DISTANCE(mask_curr,lx-1)),dist_curr_last-1,0==lx);
int label_2=v2s32_index_curr.s1-ostep;
Merge(label,label_1,label_2);
}
#endif
Tp distance=START_DISTANCE(mask_prev,SUBGROUP_SIZE);
dist_prev_last=select(distance,dist_prev_last+distance,SUBGROUP_SIZE==distance);
distance=START_DISTANCE(mask_curr,SUBGROUP_SIZE);
dist_curr_last=select(distance,dist_curr_last+distance,SUBGROUP_SIZE==distance);
}
}

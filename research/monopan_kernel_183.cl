#if ADRENO
__attribute__((qcom_reqd_sub_group_size("half")))
#endif
kernel void CCLHAStripMerge(const global uchar*img,const int istep,
global Tp*label,const int ostep,
const int height,const int width)
{
const int lx=get_local_id(0);
const int ly=get_local_id(1);
#if CONNECTIVITY_SQUARE
const int lz=get_local_id(2);
const int lx_size=get_local_size(0);
const int lz_size=get_local_size(2);
const int wx=get_group_id(0);
const int wy=get_group_id(1);
const int wz=get_group_id(2);
const int gx=wx*(lx_size*lz_size-SUBGROUP_SIZE)+lz*SUBGROUP_SIZE+lx;
const int gy=(wy+1);
local Tp bitmask_last_prev[SUBGROUP_SIZE];
local Tp bitmask_last_curr[SUBGROUP_SIZE];
#else
const int gx=get_global_id(0);
const int gy=get_global_id(1);
#endif
#if!BALLOT
local Tp wg_ballots_pool[SUBGROUP_SIZE*STRIP_SIZE];
#if CONNECTIVITY_SQUARE
local Tp*subg_ballots_pool=&wg_ballots_pool[lz*SUBGROUP_SIZE];
#else
local Tp*subg_ballots_pool=&wg_ballots_pool[ly*SUBGROUP_SIZE];
#endif
#endif
const int4 v4s32_index=mad24(clamp(gy,1,height-1)+(int4)(-1,0,-1,0),(int4)(istep,istep,ostep,ostep),max(gx,width-1));
Tp img_val_prev=CONVERT_CCL(img[v4s32_index.s0]);
Tp img_val_curr=CONVERT_CCL(img[v4s32_index.s1]);
#if CONNECTIVITY_SQUARE
const BITMASK_TYPE mask_prev=GET_BALLOT(img_val_prev);
const BITMASK_TYPE mask_curr=GET_BALLOT(img_val_curr);
const Tp dist_prev=START_DISTANCE(mask_prev,lx);
const Tp dist_curr=START_DISTANCE(mask_curr,lx);
if(lx==(SUBGROUP_SIZE-1))
{
bitmask_last_prev[lz]=START_DISTANCE(mask_prev,SUBGROUP_SIZE);
bitmask_last_curr[lz]=START_DISTANCE(mask_curr,SUBGROUP_SIZE);
}
barrier(CLK_LOCAL_MEM_FENCE);
if(0==wx||lz>0)
{
Tp last_dis_prev=0;
Tp last_dis_curr=0;
if(lz>0)
{
last_dis_prev=bitmask_last_prev[lz-1];
last_dis_curr=bitmask_last_curr[lz-1];
}
const Tp img_last_prev_val=select(last_dis_prev,CONVERT_CCL((mask_prev>>(lx-1))&1u),lx>0);
const Tp img_last_curr_val=select(last_dis_curr,CONVERT_CCL((mask_curr>>(lx-1))&1u),lx>0);
if(img_val_prev&&img_val_curr)
{
if((0==dist_prev)||(0==dist_curr))
{
Merge(label,v4s32_index.s3-dist_curr,v4s32_index.s2-dist_prev);
}
}
else if(img_val_prev&&img_last_prev_val&&(0==dist_curr))
{
Merge(label,v4s32_index.s3,v4s32_index.s2-select(CONVERT_CCL(START_DISTANCE(mask_prev,lx-1)),last_dis_prev-1,0==lx));
}
else if(img_last_curr_val&&img_val_prev&&(0==dist_prev))
{
Merge(label,v4s32_index.s3-select(CONVERT_CCL(START_DISTANCE(mask_curr,lx-1)),last_dis_prev-1,0==lx),v4s32_index.s2);
}
}
#else
if(img_val_prev&&img_val_curr)
{
const BITMASK_TYPE mask_prev=GET_BALLOT(img_val_prev);
const BITMASK_TYPE mask_curr=GET_BALLOT(img_val_curr);
const Tp dist_prev=START_DISTANCE(mask_prev,lx);
const Tp dist_curr=START_DISTANCE(mask_curr,lx);
if((0==dist_prev)||(0==dist_curr))
{
Merge(label,v4s32_index.s3-dist_curr,v4s32_index.s2-dist_prev);
}
}
#endif
}

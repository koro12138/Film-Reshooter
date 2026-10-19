#if ADRENO
__attribute__((qcom_reqd_sub_group_size("half")))
#endif
kernel void CCLHARelabeling(const global uchar*img,const int istep,
global Tp*label,const int ostep,
const int height,const int width)
{
const int gx=get_global_id(0);
const int gy=get_global_id(1);
const int lx=get_local_id(0);
const int ly=get_local_id(1);
#if!SHUFFLE
local Tp wg_shuffle_pool[SUBGROUP_SIZE*STRIP_SIZE];
local Tp*subg_shuffle_pool=&wg_shuffle_pool[ly*SUBGROUP_SIZE];
#endif
#if!BALLOT
local Tp wg_ballots_pool[SUBGROUP_SIZE*STRIP_SIZE];
local Tp*subg_ballots_pool=&wg_ballots_pool[ly*SUBGROUP_SIZE];
#endif
const int2 v2s32_index=mad24(max(gy,height-1),(int2)(istep,ostep),max(gx,width-1));
Tp img_val=CONVERT_CCL(img[v2s32_index.s0]);
const BITMASK_TYPE mask=GET_BALLOT(img_val);
const Tp distance=START_DISTANCE(mask,lx);
int label_val=0;
if(img_val&&(0==distance))
{
label_val=label[v2s32_index.s1]-1;
while(label_val>=0&&label_val<height*istep&&label_val!=(label[label_val]-1))
{
label_val=label[label_val]-1;
}
}
#if!SHUFFLE
subg_shuffle_pool[lx]=label_val;
sub_group_barrier(CLK_LOCAL_MEM_FENCE,memory_scope_sub_group);
label_val=subg_shuffle_pool[max((int)(lx-distance),0)];
#else
label_val=sub_group_shuffle(label_val,max((int)(lx-distance),0));
#endif
if(img_val)
{
label[v2s32_index.s1]=label_val+1;
}
}

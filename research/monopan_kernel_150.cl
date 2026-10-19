#define TRANSPOSE4(data,addr,step)\
{\
*(addr)=data.s0;\
*(addr+step)=data.s1;\
*(addr+2*step)=data.s2;\
*(addr+3*step)=data.s3;\
}
#define TRANSPOSE8(data,addr,step)\
{\
*(addr)=data.s0;\
*(addr+step)=data.s1;\
*(addr+2*step)=data.s2;\
*(addr+3*step)=data.s3;\
*(addr+4*step)=data.s4;\
*(addr+5*step)=data.s5;\
*(addr+6*step)=data.s6;\
*(addr+7*step)=data.s7;\
}
#define TRANSPOSE16(data,addr,step)\
{\
*(addr)=data.s0;\
*(addr+step)=data.s1;\
*(addr+2*step)=data.s2;\
*(addr+3*step)=data.s3;\
*(addr+4*step)=data.s4;\
*(addr+5*step)=data.s5;\
*(addr+6*step)=data.s6;\
*(addr+7*step)=data.s7;\
*(addr+8*step)=data.s8;\
*(addr+9*step)=data.s9;\
*(addr+10*step)=data.sa;\
*(addr+11*step)=data.sb;\
*(addr+12*step)=data.sc;\
*(addr+13*step)=data.sd;\
*(addr+14*step)=data.se;\
*(addr+15*step)=data.sf;\
}
#define TRANSPOSE_STR(data,size,addr,step)TRANSPOSE##size(data,addr,step)
#define TRANSPOSE(data,size,addr,step)TRANSPOSE_STR(data,size,addr,step)
#define ACCUM_ADD4(vec_a1,vec_a2,vec_b1,vec_b2,vec_c)\
{\
vec_c[0].lo+=vec_a1.s0*vec_b1;\
vec_c[1].lo+=vec_a1.s1*vec_b1;\
vec_c[0].hi+=vec_a1.s0*vec_b2;\
vec_c[1].hi+=vec_a1.s1*vec_b2;\
vec_c[2].lo+=vec_a2.s0*vec_b1;\
vec_c[3].lo+=vec_a2.s1*vec_b1;\
vec_c[2].hi+=vec_a2.s0*vec_b2;\
vec_c[3].hi+=vec_a2.s1*vec_b2;\
}
#define ACCUM_ADD8(vec_a1,vec_a2,vec_b1,vec_b2,vec_c)\
{\
vec_c[0].lo+=vec_a1.s0*vec_b1;\
vec_c[1].lo+=vec_a1.s1*vec_b1;\
vec_c[2].lo+=vec_a1.s2*vec_b1;\
vec_c[3].lo+=vec_a1.s3*vec_b1;\
vec_c[0].hi+=vec_a1.s0*vec_b2;\
vec_c[1].hi+=vec_a1.s1*vec_b2;\
vec_c[2].hi+=vec_a1.s2*vec_b2;\
vec_c[3].hi+=vec_a1.s3*vec_b2;\
vec_c[4].lo+=vec_a2.s0*vec_b1;\
vec_c[5].lo+=vec_a2.s1*vec_b1;\
vec_c[6].lo+=vec_a2.s2*vec_b1;\
vec_c[7].lo+=vec_a2.s3*vec_b1;\
vec_c[4].hi+=vec_a2.s0*vec_b2;\
vec_c[5].hi+=vec_a2.s1*vec_b2;\
vec_c[6].hi+=vec_a2.s2*vec_b2;\
vec_c[7].hi+=vec_a2.s3*vec_b2;\
}
#define ACCUM_ADD16(vec_a1,vec_a2,vec_b1,vec_b2,vec_c)\
{\
vec_c[0].lo+=vec_a1.s0*vec_b1;\
vec_c[1].lo+=vec_a1.s1*vec_b1;\
vec_c[2].lo+=vec_a1.s2*vec_b1;\
vec_c[3].lo+=vec_a1.s3*vec_b1;\
vec_c[4].lo+=vec_a1.s4*vec_b1;\
vec_c[5].lo+=vec_a1.s5*vec_b1;\
vec_c[6].lo+=vec_a1.s6*vec_b1;\
vec_c[7].lo+=vec_a1.s7*vec_b1;\
vec_c[0].hi+=vec_a1.s0*vec_b2;\
vec_c[1].hi+=vec_a1.s1*vec_b2;\
vec_c[2].hi+=vec_a1.s2*vec_b2;\
vec_c[3].hi+=vec_a1.s3*vec_b2;\
vec_c[4].hi+=vec_a1.s4*vec_b2;\
vec_c[5].hi+=vec_a1.s5*vec_b2;\
vec_c[6].hi+=vec_a1.s6*vec_b2;\
vec_c[7].hi+=vec_a1.s7*vec_b2;\
vec_c[8].lo+=vec_a2.s0*vec_b1;\
vec_c[9].lo+=vec_a2.s1*vec_b1;\
vec_c[10].lo+=vec_a2.s2*vec_b1;\
vec_c[11].lo+=vec_a2.s3*vec_b1;\
vec_c[12].lo+=vec_a2.s4*vec_b1;\
vec_c[13].lo+=vec_a2.s5*vec_b1;\
vec_c[14].lo+=vec_a2.s6*vec_b1;\
vec_c[15].lo+=vec_a2.s7*vec_b1;\
vec_c[8].hi+=vec_a2.s0*vec_b2;\
vec_c[9].hi+=vec_a2.s1*vec_b2;\
vec_c[10].hi+=vec_a2.s2*vec_b2;\
vec_c[11].hi+=vec_a2.s3*vec_b2;\
vec_c[12].hi+=vec_a2.s4*vec_b2;\
vec_c[13].hi+=vec_a2.s5*vec_b2;\
vec_c[14].hi+=vec_a2.s6*vec_b2;\
vec_c[15].hi+=vec_a2.s7*vec_b2;\
}
#define ACCUM_ADD_STR(vec_a1,vec_a2,vec_b1,vec_b2,vec_c,size)ACCUM_ADD##size(vec_a1,vec_a2,vec_b1,vec_b2,vec_c)
#define ACCUM_ADD(vec_a1,vec_a2,vec_b1,vec_b2,vec_c,size)ACCUM_ADD_STR(vec_a1,vec_a2,vec_b1,vec_b2,vec_c,size)
#define HVSt VTYPE(float,HALF_ELEM_COUNTS)
#define VSt VTYPE(float,ELEM_COUNTS)
#define VLt VTYPE(float,LOAD_SIZE)
kernel void Gemm(global float*src_a,int step_a,
global float*src_b,int step_b,
global float*dst_c,int step_c,
local float*local_blk_a,local float*local_blk_b,
int m,int n,int k,
int bm,int bn,int bk)
{
int offset_x=get_group_id(0)*bn;
int offset_y=get_group_id(1)*bm;
if(offset_x>=n||offset_y>=m)
{
return;
}
offset_x=min(offset_x,n-bn);
offset_y=min(offset_y,m-bm);
global float*a_row=src_a+offset_y*step_a;
global float*b_col=src_b+offset_x;
global float*c_row=dst_c+mad24(offset_y,step_c,offset_x);
int local_id=get_local_id(1)*get_local_size(0)+get_local_id(0);
int group_size=get_local_size(0)*get_local_size(1);
int num_thread_per_row=bn/ELEM_COUNTS;
int idy=local_id/num_thread_per_row;
int idx=mad24(-idy,num_thread_per_row,local_id);
HVSt vhf32_a1,vhf32_a2,vhf32_b1,vhf32_b2;
VSt vf32_c[ELEM_COUNTS];
VLt vf32_a,vf32_b;
int k_align=k&(-bk);
for(int i=0;i<ELEM_COUNTS;i++)
{
vf32_c[i]=0;
}
int tile_idx=0;
do
{
for(int tid=local_id*LOAD_SIZE;tid<bm*bk/2;tid+=group_size*LOAD_SIZE)
{
int ay=tid/bk;
int ax=mad24(-ay,bk,tid);
int by=tid/(bn/2);
int bx=mad24(-by,bn/2,tid);
int offset_a1=mad24(ay,step_a,tile_idx+ax);
int offset_a2=mad24(bm/2,step_a,offset_a1);
int offset_b1=mad24(by+tile_idx,step_b,bx);
int offset_b2=offset_b1+bn/2;
vf32_a=VLOAD(a_row+offset_a1,LOAD_SIZE);
TRANSPOSE(vf32_a,LOAD_SIZE,local_blk_a+ax*bm+ay,bm);
vf32_a=VLOAD(a_row+offset_a2,LOAD_SIZE);
TRANSPOSE(vf32_a,LOAD_SIZE,local_blk_a+ax*bm+ay+bm/2,bm);
vf32_b=VLOAD(b_col+offset_b1,LOAD_SIZE);
VSTORE(vf32_b,local_blk_b+by*bn+bx,LOAD_SIZE);
vf32_b=VLOAD(b_col+offset_b2,LOAD_SIZE);
VSTORE(vf32_b,local_blk_b+by*bn+bx+bn/2,LOAD_SIZE);
}
barrier(CLK_LOCAL_MEM_FENCE);
for(int i=0;i<bk;i++)
{
vhf32_a1=VLOAD(local_blk_a+idy*HALF_ELEM_COUNTS+i*bm,HALF_ELEM_COUNTS);
vhf32_a2=VLOAD(local_blk_a+idy*HALF_ELEM_COUNTS+i*bm+bm/2,HALF_ELEM_COUNTS);
vhf32_b1=VLOAD(local_blk_b+idx*HALF_ELEM_COUNTS+i*bn,HALF_ELEM_COUNTS);
vhf32_b2=VLOAD(local_blk_b+idx*HALF_ELEM_COUNTS+i*bn+bn/2,HALF_ELEM_COUNTS);
ACCUM_ADD(vhf32_a1,vhf32_a2,vhf32_b1,vhf32_b2,vf32_c,ELEM_COUNTS);
}
barrier(CLK_LOCAL_MEM_FENCE);
tile_idx+=bk;
}while(tile_idx<k_align);
if(tile_idx<k)
{
int rem=k-tile_idx;
for(int tid=local_id*LOAD_SIZE;tid<bm*rem/2;tid+=group_size*LOAD_SIZE)
{
int ay=tid*2/bm;
int ax=tid%(bm/2);
int offset_a=tile_idx+ay;
for(int i=0;i<LOAD_SIZE;i++)
{
local_blk_a[ay*bm+ax+i]=a_row[offset_a+(ax+i)*step_a];
local_blk_a[ay*bm+ax+i+bm/2]=a_row[offset_a+(ax+i+bm/2)*step_a];
}
int by=tid/(bn/2);
int bx=tid%(bn/2);
int offset_b1=(by+tile_idx)*step_b+bx;
int offset_b2=(by+tile_idx)*step_b+bx+bn/2;
vf32_b=VLOAD(b_col+offset_b1,LOAD_SIZE);
VSTORE(vf32_b,local_blk_b+by*bn+bx,LOAD_SIZE);
vf32_b=VLOAD(b_col+offset_b2,LOAD_SIZE);
VSTORE(vf32_b,local_blk_b+by*bn+bx+bn/2,LOAD_SIZE);
}
barrier(CLK_LOCAL_MEM_FENCE);
for(int i=0;i<rem;i++)
{
vhf32_a1=VLOAD(local_blk_a+idy*HALF_ELEM_COUNTS+i*bm,HALF_ELEM_COUNTS);
vhf32_a2=VLOAD(local_blk_a+idy*HALF_ELEM_COUNTS+i*bm+bm/2,HALF_ELEM_COUNTS);
vhf32_b1=VLOAD(local_blk_b+idx*HALF_ELEM_COUNTS+i*bn,HALF_ELEM_COUNTS);
vhf32_b2=VLOAD(local_blk_b+idx*HALF_ELEM_COUNTS+i*bn+bn/2,HALF_ELEM_COUNTS);
ACCUM_ADD(vhf32_a1,vhf32_a2,vhf32_b1,vhf32_b2,vf32_c,ELEM_COUNTS);
}
}
int offset_c1=(idy*step_c+idx)*HALF_ELEM_COUNTS;
int offset_c2=offset_c1+bn/2;
int offset_c3=offset_c1+bm*step_c/2;
int offset_c4=offset_c3+bn/2;
for(int i=0;i<HALF_ELEM_COUNTS;i++)
{
VSTORE(vf32_c[i].lo,c_row+offset_c1+i*step_c,HALF_ELEM_COUNTS);
VSTORE(vf32_c[i].hi,c_row+offset_c2+i*step_c,HALF_ELEM_COUNTS);
VSTORE(vf32_c[i+HALF_ELEM_COUNTS].lo,c_row+offset_c3+i*step_c,HALF_ELEM_COUNTS);
VSTORE(vf32_c[i+HALF_ELEM_COUNTS].hi,c_row+offset_c4+i*step_c,HALF_ELEM_COUNTS);
}
}

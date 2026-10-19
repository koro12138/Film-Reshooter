kernel void CvtBayer2bgrRemain(global Tp*dst,int ostep,
int height,int width,
int y_work_size,int x_work_size,
int remain_offset)
{
int gx=get_global_id(0);
int gy=get_global_id(1);
if((gx>=x_work_size)||(gy>=y_work_size))
{
return;
}
int x_idx=(gx>=remain_offset)?gx-remain_offset:
((gx>=width)?((gx-width)&1)*(width-1):gx);
int y_idx=(gx>=width)*((gx-width)>>1)+(gx>=width);
y_idx=(y_idx>=height)?(height-1):y_idx;
int offset_src_x=(((y_idx>0)&&(y_idx<(height-1)))?((width-1)==x_idx)*(width-3):(x_idx-1))+1;
int offset_src_y=(y_idx==(height-1))?(height-2):((y_idx>0)?y_idx:1);
if(0==x_idx&&(0==y_idx||(height-1)==y_idx))
{
offset_src_x=1;
}
else if((width-1)==x_idx&&(0==y_idx||(height-1)==y_idx))
{
offset_src_x=width-2;
}
int offset_src=offset_src_y*ostep+offset_src_x*3;
VTYPE(Tp,3)v3_result=VLOAD(dst+offset_src,3);
int offset_dst=y_idx*ostep+x_idx*3;
VSTORE(v3_result,dst+offset_dst,3);
}

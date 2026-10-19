#define ADD_DOT_STR(ELEM_COUNTS)AddDot##ELEM_COUNTS##x##ELEM_COUNTS
#define ADD_DOT(ELEM_COUNTS)ADD_DOT_STR(ELEM_COUNTS)
inline void AddDot4x4(global float*a,int step_a,
global float*b,int step_b,
global float*c,int step_c,
int k)
{
global float*a_row0=a+step_a*0;
global float*a_row1=a+step_a*1;
global float*a_row2=a+step_a*2;
global float*a_row3=a+step_a*3;
float4 v4f32_sum0=0;
float4 v4f32_sum1=0;
float4 v4f32_sum2=0;
float4 v4f32_sum3=0;
float4 v4f32_a0=0;
float4 v4f32_a1=0;
float4 v4f32_a2=0;
float4 v4f32_a3=0;
float4 v4f32_b;
int k_align4=(k&(-4));
int p=0;
for(;p<k_align4;p+=4)
{
v4f32_a0=vload4(0,a_row0+p);
v4f32_a1=vload4(0,a_row1+p);
v4f32_a2=vload4(0,a_row2+p);
v4f32_a3=vload4(0,a_row3+p);
v4f32_b=vload4(0,b+step_b*(p+0));
v4f32_sum0=mad(v4f32_a0.s0,v4f32_b,v4f32_sum0);
v4f32_sum1=mad(v4f32_a1.s0,v4f32_b,v4f32_sum1);
v4f32_sum2=mad(v4f32_a2.s0,v4f32_b,v4f32_sum2);
v4f32_sum3=mad(v4f32_a3.s0,v4f32_b,v4f32_sum3);
v4f32_b=vload4(0,b+step_b*(p+1));
v4f32_sum0=mad(v4f32_a0.s1,v4f32_b,v4f32_sum0);
v4f32_sum1=mad(v4f32_a1.s1,v4f32_b,v4f32_sum1);
v4f32_sum2=mad(v4f32_a2.s1,v4f32_b,v4f32_sum2);
v4f32_sum3=mad(v4f32_a3.s1,v4f32_b,v4f32_sum3);
v4f32_b=vload4(0,b+step_b*(p+2));
v4f32_sum0=mad(v4f32_a0.s2,v4f32_b,v4f32_sum0);
v4f32_sum1=mad(v4f32_a1.s2,v4f32_b,v4f32_sum1);
v4f32_sum2=mad(v4f32_a2.s2,v4f32_b,v4f32_sum2);
v4f32_sum3=mad(v4f32_a3.s2,v4f32_b,v4f32_sum3);
v4f32_b=vload4(0,b+step_b*(p+3));
v4f32_sum0=mad(v4f32_a0.s3,v4f32_b,v4f32_sum0);
v4f32_sum1=mad(v4f32_a1.s3,v4f32_b,v4f32_sum1);
v4f32_sum2=mad(v4f32_a2.s3,v4f32_b,v4f32_sum2);
v4f32_sum3=mad(v4f32_a3.s3,v4f32_b,v4f32_sum3);
}
for(;p<k;p++)
{
v4f32_b=vload4(0,b+step_b*p);
float ta0=*(a_row0+p);
float ta1=*(a_row1+p);
float ta2=*(a_row2+p);
float ta3=*(a_row3+p);
v4f32_sum0=mad(ta0,v4f32_b,v4f32_sum0);
v4f32_sum1=mad(ta1,v4f32_b,v4f32_sum1);
v4f32_sum2=mad(ta2,v4f32_b,v4f32_sum2);
v4f32_sum3=mad(ta3,v4f32_b,v4f32_sum3);
}
vstore4(v4f32_sum0,0,c+step_c*0);
vstore4(v4f32_sum1,0,c+step_c*1);
vstore4(v4f32_sum2,0,c+step_c*2);
vstore4(v4f32_sum3,0,c+step_c*3);
}
inline void AddDot8x8(global float*a,int step_a,
global float*b,int step_b,
global float*c,int step_c,
int k)
{
global float*a_row0=a+step_a*0;
global float*a_row1=a+step_a*1;
global float*a_row2=a+step_a*2;
global float*a_row3=a+step_a*3;
global float*a_row4=a+step_a*4;
global float*a_row5=a+step_a*5;
global float*a_row6=a+step_a*6;
global float*a_row7=a+step_a*7;
float4 v4f32_sum00=0;
float4 v4f32_sum01=0;
float4 v4f32_sum02=0;
float4 v4f32_sum03=0;
float4 v4f32_sum04=0;
float4 v4f32_sum05=0;
float4 v4f32_sum06=0;
float4 v4f32_sum07=0;
float4 v4f32_sum40=0;
float4 v4f32_sum41=0;
float4 v4f32_sum42=0;
float4 v4f32_sum43=0;
float4 v4f32_sum44=0;
float4 v4f32_sum45=0;
float4 v4f32_sum46=0;
float4 v4f32_sum47=0;
float4 v4f32_a0=0;
float4 v4f32_a1=0;
float4 v4f32_a2=0;
float4 v4f32_a3=0;
float4 v4f32_a4=0;
float4 v4f32_a5=0;
float4 v4f32_a6=0;
float4 v4f32_a7=0;
float4 v4f32_b0;
float4 v4f32_b1;
int k_align4=(k&(-4));
int p=0;
for(;p<k_align4;p+=4)
{
v4f32_a0=vload4(0,a_row0+p);
v4f32_a1=vload4(0,a_row1+p);
v4f32_a2=vload4(0,a_row2+p);
v4f32_a3=vload4(0,a_row3+p);
v4f32_a4=vload4(0,a_row4+p);
v4f32_a5=vload4(0,a_row5+p);
v4f32_a6=vload4(0,a_row6+p);
v4f32_a7=vload4(0,a_row7+p);
v4f32_b0=vload4(0,b+step_b*(p+0));
v4f32_b1=vload4(0,b+step_b*(p+0)+4);
v4f32_sum00=mad(v4f32_a0.s0,v4f32_b0,v4f32_sum00);
v4f32_sum01=mad(v4f32_a1.s0,v4f32_b0,v4f32_sum01);
v4f32_sum02=mad(v4f32_a2.s0,v4f32_b0,v4f32_sum02);
v4f32_sum03=mad(v4f32_a3.s0,v4f32_b0,v4f32_sum03);
v4f32_sum04=mad(v4f32_a4.s0,v4f32_b0,v4f32_sum04);
v4f32_sum05=mad(v4f32_a5.s0,v4f32_b0,v4f32_sum05);
v4f32_sum06=mad(v4f32_a6.s0,v4f32_b0,v4f32_sum06);
v4f32_sum07=mad(v4f32_a7.s0,v4f32_b0,v4f32_sum07);
v4f32_sum40=mad(v4f32_a0.s0,v4f32_b1,v4f32_sum40);
v4f32_sum41=mad(v4f32_a1.s0,v4f32_b1,v4f32_sum41);
v4f32_sum42=mad(v4f32_a2.s0,v4f32_b1,v4f32_sum42);
v4f32_sum43=mad(v4f32_a3.s0,v4f32_b1,v4f32_sum43);
v4f32_sum44=mad(v4f32_a4.s0,v4f32_b1,v4f32_sum44);
v4f32_sum45=mad(v4f32_a5.s0,v4f32_b1,v4f32_sum45);
v4f32_sum46=mad(v4f32_a6.s0,v4f32_b1,v4f32_sum46);
v4f32_sum47=mad(v4f32_a7.s0,v4f32_b1,v4f32_sum47);
v4f32_b0=vload4(0,b+step_b*(p+1));
v4f32_b1=vload4(0,b+step_b*(p+1)+4);
v4f32_sum00=mad(v4f32_a0.s1,v4f32_b0,v4f32_sum00);
v4f32_sum01=mad(v4f32_a1.s1,v4f32_b0,v4f32_sum01);
v4f32_sum02=mad(v4f32_a2.s1,v4f32_b0,v4f32_sum02);
v4f32_sum03=mad(v4f32_a3.s1,v4f32_b0,v4f32_sum03);
v4f32_sum04=mad(v4f32_a4.s1,v4f32_b0,v4f32_sum04);
v4f32_sum05=mad(v4f32_a5.s1,v4f32_b0,v4f32_sum05);
v4f32_sum06=mad(v4f32_a6.s1,v4f32_b0,v4f32_sum06);
v4f32_sum07=mad(v4f32_a7.s1,v4f32_b0,v4f32_sum07);
v4f32_sum40=mad(v4f32_a0.s1,v4f32_b1,v4f32_sum40);
v4f32_sum41=mad(v4f32_a1.s1,v4f32_b1,v4f32_sum41);
v4f32_sum42=mad(v4f32_a2.s1,v4f32_b1,v4f32_sum42);
v4f32_sum43=mad(v4f32_a3.s1,v4f32_b1,v4f32_sum43);
v4f32_sum44=mad(v4f32_a4.s1,v4f32_b1,v4f32_sum44);
v4f32_sum45=mad(v4f32_a5.s1,v4f32_b1,v4f32_sum45);
v4f32_sum46=mad(v4f32_a6.s1,v4f32_b1,v4f32_sum46);
v4f32_sum47=mad(v4f32_a7.s1,v4f32_b1,v4f32_sum47);
v4f32_b0=vload4(0,b+step_b*(p+2));
v4f32_b1=vload4(0,b+step_b*(p+2)+4);
v4f32_sum00=mad(v4f32_a0.s2,v4f32_b0,v4f32_sum00);
v4f32_sum01=mad(v4f32_a1.s2,v4f32_b0,v4f32_sum01);
v4f32_sum02=mad(v4f32_a2.s2,v4f32_b0,v4f32_sum02);
v4f32_sum03=mad(v4f32_a3.s2,v4f32_b0,v4f32_sum03);
v4f32_sum04=mad(v4f32_a4.s2,v4f32_b0,v4f32_sum04);
v4f32_sum05=mad(v4f32_a5.s2,v4f32_b0,v4f32_sum05);
v4f32_sum06=mad(v4f32_a6.s2,v4f32_b0,v4f32_sum06);
v4f32_sum07=mad(v4f32_a7.s2,v4f32_b0,v4f32_sum07);
v4f32_sum40=mad(v4f32_a0.s2,v4f32_b1,v4f32_sum40);
v4f32_sum41=mad(v4f32_a1.s2,v4f32_b1,v4f32_sum41);
v4f32_sum42=mad(v4f32_a2.s2,v4f32_b1,v4f32_sum42);
v4f32_sum43=mad(v4f32_a3.s2,v4f32_b1,v4f32_sum43);
v4f32_sum44=mad(v4f32_a4.s2,v4f32_b1,v4f32_sum44);
v4f32_sum45=mad(v4f32_a5.s2,v4f32_b1,v4f32_sum45);
v4f32_sum46=mad(v4f32_a6.s2,v4f32_b1,v4f32_sum46);
v4f32_sum47=mad(v4f32_a7.s2,v4f32_b1,v4f32_sum47);
v4f32_b0=vload4(0,b+step_b*(p+3));
v4f32_b1=vload4(0,b+step_b*(p+3)+4);
v4f32_sum00=mad(v4f32_a0.s3,v4f32_b0,v4f32_sum00);
v4f32_sum01=mad(v4f32_a1.s3,v4f32_b0,v4f32_sum01);
v4f32_sum02=mad(v4f32_a2.s3,v4f32_b0,v4f32_sum02);
v4f32_sum03=mad(v4f32_a3.s3,v4f32_b0,v4f32_sum03);
v4f32_sum04=mad(v4f32_a4.s3,v4f32_b0,v4f32_sum04);
v4f32_sum05=mad(v4f32_a5.s3,v4f32_b0,v4f32_sum05);
v4f32_sum06=mad(v4f32_a6.s3,v4f32_b0,v4f32_sum06);
v4f32_sum07=mad(v4f32_a7.s3,v4f32_b0,v4f32_sum07);
v4f32_sum40=mad(v4f32_a0.s3,v4f32_b1,v4f32_sum40);
v4f32_sum41=mad(v4f32_a1.s3,v4f32_b1,v4f32_sum41);
v4f32_sum42=mad(v4f32_a2.s3,v4f32_b1,v4f32_sum42);
v4f32_sum43=mad(v4f32_a3.s3,v4f32_b1,v4f32_sum43);
v4f32_sum44=mad(v4f32_a4.s3,v4f32_b1,v4f32_sum44);
v4f32_sum45=mad(v4f32_a5.s3,v4f32_b1,v4f32_sum45);
v4f32_sum46=mad(v4f32_a6.s3,v4f32_b1,v4f32_sum46);
v4f32_sum47=mad(v4f32_a7.s3,v4f32_b1,v4f32_sum47);
}
for(;p<k;p++)
{
v4f32_b0=vload4(0,b+step_b*p);
v4f32_b1=vload4(0,b+step_b*p+4);
float ta0=*(a_row0+p);
float ta1=*(a_row1+p);
float ta2=*(a_row2+p);
float ta3=*(a_row3+p);
float ta4=*(a_row4+p);
float ta5=*(a_row5+p);
float ta6=*(a_row6+p);
float ta7=*(a_row7+p);
v4f32_sum00=mad(ta0,v4f32_b0,v4f32_sum00);
v4f32_sum01=mad(ta1,v4f32_b0,v4f32_sum01);
v4f32_sum02=mad(ta2,v4f32_b0,v4f32_sum02);
v4f32_sum03=mad(ta3,v4f32_b0,v4f32_sum03);
v4f32_sum04=mad(ta4,v4f32_b0,v4f32_sum04);
v4f32_sum05=mad(ta5,v4f32_b0,v4f32_sum05);
v4f32_sum06=mad(ta6,v4f32_b0,v4f32_sum06);
v4f32_sum07=mad(ta7,v4f32_b0,v4f32_sum07);
v4f32_sum40=mad(ta0,v4f32_b1,v4f32_sum40);
v4f32_sum41=mad(ta1,v4f32_b1,v4f32_sum41);
v4f32_sum42=mad(ta2,v4f32_b1,v4f32_sum42);
v4f32_sum43=mad(ta3,v4f32_b1,v4f32_sum43);
v4f32_sum44=mad(ta4,v4f32_b1,v4f32_sum44);
v4f32_sum45=mad(ta5,v4f32_b1,v4f32_sum45);
v4f32_sum46=mad(ta6,v4f32_b1,v4f32_sum46);
v4f32_sum47=mad(ta7,v4f32_b1,v4f32_sum47);
}
vstore4(v4f32_sum00,0,c+step_c*0);
vstore4(v4f32_sum01,0,c+step_c*1);
vstore4(v4f32_sum02,0,c+step_c*2);
vstore4(v4f32_sum03,0,c+step_c*3);
vstore4(v4f32_sum04,0,c+step_c*4);
vstore4(v4f32_sum05,0,c+step_c*5);
vstore4(v4f32_sum06,0,c+step_c*6);
vstore4(v4f32_sum07,0,c+step_c*7);
vstore4(v4f32_sum40,0,c+step_c*0+4);
vstore4(v4f32_sum41,0,c+step_c*1+4);
vstore4(v4f32_sum42,0,c+step_c*2+4);
vstore4(v4f32_sum43,0,c+step_c*3+4);
vstore4(v4f32_sum44,0,c+step_c*4+4);
vstore4(v4f32_sum45,0,c+step_c*5+4);
vstore4(v4f32_sum46,0,c+step_c*6+4);
vstore4(v4f32_sum47,0,c+step_c*7+4);
}
kernel void Gemm(global float*src_a,int step_a,
global float*src_b,int step_b,
global float*dst_c,int step_c,
int m,int n,int k)
{
int gx=get_global_id(0)*ELEM_COUNTS;
int gy=get_global_id(1)*ELEM_COUNTS;
if(gx>=n||gy>=m)
{
return;
}
gx=min(gx,n-ELEM_COUNTS);
gy=min(gy,m-ELEM_COUNTS);
global float*a_row=src_a+step_a*gy;
global float*c_row=dst_c+step_c*gy;
ADD_DOT(ELEM_COUNTS)(a_row,step_a,src_b+gx,step_b,c_row+gx,step_c,k);
}

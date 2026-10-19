/* Adapted from musl log2f/exp2f, Copyright (c) 2017-2018, Arm Limited.
 * SPDX-License-Identifier: MIT. See licenses/m3-math-MIT.txt.
 * Explicit double FMA matches assets/math_arm.elf on the valid M3 domain.
 */
#include "m3_math_tables.h"
static float m3_log2f(float x) {
    uint32_t ix;memcpy(&ix,&x,4);
    if(ix==0x3f800000)return 0.f;
    if(ix<0x00800000||ix>=0x7f800000)return log2f(x);
    uint32_t tmp=ix-0x3f330000,top=tmp&0xff800000;
    int i=(tmp>>19)&15,k=(int32_t)tmp>>23;
    uint32_t iz=ix-top;float zf;memcpy(&zf,&iz,4);
    double r=fma((double)zf,m3_log_data[i*2],-1.0);
    double y0=m3_log_data[i*2+1]+(double)k,r2=r*r;
    double y=fma(m3_log_data[33],r,m3_log_data[34]);
    y=fma(m3_log_data[32],r2,y);
    double p=fma(m3_log_data[35],r,y0);
    return (float)fma(y,r2,p);
}
static float m3_exp2f(float x) {
    if(!isfinite(x)||x>=128.f||x<=-150.f)return exp2f(x);
    double xd=(double)x,kd=xd+m3_exp_data[0];
    uint64_t ki;memcpy(&ki,&kd,8);
    kd-=m3_exp_data[0];double r=xd-kd,r2=r*r;
    uint64_t t=m3_exp_tab[ki&31]+(ki<<47);
    double scale;memcpy(&scale,&t,8);
    double z=fma(m3_exp_data[1],r,m3_exp_data[2]);
    double y=fma(m3_exp_data[3],r,1.0);
    return (float)(fma(z,r2,y)*scale);
}
#define log2f m3_log2f
#define exp2f m3_exp2f

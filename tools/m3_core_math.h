/* musl float sin/exp, with the explicit double FMA order of math_arm.elf.
 * sin: Copyright (C) 1993 Sun Microsystems, Inc. All rights reserved.
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this software is freely
 * granted, provided that this notice is preserved.
 * exp: Copyright (c) 2017-2018, Arm Limited. SPDX-License-Identifier: MIT.
 * See the bundled third-party musl and m3-math-MIT notices.
 */
#include "m3_math_tables.h"
static float core_sin_poly(double x) {
    double z=x*x,w=z*z,s=z*x;
    double r=fma(z,0x16cd878c3b46a7.0p-71,-0x1a00f9e2cae774.0p-65);
    double p=fma(z,0x111110896efbb2.0p-59,-0x15555554cbac77.0p-55);
    return (float)fma(s*w,r,fma(s,p,x));
}
static float core_cos_poly(double x) {
    double z=x*x,w=z*z;
    double r=fma(z,0x199342e0ee5069.0p-68,-0x16c087e80f1e27.0p-62);
    double p=fma(w,0x155553e1053a42.0p-57,fma(z,-0x1ffffffd0c5e81.0p-54,1.0));
    return (float)fma(w*z,r,p);
}
static float core_sinf(float x) {
    uint32_t bits;memcpy(&bits,&x,4);uint32_t ix=bits&0x7fffffff;int sign=bits>>31;
    const double h=0x1.921fb54442d18p0;
    if(ix<=0x3f490fda){if(ix<0x39800000)return x;return core_sin_poly(x);}
    if(ix<=0x407b53d1){
        if(ix<=0x4016cbe3)return sign?-core_cos_poly((double)x+h):core_cos_poly((double)x-h);
        return core_sin_poly(sign?-((double)x+2*h):-((double)x-2*h));
    }
    if(ix<=0x40e231d5){
        if(ix<=0x40afeddf)return sign?core_cos_poly((double)x+3*h):-core_cos_poly((double)x-3*h);
        return core_sin_poly(sign?(double)x+4*h:(double)x-4*h);
    }
    /* M3 coordinates are bounded by 32768, far below musl's large reduction. */
    if(ix>=0x4dc90fdb)return sinf(x);
    double fn=fma((double)x,6.36619772367581382433e-01,0x1.8p52)-0x1.8p52;
    /* Keep the two successive subtractions, not reassociated products. */
    double y=fma(fn,-1.57079631090164184570,(double)x);
    y=fma(fn,-1.58932547735281966916e-08,y);
    int n=(int)fn;
    if(y < -0x1.921fb6p-1){n--;fn--;y=fma(fn,-1.57079631090164184570,(double)x);y=fma(fn,-1.58932547735281966916e-08,y);}
    else if(y > 0x1.921fb6p-1){n++;fn++;y=fma(fn,-1.57079631090164184570,(double)x);y=fma(fn,-1.58932547735281966916e-08,y);}
    switch(n&3){case 0:return core_sin_poly(y);case 1:return core_cos_poly(y);case 2:return core_sin_poly(-y);default:return -core_cos_poly(y);}
}
static float core_expf(float x) {
    if(!isfinite(x)||x>88.f||x<-88.f)return expf(x);
    double z=(double)x*0x1.71547652b82fep5,kd=z+0x1.8p52;
    uint64_t ki;memcpy(&ki,&kd,8);kd-=0x1.8p52;
    double r=z-kd,r2=r*r;
    uint64_t t=m3_exp_tab[ki&31]+(ki<<47);double scale;memcpy(&scale,&t,8);
    double p=fma(r,0x1.c6af84b912394p-20,0x1.ebfce50fac4f3p-13);
    double q=fma(r,0x1.62e42ff0c52d6p-6,1.0);
    return (float)(fma(p,r2,q)*scale);
}

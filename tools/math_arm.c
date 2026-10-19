#include <math.h>
float desktop_sinf(float x) { return sinf(x); }
float desktop_expf(float x) { return expf(x); }
float desktop_powf(float x,float y) { return powf(x,y); }
float desktop_fmodf(float x,float y) { return fmodf(x,y); }
float desktop_log2f(float x) { return log2f(x); }
float desktop_exp2f(float x) { return exp2f(x); }
float desktop_logf(float x) { return logf(x); }
int main(int argc,char **argv) { volatile float x=(float)argc; return (int)(desktop_sinf(x)+desktop_expf(x)+desktop_powf(x,x)+desktop_fmodf(x,x)+desktop_log2f(x)+desktop_exp2f(x)+desktop_logf(x)); }

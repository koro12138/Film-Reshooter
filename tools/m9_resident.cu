// Standalone CUDA driver kernels. Compiled at build time; no runtime compiler.
extern "C" __global__ void style_bytes(const float *src, unsigned char *dst, int *error) {
    int i=blockIdx.x*blockDim.x+threadIdx.x;
    if(i>=768*1024*3)return;
    int c=i%3,p=i/3,x=p%1024,y=p/1024;
    float v=src[c*864*1120+(y+48)*1120+x+48];
    if(!isfinite(v)){atomicExch(error,1);v=0;}
    v=__fadd_rn(__fmul_rn(v,127.5f),128.f);
    dst[i]=(unsigned char)__float2int_rn(fminf(255.f,fmaxf(0.f,v)));
}

extern "C" __global__ void pack_tiles(const unsigned char *original,
        const unsigned char *styled,float *dst,int first,int second,int third,int fourth,int batch) {
    int i=blockIdx.x*blockDim.x+threadIdx.x;
    if(i>=batch*6*544*544)return;
    int p=i%(544*544),c=(i/(544*544))%6,b=i/(6*544*544);
    int index=b==0?first:b==1?second:b==2?third:fourth;
    int x=(index%8)*512-16+p%544,y=(index/8)*512-16+p/544;
    int value=0;
    if(x>=0&&x<4096&&y>=0&&y<3072) {
        value=c<3?styled[((y/4)*1024+x/4)*3+c]:original[(y*4096+x)*3+c-3];
    }
    dst[i]=__fdiv_rn(__fadd_rn((float)value,-128.f),127.5f);
}

extern "C" __global__ void unpack_tiles(const float *src,unsigned char *canvas,
        int first,int second,int third,int fourth,int valid,int *error) {
    int i=blockIdx.x*blockDim.x+threadIdx.x;
    if(i>=valid*3*512*512)return;
    int c=i%3,p=(i/3)%(512*512),b=i/(3*512*512);
    int index=b==0?first:b==1?second:b==2?third:fourth;
    float v=src[b*3*544*544+c*544*544+(p/512+16)*544+p%512+16];
    if(!isfinite(v)){atomicExch(error,1);v=0;}
    v=__fadd_rn(__fmul_rn(v,127.5f),128.f);
    int x=(index%8)*512+p%512,y=(index/8)*512+p/512;
    canvas[(y*4096+x)*3+c]=(unsigned char)__float2int_rn(fminf(255.f,fmaxf(0.f,v)));
}

extern "C" __global__ void crop_canvas(const unsigned char *canvas,unsigned char *result,
                                       int left,int top,int width,int height) {
    int i=blockIdx.x*blockDim.x+threadIdx.x;
    if(i>=width*height*3)return;
    int c=i%3,p=i/3;
    result[i]=canvas[((p/width+top)*4096+p%width+left)*3+c];
}

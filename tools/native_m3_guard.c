/* Windows CPU port of the original M3 mode=1 quality guard.
 * The recovered detector retains the original float operation order. Compile
 * without fast-math, contraction, or strict-aliasing optimizations.
 */
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <pthread.h>
#include <unistd.h>
#endif
typedef unsigned int uint;
typedef unsigned char byte;
#ifdef _WIN32
#define API __declspec(dllexport)
#else
#define API __attribute__((visibility("default")))
#endif
#define SCARRY4(a,b) ((((uint32_t)(a)^(uint32_t)((uint32_t)(a)+(uint32_t)(b))) & ((uint32_t)(b)^(uint32_t)((uint32_t)(a)+(uint32_t)(b))))>>31)
#define SBORROW4(a,b) ((((uint32_t)(a)^(uint32_t)(b)) & ((uint32_t)(a)^(uint32_t)((uint32_t)(a)-(uint32_t)(b))))>>31)
#include "m3_guard_tables.h"
#include "m3_math.h"

/* Row-parallel driver. Every stage below writes only the cells of the row it is
 * given (snapshot rows own their output cells, smooth writes to a second buffer),
 * so the result is bit-identical no matter how many threads run. Threading the
 * single-threaded original is the whole win: 4 snapshot passes over a 27MP photo
 * plus two LUT/apply passes were ~4.9s of the ~10s M3 render. */
typedef void (*RowFn)(void *ctx,int y0,int y1);

typedef struct { RowFn fn; void *ctx; int y0, y1; } RowJob;

static int worker_count(void) {
#ifdef _WIN32
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    DWORD n = info.dwNumberOfProcessors;
#else
    long n = sysconf(_SC_NPROCESSORS_ONLN);
#endif
    return n < 1 ? 1 : (n > 16 ? 16 : (int)n);
}

#ifdef _WIN32
static DWORD WINAPI row_job_entry(LPVOID arg) {
    RowJob *job = (RowJob *)arg;
    job->fn(job->ctx, job->y0, job->y1);
    return 0;
}
#else
static void *row_job_entry(void *arg) {
    RowJob *job = (RowJob *)arg;
    job->fn(job->ctx, job->y0, job->y1);
    return NULL;
}
#endif

static void run_rows(RowFn fn, void *ctx, int rows) {
    int n = worker_count();
    if (n > rows) n = rows;
    if (n <= 1) { fn(ctx, 0, rows); return; }
#ifdef _WIN32
    RowJob jobs[16];
    HANDLE handles[16];
    int used = 0;
    for (int i = 1; i < n; i++) {
        jobs[used].fn = fn; jobs[used].ctx = ctx;
        jobs[used].y0 = (int)((long long)rows * i / n);
        jobs[used].y1 = (int)((long long)rows * (i + 1) / n);
        HANDLE h = CreateThread(NULL, 0, row_job_entry, &jobs[used], 0, NULL);
        if (h) handles[used++] = h;
        else fn(ctx, jobs[used].y0, jobs[used].y1);
    }
    fn(ctx, 0, (int)((long long)rows / n));
    if (used) { WaitForMultipleObjects((DWORD)used, handles, TRUE, INFINITE); for (int i = 0; i < used; i++) CloseHandle(handles[i]); }
#else
    RowJob jobs[16];
    pthread_t threads[16];
    int used = 0;
    for (int i = 1; i < n; i++) {
        jobs[used].fn = fn; jobs[used].ctx = ctx;
        jobs[used].y0 = (int)((long long)rows * i / n);
        jobs[used].y1 = (int)((long long)rows * (i + 1) / n);
        if (pthread_create(&threads[used], NULL, row_job_entry, &jobs[used]) == 0) used++;
        else fn(ctx, jobs[used].y0, jobs[used].y1);
    }
    fn(ctx, 0, (int)((long long)rows / n));
    for (int i = 0; i < used; i++) pthread_join(threads[i], NULL);
#endif
}

typedef struct {
    int w, h, full_w, full_h;
    float *log_y;
    uint8_t *rgb;
    float *min_y;
} Snapshot;
typedef struct {
    Snapshot *reference,*current;
    float *mask,*scratch;
    int mode,grade;
    uint8_t *tiles;
    int tile_width,axis;
} Detect;
_Static_assert(offsetof(Snapshot,min_y)==32,"Snapshot ABI");
_Static_assert(offsetof(Detect,mode)==32,"Detector ABI");
_Static_assert(offsetof(Detect,axis)==52,"Detector ABI");

static int clamp_index(int x,int hi){return x<0?0:(x>hi?hi:x);}static uint8_t encode_byte(float x) {
    x=fminf(1.f,fmaxf(0.f,x));
    float at=x*16384.f;int i=(int)at;
    if(i>=16384)return 255;
    int v=(int)((encode[i]+(at-(float)i)*(encode[i+1]-encode[i]))*255.f+.5f);
    return (uint8_t)clamp_index(v,255);
}
static void decode_table(float *out) {
    for(int i=0;i<256;i++) {
        /* ARM bits 0x41808081: Ghidra's printed 16.06275 loses precision. */
        float at=(float)i*0x1.010102p+4f;int j=(int)at;
        out[i]=j<4096?decode[j]+(at-(float)j)*(decode[j+1]-decode[j]):1.f;
    }
}
static void snapshot_free(Snapshot *s) {
    if(s){free(s->log_y);free(s->rgb);free(s->min_y);free(s);}
}
typedef struct {
    Snapshot *s;
    const uint8_t *pixels;
    int w, h, minimum, step;
    const float *table;
} SnapshotJob;

static void snapshot_rows(void *ctx, int row0, int row1) {
    SnapshotJob *job = (SnapshotJob *)ctx;
    Snapshot *s = job->s;
    const uint8_t *pixels = job->pixels;
    const int w = job->w, h = job->h, minimum = job->minimum;
    const float *table = job->table;
    for (int y = row0; y < row1; y++) for (int x = 0; x < s->w; x++) {
        float r=0,g=0,b=0,min_y=1.f;int count=0;
        int y0=h*y/s->h,y1=h*(y+1)/s->h;
        int x0=w*x/s->w,x1=w*(x+1)/s->w;
        for(int yy=y0;yy<y1;yy++)for(int xx=x0;xx<x1;xx++) {
            const uint8_t *p=pixels+((size_t)yy*w+xx)*job->step;
            float rr=table[p[0]],gg=table[p[1]],bb=table[p[2]];
            r+=rr;g+=gg;b+=bb;count++;
            if(minimum) {
                float v=(.2126f*rr+.7152f*gg)+.0722f*bb;
                if(v<=min_y)min_y=v;
            }
        }
        r/=(float)count;g/=(float)count;b/=(float)count;
        size_t i=(size_t)y*s->w+x;
        s->log_y[i]=log2f((.2126f*r+.7152f*g)+.0722f*b+.004f);
        if(minimum)s->min_y[i]=log2f(min_y+.004f);
        s->rgb[i*3]=encode_byte(r);s->rgb[i*3+1]=encode_byte(g);s->rgb[i*3+2]=encode_byte(b);
    }
}
static Snapshot *snapshot_step(const uint8_t *pixels,int w,int h,int minimum,const float *table,int step) {
    Snapshot *s=calloc(1,sizeof(*s));if(!s)return NULL;
    float scale=fminf(1.f,2048.f/(float)(w>h?w:h));
    s->w=(int)((float)w*scale);s->h=(int)((float)h*scale);
    if(s->w<1)s->w=1;if(s->h<1)s->h=1;
    s->full_w=w;s->full_h=h;
    size_t n=(size_t)s->w*s->h;
    s->log_y=malloc(n*4);s->rgb=malloc(n*3);
    if(minimum)s->min_y=malloc(n*4);
    if(!s->log_y||!s->rgb||(minimum&&!s->min_y)){snapshot_free(s);return NULL;}
    SnapshotJob job={s,pixels,w,h,minimum,step,table};
    run_rows(snapshot_rows,&job,s->h);
    return s;
}

#include "m3_guard_detector.h"

/* Two separable, edge-aware passes over the detected correction map. */
typedef struct { Detect *d; int axis; const float *in; float *out; int w, h; } SmoothJob;

static void smooth_rows(void *ctx, int row0, int row1) {
    SmoothJob *job = (SmoothJob *)ctx;
    Detect *d = job->d;
    const int axis = job->axis, w = job->w, h = job->h;
    const float *in = job->in;
    float *out = job->out;
    for(int y=row0;y<row1;y++)for(int x=0;x<w;x++) {
        if(d->tiles&&!d->tiles[(y/32)*d->tile_width+x/32])continue;
        size_t i=(size_t)y*w+x;float total=0.f,value=0.f;
        for(int k=-3;k<=3;k++) {
            int xx=x+(axis?k:0),yy=y+(axis?0:k);
            if(xx<0||xx>=w||yy<0||yy>=h)continue;
            size_t j=(size_t)yy*w+xx;float diff=fabsf(d->current->log_y[i]-d->current->log_y[j]);
            if(diff<=.35f) {
                float weight=(float)(4-abs(k))/(diff*diff*120.f+1.f);
                total+=weight;value+=weight*in[j];
            }
        }
        out[i]=total==0.f?0.f:value/total;
    }
}

static void smooth(Detect *d,int axis) {
    Snapshot *s=d->current;int w=s->w,h=s->h;
    SmoothJob job={d,axis,axis?d->scratch:d->mask,axis?d->mask:d->scratch,w,h};
    run_rows(smooth_rows,&job,h);
}

typedef struct { uint8_t *p; int w, h, step; uint8_t lut[256]; } GradeJob;

static void grade_rows(void *ctx, int row0, int row1) {
    GradeJob *job = (GradeJob *)ctx;
    uint8_t *p = job->p;
    const int w = job->w, h = job->h;
    const uint8_t *lut = job->lut;
    for(int y=row0;y<row1;y++)for(int x=0;x<w;x++) {
        uint8_t *q=p+((size_t)y*w+x)*job->step;
        int v=(int)(((float)q[0]*.2126f+(float)q[1]*.7152f)+(float)q[2]*.0722f+.5f);
        q[0]=q[1]=q[2]=lut[clamp_index(v,255)];
    }
}

static void grade_image(uint8_t *p,int w,int h,int step) {
    GradeJob job={p,w,h,step,{0}};
    uint8_t *lut=job.lut;
    for(int v=0;v<256;v++) {
        float at=(float)v/255.f;int j=0;
        while(j<7&&at>grade_x[j+1])j++;
        int value=(int)((grade_y[j]+((at-grade_x[j])/(grade_x[j+1]-grade_x[j]))*
                         (grade_y[j+1]-grade_y[j]))*255.f+.5f);
        lut[v]=(uint8_t)clamp_index(value,255);
    }
    run_rows(grade_rows,&job,h);
}

typedef struct {
    Snapshot *s;
    const float *mask;
    uint8_t *pixels;
    int w, h, step;
    const float *table;
} ApplyJob;

static void apply_rows(void *ctx, int row0, int row1) {
    ApplyJob *job = (ApplyJob *)ctx;
    Snapshot *s = job->s;
    const float *mask = job->mask;
    uint8_t *pixels = job->pixels;
    const int w = job->w, h = job->h;
    const float *table = job->table;
    for(int y=row0;y<row1;y++)for(int x=0;x<w;x++) {
        float fy=(((float)y+.5f)*(float)s->h)/(float)h+-.5f;
        float fx=(((float)x+.5f)*(float)s->w)/(float)w+-.5f;
        int yy=(int)fy,xx=(int)fx;
        int y0=clamp_index(yy,s->h-1),y1=clamp_index(yy+1,s->h-1);
        int x0=clamp_index(xx,s->w-1),x1=clamp_index(xx+1,s->w-1);
        size_t indices[4]={(size_t)y0*s->w+x0,(size_t)y0*s->w+x1,
                           (size_t)y1*s->w+x0,(size_t)y1*s->w+x1};
        float a=mask[indices[0]],b=mask[indices[1]],c=mask[indices[2]],d=mask[indices[3]];
        if(a+b+c+d<.0005f)continue;
        uint8_t *p=pixels+((size_t)y*w+x)*job->step;
        float r=table[p[0]],g=table[p[1]],blue=table[p[2]];
        float luminance=log2f((.2126f*r+.7152f*g)+.0722f*blue+.004f);
        fy-=(float)(int)fy;fx-=(float)(int)fx;
        float weights[4]={(1.f-fy)*(1.f-fx),(1.f-fy)*fx,fy*(1.f-fx),fy*fx};
        float total=0.f,correction=0.f;
        for(int k=0;k<4;k++) {
            float diff=fabsf(luminance-s->log_y[indices[k]]);
            if(diff<=.45f) {
                float weight=weights[k]/(diff*diff*150.f+1.f);
                total+=weight;correction+=weight*mask[indices[k]];
            }
        }
        if(total>=1e-8f) {
            correction/=total;
            float scale=exp2f(-fmaxf(correction,0.f));
            p[0]=encode_byte(r*scale);p[1]=encode_byte(g*scale);p[2]=encode_byte(blue*scale);
        }
    }
}

static void apply(Snapshot *s,const float *mask,uint8_t *pixels,int w,int h,const float *table,int step) {
    ApplyJob job={s,mask,pixels,w,h,step,table};
    run_rows(apply_rows,&job,h);
}

/* The detector keeps its own window arithmetic per row, so rows can be handed to
 * the thread pool exactly like the ported stages above. */
typedef struct { intptr_t *d; } DetectJob;
static void detect_row_job(void *ctx,int y0,int y1){ DetectJob *j=(DetectJob *)ctx; detect_rows(j->d,y0,y1); }

static int guard_impl(const uint8_t *source,uint8_t *processed,int w,int h,int grade,uint64_t *counts,int step) {
    if(counts){counts[0]=0;counts[1]=0;}
    if(!source||!processed||w<1||h<1||w>32768||h>32768||(size_t)w*h>80000000)return 0;
    if(step!=3&&step!=4)return 0;
    float table[256];decode_table(table);
    Snapshot *reference=snapshot_step(source,w,h,0,table,step),*current=NULL;
    float *mask=NULL,*scratch=NULL;uint8_t *tiles=NULL;int result=0;
    if(!reference)goto done;
    if(grade)grade_image(processed,w,h,step);
    current=snapshot_step(processed,w,h,1,table,step);if(!current)goto done;
    size_t n=(size_t)current->w*current->h;
    mask=calloc(n,4);scratch=calloc(n,4);
    int tw=(current->w+31)/32,th=(current->h+31)/32;
    tiles=calloc((size_t)tw*th,1);
    if(!mask||!scratch||!tiles)goto done;
    Detect d={reference,current,mask,scratch,1,!!grade,tiles,tw,0};
    DetectJob dj={(intptr_t *)&d};
    run_rows(detect_row_job,&dj,current->h);
    bool active=false;
    for(int y=0;y<current->h;y++)for(int x=0;x<current->w;x++) {
        if(mask[(size_t)y*current->w+x]>0.f) {
            if(counts)counts[0]++;
            active=true;
            for(int ty=clamp_index(y/32-1,th-1);ty<=clamp_index(y/32+1,th-1);ty++)
                for(int tx=clamp_index(x/32-1,tw-1);tx<=clamp_index(x/32+1,tw-1);tx++)tiles[ty*tw+tx]=1;
        }
    }
    if(active){smooth(&d,0);smooth(&d,1);}
    active=false;
    for(size_t i=0;i<n;i++)if(mask[i]>.003f){active=true;if(counts)counts[1]++;else break;}
    if(active)apply(current,mask,processed,w,h,table,step);
    result=1;
done:
    snapshot_free(reference);snapshot_free(current);free(mask);free(scratch);free(tiles);
    return result;
}

API int cl_m3_guard(const uint8_t *source,uint8_t *processed,int w,int h,int grade,uint64_t *counts) {
    return guard_impl(source,processed,w,h,grade,counts,4);
}

/* Same guard for 3-byte packed RGB: lets the caller skip the RGBA staging copies. */
API int cl_m3_guard_step(const uint8_t *source,uint8_t *processed,int w,int h,int grade,uint64_t *counts,int step) {
    return guard_impl(source,processed,w,h,grade,counts,step);
}

/* Developer oracle probe: snapshot logs/minima, detector and smoothed masks. */
API int cl_m3_probe(const uint8_t *source,uint8_t *processed,int w,int h,int grade,float *out) {
    if(!source||!processed||!out||w<1||h<1||w>32768||h>32768||(size_t)w*h>80000000)return 0;
    float table[256];decode_table(table);
    Snapshot *r=snapshot_step(source,w,h,0,table,4);
    if(grade)grade_image(processed,w,h,4);
    Snapshot *s=snapshot_step(processed,w,h,1,table,4);
    if(!r||!s){snapshot_free(r);snapshot_free(s);return 0;}
    size_t n=(size_t)s->w*s->h;
    float *mask=calloc(n,4),*scratch=calloc(n,4);
    if(!mask||!scratch){free(mask);free(scratch);snapshot_free(r);snapshot_free(s);return 0;}
    memcpy(out,r->log_y,n*4);memcpy(out+n,s->log_y,n*4);memcpy(out+2*n,s->min_y,n*4);
    Detect d={r,s,mask,scratch,1,!!grade,NULL,0,0};
    detect_rows((intptr_t *)&d,0,s->h);memcpy(out+3*n,mask,n*4);
    smooth(&d,0);smooth(&d,1);memcpy(out+4*n,mask,n*4);
    free(mask);free(scratch);snapshot_free(r);snapshot_free(s);return (int)n;
}

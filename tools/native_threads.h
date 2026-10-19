/* Minimal portable row-band thread driver shared by the native helpers.
 * Each job writes only its own rows, so the band count never changes results. */
#ifndef CAMERALOOK_NATIVE_THREADS_H
#define CAMERALOOK_NATIVE_THREADS_H
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <pthread.h>
#include <unistd.h>
#endif

typedef void (*ClRowFn)(void *ctx, int y0, int y1);

#ifndef CAMERALOOK_MAX_THREADS
#define CAMERALOOK_MAX_THREADS 16
#endif

static int cl_worker_count(void) {
#ifdef _WIN32
    SYSTEM_INFO info;
    GetSystemInfo(&info);
    int n = (int)info.dwNumberOfProcessors;
#else
    long n = sysconf(_SC_NPROCESSORS_ONLN);
#endif
    if (n < 1) n = 1;
    if (n > CAMERALOOK_MAX_THREADS) n = CAMERALOOK_MAX_THREADS;
    return n;
}

typedef struct { ClRowFn fn; void *ctx; int y0, y1; } ClRowJob;
#ifdef _WIN32
static DWORD WINAPI cl_row_band(LPVOID arg) {
    ClRowJob *job = (ClRowJob *)arg;
    job->fn(job->ctx, job->y0, job->y1);
    return 0;
}
#else
static void *cl_row_band(void *arg) {
    ClRowJob *job = (ClRowJob *)arg;
    job->fn(job->ctx, job->y0, job->y1);
    return NULL;
}
#endif

/* Split `rows` into bands of at least 4 rows; the calling thread runs band 0.
 * CAMERALOOK_NATIVE_THREADS=0 forces a single band (used for A/B measurement). */
static void cl_run_rows(ClRowFn fn, void *ctx, int rows) {
    if (rows <= 0) return;
    int workers = cl_worker_count();
    const char *off = getenv("CAMERALOOK_NATIVE_THREADS");
    if (off && off[0] == '0' && !off[1]) workers = 1;
    int bands = workers;
    if (bands > rows / 4) bands = rows / 4;
    if (bands < 1) bands = 1;
#ifdef _WIN32
    HANDLE threads[CAMERALOOK_MAX_THREADS];
    ClRowJob pack[CAMERALOOK_MAX_THREADS];
#else
    pthread_t threads[CAMERALOOK_MAX_THREADS];
    ClRowJob pack[CAMERALOOK_MAX_THREADS];
#endif
    int spawned = 0;
    int step = rows / bands;
    for (int b = 1; b < bands; b++) {
        int y0 = b * step;
        int y1 = (b + 1 == bands) ? rows : (b + 1) * step;
        pack[spawned] = (ClRowJob){fn, ctx, y0, y1};
#ifdef _WIN32
        threads[spawned] = CreateThread(NULL, 0, cl_row_band, &pack[spawned], 0, NULL);
        if (!threads[spawned]) {
            fn(ctx, y0, y1);
            continue;
        }
#else
        if (pthread_create(&threads[spawned], NULL, cl_row_band, &pack[spawned]) != 0) {
            fn(ctx, y0, y1);
            continue;
        }
#endif
        spawned++;
    }
    fn(ctx, 0, step);
#ifdef _WIN32
    if (spawned) WaitForMultipleObjects((DWORD)spawned, threads, TRUE, INFINITE);
    for (int i = 0; i < spawned; i++) CloseHandle(threads[i]);
#else
    for (int i = 0; i < spawned; i++) pthread_join(threads[i], NULL);
#endif
}
#endif

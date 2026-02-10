#pragma once

#include <stdint.h>

#if defined(_WIN32)
    #include <windows.h>
#else
    #include <time.h>
#endif

static inline uint64_t time_ns() {
    #if defined(_WIN32)
        static LARGE_INTEGER freq;
        static int initialized = 0;
        LARGE_INTEGER counter;

        if (!initialized) {
            QueryPerformanceFrequency(&freq);
            initialized = 1;
        } QueryPerformanceCounter(&counter);
        return (uint64_t)(
            (counter.QuadPart / freq.QuadPart) * 1000000000ULL +
            (counter.QuadPart % freq.QuadPart) * 1000000000ULL / freq.QuadPart
        );
    #else
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        return ts.tv_sec * 1000000000ULL + ts.tv_nsec;
    #endif
}

static const char* time_format(char *buf, size_t size, uint64_t ns)
{
    if (ns < 1000ULL) {
        snprintf(buf, size, "%lluns", (unsigned long long)ns);
    } else if (ns < 1000000ULL) {
        snprintf(buf, size, "%.1fus", ns / 1e3);
    } else if (ns < 1000000000ULL) {
        snprintf(buf, size, "%.1fms", ns / 1e6);
    } else {
        snprintf(buf, size, "%.1fs", ns / 1e9);
    }
    return buf;
}
#pragma once

#include <stdio.h>

typedef struct vec2i {
    int x, y;
} vec2i;

typedef struct vec2f {
    float x, y;
} vec2f;


inline vec2f vec2f_from_i(vec2i v) {
    return (vec2f) {(float) v.x, (float) v.y};
}

inline vec2i vec2i_from_f(vec2f v) {
    return (vec2i) {(int) v.x, (int) v.y};
}

inline vec2f vec2f_add(vec2f v1, vec2f v2) {
    return (vec2f) {v1.x + v2.x, v1.y + v2.y};
}

inline vec2f vec2f_sub(vec2f v1, vec2f v2) {
    return (vec2f) {v1.x - v2.x, v1.y - v2.y};
}

static inline const char* vec2i_str(vec2i v) {
    static char buf[32];
    snprintf(buf, sizeof buf, "(%d, %d)", v.x, v.y);
    return buf;
}

static inline const char* vec2f_str(vec2f v) {
    static char buf[32];
    snprintf(buf, sizeof buf, "(%.0f, %.0f)", v.x, v.y);
    return buf;
}



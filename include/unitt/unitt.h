#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logging/exception.h"

struct Context;

typedef struct UnitTest {
    char* name;
    void (*test)(const char* name, struct Context* ctx);
} UnitTest;

#define UNITT_INIT \
    static UnitTest tests[100]; \
    static int num_tests = 0; \
    struct Context;

#define UNITT_CONTEXT struct Context

#define UNITT_BEFORE_ALL static void unitt_before_all(struct Context* ctx)

#define UNITT_BEFORE_EACH static void unitt_before_each(struct Context* ctx)

#define UNITT_AFTER_ALL static void unitt_after_all(struct Context* ctx)

#define UNITT_AFTER_EACH static void unitt_after_each(struct Context* ctx)

#define UNITT(test_name) \
    static void unitt_##test_name(const char* name, struct Context* ctx); \
    __attribute__((constructor(101))) static void register_test_##test_name(void) { \
        tests[num_tests].name = #test_name; \
        tests[num_tests].test = unitt_##test_name; \
        num_tests++; \
    } \
    static void unitt_##test_name(const char* name, struct Context* ctx)

#ifdef UNITT_BEFORE_ALL_DEFINED
#define UNITT_BEFORE_ALL_CALL(ctx) unitt_before_all(ctx);
#else
#define UNITT_BEFORE_ALL_CALL(ctx)
#endif

#ifdef UNITT_BEFORE_EACH_DEFINED
#define UNITT_BEFORE_EACH_CALL(ctx) unitt_before_each(ctx);
#else
#define UNITT_BEFORE_EACH_CALL(ctx)
#endif

#ifdef UNITT_AFTER_EACH_DEFINED
#define UNITT_AFTER_EACH_CALL(ctx) unitt_after_each(ctx);
#else
#define UNITT_AFTER_EACH_CALL(ctx)
#endif

#ifdef UNITT_AFTER_ALL_DEFINED
#define UNITT_AFTER_ALL_CALL(ctx) unitt_after_all(ctx);
#else
#define UNITT_AFTER_ALL_CALL(ctx)
#endif

#ifndef UNITT_CONTEXT_DEFINED
struct Context {};
#endif

#define UNITT_RUN(suite_name) \
    __attribute__((constructor(102))) static void unitt_suite_##suite_name() { \
        printf("\n\n\033[1mExecuting Test Suite: %s\033[0m", #suite_name); \
        size_t passed = 0; \
        size_t failed = 0; \
        struct Context* ctx = calloc(1, sizeof(struct Context)); \
        UNITT_BEFORE_ALL_CALL(ctx) \
        for (int i = num_tests - 1; i >= 0; i--) { \
            UNITT_BEFORE_EACH_CALL(ctx) \
            printf("\n\033[3m  %s\033[0m", tests[i].name); \
            for (int j = 0; j < 40 - strlen(tests[i].name); j++) putchar(' '); \
            try { \
                tests[i].test(tests[i].name, ctx); \
                printf("\033[92m[PASSED]\033[0m"); \
                passed++; \
            } catch_any { \
                printf("\033[31m[FAILED]"); \
                Exception e = exception_context()->exception; \
                printf("\n  -> %s: %s\n\tat %s:%llu\033[0m", exception_to_string(e.type), \
                    e.message, e.file, e.line); \
                failed++; \
            } finalize; \
            UNITT_AFTER_EACH_CALL(ctx) \
        } \
        UNITT_AFTER_ALL_CALL(ctx) \
        printf("\nSummary: %llu passed, %llu failed\n", passed, failed); \
        free(ctx); \
    }

#ifdef UNITT_MAIN_ENTRY
int main(void) {
    getchar();
    return 0;
}
#endif

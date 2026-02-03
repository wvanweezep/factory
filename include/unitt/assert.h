#pragma once

#include <stdio.h>
#include <string.h>
#include "logging/exception.h"

#define TEST_FAILED(file, line, fmt, ...) \
    do { \
        printf("%s - ", name); \
        printf(fmt __VA_OPT__(,) __VA_ARGS__); \
        printf(" \t\t %s:%d\n", file, line); \
        exit(1); \
    } while(0);

#define assert_true(expression) \
    if (!expression) { TEST_FAILED(__FILE__, __LINE__, "Expected 'true' but got 'false'") }

#define assert_false(expression) \
    if (expression) { TEST_FAILED(__FILE__, __LINE__, "Expected 'false' but got 'true'") }

#define assert_equals(a, b) \
    if (a != b) { TEST_FAILED(__FILE__, __LINE__, \
        "Expected '%s' (%d) to be equal to '%s' (%d)", #a, a, #b, b) }

#define assert_null(a) \
    if (a != NULL) { TEST_FAILED(__FILE__, __LINE__, \
        "Expected NULL but got '%s' (%llu)", #a, a)} \

#define assert_not_null(a) \
    if (a == NULL) { TEST_FAILED(__FILE__, __LINE__, \
        "Expected not NULL but got '%s' (NULL)", #a)} \

#define assert_str_equals(a, b) { \
    if (strcmp(a, b) != 0) TEST_FAILED(__FILE__, __LINE__, \
        "Expected '%s' to be equal to '%s'", a, b)} \

#define assert_throws(code, ex_type) \
    do { \
        try code \
        catch(ex_type) { exception_clear_last(); break; } \
        catch_any { TEST_FAILED(__FILE__, __LINE__, \
            "Expected '%s' to be thrown, instead got '%s'", #ex_type, \
            exception_to_string((*(Exception**)deque_get_last(exception_get_context()->stack))->type)) \
            exception_clear_last(); \
        } \
        TEST_FAILED(__FILE__, __LINE__, "Expected '%s' to be thrown", #ex_type) \
    } while (0) \

#define assert_runs(code) \
    do { \
        try code \
        catch_any { \
            TEST_FAILED(__FILE__, __LINE__, "Expected no exception, instead got '%s'", \
                exception_to_string((*(Exception**)deque_get_last(exception_get_context()->stack))->type))\
        } \
    } while (0);

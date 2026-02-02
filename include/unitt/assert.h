#pragma once

#include <stdio.h>
#include "logging/exception.h"

#define TEST_FAILED(file, line, fmt, ...) \
    do { \
        printf("%s - ", name); \
        printf(fmt, __VA_ARGS__); \
        printf(" \t\t %s:%d\n", file, line); \
        exit(1); \
    } while(0);

#define assert_true(expression) \
    if (!expression) { TEST_FAILED("Expected 'true' but got 'false'") }

#define assert_false(expression) \
    if (expression) { TEST_FAILED("Expected 'false' but got 'true'") }

#define assert_equals(a, b) \
    if (a != b) { TEST_FAILED(__FILE__, __LINE__, \
        "Expected '%s' (%d) to be equal to '%s' (%d)", #a, a, #b, b) }

#define assert_throws(code, ex_type) \
    do { \
        try code \
        catch(ex_type) { exception_clear_last(); break; } \
        catch_any { TEST_FAILED(__FILE__, __LINE__, \
            "Expected '%s' to be thrown, instead got '%s'", #ex_type, \
            exception_to_string((*(Exception*)deque_get_last(exception_get_context()->stack)).type)) \
            exception_clear_last(); \
        } \
        TEST_FAILED(__FILE__, __LINE__, "Expected '%s' to be thrown", #ex_type) \
    } while (0) \

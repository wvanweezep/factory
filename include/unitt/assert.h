#pragma once

#include <stdio.h>
#include <string.h>
#include "logging/exception.h"

#define assert_true(expression) \
    if (!expression) { throw(AssertionException, "Expected 'true' but got 'false'"); }

#define assert_false(expression) \
    if (expression) { throw(AssertionException, "Expected 'false' but got 'true'"); }

#define assert_equals(a, b) \
    if (a != b) { throw(AssertionException, \
        "Expected '%s' (%d) to be equal to '%s' (%d)", #a, a, #b, b); }

#define assert_null(a) \
    if (a != NULL) { throw(AssertionException, \
        "Expected NULL but got '%s' (%llu)", #a, a); } \

#define assert_not_null(a) \
    if (a == NULL) { throw(AssertionException, \
        "Expected not NULL but got '%s' (NULL)", #a); } \

#define assert_str_equals(a, b) { \
    if (strcmp(a, b) != 0) throw(AssertionException, \
        "Expected '%s' to be equal to '%s'", a, b); } \

#define assert_throws(code, ex_type) \
    do { \
        try code \
        catch(ex_type) { exception_release_context(); break; } \
        catch_any { \
            ExceptionType etype = exception_context()->exception.type; \
            exception_release_context(); \
            throw(AssertionException, "Expected '%s' to be thrown, instead got '%s'", \
                #ex_type, exception_to_string(etype)); \
        } finalize;\
        throw(AssertionException, "Expected '%s' to be thrown", #ex_type); \
    } while (0) \

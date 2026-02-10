#include "unitt/unitt.h"
#include "unitt/assert.h"

UNITT_INIT

UNITT(assert_true_fail) {
    bool triggered = false;
    try { assert_true(false); }
    catch (AssertionException) { triggered = true; }
    finalize;
    if (!triggered) throw(AssertionException,
        "Expected 'assert_true' to fail with input 'false'");
}

UNITT(assert_true_pass) {
    bool triggered = false;
    try { assert_true(true); }
    catch (AssertionException) { triggered = true; }
    finalize;
    if (triggered) throw(AssertionException,
        "Expected 'assert_true' to pass with input 'true'");
}

UNITT(assert_false_fail) {
    bool triggered = false;
    try { assert_false(true); }
    catch (AssertionException) { triggered = true; }
    finalize;
    if (!triggered) throw(AssertionException,
        "Expected 'assert_false' to fail with input 'true'");
}

UNITT(assert_false_pass) {
    bool triggered = false;
    try { assert_false(false); }
    catch (AssertionException) { triggered = true; }
    finalize;
    if (triggered) throw(AssertionException,
        "Expected 'assert_false' to pass with input 'false'");
}

UNITT(assert_equals_fail_value) {
    bool triggered = false;
    const int a = 1;
    const int b = 2;
    try { assert_equals(a, b); }
    catch (AssertionException) { triggered = true; }
    finalize;
    if (!triggered) throw(AssertionException,
        "Expected 'assert_equals' to fail with input '%i' and '%i'", a, b);
}

UNITT(assert_equals_pass_value) {
    bool triggered = false;
    const int a = 1;
    const int b = 1;
    try { assert_equals(a, b); }
    catch (AssertionException) { triggered = true; }
    finalize;
    if (triggered) throw(AssertionException,
        "Expected 'assert_equals' to pass with input '%i' and '%i'", a, b);
}

UNITT(assert_equals_fail_memory) {
    bool triggered = false;
    const int a = 1;
    const int b = 1;
    try { assert_equals(&a, &b); }
    catch (AssertionException) { triggered = true; }
    finalize;
    if (!triggered) throw(AssertionException,
        "Expected 'assert_equals' to fail with input '%llu' and '%llu'", &a, &b);
}

UNITT(assert_equals_pass_memory) {
    bool triggered = false;
    const int a = 1;
    try { assert_equals(&a, &a); }
    catch (AssertionException) { triggered = true; }
    finalize;
    if (triggered) throw(AssertionException,
        "Expected 'assert_equals' to pass with input '%llu' and '%llu'", &a, &a);
}

UNITT(assert_null_fail) {
    bool triggered = false;
    int a = 1;
    try { assert_null(&a); }
    catch (AssertionException) { triggered = true; }
    finalize;
    if (!triggered) throw(AssertionException,
        "Expected 'assert_null' to fail with input '%llu'", &a);
}

UNITT(assert_null_pass) {
    bool triggered = false;
    try { assert_null(NULL); }
    catch (AssertionException) { triggered = true; }
    finalize;
    if (triggered) throw(AssertionException,
        "Expected 'assert_null' to pass with input 'NULL'");
}

UNITT(assert_not_null_fail) {
    bool triggered = false;
    try { assert_not_null(NULL); }
    catch (AssertionException) { triggered = true; }
    finalize;
    if (!triggered) throw(AssertionException,
        "Expected 'assert_not_null' to fail with input 'NULL'");
}

UNITT(assert_not_null_pass) {
    bool triggered = false;
    int a = 1;
    try { assert_not_null(&a); }
    catch (AssertionException) { triggered = true; }
    finalize;
    if (triggered) throw(AssertionException,
        "Expected 'assert_not_null' to pass with input '%llu'", &a);
}

UNITT(assert_str_equals_fail) {
    bool triggered = false;
    try { assert_str_equals("a", "b"); }
    catch (AssertionException) { triggered = true; }
    finalize;
    if (!triggered) throw(AssertionException,
        "Expected 'assert_str_equals' to fail with input 'a' and 'b'");
}

UNITT(assert_str_equals_pass) {
    bool triggered = false;
    try { assert_str_equals("a", "a"); }
    catch (AssertionException) { triggered = true; }
    finalize;
    if (triggered) throw(AssertionException,
        "Expected 'assert_str_equals' to pass with input 'a' and 'a'");
}

UNITT(assert_throws_fail_no_exception) {
    bool triggered = false;
    try { assert_throws({}, RuntimeException); }
    catch (AssertionException) { triggered = true; }
    finalize;
    if (!triggered) throw(AssertionException,
        "Expected 'assert_throws' to fail");
}

UNITT(assert_throws_fail_diff_exception) {
    bool triggered = false;
    try {
        assert_throws({
            throw(OutOfRangeException, "");
        }, RuntimeException);
    }
    catch (AssertionException) { triggered = true; }
    finalize;
    if (!triggered) throw(AssertionException,
        "Expected 'assert_throws' to fail");
}

UNITT(assert_throws_pass) {
    bool triggered = false;
    try { assert_throws({
            throw(RuntimeException, "");
        }, RuntimeException); }
    catch (AssertionException) { triggered = true; }
    finalize;
    if (triggered) throw(AssertionException,
        "Expected 'assert_throws' to pass");
}

UNITT_RUN(assert)

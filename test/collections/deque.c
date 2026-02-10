#define UNITT_CONTEXT_DEFINED
#define UNITT_BEFORE_EACH_DEFINED
#define UNITT_AFTER_EACH_DEFINED
#define UNITT_MAIN_ENTRY
#include "unitt/unitt.h"

#include "unitt/assert.h"
#include "collections/deque.h"

UNITT_INIT

UNITT_CONTEXT {
    Deque* dq;
};

UNITT_BEFORE_EACH {
    ctx->dq = deque_create(sizeof(int), 8);
}

UNITT_AFTER_EACH {
    deque_free(ctx->dq, NULL);
}

UNITT(create_element_size_zero_fail) {
    assert_throws({deque_create(0, 0); },
        IllegalArgumentException);
}

UNITT(size_empty) {
    assert_equals(deque_size(ctx->dq), 0);
}

UNITT(size_non_empty) {
    const int val = 1;
    deque_add_first(ctx->dq, &val);
    assert_equals(deque_size(ctx->dq), 1);
}

UNITT(size_fail_null) {
    assert_throws({ deque_size(NULL); },
        IllegalArgumentException);
}

UNITT(get_first_fail_null) {
    assert_throws({ deque_get_first(NULL); },
        IllegalArgumentException);
}

UNITT(get_first_fail_empty) {
    assert_throws({ deque_get_first(ctx->dq); },
        IllegalArgumentException);
}

UNITT(get_first_single) {
    const int val = 1;
    deque_add_first(ctx->dq, &val);
    assert_equals(*(int*)deque_get_first(ctx->dq), val);
}

UNITT(get_first_multi) {
    const int val1 = 1;
    const int val2 = 2;
    deque_add_first(ctx->dq, &val1);
    deque_add_first(ctx->dq, &val2);
    assert_equals(*(int*)deque_get_first(ctx->dq), val2);
}

UNITT(get_last_fail_null) {
    assert_throws({ deque_get_last(NULL); },
        IllegalArgumentException);
}

UNITT(get_last_fail_empty) {
    assert_throws({ deque_get_last(ctx->dq); },
        IllegalArgumentException);
}

UNITT(get_last_single) {
    Deque* dq = ctx->dq;
    const int val = 1;
    deque_add_first(dq, &val);
    assert_equals(*(int*)deque_get_last(dq), val);
}

UNITT(get_last_multi) {
    Deque* dq = ctx->dq;
    const int val1 = 1;
    const int val2 = 2;
    deque_add_first(dq, &val1);
    deque_add_first(dq, &val2);
    assert_equals(*(int*)deque_get_last(dq), val1);
}

UNITT(get_fail_null) {
    assert_throws({ deque_get(NULL, 0); },
        IllegalArgumentException);
}

UNITT(get_fail_empty) {
    assert_throws({ deque_get(ctx->dq, 0); },
        IllegalArgumentException);
}

UNITT(get_fail_out_of_range) {
    const int val = 1;
    deque_add_first(ctx->dq, &val);
    assert_throws({ deque_get(ctx->dq, 1); },
        OutOfRangeException);
}

UNITT(get_single) {
    const int val = 1;
    deque_add_first(ctx->dq, &val);
    assert_equals(*(int*)deque_get(ctx->dq, 0), val);
}

UNITT(get_multi_head) {
    const int val1 = 1;
    const int val2 = 2;
    deque_add_first(ctx->dq, &val2);
    deque_add_first(ctx->dq, &val1);
    assert_equals(*(int*)deque_get(ctx->dq, 0), val1);
}

UNITT(get_multi_tail) {
    const int val1 = 1;
    const int val2 = 2;
    deque_add_first(ctx->dq, &val2);
    deque_add_first(ctx->dq, &val1);
    assert_equals(*(int*)deque_get(ctx->dq, 1), val2);
}

UNITT(get_multi_middle) {
    const int val1 = 1;
    const int val2 = 2;
    const int val3 = 3;
    deque_add_first(ctx->dq, &val3);
    deque_add_first(ctx->dq, &val2);
    deque_add_first(ctx->dq, &val1);
    assert_equals(*(int*)deque_get(ctx->dq, 1), val2);
}

UNITT(add_first_fail_null) {

}

UNITT(add_first_multi) {

}

UNITT(add_last_fail_null) {

}

UNITT(add_last_multi) {

}

UNITT(add_first_last_combination) {

}

UNITT_RUN(deque)

#define UNITT_CONTEXT_DEFINED
#define UNITT_BEFORE_EACH_DEFINED
#define UNITT_AFTER_EACH_DEFINED
#define UNITT_MAIN_ENTRY
#include "unitt/unitt.h"

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

UNITT(deque_peek_single) {
    Deque* dq = ctx->dq;
    const int value = 42;
    deque_add_first(dq, &value);
    int result;
    deque_peek(dq, &result);
    assert_equals(result, 42);
}

UNITT(deque_peek_empty) {
    Deque* dq = ctx->dq;
    int result = 42;
    deque_peek(dq, &result);
    assert_equals(result, 42);
}

UNITT(deque_add_first_order) {
    Deque* dq = ctx->dq;
    int value = 42;
    deque_add_first(dq, &value);
    value = 43;
    deque_add_first(dq, &value);
    int result;
    deque_peek(dq, &result);
    assert_equals(result, 43);
}

UNITT(deque_add_last_order) {
    Deque* dq = ctx->dq;
    int value = 42;
    deque_add_last(dq, &value);
    value = 43;
    deque_add_last(dq, &value);
    int result;
    deque_peek(dq, &result);
    assert_equals(result, 42);
}

UNITT_RUN(deque)

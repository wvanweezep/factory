#define UNITT_AFTER_EACH_DEFINED
#include "unitt/unitt.h"

#include <stdbool.h>
#include "unitt/assert.h"
#include "logging/exception.h"

UNITT_INIT

UNITT_AFTER_EACH {
    const ExceptionContext* context = exception_get_context();
    for (size_t i = 0; i < context->stack->count; i++)
        exception_clear_last();
}

UNITT(try_isolated) {
    try throw(RuntimeException, "msg");
    const Exception* e = (Exception*)deque_get_first(exception_get_context()->stack);
    assert_not_null(e);
    assert_equals(e->type, RuntimeException);
    assert_str_equals(e->message, "msg");
}

UNITT(try_catch_succes) {
    bool caught = false;
    try {}
    catch_any caught = true;
    assert_false(caught);
}

UNITT(try_catch_single_catch) {
    bool caught = false;
    try throw(RuntimeException, "");
    catch (RuntimeException) caught = true;
    assert_true(caught);
}

UNITT(try_catch_multi_catch) {
    bool caught = false;
    try throw(RuntimeException, "");
    catch (IllegalArgumentException | RuntimeException)
        caught = true;
    assert_true(caught);
}

UNITT(try_catch_chain_catch) {
    bool caught = false;
    try throw(RuntimeException, "");
    catch (IllegalArgumentException) caught = false;
    catch (RuntimeException) caught = true;
    catch (AssertionException) caught = false;
    catch_any caught = false;
    assert_true(caught);
}

// UNITT(try_catch_nested) {
//     bool caught = false;
//     try {
//         try {
//             throw(IllegalArgumentException, "");
//         } catch (IllegalArgumentException) {
//             throw(RuntimeException, "");
//         }
//     } catch (RuntimeException) {
//         caught = true;
//     }
//     assert_true(caught);
// }

UNITT(throw_format) {
    try throw(RuntimeException, "%s %d", "test", 1);
    const Exception* e = (Exception*)deque_get_first(exception_get_context()->stack);
    assert_not_null(e);
    assert_str_equals(e->message, "test 1");
}

UNITT_RUN(exception)

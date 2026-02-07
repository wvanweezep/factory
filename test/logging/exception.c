#include "unitt/unitt.h"

#include <stdbool.h>
#include "unitt/assert.h"
#include "logging/exception.h"

UNITT_INIT

UNITT(try_catch_succes) {
    bool caught = false;
    try {}
    catch_any caught = true;
    finalize;
    assert_false(caught);
}

UNITT(try_catch_single_catch) {
    bool caught = false;
    try throw(RuntimeException, "");
    catch (RuntimeException) caught = true;
    finalize;
    assert_true(caught);
}

UNITT(try_catch_multi_catch) {
    bool caught = false;
    try throw(RuntimeException, "");
    catch (IllegalArgumentException | RuntimeException)
        caught = true;
    finalize;
    assert_true(caught);
}

UNITT(try_catch_chain_catch) {
    bool caught = false;
    try throw(RuntimeException, "");
    catch (IllegalArgumentException) caught = false;
    catch (RuntimeException) caught = true;
    catch (AssertionException) caught = false;
    catch_any caught = false;
    finalize;
    assert_true(caught);
}

UNITT(try_catch_nested) {
    bool caught = false;
    try {
        try {
            throw(IllegalArgumentException, "");
        } catch (IllegalArgumentException) { }
        finalize;
        throw(RuntimeException, "THIS");
    } catch (RuntimeException) {
        caught = true;
    } finalize;
    assert_true(caught);
}

// UNITT(throw_format) {
//     try throw(RuntimeException, "%s %d", "test", 1);
//     const Exception* e = (Exception*)deque_get_first(exception_context()->stack);
//     assert_not_null(e);
//     assert_str_equals(e->message, "test 1");
// }

UNITT_RUN(exception)

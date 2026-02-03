#include "logging/exception.h"

ExceptionContext exception_context = {NULL, {0}};
static int initialized = 0;

// Struct matching ExceptionType to a string version
typedef struct ExceptionTypeInfo {
    ExceptionType type;
    const char* name;
} ExceptionTypeInfo;

// Predefined array mapping each ExceptionType to its string version
static const ExceptionTypeInfo exception_type_names[] = {
    {RuntimeException, "RuntimeException"},
    {AssertionException, "AssertionException"},
    {OutOfRangeException, "OutOfRangeException"},
    {NullPointerException, "NullPointerException"},
    {OutOfMemoryException, "OutOfMemoryException"},
    {IllegalArgumentException, "IllegalArgumentException"}
};

const char* exception_to_string(ExceptionType type) {
    for (size_t i = 0; i < sizeof(exception_type_names)/sizeof(*exception_type_names); ++i)
        if (exception_type_names[i].type == type) return exception_type_names[i].name;
    return "UnknownException";
}

static void exception_init() {
    exception_context = (ExceptionContext){deque_create(sizeof(Exception), 8), {0}};
    initialized = 1;
}

ExceptionContext* exception_get_context() {
    if (!initialized) exception_init();
    return &exception_context;
}

void exception_clear_last() {
    Exception e;
    deque_remove_last(exception_get_context()->stack, &e);
    if (e.message) free(e.message);
}
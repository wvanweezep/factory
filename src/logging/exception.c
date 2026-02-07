#include "logging/exception.h"

static ExceptionContext base_exception_context = {
    0, {}, {0}, NULL};
static ExceptionContext* current_exception_context = &base_exception_context;
static bool initialized = false;

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
    if (setjmp(current_exception_context->env) == 0) {
        initialized = true;
        return;
    } exception_handle_uncaught();
}

ExceptionContext* exception_context() {
    return current_exception_context;
}

void exception_new_context() {
    if (!initialized) exception_init();
    if (current_exception_context->thrown_exception)
        exception_handle_uncaught();
    ExceptionContext* current = current_exception_context;
    ExceptionContext* next = malloc(sizeof(ExceptionContext));
    *next = (ExceptionContext){false, {}, {0}, current};
    current_exception_context = next;
}

void exception_release_context() {
    ExceptionContext* current = current_exception_context;
    if (!current->prev) return;
    if (current->thrown_exception && current->exception.message)
        free(current->exception.message);
    current_exception_context = current->prev;
    free(current);
}

void exception_handle_uncaught() {
    printf(current_exception_context->exception.message, 0);
    exit(1);
}
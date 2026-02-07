#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <setjmp.h>

/// Enum indicating the event for which an Exception is thrown
typedef enum ExceptionType {
    RuntimeException = 1,               // Thrown for an unspecified runtime error
    AssertionException = 2,             // Thrown for a failed (custom) assertion
    OutOfRangeException = 4,            // Thrown for an out-of-range access in an array
    NullPointerException = 8,           // Thrown for an unexpected NULL pointer
    OutOfMemoryException = 16,          // Thrown for an allocation error
    IllegalArgumentException = 32       // Thrown when an invalid argument is passed
} ExceptionType;

/// Data structure for tracking an ExceptionType and their origin
typedef struct Exception {
    ExceptionType type;                 // Type of the Exception that occurred
    char* message;                      // Message providing context to the Exception
    char* file;                         // Path to the file where the Exception occurred
    size_t line;                        // Line number where the Exception was originally thrown
} Exception;

/// Data structure for tracking the Exception stack and current environment
typedef struct ExceptionContext {
    bool thrown_exception;              // Boolean tracking if an Exception has been thrown in the current context
    Exception exception;                // Exception stack storing thrown exceptions
    jmp_buf env;                        // Current environment (for restoration)
    struct ExceptionContext* prev;      // Pointer to the previous context to return to
} ExceptionContext;

/**
 * Converts an ExceptionType into a string form.
 * @param type type of exception to stringify
 * @return string form of the ExceptionType
 */
const char* exception_to_string(ExceptionType type);

/**
 * Getter for the global ExceptionContext, ensuring it has been initialized.
 * @return globally accessible ExceptionContext
 */
ExceptionContext* exception_context();

void exception_new_context();

void exception_release_context();

void exception_handle_uncaught();

/**
 * Macro handling the throwing of an Exception with a formatted message.
 * @param exception_type type of the Exception to throw
 * @param fmt message to attach with potential formatting requirements
 */
#define throw(exception_type, fmt, ...) \
    do { \
        ExceptionContext* ectx = exception_context(); \
        ectx->thrown_exception = true; \
        int len = snprintf(NULL, 0, fmt __VA_OPT__(,) __VA_ARGS__); \
        char* buffer = malloc(len + 1); \
        if (!buffer) { \
            ectx->exception = (Exception){OutOfMemoryException, \
                NULL, __FILE__, __LINE__}; \
            longjmp(ectx->env, 1); \
        } \
        snprintf(buffer, len + 1, fmt __VA_OPT__(,) __VA_ARGS__); \
        ectx->exception = (Exception){exception_type, buffer, __FILE__, __LINE__}; \
        longjmp(ectx->env, 1); \
    } while(0)


/// Macro setting up a try-catch block by saving the current context.
#define try \
    exception_new_context(); \
    if (setjmp(exception_context()->env) == 0)

/**
 * Macro completing a try-catch block by catching specific thrown Exceptions.
 * @param exception_types type(s) of the expected Exception to catch
 */
#define catch(exception_types) else if (exception_context()->thrown_exception && \
    ((exception_types) & exception_context()->exception.type))

/// Macro completing a try-catch block by catching any thrown Exception.
#define catch_any else if (true)

/// Macro required to be called after a try-catch block to clear context and catch uncaught Exceptions.
#define finalize \
    else exception_handle_uncaught(); \
    exception_release_context()

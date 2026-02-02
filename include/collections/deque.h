#pragma once

#include <stdint.h>

typedef void (*DequeDestructor)(void* value);

// Collection for storing data of a generic type in a deque.
typedef struct Deque {
    uint8_t* entries;           // Array containing the queue entries
    size_t head;                // Index for the front of the queue
    size_t tail;                // Index for the back of the queue
    size_t element_size;        // Size of each element in bytes
    size_t capacity;            // Number of elements that can be stored (multiple of element_size)
    size_t count;               // Current number of entries in the queue
} Deque;

Deque* deque_create(size_t element_size, size_t initial_size);

void deque_peek(const Deque* dq, void* out);

void deque_add_first(Deque* dq, const void* value);

void deque_add_last(Deque* dq, const void* value);

void deque_remove_first(Deque* dq, void* out);

void deque_remove_last(Deque* dq, void* out);

void deque_clear(Deque* dq, DequeDestructor destructor);

void deque_free(Deque* dq, DequeDestructor destructor);

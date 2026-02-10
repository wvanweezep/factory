#pragma once

#include <stdint.h>
#include "logging/exception.h"

typedef void (*DequeDestructor)(void* value);

// TODO: Add purpose of Collection in docs
// TODO: Add implementation in docs

// Collection for storing data of a generic type in a deque.
typedef struct Deque {
    uint8_t* entries;           // Array containing the queue entries
    size_t head;                // Index for the front of the queue
    size_t tail;                // Index for the back of the queue
    size_t element_size;        // Size of each element in bytes
    size_t capacity;            // Number of elements that can be stored (multiple of element_size)
    size_t count;               // Current number of entries in the queue
} Deque;

/**
 * Creates a new empty Deque of an initial size for a provided element size.
 * @param element_size size of the elements that will be stored in the Deque
 * @param initial_size initial size (in elements) the deque can hold
 * @return pointer to newly created Deque
 * @throws OutOfMemoryException thrown when the memory allocation failed
 * @throws IllegalArgumentException thrown when the provided element size is zero
 */
Deque* deque_create(size_t element_size, size_t initial_size);

/**
 * Getter for the size of the Deque.
 * @param dq Deque to retrieve the size from
 * @return number of entries in the Deque
 * @throws IllegalArgumentException thrown when the provided Deque is NULL
 */
size_t deque_size(const Deque* dq);

/**
 * Retrieves the entry at the head of the Deque.
 * @param dq Deque to retrieve the entry from
 * @return immutable void pointer to the first entry in the Deque
 * @throws IllegalArgumentException thrown when the provided Deque is NULL or empty
 */
const void* deque_get_first(const Deque* dq);

/**
 * Retrieves the entry at the tail of the Deque.
 * @param dq Deque to retrieve the entry from
 * @return immutable void pointer to the last entry in the Deque
 * @throws IllegalArgumentException thrown when the provided Deque is NULL or empty
 */
const void* deque_get_last(const Deque* dq);

/**
 * Retrieves an entry of the Deque at a specified index.
 * @param dq Deque to retrieve the entry from
 * @param index index of the requested entry
 * @return immutable void pointer to the entry at the requested index in the Deque
 * @throws IllegalArgumentException thrown when the provided Deque is NULL or empty
 * @throws OutOfRangeException thrown when the provided index exceeds the Deque's size
 */
const void* deque_get(const Deque* dq, size_t index);

/**
 * Adds an entry to the head of the Deque.
 * @param dq Deque to add the entry to
 * @param value entry to add to the Deque
 * @throws IllegalArgumentException thrown when the provided Deque or value is NULL
 */
void deque_add_first(Deque* dq, const void* value);

/**
 * Adds an entry to the tail of the Deque.
 * @param dq Deque to add the entry to
 * @param value entry to add to the Deque
 * @throws IllegalArgumentException thrown when the provided Deque or value is NULL
 */
void deque_add_last(Deque* dq, const void* value);

/**
 * Extracts the entry at the head of the Deque.
 * @param dq Deque to extract an entry from
 * @param out buffer to put the extracted entry in
 * @throws IllegalArgumentException thrown when the provided Deque is NULL or empty
 */
void deque_extract_first(Deque* dq, void* out);

/**
 * Extracts the entry at the tail of the Deque.
 * @param dq Deque to extract the entry from
 * @param out buffer to put the extracted entry in
 * @throws IllegalArgumentException thrown when the provided Deque is NULL or empty
 */
void deque_extract_last(Deque* dq, void* out);

/**
 * Deletes the entry at the head of the Deque.
 * @param dq Deque to delete the entry from
 * @param destructor function to free any occupied memory by the entry
 * @throws IllegalArgumentException thrown when the provided Deque is NULL or empty
 */
void deque_delete_first(Deque* dq, DequeDestructor destructor);

/**
 * Deletes the entry at the tail of the Deque.
 * @param dq Deque to delete the entry from
 * @param destructor function to free any occupied memory by the entry
 * @throws IllegalArgumentException thrown when the provided Deque is NULL or empty
 */
void deque_delete_last(Deque* dq, DequeDestructor destructor);

/**
 * Clears and destroys all entries in the Deque.
 * @param dq Deque to clear
 * @param destructor function to free any occupied memory by an entry
 * @throws IllegalArgumentException thrown when the provided Deque is NULL
 */
void deque_clear(Deque* dq, DequeDestructor destructor);

/**
 * Destroys the Deque and its entries.
 * @param dq Deque to destroy
 * @param destructor function to free any occupied memory by an entry
 * @throws IllegalArgumentException thrown when the provided Deque is NULL
 */
void deque_free(Deque* dq, DequeDestructor destructor);

#include "collections/deque.h"

#include <stdlib.h>
#include <string.h>

Deque* deque_create(size_t element_size, size_t initial_size) {
    Deque* dq = malloc(sizeof(Deque));
    dq->entries = calloc(initial_size, element_size);
    dq->head = 0;
    dq->tail = 0;
    dq->element_size = element_size;
    dq->capacity = initial_size;
    dq->count = 0;
    return dq;
}

const void* deque_get_first(const Deque* dq) {
    if (!dq || dq->count == 0) return NULL;
    return &dq->entries[dq->head];
}

const void* deque_get_last(const Deque* dq) {
    if (!dq || dq->count == 0) return NULL;
    return &dq->entries[dq->tail];
}

static void resize(Deque* dq) {}

void deque_add_first(Deque* dq, const void* value) {
    if (!dq) return;
    if (dq->count == dq->capacity) resize(dq);
    dq->head = (dq->head - dq->element_size) % (dq->capacity * dq->element_size);
    memcpy(&dq->entries[dq->head], value, dq->element_size);
    dq->count++;
}

void deque_add_last(Deque* dq, const void* value) {
    if (!dq) return;
    if (dq->count == dq->capacity) resize(dq);
    dq->tail = (dq->tail + dq->element_size) % (dq->capacity * dq->element_size);
    if (dq->count == 0) dq->head = dq->tail;
    memcpy(&dq->entries[dq->tail], value, dq->element_size);
    dq->count++;
}

void deque_remove_first(Deque* dq, void* out) {
    if (!dq || dq->count == 0) return;
    memcpy(out, &dq->entries[dq->head], dq->element_size);
    dq->head = (dq->head + dq->element_size) % (dq->capacity * dq->element_size);
    dq->count--;
}

void deque_remove_last(Deque* dq, void* out) {
    if (!dq || dq->count == 0) return;
    memcpy(out, &dq->entries[dq->tail], dq->element_size);
    dq->tail = (dq->tail - dq->element_size) % (dq->capacity * dq->element_size);
    dq->count--;
}

void deque_clear(Deque* dq, DequeDestructor destructor) {
    if (!dq || dq->count == 0) return;
    for (size_t i = 0; i < dq->count; i++) {
        const size_t index = (dq->head + i * dq->element_size)
            % (dq->capacity * dq->element_size);
        if (destructor) destructor(&dq->entries[index]);
    }
    dq->head = 0;
    dq->tail = 0;
    dq->count = 0;
}

void deque_free(Deque* dq, DequeDestructor destructor) {
    deque_clear(dq, destructor);
    free(dq->entries);
    free(dq);
}

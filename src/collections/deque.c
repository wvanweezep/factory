#include "collections/deque.h"

#include <stdlib.h>
#include <string.h>

Deque* deque_create(size_t element_size, size_t initial_size) {
    if (element_size == 0) throw(IllegalArgumentException,
        "Deque must have an element size greater than zero");
    Deque* dq = malloc(sizeof(Deque));
    if (!dq) throw(OutOfMemoryException, "Unable to allocate memory");
    dq->entries = calloc(initial_size, element_size);
    if (!dq->entries) throw(OutOfMemoryException, "Unable to allocate memory");
    dq->head = 0;
    dq->tail = 0;
    dq->element_size = element_size;
    dq->capacity = initial_size;
    dq->count = 0;
    return dq;
}

size_t deque_size(const Deque* dq) {
    if (!dq) throw(IllegalArgumentException,
        "Unable to retrieve the size with null pointer as Deque");
    return dq->count;
}

const void* deque_get_first(const Deque* dq) {
    if (!dq || dq->count == 0) throw(IllegalArgumentException,
        "Unable to retrieve entry %s", dq ? "from an empty Deque" :
        "with null pointer as Deque");
    return &dq->entries[dq->head];
}

const void* deque_get_last(const Deque* dq) {
    if (!dq || dq->count == 0) throw(IllegalArgumentException,
        "Unable to retrieve entry %s", dq ? "from an empty Deque" :
        "with null pointer as Deque");
    return &dq->entries[dq->tail];
}

const void* deque_get(const Deque* dq, size_t index) {
    if (!dq || dq->count == 0) throw(IllegalArgumentException,
        "Unable to retrieve entry %s", dq ? "from an empty Deque" :
        "with null pointer as Deque");
    if (index >= dq->count) throw(OutOfRangeException,
        "Provided index (%llu) is outside the range of the deque (%llu)", index, dq->count);
    return &dq->entries[(dq->head + index * dq->element_size)
        % (dq->capacity * dq->element_size)];
}

static void resize(Deque* dq) {
    uint8_t* arr = calloc(dq->capacity * 2, dq->element_size);
    if (dq->head > dq->tail) {
        const size_t head_size = dq->element_size * dq->capacity - dq->head;
        memcpy(arr, &dq->entries[dq->head], head_size);
        memcpy(&arr[head_size], dq->entries, dq->tail);
    } else memcpy(arr, &dq->entries[dq->head], dq->count * dq->element_size);
    free(dq->entries);
    dq->entries = arr;
}

void deque_add_first(Deque* dq, const void* value) {
    if (!dq) throw(IllegalArgumentException,
        "Unable to add entry with null pointer as Deque");
    if (!value) throw(IllegalArgumentException,
        "Unable to add entry to Deque with null pointer to entry");
    if (dq->count == dq->capacity) resize(dq);
    dq->head = (dq->head - dq->element_size) % (dq->capacity * dq->element_size);
    if (dq->count == 0) dq->tail = dq->head;
    memcpy(&dq->entries[dq->head], value, dq->element_size);
    dq->count++;
}

void deque_add_last(Deque* dq, const void* value) {
    if (!dq) throw(IllegalArgumentException,
        "Unable to add entry with null pointer as Deque");
    if (!value) throw(IllegalArgumentException,
        "Unable to add entry to Deque with null pointer to entry");
    if (dq->count == dq->capacity) resize(dq);
    dq->tail = (dq->tail + dq->element_size) % (dq->capacity * dq->element_size);
    if (dq->count == 0) dq->head = dq->tail;
    memcpy(&dq->entries[dq->tail], value, dq->element_size);
    dq->count++;
}

void deque_extract_first(Deque* dq, void* out) {
    if (!dq || dq->count == 0) throw(IllegalArgumentException,
        "Unable to extract entry %s", dq ? "from an empty Deque" :
        "with null pointer as Deque");
    if (out) memcpy(out, &dq->entries[dq->head], dq->element_size);
    dq->head = (dq->head + dq->element_size) % (dq->capacity * dq->element_size);
    dq->count--;
}

void deque_extract_last(Deque* dq, void* out) {
    if (!dq || dq->count == 0) throw(IllegalArgumentException,
        "Unable to extract entry %s", dq ? "from an empty Deque" :
        "with null pointer as Deque");
    if (out) memcpy(out, &dq->entries[dq->tail], dq->element_size);
    dq->tail = (dq->tail - dq->element_size) % (dq->capacity * dq->element_size);
    dq->count--;
}

void deque_delete_first(Deque* dq, DequeDestructor destructor) {
    if (!dq || dq->count == 0) throw(IllegalArgumentException,
        "Unable to delete entry %s", dq ? "from an empty Deque" :
        "with null pointer as Deque");
    if (destructor) destructor(&dq->entries[dq->head]);
    dq->head = (dq->head + dq->element_size) % (dq->capacity * dq->element_size);
    dq->count--;
}

void deque_delete_last(Deque* dq, DequeDestructor destructor) {
    if (!dq || dq->count == 0) throw(IllegalArgumentException,
        "Unable to delete entry %s", dq ? "from an empty Deque" :
        "with null pointer as Deque");
    if (destructor) destructor(&dq->entries[dq->tail]);
    dq->tail = (dq->tail - dq->element_size) % (dq->capacity * dq->element_size);
    dq->count--;
}

void deque_clear(Deque* dq, DequeDestructor destructor) {
    if (!dq) throw(IllegalArgumentException,
        "Unable to clear entries with null pointer as Deque");
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

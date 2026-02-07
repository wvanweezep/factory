#include "conveyer.h"

#include "logging/exception.h"
#include <stdio.h>

ConveyerLine* conveyer_create(size_t size) {
    if (size > 256) throw(IllegalArgumentException,
        "ConveyerLine size cannot exceed 256");

    ConveyerLine* conveyer = malloc(sizeof(ConveyerLine));
    if (!conveyer) throw(OutOfMemoryException, "Unable to allocate memory");
    conveyer->resources = calloc(size, sizeof(ResourceID));
    conveyer->indices = calloc(size, sizeof(uint8_t));
    if (!conveyer->resources || !conveyer->indices) throw(
        OutOfMemoryException, "Unable to allocate memory");

    conveyer->prev = NULL;
    conveyer->dynamic_head = 0;
    conveyer->dynamic_tail = size - 1;
    conveyer->static_head = size - 1;
    conveyer->static_tail = size - 1;
    conveyer->size = size;

    conveyer->indices[0] = size - 1;
    for (int i = 1; i < size; i++)
        conveyer->indices[i] = i - 1;

    return conveyer;
}

void conveyer_free(ConveyerLine* conveyer) {
    free(conveyer->resources);
    free(conveyer->indices);
    free(conveyer);
}

void conveyer_tick(ConveyerLine* c) {
    if (!c) throw(IllegalArgumentException,
        "Unable to tick conveyer with null pointer");

    if (c->resources[c->static_tail] == RESOURCE_EMPTY) {
        if (c->static_tail != c->dynamic_tail) {
            c->indices[c->dynamic_head] = c->static_tail;
            c->indices[c->static_head] = c->dynamic_tail;
            c->dynamic_tail = c->static_tail;
        }

        c->dynamic_head = c->indices[c->dynamic_head];
        c->dynamic_tail = c->indices[c->dynamic_tail];
        c->static_head = c->dynamic_tail;
        c->static_tail = c->dynamic_tail;
    }
    else {
        while (c->resources[c->dynamic_tail] != RESOURCE_EMPTY && c->dynamic_tail != c->dynamic_head) {
            const size_t new_dt = c->indices[c->dynamic_tail];
            c->indices[c->static_head] = c->dynamic_tail;
            c->static_head = c->dynamic_tail;
            c->dynamic_tail = new_dt;
        }
        c->indices[c->dynamic_head] = c->dynamic_tail;
        c->dynamic_head = c->indices[c->dynamic_head];
        c->dynamic_tail = c->indices[c->dynamic_tail];
    }
}

bool conveyer_push_resource(ConveyerLine* conveyer, ResourceID resource) {
    if (!conveyer) throw(IllegalArgumentException,
        "Unable to push resource to conveyer with null pointer");
    if (conveyer->resources[conveyer->dynamic_head]) return false;
    conveyer->resources[conveyer->dynamic_head] = resource;
    return true;
}

const ResourceID* conveyer_peek_resource(const ConveyerLine* conveyer) {
    return &conveyer->resources[conveyer->static_tail];
}

void conveyer_pop_resource(ConveyerLine* conveyer, ResourceID* out) {
    if (out) *out = conveyer->resources[conveyer->static_tail];
    conveyer->resources[conveyer->static_tail] = RESOURCE_EMPTY;
}

void conveyer_draw(ConveyerLine* c) {
    size_t current = c->static_tail;
    while (current != c->static_head) {
        printf(c->resources[current] ? "X" : "-");
        current = c->indices[current];
    } if (c->static_head != c->dynamic_tail)
        printf(c->resources[current] ? "X" : "-");
    current = c->dynamic_tail;
    do {
        printf(c->resources[current] ? "X" : "-");
        current = c->indices[current];
    } while (current != c->dynamic_tail);
    printf("\n");
}
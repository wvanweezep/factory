#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "core/factory.h"

#define CONVEYER_MAX_LENGTH 256

typedef uint8_t ResourceID;

typedef enum ResourceType {
    RESOURCE_EMPTY = 0,
    RESOURCE_FILLED = 1
} ResourceType;

// dh --- dt sh --- st
typedef struct ConveyerLine {
    FactoryComp* prev;
    ResourceID* resources;
    uint8_t* indices;           // Indicate the logical prev index
    size_t dynamic_head;
    size_t dynamic_tail;
    size_t static_head;
    size_t static_tail;
    size_t size;
} ConveyerLine;


ConveyerLine* conveyer_create(size_t size);

void conveyer_free(ConveyerLine* conveyer);

void conveyer_tick(ConveyerLine* conveyer);

bool conveyer_push_resource(ConveyerLine* conveyer, ResourceID resource);

const ResourceID* conveyer_peek_resource(const ConveyerLine* conveyer);

void conveyer_pop_resource(ConveyerLine* conveyer, ResourceID* out);

void conveyer_draw(ConveyerLine* conveyer);

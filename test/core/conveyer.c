#include "unitt/unitt.h"

#include "../../include/core/conveyer.h"

#include <stdio.h>

UNITT_INIT

UNITT(conv) {
    ConveyerLine* c = conveyer_create(16);
    conveyer_push_resource(c, RESOURCE_FILLED);
    conveyer_draw(c);
    for (int i = 0; i < 25; i++) {
        conveyer_tick(c);
        if (i % 4 == 0) conveyer_push_resource(c, RESOURCE_FILLED);
        conveyer_draw(c);
    }

    conveyer_pop_resource(c, NULL);
    conveyer_draw(c);
    for (int i = 0; i < 40; i++) {
        conveyer_tick(c);
        if (i % 4 == 0) conveyer_push_resource(c, RESOURCE_FILLED);
        conveyer_draw(c);
    }

    conveyer_draw(c);
    for (int i = 0; i < 40; i++) {
        conveyer_tick(c);
        if (i % 4 == 0) conveyer_pop_resource(c, NULL);
        if (i % 7 == 1) conveyer_push_resource(c, RESOURCE_FILLED);
        conveyer_draw(c);
    }
}

UNITT_RUN(conveyer)
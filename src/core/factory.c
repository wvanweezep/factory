#include "core/factory.h"

#include <stdlib.h>

FactoryContext* factory_new_context() {
    FactoryContext* context = malloc(sizeof(FactoryContext));
    if (!context) throw(OutOfMemoryException, "Unable to allocate memory");
    context->chunk_map = hashmap_create(8, std_hash_func);
    context->tile_comp_map = hashmap_create(8, std_hash_func);
    // TODO: Change to ArrayList implementation
    //context->comp_list = deque_create(sizeof(FactoryComp*), 8);
    if (!context->chunk_map || !context->tile_comp_map || !context->comp_list)
        throw(OutOfMemoryException, "Unable to allocate memory");
    return context;
}

size_t factory_at(const FactoryContext* context, vec2i tile_index) {
    if (!context) throw(IllegalArgumentException,
        "Unable to locate FactoryComp with null pointer as context");
    size_t index = SIZE_MAX;
    hashmap_get(context->tile_comp_map, vec2i_hash(tile_index), (uint64_t*) &index);
    return index;
}

size_t factory_add(FactoryContext* context, FactoryComp* comp) {
    if (!context) throw(IllegalArgumentException,
        "Unable to add FactoryComp with null pointer as context");
    if (!comp) throw(IllegalArgumentException,
        "Unable to add null pointer to factory");

    return 0;
}
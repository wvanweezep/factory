#pragma once

#include "logging/exception.h"
#include "collections/hashmap.h"
#include "math/vec2.h"
#include "camera.h"
#include "collections/deque.h"

typedef enum FactoryCompType {
    FACTORY_COMP_CONVEYER = 1
} FactoryCompType;

// Single component of a factory.
typedef struct FactoryComp {
    FactoryCompType type;               // Type of FactoryComp for state interpretation
    Deque* tiles;                   // List of global tiles the FactoryComp occupies
    void* state;                        // Generic pointer to the component's state
} FactoryComp;

// Context storing an entire factory.
typedef struct FactoryContext {
    HashMap* chunk_map;                 // Hashmap with occupied chunks
    HashMap* tile_comp_map;             // Hashmap mapping global tile indices to a FactoryComp index
    Deque* comp_list;               // List of all FactoryComp in the factory
} FactoryContext;

/**
 * Create a new FactoryContext to store an entire factory.
 * @return a newly allocated FactoryContext
 * @throws OutOfMemoryException thrown when the memory allocation failed
 */
FactoryContext* factory_new_context();

/**
 * Find the index of the FactoryComp at the provided global tile index.
 * @param context factory to search through
 * @param tile_index global tile index of the FactoryComp to find
 * @return index of the FactoryComp at the given tile, or SIZE_MAX if nothing is found
 * @throws IllegalArgumentException thrown when the provided context is NULL
 */
size_t factory_at(const FactoryContext* context, vec2i tile_index);

/**
 * Add a FactoryComp to the factory.
 * @param context factory to add the FactoryComp to
 * @param comp FactoryComp to add to the factory
 * @return index of the registered FactoryComp, or SIZE_MAX if any tile index is already occupied
 * @throws IllegalArgumentException thrown when either the provided context or comp is NULL
 */
size_t factory_add(FactoryContext* context, FactoryComp* comp);

/**
 * Removes a FactoryComp from the factory at a provided global tile index.
 * @param context factory to remove the FactoryComp from
 * @param tile_index global tile index of the FactoryComp
 * @return true if a FactoryComp was removed from the factory
 * @throws IllegalArgumentException thrown when the provided context is NULL
 */
bool factory_remove(FactoryContext* context, vec2i tile_index);

/**
 * Clears an entire factory and deallocates all FactoryComp's.
 * @param context factory to clear
 * @throws IllegalArgumentException thrown when the provided context is NULL
 */
void factory_clear(FactoryContext* context);

/**
 * Destroys the factory and its components.
 * @param context factory to destroy
 * @throws IllegalArgumentException thrown when the provided context is NULL
 */
void factory_free(FactoryContext* context);

/**
 * Render the factory to the screen with a provided camera.
 * @param context factory to render
 * @param camera camera to use for the rendering
 * @throws IllegalArgumentException thrown when either the provided context or camera is NULL
 */
void factory_render(const FactoryContext* context, const fCamera camera);

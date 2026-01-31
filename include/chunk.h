#pragma once

#include <math.h>
#include "tile.h"
#include "math/vec2.h"


typedef struct Chunk {
    vec2i position;
    TileID tiles[CHUNK_SIZE][CHUNK_SIZE];
} Chunk;

/**
 * Convert global position to chunk index.
 * @param world_pos global position for conversion
 * @return index of the chunk at the global position
 */
vec2i chunk_from_world(vec2f world_pos);

/**
 * Convert chunk index to global position.
 * @param chunk_index chunk index for conversion
 * @return global position of the chunk
 */
vec2f chunk_to_world(vec2i chunk_index);

/**
 * Align global position to chunk grid.
 * @param world_pos global position to align
 * @return grid aligned global position
 */
vec2f chunk_align_world(vec2f world_pos);






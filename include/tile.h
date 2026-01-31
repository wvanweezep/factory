#pragma once

#include <stdint.h>
#include "math/vec2.h"

#define TILE_SIZE 32
#define CHUNK_SIZE 16
#define CHUNK_WORLD_SIZE (TILE_SIZE * CHUNK_SIZE)

typedef uint8_t TileID;

typedef enum TileType {
    TILE_EMPTY = 0,
    TILE_FILLED = 1
} TileType;

/**
 * Convert a TileType to its corresponding TileID.
 * @param tile_type tile type to convert
 * @return corresponding TileID
 */
static inline TileID tile_id_from_type(TileType tile_type) {
    return (TileID) tile_type;
}

/**
 * Convert a TileID to its corresponding TileType.
 * @param tile_id tile id to convert
 * @return corresponding TileType
 */
static inline TileType tile_type_from_id(TileID tile_id) {
    return (TileType) tile_id;
}

/**
 * Convert global position to local tile index.
 * @param world_pos global position for conversion
 * @return local tile index of the chunk at this global position
 */
vec2i tile_from_world(vec2f world_pos);

/**
 * Convert local tile index of a chunk to a global position.
 * @param chunk_offset offset of the chunk position
 * @param tile_index index of the local tile
 * @return global position of the local tile
 */
vec2f tile_to_world(vec2f chunk_offset, vec2i tile_index);

/**
 * Align global position to the tile grid.
 * @param world_pos global position to align
 * @return grid aligned global position
 */
vec2f tile_align_world(vec2f world_pos);
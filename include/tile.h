#pragma once

#include <stdint.h>
#include "math/vec2.h"

#define TILE_SIZE 64
#define CHUNK_SIZE 16
#define CHUNK_WORLD_SIZE (TILE_SIZE * CHUNK_SIZE)

typedef uint8_t TileID;

typedef enum TileType {
    TILE_EMPTY = 0,
    TILE_CONVEYER_EAST = 1,
    TILE_CONVEYER_NORTH = 2,
    TILE_CONVEYER_WEST = 3,
    TILE_CONVEYER_SOUTH = 4,
    TILE_FILLED = 5
} TileType;

typedef enum TileDirectionIO {
    DIR_INPUT_NORTH = 1,
    DIR_INPUT_EAST = 2,
    DIR_INPUT_SOUTH = 4,
    DIR_INPUT_WEST = 8,
    DIR_OUTPUT_NORTH = 16,
    DIR_OUTPUT_EAST = 32,
    DIR_OUTPUT_SOUTH = 64,
    DIR_OUTPUT_WEST = 128
} Direction;

typedef struct TileData {
    uint8_t io_dir;
} TileData;

static TileData tile_data[256] = {
    {0},
    {DIR_INPUT_WEST | DIR_OUTPUT_EAST},
    {DIR_INPUT_SOUTH | DIR_OUTPUT_NORTH},
    {DIR_INPUT_EAST | DIR_INPUT_WEST},
    {DIR_INPUT_NORTH | DIR_OUTPUT_SOUTH},
    {0}
};

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
#pragma once

#include <stdint.h>
#include "math/vec2.h"

#define TILE_SIZE 64
#define CHUNK_SIZE 16
#define CHUNK_WORLD_SIZE (TILE_SIZE * CHUNK_SIZE)

typedef uint8_t TileID;

typedef enum TileType {
    TILE_EMPTY = 0,
    TILE_CONVEYER_WE = 1,
    TILE_CONVEYER_WN = 2,
    TILE_CONVEYER_WS = 3,
    TILE_CONVEYER_EW = 4,
    TILE_CONVEYER_EN = 5,
    TILE_CONVEYER_ES = 6,
    TILE_CONVEYER_NS = 7,
    TILE_CONVEYER_NW = 8,
    TILE_CONVEYER_NE = 9,
    TILE_CONVEYER_SN = 10,
    TILE_CONVEYER_SW = 11,
    TILE_CONVEYER_SE = 12,
    TILE_FILLED = 13
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
    {0},                                        // 0    TILE_EMPTY
    {DIR_INPUT_WEST | DIR_OUTPUT_EAST},         // 1    TILE_CONVEYER_WE
    {DIR_INPUT_WEST | DIR_OUTPUT_NORTH},        // 2    TILE_CONVEYER_WN
    {DIR_INPUT_WEST | DIR_OUTPUT_SOUTH},        // 3    TILE_CONVEYER_WS
    {DIR_INPUT_EAST | DIR_OUTPUT_WEST},         // 4    TILE_CONVEYER_EW
    {DIR_INPUT_EAST | DIR_OUTPUT_NORTH},        // 5    TILE_CONVEYER_EN
    {DIR_INPUT_EAST | DIR_OUTPUT_SOUTH},        // 6    TILE_CONVEYER_ES
    {DIR_INPUT_NORTH | DIR_OUTPUT_SOUTH},       // 7    TILE_CONVEYER_NS
    {DIR_INPUT_NORTH | DIR_OUTPUT_WEST},        // 8    TILE_CONVEYER_NW
    {DIR_INPUT_NORTH | DIR_OUTPUT_EAST},        // 9    TILE_CONVEYER_NE
    {DIR_INPUT_SOUTH | DIR_OUTPUT_NORTH},       // 10   TILE_CONVEYER_SN
    {DIR_INPUT_SOUTH | DIR_OUTPUT_WEST},        // 11   TILE_CONVEYER_SW
    {DIR_INPUT_SOUTH | DIR_OUTPUT_EAST},        // 12   TILE_CONVEYER_SE
    {0}                                         // 13   TILE_FILLED
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
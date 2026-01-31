#include "tile.h"

#include <math.h>

vec2i tile_from_world(vec2f world_pos) {
    vec2i v;
    v.x = (int) floorf(world_pos.x / TILE_SIZE) % CHUNK_SIZE;
    v.y = (int) floorf(world_pos.y / TILE_SIZE) % CHUNK_SIZE;
    v.x = v.x >= 0 ? v.x : 16 + v.x;
    v.y = v.y >= 0 ? v.y : 16 + v.y;
    return v;
}

vec2f tile_to_world(vec2f chunk_offset, vec2i tile_index) {
    return (vec2f) {chunk_offset.x + (float) tile_index.x * TILE_SIZE,
                    chunk_offset.y + (float) tile_index.y * TILE_SIZE};
}

vec2f tile_align_world(vec2f world_pos) {
    return (vec2f) {floorf(world_pos.x / TILE_SIZE) * TILE_SIZE,
                    floorf(world_pos.y / TILE_SIZE) * TILE_SIZE};
}
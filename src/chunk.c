#include "chunk.h"

vec2i chunk_from_world(vec2f world_pos) {
    return (vec2i) {(int) floorf(world_pos.x / CHUNK_WORLD_SIZE),
                    (int) floorf(world_pos.y / CHUNK_WORLD_SIZE)};
}

vec2f chunk_to_world(vec2i chunk_index) {
    return (vec2f) {(float) chunk_index.x * CHUNK_WORLD_SIZE,
                    (float) chunk_index.y * CHUNK_WORLD_SIZE};
}

vec2f chunk_align_world(vec2f world_pos) {
    return (vec2f) {floorf(world_pos.x / CHUNK_WORLD_SIZE) * CHUNK_WORLD_SIZE,
                    floorf(world_pos.y / CHUNK_WORLD_SIZE) * CHUNK_WORLD_SIZE};
}
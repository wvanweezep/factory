#include "chunk.h"
#include <math.h>
#include <stdlib.h>

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

Chunk* chunk_at(const ChunkMap* chunk_map, vec2f world_pos) {
    const uint64_t key = vec2i_hash(chunk_from_world(world_pos));
    uint64_t chunk;
    return hashmap_get(chunk_map->map, key, &chunk) ? (Chunk*) chunk : NULL;
}

Chunk* chunk_force_get(ChunkMap* chunk_map, vec2f world_pos) {
    const uint64_t key = vec2i_hash(chunk_from_world(world_pos));
    uint64_t chunk;
    if (!hashmap_get(chunk_map->map, key, &chunk)) {
        chunk = (uint64_t) calloc(1, sizeof(Chunk));
        ((Chunk*)chunk)->position = chunk_from_world(world_pos);
        hashmap_insert(chunk_map->map, key, chunk);
    } return (Chunk*) chunk;
}

void chunk_set_tile(ChunkMap* chunk_map, vec2f world_pos, TileID tile_id) {
    Chunk* chunk = chunk_force_get(chunk_map, world_pos);
    const vec2i tile_index = tile_from_world(world_pos);
    chunk->tiles[tile_index.y][tile_index.x] = tile_id;
}
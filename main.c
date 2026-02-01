#include <stdio.h>

#include "raylib.h"
#include "chunk.h"
#include "camera.h"

#define CAM_SPEED 10.0f
#define SCREEN_WIDTH 2000
#define SCREEN_HEIGHT 1500

static void DrawBox(vec2i xy, vec2i wh, Color c) {
    DrawLine(xy.x, xy.y,xy.x + wh.x, xy.y, c);
    DrawLine(xy.x, xy.y,xy.x, xy.y + wh.y, c);
    DrawLine(xy.x + wh.x, xy.y + wh.y,xy.x + wh.x, xy.y, c);
    DrawLine(xy.x + wh.x, xy.y + wh.y,xy.x, xy.y + wh.y, c);
}

static void chunk_render(const Chunk* chunk) {
    if (!chunk) return;
    const vec2i screen_pos = cam_world_to_screen(&main_camera, chunk_to_world(chunk->position));
    for (int y = 0; y < CHUNK_SIZE; y++) {
        for (int x = 0; x < CHUNK_SIZE; x++) {
            if (chunk->tiles[y][x] == TILE_EMPTY) continue;
            DrawBox((vec2i){screen_pos.x + x * TILE_SIZE, screen_pos.y + y * TILE_SIZE},
                (vec2i){TILE_SIZE, TILE_SIZE}, WHITE);
        }
    }
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Window");

    ChunkMap chunks = {hashmap_create(32, std_hash_func)};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        SetWindowTitle(TextFormat("FPS: %d - Chunks Registered = %d", GetFPS(),
            chunks.map->count));

        Vector2 mposd = GetMousePosition();
        vec2i mpos = {(int) mposd.x, (int) mposd.y};
        vec2f worldpoint = cam_screen_to_world(&main_camera, mpos);

        if (IsKeyDown(KEY_W)) main_camera.position.y -= CAM_SPEED;
        if (IsKeyDown(KEY_S)) main_camera.position.y += CAM_SPEED;
        if (IsKeyDown(KEY_A)) main_camera.position.x -= CAM_SPEED;
        if (IsKeyDown(KEY_D)) main_camera.position.x += CAM_SPEED;

        if (IsMouseButtonDown(0)) chunk_set_tile(&chunks, worldpoint, TILE_FILLED);

        BeginDrawing();
        ClearBackground(BLACK);

        // Chunk Render Selection Demo
        const vec2i top_left_chunk = chunk_from_world(cam_screen_to_world(&main_camera, (vec2i){0, 0}));
        const vec2i bottom_right_chunk = chunk_from_world(cam_screen_to_world(&main_camera, (vec2i){SCREEN_WIDTH, SCREEN_HEIGHT}));
        for (int x = top_left_chunk.x; x <= bottom_right_chunk.x; x++) {
            for (int y = top_left_chunk.y; y <= bottom_right_chunk.y; y++) {
                chunk_render(chunk_at(&chunks, chunk_to_world((vec2i){x, y})));
                // DrawBox(cam_world_to_screen(&main_camera, chunk_to_world((vec2i){x, y})),
                //     (vec2i) {CHUNK_WORLD_SIZE, CHUNK_WORLD_SIZE}, (Color){30, 30, 30, 255});
            }
        }

        DrawBox(cam_world_to_screen(&main_camera, chunk_align_world(worldpoint)),
        (vec2i) {CHUNK_WORLD_SIZE, CHUNK_WORLD_SIZE}, WHITE);
        DrawBox(cam_world_to_screen(&main_camera, tile_align_world(worldpoint)),
        (vec2i) {TILE_SIZE, TILE_SIZE}, RED);

        DrawText(vec2i_str(tile_from_world(worldpoint)), 0, 0, 30, WHITE);
        DrawText(vec2i_str(chunk_from_world(worldpoint)), 0, 35, 30, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
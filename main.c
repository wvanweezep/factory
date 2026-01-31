#include <stdio.h>

#include "raylib.h"
#include "chunk.h"
#include "camera.h"

#define CAM_SPEED 0.05f

static void DrawBox(vec2i xy, vec2i wh, Color c) {
    DrawLine(xy.x, xy.y,xy.x + wh.x, xy.y, c);
    DrawLine(xy.x, xy.y,xy.x, xy.y + wh.y, c);
    DrawLine(xy.x + wh.x, xy.y + wh.y,xy.x + wh.x, xy.y, c);
    DrawLine(xy.x + wh.x, xy.y + wh.y,xy.x, xy.y + wh.y, c);
}

int main(void) {
    InitWindow(800, 450, "Window");

    while (!WindowShouldClose())
    {
        if (IsKeyDown(KEY_W)) main_camera.position.y -= CAM_SPEED;
        if (IsKeyDown(KEY_S)) main_camera.position.y += CAM_SPEED;
        if (IsKeyDown(KEY_A)) main_camera.position.x -= CAM_SPEED;
        if (IsKeyDown(KEY_D)) main_camera.position.x += CAM_SPEED;

        BeginDrawing();
        ClearBackground(BLACK);

        //TODO: Draw Calls Here...
        Vector2 mposd = GetMousePosition();
        vec2i mpos = {(int) mposd.x, (int) mposd.y};
        vec2f worldpoint = cam_screen_to_world(&main_camera, mpos);

        DrawBox(cam_world_to_screen(&main_camera, chunk_align_world(worldpoint)),
            (vec2i) {CHUNK_WORLD_SIZE, CHUNK_WORLD_SIZE}, WHITE);
        DrawBox(cam_world_to_screen(&main_camera, tile_align_world(worldpoint)),
            (vec2i) {TILE_SIZE, TILE_SIZE}, RED);

        DrawText(vec2i_str(tile_from_world(worldpoint)), 0, 14, 12, WHITE);
        DrawText(vec2i_str(chunk_from_world(worldpoint)), 0, 28, 12, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
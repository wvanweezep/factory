#include "camera.h"

fCamera main_camera = {{0, 0}};

vec2i cam_world_to_screen(const fCamera* camera, vec2f point) {
    return (vec2i) {(int) (point.x - camera->position.x),
                    (int) (point.y - camera->position.y)};
}

vec2f cam_screen_to_world(const fCamera* camera, vec2i point) {
    return (vec2f) {(float) point.x + camera->position.x,
                    (float) point.y + camera->position.y};
}
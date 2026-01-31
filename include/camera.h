#pragma once

#include "math/vec2.h"


typedef struct Camera {
    vec2f position;
} fCamera;

extern fCamera main_camera;

vec2i cam_world_to_screen(const fCamera* camera, vec2f point);

vec2f cam_screen_to_world(const fCamera* camera, vec2i point);

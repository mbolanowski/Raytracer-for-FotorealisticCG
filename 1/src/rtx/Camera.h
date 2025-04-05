//
// Created by cheily on 31.03.2025.
//

#pragma once

#include "Point.h"
#include "Vector.h"
#include "../tga/tga_buffer.h"

struct Camera {

    color::color_t color_delta = {0.05, 0.05, 0.05, 0.05};
    int max_sampling_depth = 3; // inclusive

    Vector position;
    Vector forward;
    Vector up;

    Camera();
    Camera(Vector position, Vector target);
    virtual ~Camera() = default;

    virtual void render_scene(tga_buffer * buffer) = 0;

};

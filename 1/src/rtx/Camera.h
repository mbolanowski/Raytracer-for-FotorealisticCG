//
// Created by cheily on 31.03.2025.
//

#pragma once

#include "Point.h"
#include "Vector.h"
#include "../tga/tga_buffer.h"

struct Camera {

    Vector position;
    Vector forward;
    Vector up;

    Camera();
    Camera(Vector position, Vector target);
    virtual ~Camera() = default;

    virtual void render_scene(tga_buffer * buffer) = 0;

};

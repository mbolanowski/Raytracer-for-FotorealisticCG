//
// Created by cheily on 01.04.2025.
//

#pragma once


#include "Camera.h"

class PanoramicCamera : public Camera {
public:

    float nearPlane = 1.0f;
    float farPlane = 100.0f;

    PanoramicCamera() = default;
    PanoramicCamera(Vector position, Vector target) : Camera(position, target) {}
    void render_scene(tga_buffer * buffer) override;

};

//
// Created by cheily on 01.04.2025.
//

#pragma once


#include "Camera.h"

class OrtographicCamera : public Camera {
public:
    bool world_space_window_size = false;

    OrtographicCamera() = default;
    OrtographicCamera(Vector position, Vector target) : Camera(position, target) {}
    void render_scene(tga_buffer * buffer) override;
};

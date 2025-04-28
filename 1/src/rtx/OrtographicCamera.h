//
// Created by cheily on 01.04.2025.
//

#pragma once


#include "Camera.h"

class OrtographicCamera : public Camera {
private:
    float window_scale = 5.0f;
    float window_width = 0.0f;
    float window_height = 0.0f;

public:
    bool world_space_window_size = false;

    OrtographicCamera() : Camera() {
        near_plane = 0.0f;
        OrtographicCamera::update_uvw(); OrtographicCamera::update_aspect(); OrtographicCamera::update_frustum();
    }
    explicit OrtographicCamera(tga_buffer * buffer) : Camera(buffer) {
        near_plane = 0.0f;
        OrtographicCamera::update_uvw(); OrtographicCamera::update_aspect(); OrtographicCamera::update_frustum();
    }
    OrtographicCamera(Vector position, Vector target, tga_buffer * buffer) : Camera(position, target, buffer) {
        near_plane = 0.0f;
        OrtographicCamera::update_uvw(); OrtographicCamera::update_aspect(); OrtographicCamera::update_frustum();
    }

    void update_uvw() override;
    void update_aspect() override;
    void update_frustum() override;

    Ray getRay(mathgik::f2 pos) const override;
};

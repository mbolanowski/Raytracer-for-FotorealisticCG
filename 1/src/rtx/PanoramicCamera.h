//
// Created by cheily on 01.04.2025.
//

#pragma once


#include "Camera.h"
#include "Ray.h"
#include "Sphere.h"
#include "Scene.h"
#include <vector>

class PanoramicCamera : public Camera {
public:

    void update_uvw() override;
    void update_frustum() override;

    PanoramicCamera() : Camera() {
        PanoramicCamera::update_uvw(); PanoramicCamera::update_aspect(); PanoramicCamera::update_frustum();
    }
    explicit PanoramicCamera(tga_buffer * buffer) : Camera(buffer) {
        PanoramicCamera::update_uvw(); PanoramicCamera::update_aspect(); PanoramicCamera::update_frustum();
    }
    PanoramicCamera(const Vector& position, const Vector& target, tga_buffer * buffer) : Camera(position, target, buffer) {
        PanoramicCamera::update_uvw(); PanoramicCamera::update_aspect(); PanoramicCamera::update_frustum();
    }

    color::color_t get_color_raw(const Ray& ray, const Scene & scene) override;
    Ray getRay(mathgik::f2 pos) const override;

};

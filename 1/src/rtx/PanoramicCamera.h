//
// Created by cheily on 01.04.2025.
//

#pragma once


#include "Camera.h"
#include "Ray.h"
#include "Sphere.h"
#include <vector>

class PanoramicCamera : public Camera {
public:

    float nearPlane = 1.0f;
    float farPlane = 100.0f;

    PanoramicCamera() = default;
    PanoramicCamera(Vector position, Vector target) : Camera(position, target) {}
    void render_scene(tga_buffer * origin) override;

    color::color_t getColor(const Ray& ray, const std::vector<Sphere> & scene);
    color::color_t quincunx(
            Vector a, Vector b, Vector c, Vector d,
            const color::color_t & delta,
            const Vector & u, const Vector & v,
            const std::vector<Sphere> & scene,
            float px_height, float px_width,
            int max, int depth = 0);

};

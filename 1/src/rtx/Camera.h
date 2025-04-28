//
// Created by cheily on 31.03.2025.
//

#pragma once

#include "Point.h"
#include "Vector.h"
#include "../tga/tga_buffer.h"
#include "Ray.h"
#include "Scene.h"
#include "RTAntialiaser.h"

struct Camera {
protected:
    Vector position = Vector(0, 0, 0);
    Vector forward = Vector(0, 0, 1);
    Vector up = Vector(0, 1, 0);

    tga_buffer * buffer = nullptr;
    float near_plane = 1.0f, far_plane = 100.0f;
    float ratio = 1, px_width = 1, px_height = 1;
    Vector u, v, w;
    Vector uvw_near_plane_start;

    RTAntialiaser antialiaser;

public:
    bool useAA = true;
    // void rotate(float angle, const Vector& axis);
    // void translate(const Vector& translation);

    virtual void update_uvw() = 0;
    virtual void update_aspect();
    virtual void update_frustum() = 0;

    Camera();
    explicit Camera(tga_buffer * buffer);
    Camera(const Vector& position, const Vector& target, tga_buffer * buffer);
    virtual ~Camera() = default;


    virtual float get_near_plane() const { return near_plane; }
    virtual float get_far_plane() const { return far_plane; }

    virtual Ray getRay(mathgik::f2 pos) const = 0;
    virtual color::color_t get_color_raw(const Ray& ray, const Scene & scene);
//    virtual color::color_t get_color_phong(const Ray& ray, const Scene & scene);

    virtual void render_raw(const Scene & scene);
//    virtual void render_phong(const Scene & scene);

    virtual void render_scene_light() = 0;
};

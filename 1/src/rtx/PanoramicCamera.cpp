//
// Created by cheily on 01.04.2025.
//

#include "PanoramicCamera.h"
#include "Ray.h"
#include "Sphere.h"

void PanoramicCamera::render_scene(tga_buffer *buffer) {
    Sphere sphere{Vector(1, 1, 6), 2};
    Sphere sphere2{Vector(-1, -1, 4), 1.5};


    Vector w = (-forward).NormalizeV();
    Vector u = (up.Cross(w).NormalizeV()); // originally negative
    Vector v = -w.Cross(u);                // originally positive

    float px_width = 2.0f / buffer->width;
    float px_height = 2.0f / buffer->height;

    float u0 = -1;
    float v0 = 1;

    Vector uvw_near_plane_start = u * u0 + v * v0 - w * nearPlane;

    for (int b = 0; b < buffer->height; ++b) {
        for (int a = 0; a < buffer->width; ++a) {

            Vector uvw_pixel_center = uvw_near_plane_start + u * (float)a * px_width - v * (float)b * px_height;
            Vector xyz_pixel_center = position + uvw_pixel_center;

            Ray ray{position, xyz_pixel_center.NormalizeV()};

            Vector intersection1, intersection2;
            sphere.Hit(ray, nearPlane, farPlane, intersection1);
            sphere2.Hit(ray, nearPlane, farPlane, intersection2);

            if (intersection1 != Vector(0, 0, 0) && intersection2 != Vector(0, 0, 0)
                && intersection1.Length() < intersection2.Length()) {
                buffer->set_pixel(a, b, color::RED);
            } else if (intersection2 != Vector(0, 0, 0)) {
                buffer->set_pixel(a, b, color::GREEN);
            } else if (intersection1 != Vector(0, 0, 0)) {
                buffer->set_pixel(a, b, color::RED);
            }

        }
    }

}

//
// Created by cheily on 01.04.2025.
//

#include "PanoramicCamera.h"
#include "Ray.h"
#include "Sphere.h"

void PanoramicCamera::render_scene(tga_buffer *buffer) {
    Sphere sphere{Vector(1, 1, 4), 2};


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

            Vector intersection;
            sphere.Hit(ray, nearPlane, farPlane, intersection);

            if (intersection != Vector(0, 0, 0)) {
                buffer->set_pixel(a, b, color::RED);
            }

        }
    }

}

//
// Created by cheily on 01.04.2025.
//

#include "OrtographicCamera.h"
#include "Ray.h"
#include "Sphere.h"

void OrtographicCamera::render_scene(tga_buffer * buffer) {
    Sphere sphere{Vector(1, 1, 4), 1};

    float px_width = 2.0f / buffer->width;
    float px_height = 2.0f / buffer->height;

    float window_width = buffer->width / 2;
    float window_height = buffer->height / 2;

    Vector w = (-forward).NormalizeV();
    Vector u = (up.Cross(w).NormalizeV()); // originally negative
    Vector v = -w.Cross(u);                // originally positive

    Vector plane_start = u * -1 + v;

    for (int b = 0; b < buffer->height; ++b) {
        for (int a = 0; a < buffer->width; ++a) {

            float centerX = (a + 0.5f) * px_width;
            float centerY = (b + 0.5f) * px_height;
            if (world_space_window_size) {
                centerX *= window_width;
                centerY *= window_height;
            }

            Vector ray_origin = position + plane_start + u * centerX - v * centerY;

            Ray ray{ray_origin, forward};

            Vector intersection;
            sphere.Hit(ray, 0, 1000, intersection);

            if (intersection != Vector(0, 0, 0)) {
                buffer->set_pixel(a, b, color::RED);
            }

        }
    }
}

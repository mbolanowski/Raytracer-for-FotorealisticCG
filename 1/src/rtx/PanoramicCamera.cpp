//
// Created by cheily on 01.04.2025.
//

#include <unordered_map>
#include "PanoramicCamera.h"
#include "Ray.h"
#include "Sphere.h"

void PanoramicCamera::render_scene(tga_buffer *buffer) {
    Sphere sphere{Vector(1, 1, 6), 2};
    Sphere sphere2{Vector(-1, -1, 4), 1.5};

    float ratio = static_cast<float>(buffer->width) / static_cast<float>(buffer->height);

    Vector w = (-forward).NormalizeV();
    Vector u = (up.Cross(w).NormalizeV()); // originally negative
    Vector v = -w.Cross(u);                // originally positive


    float px_width = 2.0f / buffer->width * ratio;
    float px_height = 2.0f / buffer->height;

    float u0 = -1 * ratio;
    float v0 = 1;

    Vector uvw_near_plane_start = u * u0 + v * v0 - w * nearPlane;

    auto getColor = [&](const Ray& ray) -> color::color_t {
        Vector intersection1, intersection2;
        sphere.Hit(ray, nearPlane, farPlane, intersection1);
        sphere2.Hit(ray, nearPlane, farPlane, intersection2);

        if (intersection1 != Vector(0, 0, 0) && intersection2 != Vector(0, 0, 0)
            && intersection1.Length() < intersection2.Length()) {
            return color::RED;
        } else if (intersection2 != Vector(0, 0, 0)) {
            return color::GREEN;
        } else if (intersection1 != Vector(0, 0, 0)) {
            return color::RED;
        }
        return color::WHITE;
    };

    auto quincunx = [&](Vector a, Vector b, Vector c, Vector d, Vector e) -> color::color_t {
        Ray rayA{position, a.NormalizeV()};
        Ray rayB{position, b.NormalizeV()};
        Ray rayC{position, c.NormalizeV()};
        Ray rayD{position, d.NormalizeV()};


        Ray rayE{position, e.NormalizeV()};

    };

    for (int b = 0; b < buffer->height; ++b) {
        for (int a = 0; a < buffer->width; ++a) {

            Vector uvw_pixel_center = uvw_near_plane_start + u * (float)a * px_width - v * (float)b * px_height;
            Vector xyz_pixel_center = position + uvw_pixel_center;

            Ray ray{position, xyz_pixel_center.NormalizeV()};

            buffer->set_pixel(a, b, getColor(ray));

        }
    }

}

//
// Created by cheily on 01.04.2025.
//

#include "OrtographicCamera.h"
#include "Ray.h"
#include "Sphere.h"
#include "PointLight.h"

void OrtographicCamera::update_uvw() {
    w = (-forward).NormalizeV();
    u = (up.Cross(w).NormalizeV()); // originally negative
    v = -w.Cross(u);                // originally positive
}

void OrtographicCamera::update_aspect() {
    ratio = static_cast<float>(buffer->width) / static_cast<float>(buffer->height);
    if (world_space_window_size) {
        px_width = 2.0f / buffer->width * window_scale * ratio;
        px_height = 2.0f / buffer->height * window_scale;
        window_width = buffer->width / 2;
        window_height = buffer->height / 2;
    }
    else {
        px_width = 2.0f / buffer->width * ratio;
        px_height = 2.0f / buffer->height;
    }
}

void OrtographicCamera::update_frustum() {
    if (world_space_window_size)
        uvw_near_plane_start = u * -1 * ratio * window_scale + v * window_scale;
    else
        uvw_near_plane_start = u * -1 * ratio + v;
}

Ray OrtographicCamera::getRay(mathgik::f2 pos) const {
    Vector uvw_pixel_top_left;
    if (world_space_window_size)
        uvw_pixel_top_left = uvw_near_plane_start + u * pos.a * px_width * window_width - v * pos.b * px_height * window_height;
    else
        uvw_pixel_top_left = uvw_near_plane_start + u * pos.a * px_width - v * pos.b * px_height;
    Vector xyz_pixel_top_left = position + uvw_pixel_top_left;

    return Ray{xyz_pixel_top_left, forward};
}

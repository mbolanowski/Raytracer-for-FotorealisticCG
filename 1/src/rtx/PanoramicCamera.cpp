//
// Created by cheily on 01.04.2025.
//

#include <map>
#include <vector>
#include <unordered_map>
#include "PanoramicCamera.h"
#include "Ray.h"
#include "Sphere.h"
#include "../tga/math/func.h"
#include "PointLight.h"
#include "Scene.h"

color::color_t PanoramicCamera::get_color_raw(const Ray &ray, const Scene &scene) {
    return Camera::get_color_raw(ray, scene);
}

Ray PanoramicCamera::getRay(mathgik::f2 pos) const {
    Vector uvw_pixel_top_left = uvw_near_plane_start + u * pos.a * px_width - v * pos.b * px_height;
    Vector xyz_pixel_top_left = position + uvw_pixel_top_left;

    return {position, xyz_pixel_top_left.NormalizeV()};
}

void PanoramicCamera::update_uvw() {
    w = (-forward).NormalizeV();
    u = (up.Cross(w).NormalizeV()); // originally negative
    v = -w.Cross(u);                // originally positive
}

void PanoramicCamera::update_frustum() {
    float u0 = -1 * ratio;
    float v0 = 1;

    uvw_near_plane_start = u * u0 + v * v0 - w * near_plane;
}

//
// Created by cheily on 01.04.2025.
//

#include <map>
#include <vector>
#include "PanoramicCamera.h"
#include "Ray.h"
#include "Sphere.h"
#include "../tga/math/func.h"

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


    for (int b = 0; b < buffer->height; ++b) {
        for (int a = 0; a < buffer->width; ++a) {

            Vector uvw_pixel_top_left = uvw_near_plane_start + u * (float)a * px_width - v * (float)b * px_height;
            Vector xyz_pixel_top_left = position + uvw_pixel_top_left;

            color::color_t clr = quincunx(
                xyz_pixel_top_left,                                                     // top left
                xyz_pixel_top_left + u * px_width,                                      // top right
                xyz_pixel_top_left - v * px_height,                                     // bottom left
                xyz_pixel_top_left + u * px_width - v * px_height,                      // bottom right
                color_delta, u, v, {sphere, sphere2}, px_height, px_width, max_sampling_depth, 0
            );

//            Ray ray{position, xyz_pixel_top_left.NormalizeV()};

            buffer->set_pixel(a, b, clr);

        }
    }

}

color::color_t
PanoramicCamera::quincunx(Vector a, Vector b, Vector c, Vector d, const color::color_t & delta, const Vector & u, const Vector & v, const std::vector<Sphere> & scene, float px_height, float px_width, int max, int depth) {
    static std::vector<std::pair<color::color_t, float>> value_list{};
    static std::map<Vector, color::color_t> registered{};
    static auto get_or_shoot = [this](const Ray & ray, const std::vector<Sphere> & scene) -> std::pair<color::color_t, bool> {
        if (registered.contains(ray.Direction())) {
            return {registered[ray.Direction()], false};
        } else {
            registered[ray.Direction()] = getColor(ray, scene);
            return {registered[ray.Direction()], true};
        }
    };

    if (depth == 0) {
        value_list = {};
        registered = {};
    }

    Ray rayA{position, a.NormalizeV()};
    Ray rayB{position, b.NormalizeV()};
    Ray rayC{position, c.NormalizeV()};
    Ray rayD{position, d.NormalizeV()};

    float current_weight = 1.0f / std::pow(4, depth + 1);
    color::color_t colorA;
    color::color_t colorB;
    color::color_t colorC;
    color::color_t colorD;
    bool isUnique;
    std::vector<color::color_t> unique_colors{};

    std::tie(colorA, isUnique) = get_or_shoot(rayA, scene);
    if (isUnique) unique_colors.push_back(colorA);
    std::tie(colorB, isUnique) = get_or_shoot(rayB, scene);
    if (isUnique) unique_colors.push_back(colorB);
    std::tie(colorC, isUnique) = get_or_shoot(rayC, scene);
    if (isUnique) unique_colors.push_back(colorC);
    std::tie(colorD, isUnique) = get_or_shoot(rayD, scene);
    if (isUnique) unique_colors.push_back(colorD);

    float sample_step_scale = 1.0f / (depth + 1);
    Ray rayE{position, (a + (u * px_width * sample_step_scale * 0.5f) - (v * px_height * sample_step_scale * 0.5f)).NormalizeV()};

    if (depth + 1 < max
        && mathgik::v_lte_scalar(colorA.data - colorB.data, delta.data)
        && mathgik::v_lte_scalar(colorA.data - colorC.data, delta.data)
        && mathgik::v_lte_scalar(colorA.data - colorD.data, delta.data)
        && mathgik::v_lte_scalar(colorB.data - colorC.data, delta.data)
        && mathgik::v_lte_scalar(colorB.data - colorD.data, delta.data)
        && mathgik::v_lte_scalar(colorC.data - colorD.data, delta.data)) {

        //A  F  B
        //I  E  G
        //C  H  D
        Vector f = a + (u * px_width * sample_step_scale * 0.5f);
        Vector g = b - (v * px_height * sample_step_scale * 0.5f);
        Vector h = c + (u * px_width * sample_step_scale * 0.5f);
        Vector i = a - (v * px_height * sample_step_scale * 0.5f);

        quincunx(a, f, i, rayE.Direction(), delta, u, v, scene, px_height, px_width, max, depth + 1);
        quincunx(f, b, rayE.Direction(), g, delta, u, v, scene, px_height, px_width, max, depth + 1);
        quincunx(i, rayE.Direction(), c, h, delta, u, v, scene, px_height, px_width, max, depth + 1);
        quincunx(rayE.Direction(), f, g, rayE.Direction(), delta, u, v, scene, px_height, px_width, max, depth + 1);
    }

    color::color_t colorE = get_or_shoot(rayE, scene).first;

    value_list.push_back({(colorA.data + colorE.data) * 0.5f, current_weight});
    value_list.push_back({(colorB.data + colorE.data) * 0.5f, current_weight});
    value_list.push_back({(colorC.data + colorE.data) * 0.5f, current_weight});
    value_list.push_back({(colorD.data + colorE.data) * 0.5f, current_weight});

    if (depth == 0) {
        color::color_t result = {0, 0, 0, 0};
        for (const auto& [color, weight] : value_list) {
            result.data += color.data * weight;
        }
        return result;
    }
    return color::color_t{0, 0, 0, 0}; // No result for intermediate calls
}

color::color_t PanoramicCamera::getColor(const Ray &ray, const std::vector<Sphere> & scene) {
    Vector intersection1, intersection2;
    scene[0].Hit(ray, nearPlane, farPlane, intersection1);
    scene[1].Hit(ray, nearPlane, farPlane, intersection2);

    if (intersection1 != Vector(0, 0, 0) && intersection2 != Vector(0, 0, 0)
        && intersection1.Length() < intersection2.Length()) {
        return color::RED;
    } else if (intersection2 != Vector(0, 0, 0)) {
        return color::GREEN;
    } else if (intersection1 != Vector(0, 0, 0)) {
        return color::RED;
    }
    return color::WHITE;
}

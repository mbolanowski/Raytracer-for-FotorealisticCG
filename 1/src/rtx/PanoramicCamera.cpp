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

void PanoramicCamera::render_scene_light() {
    Material mat(Vector(1.0f,0.0f,0.0f), 0.1f,0.05f,0.0f);
    Material mat2(Vector(1.0f,1.0f,0.0f), 0.1f,0.05f,0.0f);
    PointLight light(Vector(4.0f,5.0f,5.0f), Vector(1.0f,1.0f,0.0f));
    Sphere sphere{Vector(0, 1.2, 5), 1.5, mat};
    Sphere sphere2{Vector(0, -2.9, 5), 2.5, mat2};
    float ambientIntensity = 0.1f;
    float diffuseIntensity = 0.8f;

    float ratio = static_cast<float>(buffer->width) / static_cast<float>(buffer->height);

    Vector w = (-forward).NormalizeV();
    Vector u = (up.Cross(w).NormalizeV()); // originally negative
    Vector v = -w.Cross(u);                // originally positive


    float px_width = 2.0f / buffer->width * ratio;
    float px_height = 2.0f / buffer->height;

    float u0 = -1 * ratio;
    float v0 = 1;

    Vector uvw_near_plane_start = u * u0 + v * v0 - w * near_plane;

    auto getColor = [&](const Ray& ray) -> color::color_t {
        Vector intersection1, intersection2;
        bool hit1 = sphere.Hit(ray, near_plane, far_plane, intersection1);
        bool hit2 = sphere2.Hit(ray, near_plane, far_plane, intersection2);

        if (!hit1 && !hit2) {
            return color::WHITE;
        }

        Vector hitPoint;
        Sphere* hitSphere = nullptr;

        if (hit1 && (!hit2 || intersection1.Length() < intersection2.Length())) {
            hitPoint = intersection1;
            hitSphere = &sphere;
        } else {
            hitPoint = intersection2;
            hitSphere = &sphere2;
        }

        Material* mat = &hitSphere->Material_;

        Vector I = ray.Direction().NormalizeV(); // View direction
        Vector N = (hitPoint - hitSphere->Center()).NormalizeV(); // Surface normal
        Vector L = (light.position - hitPoint).NormalizeV(); // Light direction

        const float epsilon = 1e-4f;
        Vector shadowOrigin = hitPoint + N * epsilon;
        Ray shadowRay(shadowOrigin, L);

        float lightDistance = (light.position - hitPoint).Length();

        bool inShadow = false;
        Vector vector;
        if ((sphere.Hit(shadowRay, epsilon, lightDistance, vector) && &sphere != hitSphere) ||
            (sphere2.Hit(shadowRay, epsilon, lightDistance, vector) && &sphere2 != hitSphere)) {
            inShadow = true;
        }

        float diffuse = 0.0f;
        float specular = 0.0f;

        if (!inShadow) {
            float cosTheta = std::max(0.0f, N.DotProduct(L));
            diffuse = cosTheta * diffuseIntensity;

            Vector R = (N * (2.0f * N.DotProduct(L))) - L;
            float ss = std::max(0.0f, R.DotProduct(-I));
            specular = std::pow(ss, mat->specular_coeff) * mat->specular_amount;
        }

        Vector ambientColor = mat->color * ambientIntensity;
        Vector diffuseColor = mat->color * diffuse;
        Vector specularColor = light.color * specular;

        float fadeValue = 0.2f;
        float distanceFade = 1.0f / (fadeValue * lightDistance);

        Vector finalColor = ambientColor + ((diffuseColor + specularColor) * distanceFade);

        finalColor.x = std::min(1.0f, std::max(0.0f, finalColor.x));
        finalColor.y = std::min(1.0f, std::max(0.0f, finalColor.y));
        finalColor.z = std::min(1.0f, std::max(0.0f, finalColor.z));

        return {finalColor.x, finalColor.y, finalColor.z, 1.0f};
    };

    for (int b = 0; b < buffer->height; ++b) {
        for (int a = 0; a < buffer->width; ++a) {

            Vector uvw_pixel_center = uvw_near_plane_start + u * (float)a * px_width - v * (float)b * px_height;
            Vector xyz_pixel_center = position + uvw_pixel_center;

            Ray ray{position, xyz_pixel_center.NormalizeV()};

            color::color_t color = getColor(ray);
            buffer->set_pixel(a, b, color);
        }
    }

}

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

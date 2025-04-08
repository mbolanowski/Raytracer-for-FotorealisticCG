//
// Created by cheily on 01.04.2025.
//

#include "OrtographicCamera.h"
#include "Ray.h"
#include "Sphere.h"
#include "PointLight.h"

void OrtographicCamera::render_scene() {
    Material mat(Vector(0.0f,0.0f,1.0f), 0.5f,0.5f,0.5f);
    Sphere sphere{Vector(1, 1, 40), 1, mat};
    Sphere sphere2{Vector(-1, -1, 30), 1.5, mat};

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

            float centerX = (float)(a) * px_width;
            float centerY = (float)(b) * px_height;
            if (world_space_window_size) {
                centerX *= window_width;
                centerY *= window_height;
            }

            Vector ray_origin = position + plane_start + u * centerX - v * centerY;

            Ray ray{ray_origin, forward};

//            Ray ray = getRay({static_cast<float>(a), static_cast<float>(b)});

            Vector intersection1, intersection2;
            sphere.Hit(ray, 0, 1000, intersection1);
            sphere2.Hit(ray, 0, 1000, intersection2);

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

void OrtographicCamera::render_scene_light() {
    Material mat(Vector(1.0f,0.0f,0.0f), 0.1f,0.05f,0.0f);
    Material mat2(Vector(1.0f,1.0f,0.0f), 0.1f,0.05f,0.0f);
    PointLight light(Vector(4.0f,5.0f,5.0f), Vector(1.0f,1.0f,0.0f));
    Sphere sphere{Vector(0.2, 0.2, 4), 0.2, mat};
    Sphere sphere2{Vector(-0.3, -0.3, 4), 0.4, mat2};
    float ambientIntensity = 0.1f;
    float diffuseIntensity = 0.8f;

    float px_width = 2.0f / buffer->width;
    float px_height = 2.0f / buffer->height;

    float window_width = buffer->width / 2;
    float window_height = buffer->height / 2;

    Vector w = (-forward).NormalizeV();
    Vector u = (up.Cross(w).NormalizeV()); // originally negative
    Vector v = -w.Cross(u);                // originally positive

    Vector plane_start = u * -1 + v;

    auto getColor = [&](const Ray& ray) -> color::color_t {
        Vector intersection1, intersection2;
        bool hit1 = sphere.Hit(ray, 0, 1000, intersection1);
        bool hit2 = sphere2.Hit(ray, 0, 1000, intersection2);

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

            float centerX = (a + 0.5f) * px_width;
            float centerY = (b + 0.5f) * px_height;
            if (world_space_window_size) {
                centerX *= window_width;
                centerY *= window_height;
            }

            Vector ray_origin = position + plane_start + u * centerX - v * centerY;

            Ray ray{ray_origin, forward};

            color::color_t color = getColor(ray);
            buffer->set_pixel(a, b, color);
        }
    }
}

void OrtographicCamera::update_uvw() {
    Vector w = (-forward).NormalizeV();
    Vector u = (up.Cross(w).NormalizeV()); // originally negative
    Vector v = -w.Cross(u);                // originally positive
}

void OrtographicCamera::update_aspect() {
    ratio = static_cast<float>(buffer->width) / static_cast<float>(buffer->height);
    px_width = 2.0f / buffer->width;
    px_height = 2.0f / buffer->height;

    window_half_width = buffer->width / 2;
    window_half_height = buffer->height / 2;
}

void OrtographicCamera::update_frustum() {
    uvw_near_plane_start = u * -1 + v;
}

Ray OrtographicCamera::getRay(mathgik::f2 pos) const {
    Vector uvw_pixel_top_left;
    if (world_space_window_size) {
        float window_width = buffer->width / 2;
        float window_height = buffer->height / 2;
        uvw_pixel_top_left = uvw_near_plane_start + u * pos.a * px_width * window_width - v * pos.b * px_height * window_height;
    } else uvw_pixel_top_left = uvw_near_plane_start + u * pos.a * px_width - v * pos.b * px_height;
    Vector xyz_pixel_top_left = position + uvw_pixel_top_left;

    return Ray{xyz_pixel_top_left, forward};
}

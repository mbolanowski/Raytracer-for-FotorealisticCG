//
// Created by cheily on 31.03.2025.
//

#include "Camera.h"
#include <functional>

Camera::Camera(const Vector& position, const Vector& target, tga_buffer * buffer)
    : antialiaser(this), position(position), forward(target), buffer(buffer) {
}

color::color_t Camera::get_color_raw(const Ray &ray, const Scene &scene) {
    auto intersection = scene.getClosestIntersection(ray, this);
    if (!intersection.hit) {
        return buffer->clr_color_c;
    }
    else return intersection.material.color.to_color();
}

void Camera::update_aspect() {
    ratio = static_cast<float>(buffer->width) / static_cast<float>(buffer->height);
    px_width = 2.0f / buffer->width * ratio;
    px_height = 2.0f / buffer->height;
}

Camera::Camera(tga_buffer *buffer) : antialiaser(this), buffer(buffer) {}

Camera::Camera() : antialiaser(this) {}

void Camera::render_raw(const Scene &scene) {

    std::function<color::color_t(mathgik::i2)> get;
    if (useAA) {
        get = [this, scene](mathgik::i2 pos) {
            return antialiaser.quad_raw(pos, scene);
        };
    } else {
        get = [this, scene](mathgik::i2 pos) {
            return get_color_raw(getRay({(float) pos.a, (float) pos.b}), scene);
        };
    }

    for (int b = 0; b < buffer->height; ++b) {
        for (int a = 0; a < buffer->width; ++a) {

            buffer->set_pixel(a, b, get({a, b}));

        }
    }
}


void Camera::render_phong(const Scene &scene) {
    std::function < color::color_t(mathgik::i2) > get;
//    if (useAA) {
//        get = [this, scene](mathgik::i2 pos) {
//            return antialiaser.quad_raw(pos, scene);
//        };
//    } else {
        get = [this, scene](mathgik::i2 pos) {
            return get_color_phong(getRay({(float) pos.a, (float) pos.b}), scene);
        };
//    }

    for (int b = 0; b < buffer->height; ++b) {
        for (int a = 0; a < buffer->width; ++a) {

            buffer->set_pixel(a, b, get({a, b}));

        }
    }
}

color::color_t Camera::get_color_phong(const Ray& ray, const Scene & scene) {
        auto intersection = scene.getClosestIntersection(ray, this);
        if (!intersection.hit) {
            return buffer->clr_color_c;
        }

        Vector hitPoint = intersection.vector;
        Sphere const * hitSphere = std::any_cast<Sphere const *>(intersection.hitObject);
        PointLight light = scene.lights[0];

        Material const* mat = &hitSphere->Material_;

        Vector I = ray.Direction().NormalizeV(); // View direction
        Vector N = (hitPoint - hitSphere->Center()).NormalizeV(); // Surface normal
        Vector L = (light.position - hitPoint).NormalizeV(); // Light direction

        const float epsilon = 1e-4f;
        Vector shadowOrigin = hitPoint + N * epsilon;
        Ray shadowRay(shadowOrigin, L);

        float lightDistance = (light.position - hitPoint).Length();

        bool inShadow = false;

        auto shadowIntersection = scene.getClosestIntersection(shadowRay, this, epsilon, lightDistance);
        if (shadowIntersection.hit && shadowIntersection.type == Scene::SPHERE && std::any_cast<Sphere const *>(shadowIntersection.hitObject) != hitSphere) {
            inShadow = true;
        }

        float diffuse = 0.0f;
        float specular = 0.0f;

        if (!inShadow) {
            float cosTheta = std::max(0.0f, N.DotProduct(L));
            diffuse = cosTheta * /*diffuseIntensity*/ 0.8f;

            Vector R = (N * (2.0f * N.DotProduct(L))) - L;
            float ss = std::max(0.0f, R.DotProduct(-I));
            specular = std::pow(ss, mat->specular_coeff) * mat->specular_amount;
        }

        Vector ambientColor = mat->color * /*ambientIntensity*/ 0.1f;
        Vector diffuseColor = mat->color * diffuse;
        Vector specularColor = light.color * specular;

        float fadeValue = 0.2f;
        float distanceFade = 1.0f / (fadeValue * lightDistance);

        Vector finalColor = ambientColor + ((diffuseColor + specularColor) * distanceFade);

        finalColor.x = std::min(1.0f, std::max(0.0f, finalColor.x));
        finalColor.y = std::min(1.0f, std::max(0.0f, finalColor.y));
        finalColor.z = std::min(1.0f, std::max(0.0f, finalColor.z));

        return {finalColor.x, finalColor.y, finalColor.z, 1.0f};
}


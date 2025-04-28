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


//void Camera::render_phong(const Scene &scene) {
//    std::function < color::color_t(mathgik::i2) > get;
//    if (useAA) {
//        get = [this, scene](mathgik::i2 pos) {
//            return antialiaser.quad_raw(pos, scene);
//        };
//    } else {
//        get = [this, scene](mathgik::i2 pos) {
//            return get_color_phong(getRay({(float) pos.a, (float) pos.b}), scene);
//        };
//    }
//
//    for (int b = 0; b < buffer->height; ++b) {
//        for (int a = 0; a < buffer->width; ++a) {
//
//            buffer->set_pixel(a, b, get({a, b}));
//
//        }
//    }
//}


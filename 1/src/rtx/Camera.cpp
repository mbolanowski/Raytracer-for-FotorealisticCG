//
// Created by cheily on 31.03.2025.
//

#include "Camera.h"

Camera::Camera(const Vector& position, const Vector& target, tga_buffer * buffer)
    : antialiaser(this), position(position), forward(target), buffer(buffer) {
}

color::color_t Camera::getColor(const Ray &ray, const Scene &scene) {
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

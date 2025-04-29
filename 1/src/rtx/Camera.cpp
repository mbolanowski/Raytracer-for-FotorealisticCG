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
    else return intersection.material.diffuse.to_color();
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
    if (useAA) {
        get = [this, scene](mathgik::i2 pos) {
            return antialiaser.quad_phong(pos, scene);
        };
    } else {
        get = [this, scene](mathgik::i2 pos) {
            return get_color_phong(getRay({(float) pos.a, (float) pos.b}), scene);
        };
    }

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
        Scene::shape_type hitType = intersection.type;
        std::any hitObject = intersection.hitObject;
        Vector hitNormal;
        Material const * mat;
        std::function<bool(std::any, Scene::shape_type)> isHitObj = [hitType, hitObject](std::any obj, Scene::shape_type type) {
            if (hitType != type) return false;
            if (type == Scene::SPHERE) {
                return std::any_cast<Sphere const *>(obj) == std::any_cast<Sphere const *>(hitObject);
            } else if (type == Scene::PLANE) {
                return std::any_cast<Plane const *>(obj) == std::any_cast<Plane const *>(hitObject);
            } else if (type == Scene::TRIANGLE) {
                return std::any_cast<Triangle const *>(obj) == std::any_cast<Triangle const *>(hitObject);
            }
        };

        if (hitType == Scene::SPHERE) {
            auto sphere = std::any_cast<Sphere const *>(hitObject);
            hitNormal = (hitPoint - sphere->Center()).NormalizeV();
            mat = &sphere->Material_;
        } else if (hitType == Scene::PLANE) {
            auto plane = std::any_cast<Plane const *>(hitObject);
            hitNormal = plane->Normal();
            mat = &plane->Material_;
        } else if (hitType == Scene::TRIANGLE) {
            std::cout << "Triangle hit" << std::endl;
        }
        PointLight light = scene.lights[0];
        Vector I = (ray.Origin() + ray.Direction()).NormalizeV(); // View direction
        Vector N = hitNormal; // Surface normal
        Vector L = (light.position - hitPoint).NormalizeV(); // Light direction

        const float epsilon = 1e-4f;
        Vector shadowOrigin = hitPoint + N * epsilon;
        Ray shadowRay(shadowOrigin, L);

        float lightDistance = (light.position - hitPoint).Length();

        bool inShadow = false;

        auto shadowIntersection = scene.getClosestIntersection(shadowRay, epsilon, lightDistance);
        if (shadowIntersection.hit && !isHitObj(shadowIntersection.hitObject, shadowIntersection.type)) {
            inShadow = true;
        }

        if (inShadow) {
//            auto plane = std::any_cast<Plane const *>(intersection.hitObject);
//            auto planeShadow = std::any_cast<Plane const *>(shadowIntersection.hitObject);
//            std::cout << "In shadow" << std::endl;
        }

        float diffuse = 0.0f;
        float specular = 0.0f;

        if (inShadow) {
            float cosTheta = std::max(0.0f, N.DotProduct(L));
            diffuse = cosTheta * /*diffuseIntensity*/ 0.8f;

            Vector R = (N * (2.0f * N.DotProduct(L))) - L;
            float ss = std::max(0.0f, R.DotProduct(-I));
            specular = std::pow(ss, mat->specular_coeff) * mat->specular_amount;
        }

        Vector ambientColor = mat->diffuse * /*ambientIntensity*/ 0.1f;
        Vector diffuseColor = mat->diffuse * diffuse;
        Vector specularColor = light.color * specular;

        float fadeValue = 0.2f;
        float distanceFade = 1.0f / (fadeValue * lightDistance);

        Vector finalColor = ambientColor + ((diffuseColor + specularColor) * distanceFade);

        finalColor.x = std::min(1.0f, std::max(0.0f, finalColor.x));
        finalColor.y = std::min(1.0f, std::max(0.0f, finalColor.y));
        finalColor.z = std::min(1.0f, std::max(0.0f, finalColor.z));

        return {finalColor.x, finalColor.y, finalColor.z, 1.0f};
}

void Camera::render_recurse(const Scene &scene, int recurse_max) {
    std::function < color::color_t(mathgik::i2) > get;
//    if (useAA) {
//        get = [this, scene](mathgik::i2 pos) {
//            return antialiaser.quad_phong(pos, scene);
//        };
//    } else {
        get = [this, scene, &recurse_max](mathgik::i2 pos) {
            return get_color_recurse(getRay({(float) pos.a, (float) pos.b}), scene, recurse_max);
        };
//    }

    for (int b = 0; b < buffer->height; ++b) {
        for (int a = 0; a < buffer->width; ++a) {

            buffer->set_pixel(a, b, get({a, b}));

        }
    }
}

color::color_t Camera::get_color_recurse(const Ray &ray, const Scene &scene, int recurse_max, int recurse) {
    auto intersection = scene.getClosestIntersection(ray, this);
    if (!intersection.hit) {
        return buffer->clr_color_c;
    }

    Vector hitPoint = intersection.vector;
    Scene::shape_type hitType = intersection.type;
    std::any hitObject = intersection.hitObject;
    Vector hitNormal;
    Material const * mat;
    std::function<bool(std::any, Scene::shape_type)> isHitObj = [hitType, hitObject](std::any obj, Scene::shape_type type) {
        if (hitType != type) return false;
        if (type == Scene::SPHERE) {
            return std::any_cast<Sphere const *>(obj) == std::any_cast<Sphere const *>(hitObject);
        } else if (type == Scene::PLANE) {
            return std::any_cast<Plane const *>(obj) == std::any_cast<Plane const *>(hitObject);
        } else if (type == Scene::TRIANGLE) {
            return std::any_cast<Triangle const *>(obj) == std::any_cast<Triangle const *>(hitObject);
        }
    };

    if (hitType == Scene::SPHERE) {
        auto sphere = std::any_cast<Sphere const *>(hitObject);
        hitNormal = (hitPoint - sphere->Center()).NormalizeV();
        mat = &sphere->Material_;
    } else if (hitType == Scene::PLANE) {
        auto plane = std::any_cast<Plane const *>(hitObject);
        hitNormal = plane->Normal();
        mat = &plane->Material_;
    } else if (hitType == Scene::TRIANGLE) {
        std::cout << "Triangle hit" << std::endl;
    }


    if (!mat->is_diffuse() && recurse_max > 0) {

        Ray secondary;
        if (mat->is_refract) {
            secondary = {hitPoint, (ray.Origin() + ray.Direction()).refract(hitNormal, recurse == 0 ? 1.0f : mat->refract_coeff, mat->refract_coeff)};
        } else {
            secondary = {hitPoint, (ray.Origin() + ray.Direction()).reflect(hitNormal)};
        }

        return get_color_recurse(secondary, scene, recurse_max - 1);
    }

//    if (recurse_max == 0) {
//        std::cout << "Recurse max reached" << std::endl;
//    }

    PointLight light = scene.lights[0];
    Vector I = ray.Direction().NormalizeV(); // View direction
    Vector N = hitNormal; // Surface normal
    Vector L = (light.position - hitPoint).NormalizeV(); // Light direction

    const float epsilon = 1e-4f;
    Vector shadowOrigin = hitPoint + N * epsilon;
    Ray shadowRay(shadowOrigin, L);

    float lightDistance = (light.position - hitPoint).Length();

    bool inShadow = false;

    auto shadowIntersection = scene.getClosestIntersection(shadowRay, epsilon, lightDistance);
    if (shadowIntersection.hit && !isHitObj(shadowIntersection.hitObject, shadowIntersection.type)) {
        inShadow = true;
    }

    float diffuse = 0.0f;
    float specular = 0.0f;

    if (inShadow) {
        float cosTheta = std::max(0.0f, N.DotProduct(L));
        diffuse = cosTheta * /*diffuseIntensity*/ 0.8f;

        Vector R = (N * (2.0f * N.DotProduct(L))) - L;
        float ss = std::max(0.0f, R.DotProduct(-I));
        specular = std::pow(ss, mat->specular_coeff) * mat->specular_amount;
    }

    Vector ambientColor = mat->diffuse * /*ambientIntensity*/ 0.1f;
    Vector diffuseColor = mat->diffuse * diffuse;
    Vector specularColor = light.color * specular;

    float fadeValue = 0.2f;
    float distanceFade = 1.0f / (fadeValue * lightDistance);

    Vector finalColor = ambientColor + ((diffuseColor + specularColor) * distanceFade);

    finalColor.x = std::min(1.0f, std::max(0.0f, finalColor.x));
    finalColor.y = std::min(1.0f, std::max(0.0f, finalColor.y));
    finalColor.z = std::min(1.0f, std::max(0.0f, finalColor.z));

//    if (finalColor.y > 0.18f)
//        std::cout << "At " << recurse_max << " left, " <<  finalColor.x << " " << finalColor.y << " " << finalColor.z << std::endl;
    return {finalColor.x, finalColor.y, finalColor.z, 1.0f};
}


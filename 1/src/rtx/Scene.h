//
// Created by cheily on 08.04.2025.
//

#pragma once

#include <vector>
#include <any>
#include "Sphere.h"
#include "Triangle.h"
#include "PointLight.h"
#include "Plane.h"
struct Camera;

struct Scene {
    // todo Refactor all shapes to use a common base class with a virtual Hit(Ray) function, then optionally register to pointer vectors outside a main Shape * vector

    std::vector<Sphere> spheres;
    std::vector<Triangle> triangles;
    std::vector<PointLight> lights;
    std::vector<Plane> planes;
    Vector ambientLight;

    enum shape_type {
        SPHERE,
        TRIANGLE,
        PLANE
    };

    struct SceneIntersection {
        bool hit = false;
        Vector vector;
        Material material;
        std::any hitObject;
        shape_type type;
    };

    SceneIntersection getClosestIntersection(const Ray & ray, Camera * camera) const;
};
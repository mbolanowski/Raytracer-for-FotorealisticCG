//
// Created by cheily on 08.04.2025.
//

#include "Scene.h"
#include "Camera.h"

Scene::SceneIntersection Scene::getClosestIntersection(const Ray &ray, Camera *camera) const {
    return getClosestIntersection(ray, camera->get_near_plane(), camera->get_far_plane());
};

Scene::SceneIntersection Scene::getClosestIntersection(const Ray &ray, float t_min, float t_max) const {
    std::vector<SceneIntersection> intersections{};
    intersections.reserve(spheres.size() + triangles.size() + planes.size());

    for (const auto &sphere : spheres) {
        Vector intersection;
        if (sphere.Hit(ray, t_min, t_max, intersection)) {
            intersections.push_back(SceneIntersection{.hit = true, .vector = intersection, .material = sphere.Material_, .hitObject = &sphere, .type = SPHERE});
        }
    }

    for (const auto &triangle : triangles) {
        Vector intersection;
        if (triangle.IntersectTriangle(ray, intersection) && intersection.Length() > t_min && intersection.Length() < t_max) {
            intersections.push_back({true, intersection, {}, &triangle, TRIANGLE});
        }
    }

    for (const auto &plane : planes) {
        IntersectionResult result;
        result = plane.Intersects(ray, t_max);
//        std::cout << result.type;
        if (result.type == HIT && result.distance > t_min) {
            intersections.push_back({true, result.intersectionPoint, plane.Material_, &plane, PLANE});
        }
    }

    if (intersections.empty()) {
        return {false, Vector(0, 0, 0), {}, nullptr, SPHERE};
    }

    std::sort(intersections.begin(), intersections.end(), [](const SceneIntersection &a, const SceneIntersection &b) {
        return a.vector.Length() < b.vector.Length();
    });
    return intersections.front();
}


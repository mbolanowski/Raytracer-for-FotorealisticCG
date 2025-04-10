//
// Created by cheily on 08.04.2025.
//

#include "Scene.h"
#include "Camera.h"

Scene::SceneIntersection Scene::getClosestIntersection(const Ray &ray, Camera *camera) const {
    std::vector<SceneIntersection> intersections{};
    intersections.reserve(spheres.size() + triangles.size() + planes.size());

    for (const auto &sphere : spheres) {
        Vector intersection;
        if (sphere.Hit(ray, camera->get_near_plane(), camera->get_far_plane(), intersection)) {
            intersections.push_back({true, intersection, sphere.Material_});
        }
    }

    for (const auto &triangle : triangles) {
        Vector intersection;
        if (triangle.IntersectTriangle(ray, intersection) && intersection.Length() > camera->get_near_plane() && intersection.Length() < camera->get_far_plane()) {
            intersections.push_back({true, intersection, {}});
        }
    }

    for (const auto &plane : planes) {
        IntersectionResult result;
        if ((result = plane.Intersects(ray, camera->get_far_plane())).type == HIT && result.distance > camera->get_near_plane()) {
            intersections.push_back({true, result.intersectionPoint, {}});
        }
    }

    if (intersections.empty()) {
        return {false, Vector(0, 0, 0), {}};
    }

    std::sort(intersections.begin(), intersections.end(), [](const SceneIntersection &a, const SceneIntersection &b) {
        return a.vector.Length() < b.vector.Length();
    });
    return intersections.front();
};


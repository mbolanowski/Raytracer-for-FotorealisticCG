//
// Created by mbola on 3/24/2025.
//

#ifndef INC_2_PLANE_H
#define INC_2_PLANE_H

#include "Vector.h"
#include "Ray.h"
#include "Material.h"
#include <iostream>

enum IntersectionType { MISS, HIT, INSIDE_PRIMITIVE };

struct IntersectionResult {
    IntersectionType type;
    Vector intersectionPoint;
    float distance;
    Vector intersectionNormal;
};

class Plane {
public:
    Plane();
    Plane(Vector normal, float distance);
    Plane(Vector normal, Vector point);

    Material Material_ = Material();

    bool Intersect3(const Plane &p2, const Plane &p3, Vector &result) const;
    IntersectionResult Intersects(const Ray &ray, float range = 0.0f) const;

    Vector Normal() const { return normal; }
    void Normal(Vector n) { normal = n; }

    float Distance() const { return distance; }
    void Distance(float d) { distance = d; }

private:
    Vector normal;
    float distance;
};

#endif //INC_2_PLANE_H

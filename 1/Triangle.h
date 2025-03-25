//
// Created by mbola on 3/24/2025.
//

#ifndef INC_2_TRIANGLE_H
#define INC_2_TRIANGLE_H

#include "Vector.h"
#include "Ray.h"
#include "Plane.h"

class Triangle{
public:
    Triangle();
    Triangle(const Vector &vertex1, const Vector &vertex2, const Vector &vertex3);
    Triangle(const Vector &vertex1, const Vector &vertex2, const Vector &vertex3, const Vector &normal1, const Vector &normal2, const Vector &normal3);

    Vector vertices[3];
    Vector normals[3];

    //IntersectionResult Intersects(const Ray &ray, float range = 0.0f) const;
    bool IntersectTriangleV(const Ray &ray, Vector &A, Vector &B, Vector &C, Vector &intersectionPoint);
    bool IntersectTriangle(const Ray &ray, Vector &intersectionPoint);
};

#endif //INC_2_TRIANGLE_H

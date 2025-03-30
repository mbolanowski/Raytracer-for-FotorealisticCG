#include "Triangle.h"


Triangle::Triangle()
        : vertices{Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f)},
          normals{Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f)} {}


Triangle::Triangle(const Vector &vertex1, const Vector &vertex2, const Vector &vertex3)
: vertices{vertex1, vertex2, vertex3}, normals{Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f), Vector(0.0f, 0.0f, 0.0f)} {}

Triangle::Triangle(const Vector &vertex1, const Vector &vertex2, const Vector &vertex3, const Vector &normal1, const Vector &normal2, const Vector &normal3)
: vertices{vertex1, vertex2, vertex3}, normals{normal1, normal2, normal3} {}


bool Triangle::IntersectTriangleV(const Ray &ray, Vector &A, Vector &B, Vector &C, Vector &intersectionPoint) {
    Vector AB = B.SubV(A);
    Vector AC = C.SubV(A);
    Vector normal = AB.Cross(AC);

    float dot = normal.DotProduct(ray.Direction());
    if(fabsf(dot) < std::numeric_limits<float>::epsilon()) {
        return false;
    }

    float t = normal.DotProduct(A.SubV(ray.Origin())) / dot;

    if(t < 0.0f){
        return false;
    }

    intersectionPoint = ray.Origin().AddV(ray.Direction().MagV(t));

    Vector AP = intersectionPoint.SubV(A);
    Vector BP = intersectionPoint.SubV(B);
    Vector CP = intersectionPoint.SubV(C);
    Vector v1 = AB.Cross(AP);
    Vector v2 = (C.SubV(B)).Cross(BP);
    Vector v3 = (A.SubV(C)).Cross(CP);
    if(v1.DotProduct(normal) >= 0.0f && v2.DotProduct(normal) >= 0.0f && v3.DotProduct(normal) >= 0.0f) {
        return true;
    }

    return false;
}

bool Triangle::IntersectTriangle(const Ray &ray, Vector &intersectionPoint) {
    Vector A = vertices[0];
    Vector B = vertices[1];
    Vector C = vertices[2];

    Vector AB = B.SubV(A);
    Vector AC = C.SubV(A);
    Vector normal = AB.Cross(AC);

    float dot = normal.DotProduct(ray.Direction());
    if(fabsf(dot) < std::numeric_limits<float>::epsilon()) {
        return false;
    }

    float t = normal.DotProduct(A.SubV(ray.Origin())) / dot;

    if(t < 0.0f){
        return false;
    }

    intersectionPoint = ray.Origin().AddV(ray.Direction().MagV(t));

    Vector AP = intersectionPoint.SubV(A);
    Vector BP = intersectionPoint.SubV(B);
    Vector CP = intersectionPoint.SubV(C);
    Vector v1 = AB.Cross(AP);
    Vector v2 = (C.SubV(B)).Cross(BP);
    Vector v3 = (A.SubV(C)).Cross(CP);
    if(v1.DotProduct(normal) >= 0.0f && v2.DotProduct(normal) >= 0.0f && v3.DotProduct(normal) >= 0.0f) {
        return true;
    }

    return false;
}

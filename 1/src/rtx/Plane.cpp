#include "Plane.h"


Plane::Plane() : normal(Vector(0, 1, 0)), distance(0) {}
Plane::Plane(Vector normal, float distance) : normal(normal), distance(distance) {}
Plane::Plane(Vector normal, Vector point) : normal(normal), distance(-normal.DotProduct(point)) {}

bool Plane::Intersect3(const Plane &p2, const Plane &p3, Vector &result) const {
    float denominator = normal.DotProduct(p2.normal.Cross(p3.normal));

    if (denominator == 0.0f) {
        return false;
    }

    Vector temp1 = p2.normal.Cross(p3.normal).MagV(distance);
    Vector temp2 = p3.normal.Cross(normal).MagV(p2.distance);
    Vector temp3 = normal.Cross(p2.normal).MagV(p3.distance);

    temp1.Add(temp2);
    temp1.Add(temp3);
    result = temp1.DivV(-denominator);
    return true;
}

IntersectionResult Plane::Intersects(const Ray &ray, float range) const{
    IntersectionResult result;
    result.type = MISS;

    float ndotD = normal.DotProduct(ray.Origin() + ray.Direction());

    if (ndotD == 0.0f) {
        return result;
    }

//    float t = (-distance - normal.DotProduct(ray.Origin() + ray.Direction())) / ndotD;
    float t = (distance - normal.DotProduct(ray.Origin() + ray.Direction())) / ndotD;
    if (t >= 0) {
        if (range == 0.0f || t < range) {
            result.type = (normal.DotProduct(ray.Origin() + ray.Direction()) < 0) ? HIT : INSIDE_PRIMITIVE;
            Vector OriginCopy = ray.Origin();
            Vector DirectionCopy = ray.Direction();
            DirectionCopy.Mag(t);
            OriginCopy.Add(DirectionCopy);
            result.intersectionPoint = OriginCopy;
            result.distance = t;
            result.intersectionNormal = normal;
        }
    }

    return result;
}

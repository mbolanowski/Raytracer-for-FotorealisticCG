#include "Sphere.h"
#include "../tga/color.h"

Sphere::Sphere() : Center_(Vector(0, 0, 0)), Radius_(0), Material_(Material(Vector(0.0f,0.0f,1.0f), 0.5f, 0.5f, 0.5f)) {}
Sphere::Sphere(Vector v, float r, Material mat) : Center_(v), Radius_(r), Material_(mat) {}

bool Sphere::Hit(Ray ray, float t_min, float t_max, Vector &intersection) const {
    Vector oc = ray.Origin().SubV(Center_);

    float a = ray.Direction().DotProduct(ray.Direction());
    float b = oc.DotProduct(ray.Direction());
    float c = oc.DotProduct(oc) - Radius_ * Radius_;

    float discriminant = b * b - a * c;

    if(discriminant >= 0){
        float temp = (-b - std::sqrtf(discriminant)) / a;

        if(temp < t_max && temp > t_min){
            Vector dirCopy = ray.Direction();
            Vector originCopy = ray.Origin();
            dirCopy.Mag(temp);
            originCopy.Add(dirCopy);
            intersection = originCopy;
            return true;
        }

        temp = (-b + std::sqrtf(discriminant)) / a;

        if(temp < t_max && temp > t_min){
            Vector dirCopy = ray.Direction();
            Vector originCopy = ray.Origin();
            dirCopy.Mag(temp);
            originCopy.Add(dirCopy);
            intersection = originCopy;
            return true;
        }
    }
    return false;
}
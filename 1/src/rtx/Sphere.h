//
// Created by mbola on 3/24/2025.
//

#ifndef INC_2_SPHERE_H
#define INC_2_SPHERE_H

#include "Vector.h"
#include "Ray.h"
#include "Material.h"

class Sphere{
public:
    Sphere();
    Sphere(Vector v, float r, Material mat);

    bool Hit(Ray ray, float t_min, float t_max, Vector &intersection) const;

    Vector Center() const {return Center_;}
    void Center(Vector o) {Center_ = o;}

    float Radius() const {return Radius_;}
    void Radius(float r) {Radius_ = r;}

    friend std::ostream& operator <<(std::ostream& os, const Sphere& sph);

    Material Material_;
private:
    Vector Center_;
    float Radius_;
};

#endif //INC_2_SPHERE_H

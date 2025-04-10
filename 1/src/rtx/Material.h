//
// Created by mbola on 4/6/2025.
//

#ifndef INC_2_MATERIAL_H
#define INC_2_MATERIAL_H

#pragma once
#include "../tga/color.h"

class Material{
public:
    Material() : color(Vector(1,1,1)), specular_amount(0), specular_coeff(0), reflect_fraction(0) {};
    Material(Vector color, float specular_amount, float specular_coeff, float reflect_fraction)
    : color(color), specular_amount(specular_amount), specular_coeff(specular_coeff), reflect_fraction(reflect_fraction){}

    ~Material()= default;

    Vector color;
    float specular_amount;
    float specular_coeff;
    float reflect_fraction;
};


#endif //INC_2_MATERIAL_H

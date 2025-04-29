//
// Created by mbola on 4/6/2025.
//

#ifndef INC_2_MATERIAL_H
#define INC_2_MATERIAL_H

#pragma once
#include "../tga/color.h"

class Material{
public:
    Material() : diffuse(Vector(1, 1, 1)), specular_amount(0), specular_coeff(0), refract_coeff(0) {};
    Material(Vector color, float specular_amount, float specular_coeff, float refract_coeff)
        : diffuse(color), specular_amount(specular_amount), specular_coeff(specular_coeff), refract_coeff(refract_coeff){}
    Material(Vector color, float specular_amount, float specular_coeff, float refract_coeff, bool is_reflect)
        : diffuse(color), specular_amount(specular_amount), specular_coeff(specular_coeff), refract_coeff(refract_coeff), is_refract(refract_coeff > 1.0f), is_reflect(is_reflect) {}
    Material(Vector color, float specular_amount, float specular_coeff, bool is_reflect, bool is_refract, float refract_coeff = 1.0f)
        : diffuse(color), specular_amount(specular_amount), specular_coeff(specular_coeff), is_reflect(is_reflect), is_refract(is_refract), refract_coeff(refract_coeff) {}

    ~Material()= default;

    Vector diffuse;
    float specular_amount;
    float specular_coeff;
    bool is_reflect = false;
    bool is_refract = false;
    float refract_coeff = 1.0f;

    inline bool is_diffuse() const { return !is_reflect && !is_refract; }
};


#endif //INC_2_MATERIAL_H

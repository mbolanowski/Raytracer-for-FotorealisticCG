//
// Created by mbola on 4/6/2025.
//

#ifndef INC_2_POINTLIGHT_H
#define INC_2_POINTLIGHT_H

#pragma once
#include "Light.h"
#include "Vector.h"

class PointLight : public Light{
public:
    PointLight(Vector position, Vector color) : position(position), color(color){}

    Vector position;
    Vector color;
};

#endif //INC_2_POINTLIGHT_H

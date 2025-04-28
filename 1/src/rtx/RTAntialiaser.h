//
// Created by cheily on 08.04.2025.
//

#pragma once


#include "../tga/math/vector.h"
#include "../tga/color.h"
#include "Scene.h"
struct Camera;

class RTAntialiaser {
public:
    Camera * camera = nullptr;
    int quad_divisions = 4;

    RTAntialiaser(Camera * camera, int quad_subdivisions = 4) : camera(camera), quad_divisions(quad_subdivisions) {};
    ~RTAntialiaser() = default;

    color::color_t quad_raw(const mathgik::i2 & pos, const Scene & scene) const;
    color::color_t quad_phong(const mathgik::i2 & pos, const Scene & scene) const;
};

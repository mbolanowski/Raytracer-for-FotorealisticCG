//
// Created by cheily on 08.04.2025.
//

#include "RTAntialiaser.h"
#include "Camera.h"

color::color_t RTAntialiaser::quad_raw(const mathgik::i2 & pos, const Scene & scene) const {
    color::color_t average{};

    float step = 1.0f / (quad_divisions + 1);
    float div = 1.0f / (quad_divisions * quad_divisions);

    for (int y = 0; y < quad_divisions; ++y) {
        for (int x = 0; x < quad_divisions; ++x) {
            mathgik::f2 position = { (float)pos.a + (float)(x + 1) * step, (float)pos.b + (float)(y + 1) * step };
            average.data += camera->get_color_raw(camera->getRay(position), scene).data * div;
        }
    }

    return average;
}

color::color_t RTAntialiaser::quad_phong(const mathgik::i2 & pos, const Scene & scene) const {
    color::color_t average{};

    float step = 1.0f / (quad_divisions + 1);
    float div = 1.0f / (quad_divisions * quad_divisions);

    for (int y = 0; y < quad_divisions; ++y) {
        for (int x = 0; x < quad_divisions; ++x) {
            mathgik::f2 position = { (float)pos.a + (float)(x + 1) * step, (float)pos.b + (float)(y + 1) * step };
            average.data += camera->get_color_phong(camera->getRay(position), scene).data * div;
        }
    }

    return average;
}
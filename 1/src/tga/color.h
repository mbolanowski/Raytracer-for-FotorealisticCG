//
// Created by cheily on 24.03.2025.
//

#pragma once
#include "math/vector.h"

namespace color {
    using color_t = mathgik::f4;

    const color_t TRANSPARENT ={ 0,    0,     0,    0 };
    const color_t BLACK =      { 0,    0,     0,    1 };
    const color_t WHITE =      { 1,    1,     1,    1 };
    const color_t RED =        { 1,    0,     0,    1 };
    const color_t GREEN =      { 0,    1,     0,    1 };
    const color_t BLUE =       { 0,    0,     1,    1 };
    const color_t YELLOW =     { 1,    1,     0,    1 };
    const color_t CYAN =       { 0,    1,     1,    1 };
    const color_t MAGENTA =    { 1,    0,     1,    1 };
    const color_t GRAY =       { 0.5,  0.5,   0.5,  1 };
    const color_t BROWN =      { 0.647,0.165, 0.165,1 };
    const color_t ORANGE =     { 1,    0.647, 0,    1 };
    const color_t PURPLE =     { 0.5,  0,     0.5,  1 };
    const color_t TEAL =       { 0,    0.5,   0.5,  1 };
    const color_t PINK =       { 1,    0.753, 0.796,1 };
    const color_t LIME =       { 0,    1,     0,    1 };
    const color_t NAVY =       { 0,    0,     0.5,  1 };
    const color_t MAROON =     { 0.5,  0,     0,    1 };
    const color_t OLIVE =      { 0.5,  0.5,   0,    1 };
    const color_t TURQUOISE =  { 0.251,0.878, 0.816,1 };
    const color_t INDIGO =     { 0.294,0,     0.51, 1 };
    const color_t SILVER =     { 0.753,0.753, 0.753,1 };
    const color_t GOLD =       { 1,    0.843, 0,    1 };
    const color_t CRIMSON =    { 0.863,0.078, 0.235,1 };
    const color_t ROSE =       { 1,    0.078, 0.576,1 };
    const color_t BEIGE =      { 0.961,0.961, 0.863,1 };
    const color_t CORAL =      { 1,    0.498, 0.314,1 };
    const color_t KHAKI =      { 0.765,0.69,  0.569,1 };
    const color_t LAVENDER =   { 0.902,0.902, 0.98, 1 };
    const color_t PLUM =       { 0.867,0.627, 0.867,1 };

        template<typename data_t>
    static mathgik::vec4<data_t> as(color_t color) {
        data_t max = 0;
        for (int i = 0; i < sizeof(data_t); ++i) {
            max += 0xff;
            if (i != sizeof(data_t) - 1) max <<= 8;
        }

        mathgik::vec4<data_t> result;
        result.data = {
            (data_t)(color.r * max),
            (data_t)(color.g * max),
            (data_t)(color.b * max),
            (data_t)(color.a * max)};

        return result;
    }

    template<typename data_t>
    static data_t as_packed(color_t color, bool tga_format = true) {
        auto pack_size = sizeof(data_t) * 8;
        auto field_size = pack_size / 4;

        data_t field_mask = 0;
        for (int i = 0; i < field_size; ++i) {
            field_mask |= 0b1;
            if (i != field_size - 1) field_mask <<= 1;
        }

        data_t result = 0;
        if (tga_format) {
            result |= (data_t)(color.b * field_mask);
            result |= (data_t)(color.g * field_mask) << field_size;
            result |= (data_t)(color.r * field_mask) << field_size * 2;
            result |= (data_t)(color.a * field_mask) << field_size * 3;
        } else {
            result |= (data_t) (color.r * field_mask);
            result |= (data_t) (color.g * field_mask) << field_size;
            result |= (data_t) (color.b * field_mask) << field_size * 2;
            result |= (data_t) (color.a * field_mask) << field_size * 3;
        }

        return result;
    }
}


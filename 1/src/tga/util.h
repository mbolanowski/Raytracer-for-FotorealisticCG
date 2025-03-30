//
// Created by cheily on 25.03.2025.
//

#pragma once
#include <bit>
#include "color.h"

template<typename T>
T adj_endian(T data) {
    T temp;
    if (std::endian::native == std::endian::big) {
        for (int i = 0; i < sizeof(T); ++i) {
            temp |= (data & 0xff) << (8 * i);
            data >>= 8;
        }
    } else {
        temp = data;
    }

    return temp;
}

// DO NOT USE DIFFERENT COLORS FOR EACH VERTEX!!!
struct vertex_data {
    mathgik::f3 position;
    color::color_t color;
};
using triangle_vertices = mathgik::vec< vertex_data, 3 >;
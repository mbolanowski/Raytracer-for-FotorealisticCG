//
// Created by cheily on 05.04.2025.
//

#include "color.h"

color::color_t color::negative(color::color_t color) {
    return {
        1 - color.r,
        1 - color.g,
        1 - color.b,
        color.a
    };
}

color::color_t color::negative_alpha(color::color_t color) {
    return {
        1 - color.r,
        1 - color.g,
        1 - color.b,
        1 - color.a
    };
}

template<typename data_t>
mathgik::vec4<data_t> color::as(color::color_t color) {
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
data_t color::as_packed(color::color_t color, bool tga_format) {
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

tga_spec::tga_pixel color::as_pixel(color::color_t color) {
    return tga_spec::tga_pixel(as<tga_spec::tga_pixel_field>(color));
}

color::color_t color::from_pixel(tga_spec::tga_pixel pixel) {
    color::color_t result;
    auto max = std::numeric_limits<tga_spec::tga_pixel_field>::max();
    result.data = {
        (float) pixel.r / max,
        (float) pixel.g / max,
        (float) pixel.b / max,
        (float) pixel.a / max
    };
    return result;
}

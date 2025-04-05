//
// Created by cheily on 24.03.2025.
//

#pragma once
#include "math/vector.h"
#include "tga_spec/tga_pixel.h"

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

    color_t negative(color_t color);
    color_t negative_alpha(color_t color);

    /**
     * @brief Converts a color_t to a tga_spec::tga_pixel.
     * @param color The color to convert.
     * @return Color converted to tga_spec::tga_pixel.
     */
    tga_spec::tga_pixel as_pixel(color_t color);

    /**
     * @brief Converts a tga_spec::tga_pixel to a color_t.
     * @param pixel The pixel to convert.
     * @return Pixel converted to color_t.
     * @implnote Uses std::numeric_limits to get the maximum value of tga_spec::tga_pixel_field.
     */
    color_t from_pixel(tga_spec::tga_pixel pixel);

    /**
     * @brief Converts a color_t to a mathgik::vec4<data_t> with the given data type.
     * @tparam data_t Type of fields in the vector.
     * @param color The color to convert.
     * @return Color converted to mathgik::vec4<data_t>.
     */
    template<typename data_t>
    mathgik::vec4<data_t> as(color_t color);

    /**
     * @brief Converts a color_t to a packed representation, with all fields packed into a single variable.
     * @tparam data_t Type of packed data.
     * @param color The color to convert.
     * @param tga_format If true, the color is packed in TGA format (BGRA, necessary for proper data saving), otherwise in normal format (RGBA).
     * @return Packed color.
     */
    template<typename data_t>
    data_t as_packed(color_t color, bool tga_format = true);
}


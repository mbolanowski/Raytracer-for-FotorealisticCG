//
// Created by cheily on 24.03.2025.
//

#include "tga_buffer.h"


void tga_buffer::set_pixel(int x, int y, color::color_t color) {
    set_pixel_pxt(x, y, tga_spec::tga_pixel(color::as<std::uint8_t>(color)));
}

float tga_buffer::get_depth(int x, int y) {
    return depth_buffer[y * width + x];
}

void tga_buffer::set_depth(int x, int y, float depth) {
    depth_buffer[y * width + x] = depth;
}

tga_spec::tga_pixel tga_buffer::get_pixel(int x, int y)  {
    return color_buffer[y * width + x];
}

void tga_buffer::set_pixel_pxt(int x, int y, tga_spec::tga_pixel pixel) {
    color_buffer[y * width + x] = pixel;
//    std::memcpy(color_buffer + y * width + x, &pixel, sizeof(pixel_t));
}

void tga_buffer::clear_color() {
    std::fill(color_buffer, color_buffer + width * height, clr_color);
}

void tga_buffer::clear_depth() {
    std::fill(depth_buffer, depth_buffer + width * height, clr_depth);
}

void tga_buffer::clear() {
    clear_color();
    clear_depth();
}
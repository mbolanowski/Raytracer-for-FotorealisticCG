//
// Created by cheily on 24.03.2025.
//

#pragma once
#include <concepts>
#include <algorithm>
#include "tga_spec/tga_spec.h"
#include "color.h"

struct tga_buffer {
    tga_spec::tga_pixel * color_buffer;
    float * depth_buffer;

    tga_spec::tga_pixel clr_color;
    float clr_depth = 0;

    std::size_t width;
    std::size_t height;

    tga_buffer(std::size_t width, std::size_t height, color::color_t clr_color, float clr_depth) :
            width(width), height(height), clr_color(color::as_pixel(clr_color)), clr_depth(clr_depth) {
        color_buffer = new tga_spec::tga_pixel[width * height];
        depth_buffer = new float[width * height];
        clear();
    }
    ~tga_buffer() {
        delete[] color_buffer;
        delete[] depth_buffer;
    }

    tga_spec::tga_pixel get_pixel(int x, int y);
    void set_pixel_pxt(int x, int y, tga_spec::tga_pixel pixel);
    void set_pixel(int x, int y, color::color_t color);

    float get_depth(int x, int y);
    void set_depth(int x, int y, float depth);

    void set_clear_color(color::color_t color);

    void clear_color();
    void clear_depth();
    void clear();

    size_t size() const {
        return width * height;
    }
};


//
// Created by cheily on 24.03.2025.
//

#include "tga_data.h"
#include "../util.h"

namespace tga_spec {
    tga_data::tga_data(tga_header::pixel_depth_t depth, std::size_t width, std::size_t height) {
        std::size_t length = width * height * depth / 8;
        image_data = new std::uint8_t[length];
    }

    tga_data::tga_data(tga_header header) {
        std::size_t length = header.width * header.height * header.pixel_depth / 8;
        image_data = new std::uint8_t[length];

        if (header.id_length > 0) {
            image_id = new std::uint8_t[header.id_length];
        }

        if (header.color_map_type == tga_header::color_map_type_t::COLOR_MAP) {
            std::size_t color_map_length = header.color_map_length * header.color_map_entry_size / 8;
            color_map = new std::uint8_t[color_map_length];
        }
    }

    tga_data::~tga_data() {
        delete[] image_data;
        delete[] image_id;
        delete[] color_map;
    }

    void tga_data::buffer_data(std::size_t data_len, tga_pixel * data) {
        for (std::size_t i = 0; i < data_len; ++i) {
            int j = i * 4;
            image_data[j] = data[i].b;
            image_data[j + 1] = data[i].g;
            image_data[j + 2] = data[i].r;
            image_data[j + 3] = data[i].a;
        }
    }
} // tga_spec
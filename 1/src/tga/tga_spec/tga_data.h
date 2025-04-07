//
// Created by cheily on 24.03.2025.
//

#pragma once

#include <cstdint>
#include <ostream>
#include "tga_pixel.h"
#include "tga_header.h"

namespace tga_spec {
    struct tga_data {

        std::uint8_t * image_id = nullptr;
        std::uint8_t * color_map = nullptr;
        std::uint8_t * image_data = nullptr;

        tga_data(tga_header::pixel_depth_t depth, std::size_t width, std::size_t height);
        tga_data(tga_header header);
        ~tga_data();

        // has partial spec for pixel detail
        void buffer_data(std::size_t data_len, tga_pixel * data);

        template<typename pixel_t>
        void set_img_size(std::size_t width, std::size_t height) {
            delete[] image_data;
            std::size_t length = width * height * sizeof(pixel_t);
            image_data = new std::uint8_t[length];
        }
        void set_img_length(std::size_t length) {
            image_data = new std::uint8_t[length];
        }

    };

} // tga_spec

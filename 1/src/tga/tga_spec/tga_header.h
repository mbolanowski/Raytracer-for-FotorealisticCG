//
// Created by cheily on 24.03.2025.
//

#pragma once

#include <cstdint>
#include <ostream>

namespace tga_spec {
    struct tga_header {

        std::uint8_t id_length = 0;
        std::uint8_t color_map_type = NO_COLOR_MAP;
        std::uint8_t image_type = TRUE_COLOR;

        std::uint16_t color_map_origin = 0;
        std::uint16_t color_map_length = 0;
        std::uint8_t color_map_entry_size = 0;

        std::uint16_t x_origin = 0;
        std::uint16_t y_origin = 0;
        std::uint16_t width = 640;
        std::uint16_t height = 480;
        std::uint8_t pixel_depth = RGBA_1BPF;
        std::uint8_t image_descriptor = (ALPHA_CHANNEL_BITS & 8) | ORIENTATION_TOP_TO_BOTTOM;

        enum color_map_type_t {
            NO_COLOR_MAP = 0,
            COLOR_MAP = 1
        };

        enum image_type_t {
            NO_IMAGE_DATA = 0,
            COLOR_MAPPED = 1,
            TRUE_COLOR = 2,
            BLACK_AND_WHITE = 3,
            RLE_COLOR_MAPPED = 9,
            RLE_TRUE_COLOR = 10,
            RLE_BLACK_AND_WHITE = 11
        };

        enum pixel_depth_t {
            RGBA_1BPF = 32,
            RGBA_2BPF = 64,
            RGBA_4BPF = 128,

            RGBA_4bPF = 16,
            RGBA_2bPF = 8,
        };

        enum image_descriptor_t {
            ORIENTATION_RIGHT_TO_LEFT = 0b00010000,
            ORIENTATION_TOP_TO_BOTTOM = 0b00100000,

            ALPHA_CHANNEL_BITS = 0b00001111,
            ORIENTATION_BITS = 0b00110000,
        };

        tga_header() = default;
    };

    std::ostream &operator<<(std::ostream &os, const tga_header &header);
}
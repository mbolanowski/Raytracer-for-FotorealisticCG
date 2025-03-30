//
// Created by cheily on 24.03.2025.
//

#include "tga_header.h"
#include "../util.h"

std::ostream &tga_spec::operator<<(std::ostream &os, const tga_spec::tga_header &header) {
        os << header.id_length << header.color_map_type << header.image_type;

        std::uint16_t temp = adj_endian<std::uint16_t>(header.color_map_origin);
        os << (uint8_t)(temp & 0x00ff) << (uint8_t)(temp >> 8);
        temp = adj_endian<std::uint16_t>(header.color_map_length);
        os << (uint8_t)(temp & 0x00ff) << (uint8_t)(temp >> 8);
        os << header.color_map_entry_size;

        temp = adj_endian<std::uint16_t>(header.x_origin);
        os << (uint8_t)(temp & 0x00ff) << (uint8_t)(temp >> 8);
        temp = adj_endian<std::uint16_t>(header.y_origin);
        os << (uint8_t)(temp & 0x00ff) << (uint8_t)(temp >> 8);
        temp = adj_endian<std::uint16_t>(header.width);
        os << (uint8_t)(temp & 0x00ff) << (uint8_t)(temp >> 8);
        temp = adj_endian<std::uint16_t>(header.height);
        os << (uint8_t)(temp & 0x00ff) << (uint8_t)(temp >> 8);
        os << header.pixel_depth << header.image_descriptor;
        return os;
    }

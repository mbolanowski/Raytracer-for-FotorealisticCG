//
// Created by cheily on 24.03.2025.
//

#include <fstream>
#include "tga_file.h"

namespace tga_spec {
    tga_file::tga_file()
    : header(), data(header), footer() {
    }

    void tga_file::set_size(std::size_t width, std::size_t height) {
        header.width = width;
        header.height = height;
        data.set_img_length(width * height * header.pixel_depth / 8);
    }

    void tga_file::write(const char *filename) {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file");
        }

        file << header;
        for (std::size_t i = 0; i < header.id_length; i++) {
            file << data.image_id[i];
        }
        for (std::size_t i = 0; i < header.color_map_length * header.color_map_entry_size / 8; i++) {
            file << data.color_map[i];
        }
        for (std::size_t i = 0; i < header.width * header.height * header.pixel_depth / 8; i++) {
            file << data.image_data[i];
        }
        file << footer;

        file.close();
    }
} // tga_spec
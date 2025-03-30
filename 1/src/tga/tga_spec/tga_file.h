//
// Created by cheily on 24.03.2025.
//

#pragma once

#include "tga_header.h"
#include "tga_footer.h"
#include "tga_data.h"

namespace tga_spec {
    struct tga_file {

        tga_header header;
        tga_data data;
        // tga_extension extension;
        // tga_developer developer;
        tga_footer footer;

        tga_file();
        ~tga_file() = default;

        void set_size(std::size_t width, std::size_t height);
        void write(const char *filename);

    };
} // tga_spec

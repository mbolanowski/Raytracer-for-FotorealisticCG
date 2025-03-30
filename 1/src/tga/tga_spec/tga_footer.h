//
// Created by cheily on 24.03.2025.
//

#pragma once


#include <cstdint>
#include "tga_header.h"

namespace tga_spec {
    struct tga_footer {
        std::uint32_t extensionOffset = 0;
        std::uint32_t developerOffset = 0;
        const char * signature = "TRUEVISION-XFILE.";
        char terminator = '\0';

        tga_footer() = default;

        tga_footer(tga_header header) {}

        tga_footer(std::uint32_t extensionOffset, std::uint32_t developerOffset)
                : extensionOffset(extensionOffset), developerOffset(developerOffset) {}
    };

    std::ostream &operator<<(std::ostream &os, const tga_footer &footer);
}
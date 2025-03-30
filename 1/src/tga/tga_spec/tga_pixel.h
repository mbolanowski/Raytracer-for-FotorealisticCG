//
// Created by cheily on 24.03.2025.
//

#pragma once

#include <cstdint>
#include "../math/vector.h"

namespace tga_spec {
    // Warning: Do not change the field type without implementing a tga_data::buffer_data partial spec for that type
    // Do not change the container type at all.

    template<typename data_t>
    using tga_pixel_container = mathgik::vec4<data_t>;

    using tga_pixel_field = std::uint8_t;

    using tga_pixel = tga_pixel_container<tga_pixel_field>;

} // tga_spec
//
// Created by cheily on 24.03.2025.
//

#include "tga_footer.h"
#include "../util.h"

std::ostream &tga_spec::operator<<(std::ostream &os, const tga_spec::tga_footer &footer) {
    std::uint32_t temp = adj_endian<std::uint32_t>(footer.extensionOffset);
    os << (uint8_t)(temp & 0x000000ff) << (uint8_t)((temp & 0x0000ff00) >> 8) << (uint8_t)((temp & 0x00ff0000) >> 16) << (uint8_t)((temp & 0xff000000) >> 24);
    temp = adj_endian<std::uint32_t>(footer.developerOffset);
    os << (uint8_t)(temp & 0x000000ff) << (uint8_t)((temp & 0x0000ff00) >> 8) << (uint8_t)((temp & 0x00ff0000) >> 16) << (uint8_t)((temp & 0xff000000) >> 24);
    os << footer.signature;
    os << footer.terminator;

//    os << footer.extensionOffset << footer.developerOffset << footer.signature;
    return os;
}

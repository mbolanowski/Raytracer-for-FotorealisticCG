//
// Created by cheily on 26.03.2025.
//

#pragma once

#include "tga_buffer.h"
#include "tga_spec/tga_pixel.h"
#include "color.h"
#include "math/math.h"
#include "util.h"

struct tga_rasterizer {

    tga_buffer * buffer;

    tga_rasterizer(tga_buffer * buffer) : buffer(buffer) {}
    
    mathgik::i3 scale(mathgik::f3 v) {
        return {
            static_cast<int>((v.x + 1) * buffer->width * 0.5),
            static_cast<int>((v.y + 1) * buffer->height * 0.5),
            static_cast<int>(v.z)
        };
    }
    mathgik::f3 unscale(mathgik::i3 v) {
        return {
                (static_cast<float>(v.x) / buffer->width) * 2 - 1,
                (static_cast<float>(v.y) / buffer->height) * 2 - 1,
                static_cast<float>(v.z)
        };
    }

    void triangle(const mathgik::vec< vertex_data, 3 > vertices) {
        mathgik::vec< mathgik::i3, 3 > scaled = {
            scale(vertices[0].position),
            scale(vertices[1].position),
            scale(vertices[2].position)
        };

        mathgik::f3 af = vertices[0].position;
        mathgik::f3 bf = vertices[1].position;
        mathgik::f3 cf = vertices[2].position;

        mathgik::i3 a = scaled[0];
        mathgik::i3 b = scaled[1];
        mathgik::i3 c = scaled[2];

        int minx, maxx, miny, maxy;
        minx = std::min({scaled[0].x, scaled[1].x, scaled[2].x});
        maxx = std::max({scaled[0].x, scaled[1].x, scaled[2].x});
        miny = std::min({scaled[0].y, scaled[1].y, scaled[2].y});
        maxy = std::max({scaled[0].y, scaled[1].y, scaled[2].y});

        minx = std::max(0, minx);
        maxx = std::min((int)buffer->width - 1, maxx);
        miny = std::max(0, miny);
        maxy = std::min((int)buffer->height - 1, maxy);

        int dx_ab = a.x - b.x;
        int dx_bc = b.x - c.x;
        int dx_ca = c.x - a.x;
        int dy_ab = a.y - b.y;
        int dy_bc = b.y - c.y;
        int dy_ca = c.y - a.y;

        float lua = 1.0f / ((bf.y - cf.y) * (af.x - cf.x) + (cf.x - bf.x) * (af.y - cf.y) );
        float lub = 1.0f / ((cf.y - af.y) * (bf.x - cf.x) + (af.x - cf.x) * (bf.y - cf.y) );

        float ldy_bc = bf.y - cf.y;
        float ldx_cb = cf.x - bf.x;
        float ldy_ca = cf.y - af.y;
        float ldx_ac = af.x - cf.x;

        for (int y = miny; y < maxy + 1; ++y) {
            for (int x = minx; x < maxx + 1; ++x) {
                mathgik::i3 p = {x, y, 0};
                mathgik::f3 pf = unscale(p);

                if (dx_ab * (p.y - a.y) - dy_ab * (p.x - a.x) > 0 &&
                    dx_bc * (p.y - b.y) - dy_bc * (p.x - b.x) > 0 &&
                    dx_ca * (p.y - c.y) - dy_ca * (p.x - c.x) > 0) {


                    float la = (ldy_bc * (pf.x - cf.x) + ldx_cb * (pf.y - cf.y)) * lua;
                    float lb = (ldy_ca * (pf.x - cf.x) + ldx_ac * (pf.y - cf.y)) * lub;
                    float lc = 1 - la - lb;

                    float depth = (vertices[0].position.z * la + vertices[1].position.z * lb + vertices[2].position.z * lc);
                    if (depth >= buffer->get_depth(x, y)) {
                        continue;
                    }

                    color::color_t px_color = (vertices[0].color.data * la + vertices[1].color.data * lb + vertices[2].color.data * lc);

                    buffer->set_pixel(x, y, px_color);
                    buffer->set_depth(x, y, 0);
                }

            }
        }
    }

    void negative() {
        for (int y = 0; y < buffer->height; ++y) {
            for (int x = 0; x < buffer->width; ++x) {
                auto pixel = buffer->get_pixel(x, y);
                auto color = color::from_pixel(pixel);
                color = color::negative(color);
                buffer->set_pixel(x, y, color);
            }
        }
    }


    void debug() {
        auto c00 = color::CYAN;
        auto c01 = color::MAGENTA;
        auto c10 = color::YELLOW;
        auto c11 = color::BLACK;

        for (int y = 0; y < buffer->height; ++y) {
            buffer->set_pixel(0, y, mathgik::vlerp(c00.data, c01.data, y/(1.0f * buffer->height)));
            buffer->set_pixel(buffer->width - 1, y, mathgik::vlerp(c10.data, c11.data, y/(1.0f * buffer->height)));
        }

        for (int x = 0; x < buffer->width; ++x) {
            buffer->set_pixel(x, 0, mathgik::vlerp(c00.data, c10.data, x/(1.0f * buffer->width)));
            buffer->set_pixel(x, buffer->height - 1, mathgik::vlerp(c01.data, c11.data, x/(1.0f * buffer->width)));
        }
    }

};


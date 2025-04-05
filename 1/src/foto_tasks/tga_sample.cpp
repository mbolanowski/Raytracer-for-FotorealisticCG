//
// Created by cheily on 30.03.2025.
//

#include "tasks.h"
#include "../tga/tga_spec/tga_spec.h"
#include "../tga/color.h"
#include "../tga/tga_buffer.h"
#include "../tga/tga_rasterizer.h"

using namespace std;
using namespace tga_spec;

// Because the top-left filling has not been implemented yet, expect these edges to have a 1px gap from any other edge.
void foto::tga_sample() {

    tga_file file;
    file.set_size(400, 400);

    tga_buffer buffer(file.header.width, file.header.height, color::WHITE, 0);
    tga_rasterizer rasterizer(&buffer);

    triangle_vertices triangle_red{
        vertex_data{ {-1, -1, -1}, color::RED },
        vertex_data{ {0, 1, -1}, color::RED },
        vertex_data{ {1, -1, -1}, color::RED }
    };

    rasterizer.triangle(triangle_red);

    file.data.buffer_data(buffer.size(), buffer.color_buffer);

    file.write("output.tga");

}
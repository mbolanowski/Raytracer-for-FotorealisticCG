//
// Created by cheily on 30.03.2025.
//

#include "tasks.h"
#include "../tga/tga_spec/tga_spec.h"
#include "../tga/color.h"
#include "../tga/tga_buffer.h"
#include "../tga/tga_rasterizer.h"
#include "../rtx/Camera.h"
#include "../rtx/OrtographicCamera.h"
#include "../rtx/Sphere.h"
#include "../rtx/PanoramicCamera.h"

using namespace std;
using namespace tga_spec;

void foto::task2() {

    tga_file file;
    file.set_size(600, 400);

    tga_buffer buffer_pano(file.header.width, file.header.height, color::WHITE, 0);
    tga_buffer buffer_ortho(file.header.width, file.header.height, color::WHITE, 0);
    tga_rasterizer rasterizer_pano(&buffer_pano);
    tga_rasterizer rasterizer_ortho(&buffer_ortho);

    Material mat(Vector(0.0f,0.0f,1.0f), 0.5f,0.5f,0.5f);
    Material mat2(Vector(1.0f,0.0f,0.0f), 0.5f,0.5f,0.5f);
    Scene scene;
    scene.spheres = {
            {Vector(1, 1, 5), 2, mat},
            {Vector(-1, -1, 6), 1.5, mat2}
    };

    PanoramicCamera camera_pano(&buffer_pano);
    OrtographicCamera camera_ortho(&buffer_ortho);

    camera_pano.render_raw(scene);
    camera_ortho.render_raw(scene);

//    camera.render_scene();

    rasterizer_pano.debug();
    rasterizer_ortho.debug();
//    rasterizer.negative();
    file.data.buffer_data(buffer_pano.size(), buffer_pano.color_buffer);
    file.write("output-pnaoramic.tga");

    file.data.buffer_data(buffer_ortho.size(), buffer_ortho.color_buffer);
    file.write("output-orthographic.tga");

}
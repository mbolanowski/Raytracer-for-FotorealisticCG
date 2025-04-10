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

void foto::task3() {

    tga_file file;
    file.set_size(1600, 900);

    tga_buffer buffer(file.header.width, file.header.height, color::WHITE, 0);
    tga_rasterizer rasterizer(&buffer);

    OrtographicCamera camera(&buffer);
    camera.render_scene_light();

    //PanoramicCamera camera(&buffer);
    //camera.render_scene_light();

    rasterizer.debug();
    //rasterizer.negative();
    file.data.buffer_data(buffer.size(), buffer.color_buffer);

    file.write("output.tga");

}
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

void foto::task4() {

    tga_file file;
    file.set_size(400, 250);

    tga_buffer buffer_pano(file.header.width, file.header.height, color::WHITE, 0);
    tga_rasterizer rasterizer_pano(&buffer_pano);
    tga_buffer buffer_ortho(file.header.width, file.header.height, color::WHITE, 0);
    tga_rasterizer rasterizer_ortho(&buffer_ortho);

    //setup cornel box sides
    Material mat_wall_red(Vector(color::RED), 0.1f,0.05f,false, false);
    Material mat_wall_green(Vector(color::GREEN), 0.1f,0.05f,false, false);
    Material mat_wall_white(Vector(color::WHITE), 0.1f,0.05f,false, false);

    Plane left(Vector(-1,0,0), Vector(-3, 0, 0));
    left.Material_ = mat_wall_red;
    Plane right(Vector(1,0,0), Vector(3, 0, 0));
    right.Material_ = mat_wall_green;
    Plane top(Vector(0,-1,0), Vector(0, -3, 0));
    top.Material_ = mat_wall_white;
    Plane bottom(Vector(0,1,0), Vector(0, 3, 0));
    bottom.Material_ = mat_wall_white;
    Plane back(Vector(0,0,-1), Vector(0, 0, -5));
    back.Material_ = mat_wall_green;

    PointLight light(Vector(0.0f, 0.0f, 2.f), Vector(1.0f, 1.0f, 1.0f));


    Material mat(Vector(color::RED), 0.1f,0.05f,true, false);
    Material mat2(Vector(color::GREEN), 0.1f,0.05f,false, true, 1.2f);
    Material mat3(Vector(color::BLUE), 0.1f,0.05f,false, false);
//    PointLight light(Vector(4.0f,5.0f,5.0f), Vector(1.0f,1.0f,0.0f));
    Sphere sphere{Vector(0, 0, 4), 1.5, mat3};
    Sphere sphere2{Vector(0, -1.75, 2.5), 0.75, mat2};
    Sphere sphere3{Vector(1, 0, 1.5), 0.75, mat};

    Scene panoramicScene;
    panoramicScene.spheres = {sphere, sphere2, sphere3};
    panoramicScene.planes = {left, right, top, bottom, back};
    panoramicScene.lights = {light};
    panoramicScene.ambientLight = Vector(0.1f, 0.1f, 0.1f);

//    Scene orthoScene;
//    orthoScene.spheres = {sphere, sphere2, sphere3};
//    orthoScene.planes = {left, right, top, bottom, back};
//    orthoScene.lights = {light};
//    orthoScene.ambientLight = Vector(0.1f, 0.1f, 0.1f);

    PanoramicCamera camera(&buffer_pano);
    camera.useAA = false;
//    camera.render_phong(panoramicScene);
    camera.render_recurse(panoramicScene, 3);

//    OrtographicCamera camera_ortho(&buffer_ortho);
//    camera_ortho.render_phong(panoramicScene);
//    camera_ortho.render_recurse(panoramicScene, 1);

    rasterizer_pano.debug();
//    rasterizer_ortho.debug();
//    rasterizer_pano.negative();
    //rasterizer_ortho.negative();
    file.data.buffer_data(buffer_pano.size(), buffer_pano.color_buffer);
    file.write("output-panoramic.tga");
//    file.data.buffer_data(buffer_ortho.size(), buffer_ortho.color_buffer);
//    file.write("output-orthographic.tga");

}
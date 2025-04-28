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
    file.set_size(400, 250);

    tga_buffer buffer(file.header.width, file.header.height, color::WHITE, 0);
    tga_rasterizer rasterizer(&buffer);

        Material mat(Vector(1.0f,0.0f,0.0f), 0.1f,0.05f,0.0f);
    Material mat2(Vector(1.0f,1.0f,0.0f), 0.1f,0.05f,0.0f);
    PointLight light(Vector(4.0f,5.0f,5.0f), Vector(1.0f,1.0f,0.0f));
    Sphere sphere{Vector(0, 1.2, 5), 1.5, mat};
    Sphere sphere2{Vector(0, -2.9, 5), 2.5, mat2};

    Scene panoramicScene;
    panoramicScene.spheres = {sphere, sphere2};
    panoramicScene.lights = {light};
    panoramicScene.ambientLight = Vector(0.1f, 0.1f, 0.1f);

    Sphere ortsphere{Vector(0.2, 0.2, 4), 0.2, mat};
    Sphere ortsphere2{Vector(-0.3, -0.3, 4), 0.4, mat2};
    Scene orthoScene;
    orthoScene.spheres = {ortsphere, ortsphere2};
    orthoScene.lights = {light};
    orthoScene.ambientLight = Vector(0.1f, 0.1f, 0.1f);

    OrtographicCamera camera(&buffer);
//    camera.render_scene_light();
    camera.render_phong(orthoScene);

//    PanoramicCamera camera(&buffer);
//    camera.render_scene_light();
//    camera.render_phong(panoramicScene);

    rasterizer.debug();
    //rasterizer.negative();
    file.data.buffer_data(buffer.size(), buffer.color_buffer);

    file.write("output.tga");

}
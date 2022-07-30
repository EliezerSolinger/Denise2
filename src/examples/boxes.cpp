
#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <cstdlib>
#include <cstdio>

#include "dmath.hpp"
#include "dsystem.hpp"
#include "mesh_renderer.hpp"

#include "FPSCamera.cpp"

//#include "mesh_renderer.hpp"

using namespace DMath;
using namespace DSystem;
using namespace MeshRenderer;


int main (int argc, char *argv[]) {  
    printf("main fun called..\n");
    DSystem::init("MeshRenderer2 Demo - BOXES");
    MeshRenderer::init();
    Camera camera=Camera();
    camera.setup2D();
    GPUMesh box=mesh_box();
    Material material=Material();
    FPSCamera::init();
    while(update()) {
        //camera.draw_viewport();
        FPSCamera::update();
        if(Input::pressing(Input::BACK)) break;
       // printf("%f \n",Time::elapsed());
        material.diffuse_color=Color::CYAN();
        draw(box,Mat4().translated(0,-2,0),    FPSCamera::camera,material);
        material.diffuse_color=Color::BLACK();
        draw(box,Mat4().translated(0,2,0),     FPSCamera::camera,material);
        material.diffuse_color=Color::WHITE();
        draw(box,Mat4().translated(0,4,0),     FPSCamera::camera,material);
        material.diffuse_color=Color::RED();
        draw(box,Mat4().translated(0,0,0),    FPSCamera::camera,material);
        // printf("%f\n",delta());
    }
    destroy();
    return 0;
}

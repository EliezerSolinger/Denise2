
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <cstdlib>
#include <cstdio>
#include "dmath.hpp"
#include "dsystem.hpp"
#include "denise.hpp"

#include "FPSCamera.cpp"
//#include "denise.hpp"

using namespace DMath;
using namespace DSystem;
using namespace Denise;
int main() {
    DSystem::init("Denise2 Demo - BOXES");
    Denise::init();
    Camera camera=Camera();
    camera.setup2D();
    VBO box=vbo_box();
    Material material=Material();
    FPSCamera::init();
    while(update()) {
        //camera.draw_viewport();
        FPSCamera::update();
        if(Input::pressing(GLFW_KEY_ESCAPE)) break;
       // printf("%f \n",Time::elapsed());
        material.diffuse=Color::CYAN();
        draw(box,Mat4().translated(0,-2,0),    FPSCamera::camera,material);
        material.diffuse=Color::BLACK();
        draw(box,Mat4().translated(0,2,0),     FPSCamera::camera,material);
        material.diffuse=Color::WHITE();
        draw(box,Mat4().translated(0,4,0),     FPSCamera::camera,material);
        material.diffuse=Color::RED();
        draw(box,Mat4().translated(0,0,0),    FPSCamera::camera,material);
        // printf("%f\n",delta());
    }
    destroy();
}

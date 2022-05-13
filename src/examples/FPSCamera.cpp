#ifndef FPSCAMERA_HPP
#define FPSCAMERA_HPP
#include "denise.hpp"
#include "dmath.hpp"
#include "dsystem.hpp"
#include "GLFW/glfw3.h"

namespace FPSCamera {
    using namespace DMath;
    using namespace Denise;
    using namespace DSystem;
    Camera camera=Camera();
    static Vec2 axis=Vec2(0,0);
    static Vec3 pos=Vec3(0,0,-10);
    static float speed=0;
    inline void init() {
        camera.setup3D();
    }
    inline void update() {
        speed=Time::delta()/2;
        if(Input::pressing(GLFW_KEY_LEFT_SHIFT)) speed*=3;
        Vec3 mov=Vec3(0,0,0);
        if(Input::pressing(GLFW_KEY_W)) mov=mov+Vec3(0,0,1);
        if(Input::pressing(GLFW_KEY_S)) mov=mov+Vec3(0,0,-1);
        if(Input::pressing(GLFW_KEY_A)) mov=mov+Vec3(1,0,0);
        if(Input::pressing(GLFW_KEY_D)) mov=mov+Vec3(-1,0,0);
        if(Input::pressing(GLFW_KEY_E)) mov=mov+Vec3(0,1,0);
        if(Input::pressing(GLFW_KEY_Q)) mov=mov+Vec3(0,-1,0);


        if(Input::pressing(GLFW_KEY_LEFT))      axis.y-=speed;
        if(Input::pressing(GLFW_KEY_RIGHT))     axis.y+=speed;
        if(Input::pressing(GLFW_KEY_UP))        axis.x-=speed;
        if(Input::pressing(GLFW_KEY_DOWN))      axis.x+=speed;

        pos+= Mat4().translated(mov).rotated(Vec3(axis.x,axis.y,0)).translation()/20;
        camera.draw_viewport();
        camera.view_matrix=Mat4::mul(
            Mat4::mul(Mat4().rotated(-axis.x,0,0),Mat4().rotated(0,-axis.y,0))  ,
            Mat4().translated(Vec3(pos.x,-pos.y,pos.z))
        );
        
    }
}
#endif
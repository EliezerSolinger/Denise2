#ifndef FPSCAMERA_HPP
#define FPSCAMERA_HPP
#include "../mesh_renderer.hpp"
#include "../dmath.hpp"
#include "../dsystem.hpp"
 
using DMath::Vec2;
using DMath::Vec3;
using DMath::Mat4;
using MeshRenderer::Camera;
using namespace DSystem;

class FPSCamera { 
    public:
        Camera camera=Camera();
        Vec2 rotation=Vec2(0,0);
        Vec3 pos=Vec3(0,0,-10);
    float speed=0;

    inline void init() {
        camera.setup3D();
    }
    inline void update() {
        float _speed=Time::delta()*4;
        if(Input::pressing(Input::LT)) _speed*=3;

        // rotacao
        rotation+=Input::alt_axis()*Time::delta();

        // movimento
        Vec2 mov_axis=Input::axis()*3*_speed;
        pos+= Mat4().translated(Vec3(mov_axis.x,0,-mov_axis.y)).rotated(rotation.y, rotation.x, 0).translation();
        camera.position=pos;
        camera.draw_viewport();
        camera.view_matrix=
        Mat4::mul(
            Mat4::mul(Mat4().rotated(-rotation.y,0,0),Mat4().rotated(0,-rotation.x,0)), 
            Mat4().translated( -pos.x,-pos.y,-pos.z ) 
        );
        
    }
};
#endif
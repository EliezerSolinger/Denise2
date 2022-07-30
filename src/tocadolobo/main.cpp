/* C++ HELLO WORLD */
/*
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
*/
#include <stdio.h>



#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "dmath.hpp"
#include "dsystem.hpp"
#include "mesh_renderer.hpp"
#include <iostream>
#include "FPSCamera.hpp"
//#include "mesh_renderer.hpp"

using namespace DMath;
using namespace DSystem;
using namespace MeshRenderer;

#include "voxel.cpp"

#include "chunk.cpp"
 
Texture load_grid_texture() {
    constexpr int texture_res=32;
    constexpr int grid_distance=4;
    CPUTextureBuffer buffer=CPUTextureBuffer(texture_res,texture_res,4);
    buffer.alloc(); 
    for(int y=0; y<texture_res; y++) for(int x=0; x<texture_res; x++) { 
        buffer.put_pixel_color(x,y,
            Color(0,0,0,(x%grid_distance==0 || y%grid_distance==0) ? 1.f : 0.f )
        ); 
    }  
    Texture texture=Texture::LOAD_FROM_BUFFER(buffer);
    buffer.free();         
    return texture; 
}

Texture load_perlin_texture(uint32_t texture_res=32,float freq=0.4, uint32_t depth=4, uint32_t seed=0) {  
    CPUTextureBuffer buffer=CPUTextureBuffer(texture_res,texture_res,1);
    buffer.alloc(); 
    for(int y=0; y<texture_res; y++) for(int x=0; x<texture_res; x++) {  
        buffer.put_pixel_color(x,y,float_to_byte(perlin2d(x, y, freq, depth,seed))); 
    }  
    Texture texture=Texture::LOAD_FROM_BUFFER(buffer,true,true);
    buffer.free();        
    return texture; 
}


FPSCamera fpscamera;

int main() {
    printf("main fun called..\n");
    DSystem::init("MeshRenderer2 Demo - BOXES");
    MeshRenderer::init();
   
    Camera camera=Camera();
    GPUMesh quad=mesh_quad();
    GPUMesh box=mesh_box();
    fpscamera.init(); 

    printf("chegou aqui 1\n");
    fpscamera.camera.skybox.albedo=MeshRenderer::LOAD_TEXTURE("skybox2.jpg",true);

    printf("chegou aqui 2\n");
    Material material=Material(); 
    material.opaque();
    material.Kd=0.4;

    Chunk chunk;
    chunk.load();
    //material.albedo=chunk.texture.id;

    Material water;
    water.albedo_color=Color(0.5, 0.5, 1, 1);
    water.opaque();
    water.Kd=0.2;
    water.albedo=MeshRenderer::LOAD_TEXTURE("water1.jpg",true);
    water.texture_scale=Vec2(2000.f,2000.f);
    water.cubemap=MeshRenderer::LOAD_CUBEMAP("skybox2.jpg",true);
    //water.cubemap=fpscamera.camera.skybox.albedo;
    //water.cubemap=MeshRenderer::LOAD_CUBEMAP("skybox2.jpg",true);
   
    Material grid;
    grid.albedo=load_grid_texture();
    grid.opaque();
    

    printf("Generating drawing...\n"); 
    load_chunks(fpscamera.pos);
    fpscamera.camera.skybox_y=0.05;
    fpscamera.camera.skybox_yaw=0.5;
    fpscamera.camera.fog_density=6;
    int timerx=0;
    water.mirror=0.4;
    while(update()) {
        
        fpscamera.camera.skybox_yaw=Time::elapsed()/300.0;
        //camera.draw_viewport();
        fpscamera.update();
        fpscamera.camera.draw_skybox();

        if(Input::pressed(Input::BACK)) break; 
        auto player_pos=fpscamera.pos;
        if(Input::pressing(Input::B)) {
            load_chunks(player_pos);
        }
       //if(Time::every(&timerx,1))
        load_chunks(player_pos);
        // printf("%f \n",Time::elapsed());
        material.diffuse_color=Color::CYAN();
        draw(box,Mat4().translated(0,-2,0),fpscamera.camera,material);
        material.diffuse_color=Color::BLACK();
        draw(box,Mat4().translated(0,2,0),fpscamera.camera,material);
        material.diffuse_color=Color::WHITE();
        draw(box,Mat4().translated(0,4,0),fpscamera.camera,material);
        material.diffuse_color=Color::RED();
        draw(box,Mat4().translated(0,0,0),fpscamera.camera,material);
        material.diffuse_color=Color::WHITE();
        uint32_t chunks_drawed=0;
        for(auto &ck:chunks) {
            //float chunk_distance=Vec3::distance(chunk_global_position(x,y),player_pos);
           // if(chunk_distance>render_distance*CHUNK_SIZE) continue;
          //  if(Vec3::distance(ck.global_position(),Vec3(player_pos.x,0,player_pos.z))>render_distance*CHUNK_SIZE) continue;
            if(!ck.loaded) continue;
            if(ck.peak_height<0.5725490196) continue;
            material.albedo=ck.texture.id;
            auto ckpos=ck.global_position();
            if(
                (fpscamera.camera.view_matrix*ckpos).z>CHUNK_SIZE
            ) continue;
            Mat4 model_m=Mat4().translated(ckpos.x,-6,ckpos.z);
           // draw(box,model_m*ck.terrain.bound_box.matrix(),fpscamera.camera,grid); 
            if(draw(ck.terrain,model_m,fpscamera.camera,material)) { chunks_drawed++; }
        }
        water.texture_offset.x=sin(Time::elapsed()*0.005)*0.01;
        water.texture_offset.y=cos(Time::elapsed()*0.005)*0.01;
 
        // printf("%f\n",delta());
        draw(box,Mat4().scaled(CHUNK_SIZE*200,1,CHUNK_SIZE*200).translated(CHUNK_SIZE/2,0,CHUNK_SIZE/2),fpscamera.camera,water);
        draw_sprite(Mat4().scaled(10),fpscamera.pos,fpscamera.camera,water);
        if(Input::pressed(Input::X)) {
            std::cout << "player chunk X " << player_to_chunk_coord(fpscamera.pos.x)
                                    << " Y " << player_to_chunk_coord(fpscamera.pos.z) 
                                    << " DRAWING " << chunks_drawed << " CHUNKS" << std::endl;
        }
    }

    unload_all_chunks();
    destroy();

    return 0;
}

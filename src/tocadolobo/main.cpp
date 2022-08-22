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
 
#include "world/perlin.hpp"
#include "world/world.hpp"

static const int default_permutation[] = {
    208,34,231,213,32,248,233,56,161,78,24,140,71,48,140,254,245,255,247,247,40,
    185,248,251,245,28,124,204,204,76,36,1,107,28,234,163,202,224,245,128,167,204,
    9,92,217,54,239,174,173,102,193,189,190,121,100,108,167,44,43,77,180,204,8,81,
    70,223,11,38,24,254,210,210,177,32,81,195,243,125,8,169,112,32,97,53,195,13,
    203,9,47,104,125,117,114,124,165,203,181,235,193,206,70,180,174,0,167,181,41,
    164,30,116,127,198,245,146,87,224,149,206,57,4,192,210,65,210,129,240,178,105,
    228,108,245,148,140,40,35,195,38,58,65,207,215,253,65,85,208,76,62,3,237,55,89,
    232,50,217,64,244,157,199,121,252,90,17,212,203,149,152,140,187,234,177,73,174,
    193,100,192,143,97,53,145,135,19,103,13,90,135,151,199,91,239,247,33,39,145,
    101,120,99,3,186,86,99,41,237,203,111,79,220,135,158,42,30,154,120,67,87,167,
    135,176,183,191,253,115,184,21,233,58,129,233,142,39,128,211,118,137,139,255,
    114,20,218,113,154,27,127,246,250,1,8,198,250,209,92,222,173,21,88,102,219
};

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

Texture load_perlin_texture() {  
    Perlin seed(10);
    // memcpy(perlin.permutation_table,default_permutation,256);
    NoiseParameter p;
    uint32_t texture_res=1024;

    CPUTextureBuffer buffer=CPUTextureBuffer(texture_res,texture_res,1);
    buffer.alloc(); 
    for(int y=0; y<texture_res; y++) for(int x=0; x<texture_res; x++) {  
       // buffer.put_pixel_color(x,y,float_to_byte(p.noise(Vec2(x, y))));  
        buffer.put_pixel_color(x,y,float_to_byte(p.noise(Vec2(x, y)))); 
    }  
    Texture texture=Texture::LOAD_FROM_BUFFER(buffer,false,false);
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
    fpscamera.camera.skybox.diffuse=MeshRenderer::LOAD_TEXTURE("skybox2.jpg",true);

    printf("chegou aqui 2\n");


    Material wmap;
    wmap.opaque();



    Material material=Material(); 
    material.opaque();
    material.Ka=0.1;
    material.Kd=0.8f;
    material.Ks=0.7;

    Chunk chunk;
    chunk.load();
    //material.diffuse=chunk.texture.id;

    Material water;
    water.diffuse_color=Color(0.5, 0.5, 1, 1);
  //  water.opaque();
    water.Kd=0.2;
    water.diffuse=MeshRenderer::LOAD_TEXTURE("water1_COLOR.jpg",true);
    water.specular_map=MeshRenderer::LOAD_TEXTURE("water1_SPEC.jpg",true);
    water.normal_map=MeshRenderer::LOAD_TEXTURE("water1_NRM.jpg",true);
    water.texture_scale=Vec2(2000.f,2000.f);
    water.cubemap=MeshRenderer::LOAD_CUBEMAP("skybox2.jpg",true);
    water.Ks=0.6;
   water.shininess=2;
    //water.cubemap=fpscamera.camera.skybox.diffuse;
    water.cubemap=MeshRenderer::LOAD_CUBEMAP("skybox2.jpg",true);
   
    material.diffuse=MeshRenderer::LOAD_TEXTURE("water1_COLOR.jpg",true);
    material.specular_map=MeshRenderer::LOAD_TEXTURE("water1_SPEC.jpg",true);
    material.normal_map=MeshRenderer::LOAD_TEXTURE("water1_NRM.jpg",true);

        wmap.diffuse=load_perlin_texture();
    Material grid;
    grid.diffuse=load_grid_texture();
    grid.opaque();
    

    printf("Generating drawing...\n"); 
    load_chunks(fpscamera.pos);
    fpscamera.camera.skybox_y=0.05;
    fpscamera.camera.skybox_yaw=0.5;
    fpscamera.camera.fog_density=6;
    fpscamera.camera.fog_color=Color(0.05,0.06,0.1,1);
    int timerx=0;
    water.mirror=0.6;
    material.mirror=0.3;
    //material.Ks=0.7;
   /// material.shininess=20;
    while(update()) {   
        
        fpscamera.camera.skybox_yaw=DEG_TO_RAD*90;;//Time::elapsed()/300.0;
        //camera.draw_viewport();
        fpscamera.update();
        fpscamera.camera.draw_skybox();


        if(Input::pressed(Input::BACK)) break; 
        auto player_pos=fpscamera.pos;
        if(Input::pressing(Input::B)) {
            load_chunks(player_pos);
        }
        wmap.diffuse_color=Color::WHITE();
        draw(mesh_box(),Mat4().scaled(30,30,1).translated(0,20,0) ,fpscamera.camera,wmap);
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
            material.diffuse=ck.texture.id; 
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

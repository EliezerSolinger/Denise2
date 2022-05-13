/* C++ HELLO WORLD */
/*
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
*/
#include <stdio.h>
extern "C" {
    #include "perlin.c"
}

#define SEED_MAPA 0
#define SEED_BIOMA 1
#define TERRAIN_SIZE 1024

enum Tipo {
    AGUA,
    TERRA,
    AREIA,
    ARVORE,
    NEVE,
    PEDRA
};


#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "dmath.hpp"
#include "dsystem.hpp"
#include "denise.hpp"

#include "../FPSCamera.cpp"
//#include "denise.hpp"

using namespace DMath;
using namespace DSystem;
using namespace Denise;


int main() {
    DSystem::init("Denise2 Demo - BOXES");
    Denise::init();
    printf("alocatting..\n");
    
    unsigned char* mapa = new unsigned char[TERRAIN_SIZE*TERRAIN_SIZE];
    unsigned char* texture = new unsigned char[TERRAIN_SIZE*TERRAIN_SIZE*4];
    memset(mapa, 0, TERRAIN_SIZE*TERRAIN_SIZE);
    memset(texture, 0, TERRAIN_SIZE*TERRAIN_SIZE*4);
    printf("Generating map...\n");
    int x, y;
    for(y=0; y<TERRAIN_SIZE; y++) for(x=0; x<TERRAIN_SIZE; x++) {
        float h=perlin2d(x, y, 0.01, 3,SEED_BIOMA)*255;
        mapa[(y * TERRAIN_SIZE + x)] = h;
        Tipo tipo = AGUA;
        if(h>=56+90) tipo = AREIA;
        if(h>=56+90) {
            srand(x*y);
            if(perlin2d(x, y, 0.006, 2,SEED_BIOMA)>0.68) tipo = NEVE;
            else if(perlin2d(x, y, 0.006, 2,SEED_BIOMA)<0.4) tipo = AREIA;
            else tipo = TERRA;


            // deixa espaços em branco que nao existem arvores no mapa
            if(perlin2d(x, y, 0.9, 4,SEED_MAPA)>0.55) {
                if(x%3==rand()%3 && y%3==rand()%3)  tipo = ARVORE;
            }
            
        }
        if(h>=65+170) {
            tipo = PEDRA;
        }
        

        float r=1, g=1, b=1;
        if(tipo==AGUA) r=0.5, g=0.5, b=1;
        if(tipo==AREIA) r=0.76, g=0.7, b=0.5;
        if(tipo==TERRA) r=0.3, g=0.4, b=0.2;
        if(tipo==NEVE) r=0.9, g=0.9, b=0.9;
        if(tipo==PEDRA) r=0.5, g=0.5, b=0.5;

        if(tipo==ARVORE) {
            r=0.3, g=0.4, b=0.2;
            if(h>=65+90) r=0.5, g=0.5, b=0.5;
        }

        texture[(y * TERRAIN_SIZE + x)*4] = r*255;
        texture[(y * TERRAIN_SIZE + x)*4+1] = g*255;
        texture[(y * TERRAIN_SIZE + x)*4+2] = b*255;
        texture[(y * TERRAIN_SIZE + x)*4+4] = 255;
    }
    /*
        stbi_write_png("texture.png", TERRAIN_SIZE, TERRAIN_SIZE, 4, texture, TERRAIN_SIZE*4);
        stbi_write_png("heightmap.png", TERRAIN_SIZE, TERRAIN_SIZE, 4, mapa, TERRAIN_SIZE*4);
    */
    Camera camera=Camera();
    VBO box=vbo_box();
    Material material=Material();
    FPSCamera::init();
    printf("Generating texture...\n");
 
    material.albedo=Textures::load_RGBAIntArray(texture, TERRAIN_SIZE, TERRAIN_SIZE);
    printf("Generating vertice buffer...\n");
    VertexData *vertices= new VertexData[TERRAIN_SIZE*TERRAIN_SIZE*6];
    int i=0;
    for(y=0; y<TERRAIN_SIZE-1; y++) for(x=0; x<TERRAIN_SIZE-1; x++) {
       // printf("washing %dx%d\n", x, y);
        double prop=1.0/(double)TERRAIN_SIZE;
        vertices[i].vertex=Vec3(x, (double) mapa[(y * TERRAIN_SIZE + x)] / 255, y);
        vertices[i].normal=Vec3(0, 1, 0);
        vertices[i].uv=Vec2(x, y)*prop;
        i++;
        vertices[i].vertex=Vec3(x+1, (double)  mapa[((y+1) * TERRAIN_SIZE + (x+1))]/ 255, y+1);
        vertices[i].normal=Vec3(0, 1, 0);
        vertices[i].uv=Vec2(x+1, y+1)*prop;
        i++;
        vertices[i].vertex=Vec3(x+1,  (double)mapa[(y * TERRAIN_SIZE + (x+1))] / 255,y);
        vertices[i].normal=Vec3(0, 1, 0);
        vertices[i].uv=Vec2(x+1, y)*prop;
        i++;

        vertices[i].vertex=Vec3(x, (double)mapa[((y+1) * TERRAIN_SIZE + x)] / 255, y+1);
        vertices[i].normal=Vec3(0, 1, 0);
        vertices[i].uv=Vec2(x, y+1)*prop;
        i++;
        vertices[i].vertex=Vec3(x+1,  (double)mapa[((y+1) * TERRAIN_SIZE + (x+1))] / 255,y+1);
        vertices[i].normal=Vec3(0, 1, 0);
        vertices[i].uv=Vec2(x+1, y+1)*prop;
        i++;
        vertices[i].vertex=Vec3(x, (double)mapa[(y * TERRAIN_SIZE + x)] / 255, y);
        vertices[i].normal=Vec3(0, 1, 0);
        vertices[i].uv=Vec2(x, y)*prop;
        i++;
        

    }
    printf("sending mesh to gpu...\n");
    VBO terrain=VBO::LOAD_MESH(vertices, TERRAIN_SIZE*TERRAIN_SIZE*6);
    Material water=Material();
    water.diffuse=Color(0.5, 0.5, 1, 1);
    printf("Generating drawing...\n");
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
        material.diffuse=Color::WHITE();
        draw(terrain,Mat4().scaled(1,50,1).translated(-TERRAIN_SIZE/2,-50,-TERRAIN_SIZE/2),FPSCamera::camera,material);
        // printf("%f\n",delta());
        draw(box,Mat4().scaled(TERRAIN_SIZE,1,TERRAIN_SIZE).translated(-TERRAIN_SIZE/2,-25,-TERRAIN_SIZE/2),FPSCamera::camera,water);
    }
    destroy();

    return 0;
}
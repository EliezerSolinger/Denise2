#include <stdio.h>
#include <stdint.h>

#include "perlin.hpp"
#include "../dmath.hpp"
#include <map>

#include "world.hpp"
#include "string.h"
#include "stdio.h"

using std::map; 
// Perlin seed; 

static const int world_coordinate_bias=100000;
static map<uint32_t,Perlin> seeds;
static const uint32_t pow2[] = { 1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384,32768};




static Perlin perlin(0);
static bool in=false;
float NoiseParameter::noise(DMath::Vec2 point) {
   
    point+=world_coordinate_bias;
    point+=offset;
    if(flip) point=point.flipped();
    point=point.abs();
    
    if(!seeds.count(seed)) {
        auto new_seed=new Perlin(seed);
        seeds[seed]=*new_seed;
        delete new_seed;            
    }

    Perlin& perlin=(seeds.find(seed)->second);
    float h=perlin.noise2d(point.x,point.y);
    for(auto i=1;i<=octaves-1;i++) {  
        float factor=1.0/pow2[i];
        float sc=scale*factor;
        auto sp=(point*sc)+pow2[i];
        h+=(perlin.noise2d(sp.x,sp.y)+1)/2;
        h/=2;
    }
    return h;
}   
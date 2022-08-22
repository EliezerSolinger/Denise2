#ifndef TOCA_WORLD_H
#define TOCA_WORLD_H
 
#include "../dmath.hpp"
using DMath::Vec2;
enum LevelName {
    VERY_LOW    =0,
    LOW         =1,
    MEDIUM      =2,
    HIGH        =3,
    VERY_HIGH   =4
};
struct NoiseLevels {
    float very_low=0,low=0,high=0,very_high=0;
    inline LevelName get_level(float value) { 
      if(value<=very_low) return VERY_LOW;
      else if(value<=low) return LOW;
      else if(value<=high) return MEDIUM;
      else if(value<=very_high) return HIGH;
      else return VERY_HIGH;
    } 
};
struct NoiseParameter {
    float scale = 20;
    uint32_t octaves=1;
    Vec2 offset=Vec2(0,0);
    uint32_t seed=0;
    bool flip=false;
    NoiseLevels levels;
    
    float noise(Vec2 point);
};


#endif
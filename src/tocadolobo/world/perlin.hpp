#ifndef TOCA_PERLIN_H
#define TOCA_PERLIN_H 

#include <stdint.h>
#include <random>

struct Perlin { 
    uint32_t seed=0;
    uint8_t permutation_table[256];
    
    public:
    inline void set_seed(uint32_t s) {
        std::mt19937 mt(s);
        seed = s;
        mt.seed(s);
        std::uniform_int_distribution<uint8_t> dist(0,255);
        for (int i=0; i<256; i++) {
            permutation_table[i] = dist(mt);
        }
    };
    Perlin() {
        set_seed(0);
    }
    Perlin(uint32_t s) {
        set_seed(s);
    }  
    /** 0 to 256 i suppose */
    inline uint8_t noise2(int x, int y) {
        int ind=(permutation_table[y % 256] + x);
        if(ind<0) ind=-ind;
        return permutation_table[ ind % 256 ];
    }

    inline float lin_inter(float x, float y, float s) { // interpolacao linear
        return x + s * (y-x);
    }
    inline float smooth_inter(float x, float y, float s) { // interpolacao bicubica acho 
        return lin_inter(x, y, s * s * (3-2*s));
    }

    inline float noise2d(float x, float y) {
        int x_int = x;
        int y_int = y;
        float x_frac = x - x_int;
        float y_frac = y - y_int;
        int s = noise2(x_int, y_int);
        int t = noise2(x_int+1, y_int);
        int u = noise2(x_int, y_int+1);
        int v = noise2(x_int+1, y_int+1);
        float low = smooth_inter(s, t, x_frac);
        float high = smooth_inter(u, v, x_frac);
        return (float) smooth_inter(low, high, y_frac)/255.0f;
    }
};

#endif

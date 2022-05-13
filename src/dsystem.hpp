#ifndef DENISE_SYSTEM_HPP
#define DENISE_SYSTEM_HPP
#include <cstdio>

#include  "dmath.hpp"


namespace DSystem {
    using namespace DMath;
    
    bool init(const char* title);
    bool update();
    void destroy();
    Vec2 window_size();
    void stop();

    namespace Time {
        
        double delta();
        double elapsed();
        double elapsed_since(double time);
        double fps_approx();
    }
    namespace Input {
        enum KeyStatus {
            NOT_PRESSED = 0,
            PRESSED = 1,
            PRESSING = 2,
            RELEASED = 3
        };

        void register_key(int key, KeyStatus status);
        bool released(int key);
        bool pressed(int key);
        bool pressing(int key);
    }
}

#endif
#ifndef MESH_RENDERER_SYSTEM_HPP
#define MESH_RENDERER_SYSTEM_HPP
#include <cstdio>
#include  "dmath.hpp"

namespace DSystem {
    using DMath::Vec2;
     
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
        inline bool every(int *timer,int seconds) {
            int elapsed_time=(int) elapsed();
            if(elapsed_time%seconds==0 && elapsed_time!=*timer) {
                *timer=elapsed_time;
                return true;
            }
            return false;
        }
    }
    namespace Input {
        enum Key { // based on XBOX Controller
            UNKNOWN=0,
            UP,  DOWN,
            LEFT, RIGHT,
            ALT_UP, ALT_DOWN,
            ALT_LEFT, ALT_RIGHT,
            X, Y, A , B,
            RB, RT, LB, LT,
            START, BACK
        };
        enum KeyStatus {
            NOT_PRESSED = 0,
            PRESSED = 1,
            PRESSING = 2,
            RELEASED = 3
        };

        void register_key(Key key, KeyStatus status);
        bool released(Key key);
        bool pressed(Key key);
        bool pressing(Key key);
        inline Vec2 axis() {
            return Vec2(
                (pressing(LEFT) ? -1.0f : 0.0f) + (pressing(RIGHT) ? 1.0f : 0.0f),
                (pressing(DOWN) ? -1.0f : 0.0f) + (pressing(UP) ? 1.0f : 0.0f)
            );
        }
        inline Vec2 alt_axis() {
            return Vec2(
                (pressing(ALT_LEFT) ? -1.0f : 0.0f) + (pressing(ALT_RIGHT) ? 1.0f : 0.0f),
                (pressing(ALT_DOWN) ? -1.0f : 0.0f) + (pressing(ALT_UP) ? 1.0f : 0.0f)  
            );
        }
    }
    namespace VFS { // VIRTUAL FILESYSTEM
        struct FileInfo {   
            size_t size=0;
            void* data=NULL;
            inline void free_pointer() {
                if(data) free(data);
                size=0;
                data=NULL;
            }  
        };
        FileInfo load_file(const char *path);
        struct ImageInfo {
            uint32_t width, height, channels;
            void* data=NULL;
            inline void free_pointer() {
                if(data) free(data);
                width=height=channels=0;
                data=NULL;
            }
        };
        ImageInfo load_jpeg(const char *path);
    }
}

#endif
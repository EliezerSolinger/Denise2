#ifndef DENISE_HPP
#define DENISE_HPP
#include <glad/glad.h>
#include "dmath.hpp"
#include "glhelpers.hpp"
#include "dsystem.hpp"
#include "denise.hpp"

namespace Denise {
    using namespace DMath;
    enum CameraMode {
        CAMERA_HUD,
        CAMERA_2D,
        CAMERA_3D
    };
    class Camera {
        public:
        CameraMode mode;
        bool fix_aspect, is_perspective;
        double fov, near, far, aspect,
                ortho_left, ortho_right,
                ortho_bottom, ortho_top;
        Color clear_color;
        Rect viewport;
        Mat4 view_matrix; 

        Camera() {
            mode=CAMERA_2D;
            fix_aspect=false;
            is_perspective=false;
            clear_color=Color(0.6,0.75,1.0,1.0);
            fov=70; near=-0.1; far=1000;
            aspect=1.0;
            ortho_left=-1; ortho_right=1;
            ortho_bottom=-1; ortho_top=1;
            viewport=Rect();
            view_matrix=Mat4::IDENTITY();
            
       }

         inline void setup2D(double zoom=10) {
            mode=CAMERA_2D;
            is_perspective=false;
            fix_aspect=true;
            near=-0.01;far=30;
            double half_width=zoom*0.5;
            ortho_top=half_width;    ortho_bottom=-half_width;
            ortho_left=-half_width;  ortho_right=half_width;
        }
        inline void setupHUD() {
            mode=CAMERA_HUD;
            is_perspective=false;
            fix_aspect=false;
            near=-0.01;far=30;
            Vec2 win_size=DSystem::window_size();
            ortho_top=0;  ortho_bottom=win_size.y;
            ortho_left=0; ortho_right=win_size.x;
        }
        inline void setup3D(double fovy=70) {
            mode=CAMERA_3D;
            is_perspective=true;
            fix_aspect=true;
            near=0.1;far=200;
            fov=fovy;
        }
        inline Mat4 projection_matrix() {
            if(is_perspective) return Mat4::perspective(fov,aspect,near,far);

            return fix_aspect ?
                Mat4::ortho(ortho_bottom*aspect,ortho_top*aspect,ortho_bottom,ortho_top,near,far):
                Mat4::ortho(ortho_left,ortho_right,ortho_bottom,ortho_top,near,far);            
        }
        inline void draw_viewport() {
            Vec2 win_size=DSystem::window_size();
            if(fix_aspect) aspect=win_size.x/win_size.y;
            Vec2 pos=viewport.position*win_size;
            Vec2 size=viewport.size*win_size;
            glViewport(pos.x,pos.y,size.x,size.y);

            glClearColor(clear_color.r,clear_color.g,clear_color.b,clear_color.a);
            if(mode==CAMERA_3D) {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                glEnable(GL_DEPTH_TEST);
                //glEnable(GL_CULL_FACE);
                //glCullFace(GL_BACK);
            } else {
                glClear(GL_COLOR_BUFFER_BIT);
                glDisable(GL_DEPTH_TEST);
                glDisable(GL_CULL_FACE);
            }
            
             /*
                glEnable(GL_SCISSOR_TEST)
                glScissor(pos.x.toInt(), pos.y.toInt(), size.x.toInt(), size.y.toInt())
                glClear(GL_COLOR_BUFFER_BIT or GL_DEPTH_BUFFER_BIT)
                glDisable(GL_SCISSOR_TEST)
            */
        }
    };

    struct VertexData {
        Vec3 vertex,normal;
        Vec2 uv;
    };

    class VBO {
        public: GLuint buffer_id,draw_mode,vertices_count;
        VBO(GLuint buffer_id,GLuint vertices_count){ 
            this->buffer_id=buffer_id;
            this->vertices_count=vertices_count;
            draw_mode=GL_TRIANGLES;
          }
          VBO(){buffer_id=0;vertices_count=0; 
            draw_mode=GL_TRIANGLES;
          }
        inline void free() {
            glDeleteBuffers(1, &buffer_id);
            buffer_id=0;
            vertices_count=0;
        }
        static inline VBO LOAD_MESH(VertexData * data,GLuint vertices_count) {
            VBO vbo=VBO(0,vertices_count);
            glGenBuffers(1,&vbo.buffer_id);
            glBindBuffer(GL_ARRAY_BUFFER,vbo.buffer_id);
            printf ("VBO: %d generated \n", vbo.buffer_id);
            glBufferData(GL_ARRAY_BUFFER,sizeof(VertexData)*vertices_count,data,GL_STATIC_DRAW);
           
            glBindBuffer(GL_ARRAY_BUFFER,0);
            printf("loaded mesh with %d vertices\n",vertices_count);
            return vbo;
        }
    };
    struct PointLight {
        Vec3 position;
        Color color;
        float intensity;
        float radius;
        PointLight() {
            position=Vec3();
            color=Color(1,1,1,1);
            intensity=1;
            radius=1;
        }
    };

    struct Material {
        Color diffuse;
        GLuint albedo;
        Vec2 texture_scale;
        Material() {
            diffuse=Color(1,1,1,1);
            albedo=0;texture_scale=Vec2(1,1);
        }
    };
    void draw(VBO vbo,Mat4 matrix,Camera camera,Material material);
    void init();
    VBO vbo_quad();
    VBO vbo_box();
}
#endif
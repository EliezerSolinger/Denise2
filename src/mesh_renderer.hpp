#ifndef MESH_RENDERER_HPP
#define MESH_RENDERER_HPP

#include <glad/glad.h>
#include "dmath.hpp"
#include "glhelpers.hpp"
#include "dsystem.hpp" 


//#define DEBUG
namespace MeshRenderer {

    using namespace DMath;
    using namespace DGL;
    using namespace DSystem; 
    GPUMesh mesh_quad();
    GPUMesh mesh_box();
    GPUMesh mesh_skybox();

    /** VBO VERTICE GPU FORMAT */
    struct VertexData {  Vec3 vertex, normal; Vec2 uv; Vec3 tangent; Vec3 bitangent; };  

    struct MeshTriangle { 
        struct VertIndex { uint32_t vert, uv,normal; } vertices[3];
    };

    inline Texture LOAD_TEXTURE(std::string path,bool smoth=true,bool mipmap=true) {
        auto img = VFS::load_jpeg(path);
        auto buff =CPUTextureBuffer::FROM_POINTER(img.width,img.height,img.channels,img.data);
        Texture t=Texture::LOAD_FROM_BUFFER(buff,smoth,mipmap);
        //img.free_pointer(); // na verdade é o mesmo ponteiro
        buff.free(); // porque ele nao copia o ponteiro apenas o reinterpreta
        return t;
    }
    inline Texture LOAD_CUBEMAP(std::string path,bool smoth=true,bool mipmap=false) {
        auto img = VFS::load_jpeg(path);
        auto buff =CPUTextureBuffer::FROM_POINTER(img.width,img.height,img.channels,img.data);
        Texture t=Texture::LOAD_CUBEMAP_FROM_BUFFER(buff,smoth,mipmap);
        //img.free_pointer(); // na verdade é o mesmo ponteiro
        buff.free(); // porque ele nao copia o ponteiro apenas o reinterpreta
        return t;
    }
    inline GPUMesh LOAD_MESH(MeshRenderer::VertexData *data,unsigned int vertices_count) {
        #ifdef DEBUG
            printf("Loading mesh with %d vertices...\n",vertices_count);
        #endif
        VBO vbo; 
        for(int c=0; c<vertices_count; c++) vbo.bound_box.put_point(data[c].vertex);
        vbo.create();
        vbo.bind();
        vbo.set_data(sizeof(MeshRenderer::VertexData)*vertices_count,data);
        vbo.unbind(); 
        return GPUMesh::FROM_VBO(vbo);
    }

    class Mesh {
        public:
        std::vector<Vec3> vertices;
        std::vector<Vec3> normals;
        std::vector<Vec2> uvs; 
        std::vector<MeshTriangle> triangles;  // triangle indexes starting in 1

        inline GPUMesh send_to_gpu() {
           // printf("%d triangles \n",triangles.size());
            auto* data=new MeshRenderer::VertexData[triangles.size()*3];
            for(uint32_t t=0; t<triangles.size(); t++) {  
                
                auto triangle=triangles[t];    

                for(uint32_t v=0; v<3; v++) {
                    uint32_t vp=t*3+v; 
                    auto vert_indexes=triangle.vertices[v]; 
                    data[vp].vertex=vertices[vert_indexes.vert-1];
                    data[vp].normal=vert_indexes.normal ? normals[vert_indexes.normal-1] : Vec3(0,0,0);
                    data[vp].uv=vert_indexes.uv ? uvs[vert_indexes.uv-1] : Vec2(0,0);  
                }

                // TANGENT AND BITANGENT CALCULATION
                auto t3=t*3;
                Vec3 pos[]={
                    data[t3].vertex,
                    data[t3+1].vertex,
                    data[t3+2].vertex
                };
                Vec2 uv[]={
                    data[t3].uv,
                    data[t3+1].uv,
                    data[t3+2].uv
                };
                Vec3 edge1 = pos[1] - pos[0];
                Vec3 edge2 = pos[2] - pos[0];
                Vec2 deltaUV1 = uv[1] - uv[0];
                Vec2 deltaUV2 = uv[2] - uv[0];
                GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
                
                Vec3 tangent=(Vec3(
                    (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x),
                    (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y),
                    (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z)                    
                )*f).normalized(); 

                Vec3 bitangent=(
                    Vec3( 
                        (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x),
                        (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y),
                        (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z)            
                    ) * f
                ).normalized();   

                for(uint32_t v=0; v<3; v++) {
                    uint32_t vp=t*3+v;  
                    data[vp].tangent=tangent;
                    data[vp].bitangent=bitangent;
                }
            }
            GPUMesh mesh=LOAD_MESH(data,triangles.size()*3);
            delete[] data;
            return mesh;
        }
        inline void clear() {
            vertices.clear();
            normals.clear();
            uvs.clear();
            triangles.clear();
        }
    };


    struct Material { 
        Texture diffuse=Texture(0);
        Texture cubemap=Texture(0);
        Texture specular_map=Texture(0);
        Texture normal_map=Texture(0);
        Vec2 texture_scale=Vec2(1,1); 
        Vec2 texture_offset=Vec2(0,0);
        Color diffuse_color=Color(1,1,1,1);
        Color ambient_color=Color(0.9,0.9,0.9,1);
       // Color diffuse_color=Color(1,1,1,1); 
        Color specular_color=Color(1,1,1,1);

        float Ka=1.0f;   // Ambient reflection coefficient
        float Kd=1.0f;   // Diffuse reflection coefficient
        float Ks=1.0f;   // Specular reflection coefficient
        float shininess=8.0f;  
        float mirror=0.0f;
        bool blinn=true;
        Material() {   }
        inline void opaque() {Ks=0;shininess=1;}

    };
    enum CameraMode {
        CAMERA_HUD,
        CAMERA_2D,
        CAMERA_3D
    };
    
    class Camera {
        public:
        Vec3 position; // for cubemap calculations
        CameraMode mode;
        bool fix_aspect, is_perspective;
        double fov, near, far, aspect,
                ortho_left, ortho_right,
                ortho_bottom, ortho_top;
        Color clear_color;
        Rect viewport;
        Mat4 view_matrix;
        Material skybox;
        float skybox_yaw=0;
        float skybox_y=0;
        float fog_density=1;
        Color fog_color=Color(0.78,0.80,0.86,1); 


        Camera() {
            mode=CAMERA_2D;
            fix_aspect=false;
            is_perspective=false;
            clear_color=Color(0.6,0.75,1.0,1.0);
            fov=70; near=-0.1; far=600;
            aspect=1.0;
            ortho_left=-1; ortho_right=1;
            ortho_bottom=-1; ortho_top=1;
            viewport=Rect();
            view_matrix=Mat4::IDENTITY(); 
            skybox.opaque();
            skybox.diffuse_color=Color::WHITE();
            skybox.diffuse_color=Color::WHITE();
            skybox.ambient_color=Color::WHITE();
            skybox.Ka=1;
            skybox.Kd=0;
            skybox.Ks=0;  
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
            near=0.1;far=3000;
            fog_density=2;
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
                //  glEnable(GL_CULL_FACE);
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
        void draw_skybox();
    };

    bool draw(const GPUMesh vbo,Mat4 matrix,Camera camera,Material material);
    bool draw_sprite(Mat4 matrix,Vec3 camera_pos,Camera camera,Material material);
    void init();
};
#endif
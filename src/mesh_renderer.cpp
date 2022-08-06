#include "glhelpers.hpp"
#include "mesh_renderer.hpp"
 
namespace MeshRenderer { 
        Mesh hardcoded_skybox={
                {    /// VERTICES
                        { 1.0f, -1.0f, -1.0f},
                        {-1.0f, -1.0f, -1.0f},
                        {-1.0f, -1.0f,  1.0f},
                        { 1.0f, -1.0f,  1.0f},
                        { 1.0f,  1.0f, -1.0f},
                        { 1.0f,  1.0f,  1.0f},
                        {-1.0f,  1.0f,  1.0f},
                        {-1.0f,  1.0f, -1.0f} 
                }, { // NORMALS
                        { 0.5f,  0.5f,  0.5f},
                        {-0.5f,  0.5f, -0.5f},
                        {-0.5f,  0.5f,  0.5f},
                        {-0.5f, -0.5f, -0.5f},
                        { 0.5f, -0.5f,  0.5f},
                        {-0.5f, -0.5f,  0.5f},
                        { 0.5f,  0.5f, -0.5f},
                        { 0.5f, -0.5f, -0.5f}
                },{  // UVS
                        {0.250639, 0.334420},
                        {0.498940, 0.000571},
                        {0.250978, 0.001026},
                        {0.499363, 0.999334},
                        {0.250707, 0.666143},
                        {0.250392, 0.999655},
                        {0.743974, 0.335722},
                        {0.999141, 0.665375},
                        {0.998497, 0.335134},
                        {0.499303, 0.335277},
                        {0.744097, 0.665703},
                        {0.499138, 0.665539},
                        {0.000556, 0.334289},
                        {0.000491, 0.665816}
                },{ // TRIANGLES INDEXES
                        {{{ 2,1,1},{4,2,2}, {1,3,3}}},
                        {{{ 6,4,4},{8,5,5}, {5,6,6}}},
                        {{{ 4,7,2},{5,8,6}, {1,9,3}}},
                        {{{ 3,10,7},{6,11,4}, {4,7,2}}},
                        {{{ 2,1,1},{7,12,8}, {3,10,7}}},
                        {{{ 8,5,5},{1,13,3}, {5,14,6}}},
                        {{{ 2,1,1},{3,10,7}, {4,2,2}}},
                        {{{ 6,4,4},{7,12,8}, {8,5,5}}},
                        {{{ 4,7,2},{6,11,4}, {5,8,6}}},
                        {{{ 3,10,7},{7,12,8}, {6,11,4}}},
                        {{{ 2,1,1},{8,5,5}, {7,12,8}}},
                        {{{ 8,5,5},{2,1,1}, {1,13,3}}}
                }
        };
        Mesh hardcoded_quad={
                {    /// VERTICES
                        { -0.5f, -0.5f,   0.0f}, 
                        {  0.5f, -0.5f,   0.0f}, 
                        {  0.5f,  0.5f,   0.0f}, 
                        { -0.5f,  0.5f,   0.0f}
                }, { // NORMALS
                        { 0.0f,   0.0f,   1.0f}
                },{  // UVS 
                        {0.0f, 0.0f},
                        {1.0f, 0.0f},
                        {1.0f, 1.0f},
                        {0.0f, 1.0f}
                },{ // TRIANGLES INDEXES 
                        {{{4,4,1},{2,2,1},{3,3,1}}},
                        {{{4,4,1},{2,2,1},{3,3,1}}}, 
                }
        };
 
        Mesh hardcoded_cube= {
                {
                        {0.5,-0.5,-0.5},
                        {0.5,-0.5,0.5},
                        {-0.5,-0.5,0.5},
                        {-0.5,-0.5,-0.5},
                        {0.5,0.5,-0.5},
                        {0.5,0.5,0.5},
                        {-0.5,0.5,0.5},
                        {-0.5,0.5,-0.5}
                },
                {
                        {0.0,-1.0,0.0}, 
                        {0.0,1.0,0.0},
                        {1.0,0.0,0.0},
                        {0.0,0.0,1.0},
                        {-1.0,0.0,0.0},
                        {0.0,0.0,-1.0}
                },
                {
                         {1.0, 0.0},
                         {0.0, 1.0},
                         {0.0, 0.0},
                         {1.0, 0.0},
                         {0.0, 1.0},
                         {0.0, 0.0},
                         {1.0, 0.0},
                         {0.0, 1.0},
                         {1.0, 0.0},
                         {0.0, 1.0},
                         {0.0, 0.0},
                         {0.0, 0.0},
                         {1.0, 1.0},
                         {1.0, 0.0},
                         {0.0, 1.0},
                         {1.0, 1.0},
                         {1.0, 1.0},
                         {1.0, 1.0},
                         {1.0, 0.0},
                         {1.0, 1.0}
                },{                         
                        {{{2,1,1},{4,2,1},{1,3,1}}}, 
                        {{{8,4,2},{6,5,2},{5,6,2}}}, 
                        {{{5,7,3},{2,8,3},{1,3,3}}}, 
                        {{{6,9,4},{3,10,4},{2,11,4}}},
                        {{{3,12,5},{8,13,5},{4,2,5}}},
                        {{{1,14,6},{8,15,6},{5,6,6}}},
                        {{{2,1,1},{3,16,1},{4,2,1}}},
                        {{{8,4,2},{7,17,2},{6,5,2}}},
                        {{{5,7,3},{6,18,3},{2,8,3}}},
                        {{{6,9,4},{7,17,4},{3,10,4}}},
                        {{{3,12,5},{7,19,5},{8,13,5}}},
                        {{{1,14,6},{4,20,6},{8,15,6}}}
                }

        }; 



    /// SHADERSSSSSSS
    static const char vertex_shader[]= SHADER_INLINE( 
        precision highp float;
        precision highp int;
        uniform mat4 model_matrix;
        uniform mat4 view_matrix;
        uniform mat4 projection_matrix;
        uniform mat4 model_view_matrix;
        uniform mat4 model_view_projection_matrix; 
        uniform vec3 camera_pos;
        uniform vec3 light_pos;
        

        attribute vec3 a_vertex;
        attribute vec3 a_normal;
        attribute vec2 a_textcoord;
        attribute vec3 a_tangent;
        attribute vec3 a_bitangent;

        varying vec2 texture_coordinates;
        varying vec3 normal_iterpolated;
        varying vec3 vert_pos; // posicao do vertice no em relacao a camera
        varying vec3 world_pos; 
        varying float frag_distance;
        
        varying vec3 tangent_light_pos;
        varying vec3 tangent_camera_pos;
        varying vec3 tangent_world_pos;

       // varying vec3 tPosition;
        mat3 m_transpose(mat3 m) {
            return  mat3(
                vec3(m[0].x, m[1].x, m[2].x),
                vec3(m[0].y, m[1].y, m[2].y),
                vec3(m[0].z, m[1].z, m[2].z)
            );
        }
        float m_det(mat2 matrix) {
            return matrix[0].x * matrix[1].y - matrix[0].y * matrix[1].x;
        }

        mat3 m_inverse(mat3 matrix) {
            vec3 row0 = matrix[0];
            vec3 row1 = matrix[1];
            vec3 row2 = matrix[2];
            vec3 minors0 = vec3(
                m_det(mat2(row1.y, row1.z, row2.y, row2.z)),
                m_det(mat2(row1.z, row1.x, row2.z, row2.x)),
                m_det(mat2(row1.x, row1.y, row2.x, row2.y))
            );
            return mat3(1.0);
            vec3 minors1 = vec3(
                m_det(mat2(row2.y, row2.z, row0.y, row0.z)),
                m_det(mat2(row2.z, row2.x, row0.z, row0.x)),
                m_det(mat2(row2.x, row2.y, row0.x, row0.y))
            );
            vec3 minors2 = vec3(
                m_det(mat2(row0.y, row0.z, row1.y, row1.z)),
                m_det(mat2(row0.z, row0.x, row1.z, row1.x)),
                m_det(mat2(row0.x, row0.y, row1.x, row1.y))
            );

            mat3 adj = m_transpose(mat3(minors0, minors1, minors2));

            return (1.0 / dot(row0, minors0)) * adj;
        }  
        void main() { 
            world_pos = vec3(model_matrix * vec4(a_vertex, 1.0)); // posicao do vertice no mundo
            vec4 v = model_view_matrix * vec4(a_vertex, 1.0);
            vert_pos = vec3(v) / v.w; // posicao do vertice no em relacao a camera
            normal_iterpolated=a_normal;
            gl_Position = model_view_projection_matrix * vec4(a_vertex, 1.0);
            frag_distance=gl_Position.z;///gl_Position.w;
            texture_coordinates= a_textcoord; 
             
            mat3 normalMatrix = m_transpose(m_inverse(mat3(model_matrix)));
            vec3 T = normalize(normalMatrix * a_tangent);
            vec3 N = normalize(normalMatrix * a_normal);
            T = normalize(T - dot(T, N) * N);
            vec3 B = cross(N, T);
            
            mat3 TBN = m_transpose(mat3(T, B, N));    
            tangent_light_pos = TBN * light_pos;
            tangent_camera_pos  = TBN * camera_pos;
            tangent_world_pos  = TBN * world_pos;
            
        }
    );
    static const char fragment_shader[]= SHADER_INLINE(
        precision highp float;
        precision highp int;
        uniform sampler2D diffuse;
        uniform samplerCube cubemap;
        uniform bool has_cubemap;
        uniform sampler2D specular_map;
        uniform bool has_specular_map;
        uniform sampler2D normal_map;
        uniform bool has_normal_map;
        uniform vec2 texture_scale;
        uniform vec2 texture_offset;
        uniform vec4 diffuse_color;
        uniform vec4 ambient_color;
       // uniform vec4 diffuse_color;  
        uniform vec4 specular_color; 
        uniform vec3 light_pos;
        uniform float Ka;   // Ambient reflection coefficient
        uniform float Kd;   // Diffuse reflection coefficient
        uniform float Ks;   // Specular reflection coefficient
        uniform float shininess; 
        uniform float fog_distance; 
        uniform float fog_density;
        uniform float mirror;
        uniform vec4 fog_color; 
        uniform bool blinn; // Use blinn-phong shading or not
        uniform vec3 camera_pos;
        varying vec2 texture_coordinates;
        varying vec3 normal_iterpolated;
        varying vec3 world_pos;
        varying vec3 vert_pos;
        varying float frag_distance;
        
        varying vec3 tangent_light_pos;
        varying vec3 tangent_camera_pos;
        varying vec3 tangent_world_pos;
        /*
        vec3 vert(float x,float y) {
            vec2 tv=texture_coordinates+vec2(x,y);
            float r=texture2D(diffuse,(texture_offset+tv)*texture_scale).z;
            return vec3(tv.x,r,tv.z);
        }
        vec3 norm() {
            float ff=0.1;   
            return normalize(cross(
                    vert(-ff,0.0)-vert(ff,0.0), 
                    vert(0.0,ff)-vert(0.0,-ff)
                ));
        }*/
        float gray(vec4 c) {
            return (c.x+c.y+c.z)/3.0;
        }
        /*
        i dont know if is light direction or light position
        float ggx (vec3 N, vec3 V, vec3 L, float roughness, float F0) {
            float alpha = roughness*roughness;
            vec3 H = normalize(L - V);
            float dotLH = max(0.0, dot(L,H));
            float dotNH = max(0.0, dot(N,H));
            float dotNL = max(0.0, dot(N,L));
            float alphaSqr = alpha * alpha;
            float denom = dotNH * dotNH * (alphaSqr - 1.0) + 1.0;
            float D = alphaSqr / (3.141592653589793 * denom * denom);
            float F = F0 + (1.0 - F0) * pow(1.0 - dotLH, 5.0);
            float k = 0.5 * alpha;
            float k2 = k * k;
            return dotNL * D * F / (dotLH*dotLH*(1.0-k2)+k2);
        }*/
        void main() {            
            bool fog_exponential=false;
          //  vec3 lightDir=vec3(0.2,1,0); 
            vec2 uvc=(texture_offset+texture_coordinates)*texture_scale;


            vec3 N = normalize(normal_iterpolated);
            vec3 L = normalize(light_pos-world_pos); //lightPos - vert_pos; 
            vec3 V = normalize(-vert_pos); // Vector to viewer

            
             // transform normal vector to range [-1,1]
            if(has_normal_map) {
                N=normalize(vec3(texture2D(normal_map,uvc)) * 2.0 - 1.0); // this normal is in tangent space
                L=normalize(tangent_light_pos-tangent_world_pos); //lightPos - vert_pos;
                V=normalize(tangent_camera_pos-tangent_world_pos); // Vector to viewer
            } 
           

            //vec3 L = vec3(0.2,1,0);
            // Lambert's cosine law
            float lambertian = max(dot(N, L), 0.0);
            float specular = 0.0;
            if(lambertian > 0.0) {
                vec3 R = reflect(-L, N);      // Reflected light vector
                // Compute the specular term
                if(blinn) {
                    vec3 halfwayDir = normalize(L + V);  
                    specular = pow(max(dot(N, halfwayDir), 0.0), shininess);
                } else  { 
                    //specular = ggx(N,V,L,1.0,shininess); 
                    specular=pow(max(dot(R, V), 0.0), shininess); 
                }
            } 
            // vec4 tex_color=vec4(N,1.0); // debug normals
            vec4 tex_color=texture2D(diffuse,uvc)*diffuse_color;//vec4(1.0)*gray(texture2D(diffuse,uvc));
            vec4 spc_serasa=(Ks * specular * specular_color);
            
            float m=mirror; 
            if(has_specular_map) {
                float spm=gray(texture2D(specular_map,uvc));
                spc_serasa=spc_serasa*spm;
                m*=spm;
            }

            gl_FragColor = Ka * ambient_color * tex_color +
                                Kd * lambertian * tex_color +
                                spc_serasa;

            // cubemap reflection
            if(m>0.05) { 
                vec3 VI = normalize(world_pos - camera_pos);
                vec3 VR = reflect(VI, N);
                vec4 ccolor=textureCube(cubemap,normalize(-VR));
                gl_FragColor=mix(gl_FragColor,ccolor,m);
            }
            float d_factor=(frag_distance/fog_distance)*fog_density;

            d_factor= clamp(d_factor,0.0,1.0);
            if(fog_exponential) d_factor*=d_factor;

            gl_FragColor = mix(gl_FragColor,fog_color,d_factor);

            //if(gl_FragColor.a<0.6) discard;
        }
    );
    
    static ShaderProgram shader_program(0);// must be zero uninitialized

    static GPUMesh debug_box;
    static GPUMesh debug_quad;
    static GPUMesh skybox;
    
    static GLuint blank_texture;
    static GLuint font_texture;
    
    GPUMesh mesh_quad()  { return debug_quad; }
    GPUMesh mesh_box()   { return debug_box;  }
    GPUMesh mesh_skybox()   { return skybox;  }
    inline bool draw_call(GPUMesh mesh,Mat4 model_matrix,Mat4 view_matrix,Mat4 projection_matrix,Material material,Camera camera) {
       
        Mat4 model_view_matrix=model_matrix*view_matrix; 
        Mat4 model_view_projection_matrix=(projection_matrix*view_matrix)*model_matrix;
 

       shader_program.use(); 
       
        shader_program.uniform("diffuse",0); 
        if(material.diffuse.id) material.diffuse.bind(0);
        else glBindTexture(GL_TEXTURE_2D, blank_texture);

        bool has_normal_map=material.normal_map.is_texture(); 
        shader_program.uniform("has_normal_map",has_normal_map);
        if(has_normal_map)  material.normal_map.bind(1);
        shader_program.uniform("normal_map",1);  
        
        bool has_specular_map=material.specular_map.is_texture(); 
        shader_program.uniform("has_specular_map", has_specular_map);
        if(has_specular_map)  material.specular_map.bind(2);
        shader_program.uniform("specular_map",2);

        bool has_cubemap=material.cubemap.is_texture(); 
        shader_program.uniform("has_cubemap",has_cubemap);
        if(has_cubemap)  material.cubemap.bind(3); 
        shader_program.uniform("cubemap",3);

        shader_program.uniform_mat4("model_matrix",model_matrix);
        shader_program.uniform_mat4("view_matrix",view_matrix); 
        shader_program.uniform_mat4("projection_matrix",projection_matrix);
        shader_program.uniform_mat4("model_view_matrix",model_view_matrix);

        shader_program.uniform_mat4("model_view_projection_matrix",model_view_projection_matrix);

        shader_program.uniform_vec2("texture_offset",material.texture_offset);
        shader_program.uniform_vec3("camera_pos",camera.position);
        shader_program.uniform_vec2("texture_scale",material.texture_scale);
        shader_program.uniform_color("ambient_color",material.ambient_color);
        shader_program.uniform_color("diffuse_color",material.diffuse_color);
        shader_program.uniform_color("specular_color",material.specular_color);
        shader_program.uniform("Ka",material.Ka);
        shader_program.uniform("Kd",material.Kd);
        shader_program.uniform("Ks",material.Ks);
        shader_program.uniform("shininess",material.shininess);
        shader_program.uniform("blinn",material.blinn);
        shader_program.uniform_color("fog_color",camera.fog_color);
        shader_program.uniform("fog_density",camera.fog_density);
        shader_program.uniform("fog_distance",(float)camera.far);
        shader_program.uniform("mirror",(float)material.mirror);
        shader_program.uniform_vec3("light_pos",Vec3(0,4000,4000));

        
        
        //vbo.bind();
        GLint vertex_attr=shader_program.attribute_location("a_vertex");
        GLint normal_attr=shader_program.attribute_location("a_normal");
        GLint uv_attr=shader_program.attribute_location("a_textcoord");
        GLint tangent_attr=shader_program.attribute_location("a_tangent");
        GLint bitangent_attr=shader_program.attribute_location("a_bitangent");

        mesh.vbo.bind();

        glEnableVertexAttribArray(vertex_attr);
        glEnableVertexAttribArray(normal_attr);
        glEnableVertexAttribArray(uv_attr);
        glEnableVertexAttribArray(tangent_attr);
        glEnableVertexAttribArray(bitangent_attr);

        glVertexAttribPointer(vertex_attr, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData,vertex));
        glVertexAttribPointer(normal_attr, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData,normal));
        glVertexAttribPointer(uv_attr, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData,uv));
        glVertexAttribPointer(tangent_attr, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData,tangent));
        glVertexAttribPointer(bitangent_attr, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData,bitangent));
        
        mesh.draw();

        glDisableVertexAttribArray(vertex_attr);
        glDisableVertexAttribArray(normal_attr);
        glDisableVertexAttribArray(uv_attr);
        glDisableVertexAttribArray(tangent_attr);
        glDisableVertexAttribArray(bitangent_attr);
        mesh.vbo.unbind();
        shader_program.unbind();
        return true;
    } 
    bool draw(GPUMesh mesh, Mat4 model_matrix,Camera camera,Material material) {
        
        if(!mesh.is_valid()) {
            printf("tryng to draw a null gpumesh\n");
            return false;
        }
        
        Mat4 view_matrix=camera.view_matrix;
        Mat4 projection_matrix=camera.projection_matrix();
        return draw_call(mesh,model_matrix,view_matrix,projection_matrix,material,camera);
        //if(!bbox_verts.to_screen_space(model_view_projection_matrix).inside_screen()) return ;
        
        /*auto t_draw=[&]() {*/ 
        // printf("%d\n",vbo.vertices_count);
        /*};
        t_draw();*/ 
        /***/
    }  
    bool draw_sprite(Mat4 model,Vec3 camera_pos,Camera camera,Material material) { 
        Mat4 view_matrix=camera.view_matrix;
        Mat4 projection_matrix=camera.projection_matrix();
        Mat4 rot=Mat4::from_dir(-camera_pos.normalized());
        //rot=rot.translated(-rot.translation());
        //Mat4 rot=Mat4::rotation_old((model.translation()).normalized());
        
        return draw_call(mesh_quad(),rot*model,view_matrix,projection_matrix,material,camera);

    }  
    void init() {
        printf("initializing renderer shaders\n");
        shader_program=DGL::ShaderProgram::compile_shaders_and_link_program(vertex_shader,fragment_shader);
        shader_program.use(); 
        blank_texture=DGL::Texture::create_blank_texture().id;
        //debug_quad= LOAD_MESH((VertexData*) quad_vertices,sizeof(quad_vertices)/sizeof(VertexData));
        debug_quad=hardcoded_quad.send_to_gpu();  
        hardcoded_quad.clear();

        //debug_box=  LOAD_MESH((VertexData*) box_vertices,sizeof(box_vertices)/sizeof(VertexData));
        
        debug_box=hardcoded_cube.send_to_gpu();  
        hardcoded_cube.clear();

        skybox=hardcoded_skybox.send_to_gpu();  
        hardcoded_skybox.clear();
        printf("initializing renderer shaders done\n");
    }
     void Camera::draw_skybox() { 
        glDisable(GL_DEPTH_TEST); 
        Mat4 v=view_matrix;
        v.m[3][0]=v.m[3][1]=v.m[3][2]=0; 
        draw_call(mesh_skybox(),Mat4().rotated(0,skybox_yaw,0).translated(0,skybox_y,0),v,projection_matrix(),skybox,*this);

        if(mode==CameraMode::CAMERA_3D) glEnable(GL_DEPTH_TEST);
    }
}
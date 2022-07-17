#include "mesh_renderer.hpp"
#include "glhelpers.hpp"

#include "basic_meshes.cpp"


namespace MeshRenderer {
    /// SHADERSSSSSSS
    static const char vertex_shader[]= SHADER_INLINE( 
        precision highp float;
        precision highp int;
        uniform mat4 model_matrix;
        uniform mat4 view_matrix;
        uniform mat4 projection_matrix;
        uniform mat4 model_view_matrix;
        uniform mat4 model_view_projection_matrix; 
        attribute vec3 a_vertex;
        attribute vec3 a_normal;
        attribute vec2 a_textcoord;
        varying vec2 texture_coordinates;
        varying vec3 normal_iterpolated;
        varying vec3 vert_pos;
        varying vec3 glpos;
        void main() {
            vec4 v = model_view_matrix * vec4(a_vertex, 1.0);
            vert_pos = vec3(v) / v.w;

            gl_Position = model_view_projection_matrix * vec4(a_vertex, 1.0);
            glpos=vec3(gl_Position);///gl_Position.w;
            texture_coordinates= a_textcoord;
            normal_iterpolated=a_normal;
        }
    );
    static const char fragment_shader[]= SHADER_INLINE(
        precision highp float;
        precision highp int;
        uniform sampler2D albedo;
        uniform vec2 texture_scale;
        uniform vec2 texture_offset;
        uniform vec4 albedo_color;
        uniform vec4 ambient_color;
        uniform vec4 diffuse_color;  
        uniform vec4 specular_color; 
        uniform float Ka;   // Ambient reflection coefficient
        uniform float Kd;   // Diffuse reflection coefficient
        uniform float Ks;   // Specular reflection coefficient
        uniform float shininess; 
        uniform float fog_distance; 
        uniform float fog_density;
        uniform vec4 fog_color; 
        uniform bool blinn; // Use blinn-phong shading or not
        varying vec2 texture_coordinates;
        varying vec3 normal_iterpolated;
        varying vec3 vert_pos;
        varying vec3 glpos;
        
        void main() {            
            bool fog_exponential=false;
            //vec3 lightPos=vec3(0,100,0);
            vec3 lightDir=vec3(0.2,1,0); 

            vec3 N = normalize(normal_iterpolated);
            vec3 L = normalize(lightDir); //lightPos - vert_pos;

            // Lambert's cosine law
            float lambertian = max(dot(N, L), 0.0);
            float specular = 0.0;
            if(lambertian > 0.0) {
                vec3 R = reflect(-L, N);      // Reflected light vector
                vec3 V = normalize(-vert_pos); // Vector to viewer
                // Compute the specular term
                if(blinn) {
                    vec3 halfwayDir = normalize(L + V);  
                    specular = pow(max(dot(N, halfwayDir), 0.0), shininess);
                } else  { 
                    specular = pow(max(dot(R, V), 0.0), shininess); 
                }
            } 
            vec4 tex_color=texture2D(albedo,(texture_offset+texture_coordinates)*texture_scale)*albedo_color;

            gl_FragColor = Ka * ambient_color*tex_color +
                                Kd * lambertian * diffuse_color*tex_color +
                                Ks * specular * specular_color;

            float d_factor=(glpos.z/fog_distance)*fog_density;
            if(d_factor<0.0) d_factor=0.0;
            else if(d_factor>1.0) d_factor=1.0;
            if(fog_exponential) d_factor*=d_factor;

            gl_FragColor = mix(gl_FragColor,fog_color,d_factor);

            if(gl_FragColor.a<0.6) discard;
        }
    );
    
    static ShaderProgram shader_program(0);// must be zero uninitialized

    static VBO debug_box(0);
    static VBO debug_quad(0);
    static VBO skybox(0);
    
    static GLuint blank_texture;
    static GLuint font_texture;
    VBO vbo_quad()  { return debug_quad; }
    VBO vbo_box()   { return debug_box;  }
    VBO vbo_skybox()   { return skybox;  }
    inline bool draw_call(VBO vbo,Mat4 model_matrix,Mat4 view_matrix,Mat4 projection_matrix,Material material,Camera camera) {
       
        Mat4 model_view_matrix=model_matrix*view_matrix; 
        Mat4 model_view_projection_matrix=(projection_matrix*view_matrix)*model_matrix;
 

       shader_program.use(); 
        if(material.albedo.id) material.albedo.bind();
        else glBindTexture(GL_TEXTURE_2D, blank_texture);
        
        shader_program.uniform_mat4("model_matrix",model_matrix);
        shader_program.uniform_mat4("view_matrix",view_matrix); 
        shader_program.uniform_mat4("projection_matrix",projection_matrix);
        shader_program.uniform_mat4("model_view_matrix",model_view_matrix);

        shader_program.uniform_mat4("model_view_projection_matrix",model_view_projection_matrix);

        shader_program.uniform_vec2("texture_offset",material.texture_offset);
        shader_program.uniform_vec2("texture_scale",material.texture_scale);
        shader_program.uniform_color("ambient_color",material.ambient_color);
        shader_program.uniform_color("diffuse_color",material.diffuse_color);
        shader_program.uniform_color("specular_color",material.specular_color);
        shader_program.uniform_color("albedo_color",material.albedo_color);
        shader_program.uniform("Ka",material.Ka);
        shader_program.uniform("Kd",material.Kd);
        shader_program.uniform("Ks",material.Ks);
        shader_program.uniform("shininess",material.shininess);
        shader_program.uniform("blinn",material.blinn);
        shader_program.uniform_color("fog_color",camera.fog_color);
        shader_program.uniform("fog_density",camera.fog_density);
        shader_program.uniform("fog_distance",(float)camera.far);

        
        
        vbo.bind();

        GLint vertex_attr=shader_program.attribute_location("a_vertex");
        GLint normal_attr=shader_program.attribute_location("a_normal");
        GLint uv_attr=shader_program.attribute_location("a_textcoord");

        glEnableVertexAttribArray(vertex_attr);
        glEnableVertexAttribArray(normal_attr);
        glEnableVertexAttribArray(uv_attr);

        glVertexAttribPointer(vertex_attr, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData,vertex));
        glVertexAttribPointer(normal_attr, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData,normal));
        glVertexAttribPointer(uv_attr, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData,uv));
        
        vbo.draw(); 
        glDisableVertexAttribArray(vertex_attr);
        glDisableVertexAttribArray(normal_attr);
        glDisableVertexAttribArray(uv_attr);
        vbo.unbind();
        shader_program.unbind();
        return true;
    }
    bool draw(VBO vbo, Mat4 model_matrix,Camera camera,Material material) {
        
        if(!vbo.id) {
            printf("tryng to draw a null buffer\n");
            return false;
        }
        
        Mat4 view_matrix=camera.view_matrix;
        Mat4 projection_matrix=camera.projection_matrix();
        return draw_call(vbo,model_matrix,view_matrix,projection_matrix,material,camera);
        //if(!bbox_verts.to_screen_space(model_view_projection_matrix).inside_screen()) return ;
        
        /*auto t_draw=[&]() {*/
      
        // printf("%d\n",vbo.vertices_count);
        /*};
        t_draw();*/
       
        /***/
    }  
    
    void init() {
        printf("initializing renderer shaders\n");
        shader_program=DGL::ShaderProgram::compile_shaders_and_link_program(vertex_shader,fragment_shader);
        shader_program.use(); 
        blank_texture=DGL::Texture::create_blank_texture().id;
        debug_quad= LOAD_MESH((VertexData*) quad_vertices,sizeof(quad_vertices)/sizeof(VertexData));
        debug_box=  LOAD_MESH((VertexData*) box_vertices,sizeof(box_vertices)/sizeof(VertexData));
        
        skybox=hardcoded_skybox.send_to_gpu();  
        hardcoded_skybox.clear();
        printf("initializing renderer shaders done\n");
    }
     void Camera::draw_skybox() { 
        glDisable(GL_DEPTH_TEST); 
        Mat4 v=view_matrix;
        v.m[3][0]=v.m[3][1]=v.m[3][2]=0; 
        draw_call(vbo_skybox(),Mat4().rotated(0,skybox_yaw,0).translated(0,skybox_y,0),v,projection_matrix(),skybox,*this);

        if(mode==CameraMode::CAMERA_3D) glEnable(GL_DEPTH_TEST);
    }

}
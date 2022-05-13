#include "denise.hpp"
#include "glhelpers.hpp"


#include "basic_meshes.h"
namespace Denise {
    /// SHADERSSSSSSS
    static const char vertex_shader[]= SHADER_INLINE(
        precision lowp float;
        precision lowp int;
        uniform mat4 model_matrix;
        uniform mat4 view_matrix;
        uniform mat4 projection_matrix;
        attribute vec3 a_vertex;
        attribute vec3 a_normal;
        attribute vec2 a_textcoord;
        varying vec2 texture_coordinates;
        void main() {
            gl_Position = (projection_matrix*view_matrix*model_matrix) * vec4(a_vertex, 1.0);
            texture_coordinates= vec2(a_textcoord.x, a_textcoord.y);
        }
    );
    static const char fragment_shader[]= SHADER_INLINE(
        precision lowp float;
        precision lowp int;
        uniform vec4 color;
        uniform vec2 texture_scale;
        uniform sampler2D texture;
        varying vec2 texture_coordinates;
        void main() {
            vec2 txc=texture_coordinates;
        /* if(texture_scale.x>0) {
                txc.x*=texture_scale.x;
                txc.y*=texture_scale.y;
            }*/
            gl_FragColor=color*texture2D(texture,txc);
            //if(gl_FragColor.a<0.6) discard;
        }
    );
    static GLuint attribute_vertex;
    static GLuint attribute_normal;
    static GLuint attribute_textcoord;
    static GLuint uniform_color;
    static GLuint uniform_texture;
    static GLuint uniform_model_matrix;
    static GLuint uniform_view_matrix;
    static GLuint uniform_projection_matrix;
    static GLuint uniform_texture_scale;
    
    static GLuint shader_program;

    static VBO debug_box;
    static VBO debug_quad;
    
    static GLuint blank_texture;

    VBO vbo_quad()  { return debug_quad; }
    VBO vbo_box()   { return debug_box;  }

    void draw(VBO vbo, Mat4 matrix,Camera camera,Material material) {
        glUseProgram(shader_program);
        glActiveTexture(GL_TEXTURE0);
        if(material.albedo) glBindTexture(GL_TEXTURE_2D, material.albedo);
        else glBindTexture(GL_TEXTURE_2D, blank_texture);
        glUniformMatrix4fv(uniform_model_matrix, 1, GL_FALSE, (float*) matrix.m);
        glUniformMatrix4fv(uniform_view_matrix, 1, GL_FALSE, (float*) camera.view_matrix.m);
        glUniformMatrix4fv(uniform_projection_matrix, 1, GL_FALSE, (float*) camera.projection_matrix().m);

        glUniform2fv(uniform_texture_scale, 1,(float*) &material.texture_scale);
        // print diffuse color
        glUniform4fv(uniform_color, 1,(float*) &(material.diffuse));
    
        glBindBuffer(GL_ARRAY_BUFFER, vbo.buffer_id);
        glEnableVertexAttribArray(attribute_vertex);
        glVertexAttribPointer(attribute_vertex, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData,vertex));
        glEnableVertexAttribArray(attribute_normal);
        glVertexAttribPointer(attribute_normal, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData,normal));
        glEnableVertexAttribArray(attribute_textcoord);
        glVertexAttribPointer(attribute_textcoord, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData,uv));
        glDrawArrays(vbo.draw_mode, 0, vbo.vertices_count);
       // printf("%d\n",vbo.vertices_count);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glUseProgram(0);
        /***/
    }  
    
    void init() {
        printf("initializing renderer shaders\n");
        shader_program=Shaders::compile_program(vertex_shader,fragment_shader);
        uniform_color=glGetUniformLocation(shader_program,"color");
        uniform_model_matrix=glGetUniformLocation(shader_program,"model_matrix");
        uniform_view_matrix=glGetUniformLocation(shader_program,"view_matrix");
        uniform_projection_matrix=glGetUniformLocation(shader_program,"projection_matrix");
        uniform_texture=glGetUniformLocation(shader_program,"texture");
        uniform_texture_scale=glGetUniformLocation(shader_program,"texture_scale");
        attribute_vertex=glGetAttribLocation(shader_program,"a_vertex");
        attribute_normal=glGetAttribLocation(shader_program,"a_normal");
        attribute_textcoord=glGetAttribLocation(shader_program,"a_textcoord");
        blank_texture=Textures::load_blank_texture();
        debug_quad=VBO::LOAD_MESH((VertexData*) quad_vertices,sizeof(quad_vertices)/sizeof(VertexData));
        debug_box=VBO::LOAD_MESH((VertexData*) box_vertices,sizeof(box_vertices)/sizeof(VertexData));
        printf("initializing renderer shaders done\n");
    }


}
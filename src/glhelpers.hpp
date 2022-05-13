#ifndef GLHELPERS_HPP
#define GLHELPERS_HPP
#include <glad/glad.h>

#define SHADER_INLINE(shader)  "" #shader

#include <cstdio>

namespace Shaders {
    
    inline int compile(const char* source_code, int shader_type) {
        int shader_id=glCreateShader(shader_type);
        glShaderSource(shader_id, 1, &source_code, NULL);
        glCompileShader(shader_id);
        int success=0;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS,&success);
        if(success==GL_FALSE) {
            int length;
            glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
            char* log=new char[length];
            glGetShaderInfoLog(shader_id, length, &length, log);
            printf("%s\n", log);
            delete[] log;
            glDeleteShader(shader_id);
            return -1;
        }
        return shader_id;
    }
    inline int link_program(int vertex_shader_id, int fragment_shader_id) {
        printf("linking shaders %d %d \n", vertex_shader_id, fragment_shader_id);
        int program_id=glCreateProgram();
        glAttachShader(program_id, vertex_shader_id);
        glAttachShader(program_id, fragment_shader_id);
        glLinkProgram(program_id);
        int success=0;
        glGetProgramiv(program_id, GL_LINK_STATUS, &success);
        if(success==GL_FALSE) {
            int length;
            glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &length);
            char* log=new char[length];
            glGetProgramInfoLog(program_id, length, &length, log);
            printf("%s\n", log);
            delete[] log;
            glDeleteProgram(program_id);
            return -1;
        }
        glDeleteShader(vertex_shader_id);
        glDeleteShader(fragment_shader_id);
        printf("program %d linked\n", program_id);
        return program_id;
    }
    inline int compile_program(const char* vertex_shader, const char* fragment_shader) {
        return link_program(
            compile(vertex_shader, GL_VERTEX_SHADER), 
            compile(fragment_shader, GL_FRAGMENT_SHADER)
        );
    }
}
namespace Textures {
    inline int load_RGBAIntArray(void *data, int width, int height) {
        unsigned int texture_id=0;
        glGenTextures(1, &texture_id);
        glBindTexture(GL_TEXTURE_2D, texture_id);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glBindTexture(  GL_TEXTURE_2D, 0);
        return texture_id;
    }
    inline int load_blank_texture() {
        unsigned char data[4]={255,255,255,255};
        int texture_id=load_RGBAIntArray(data, 1, 1);
        return texture_id;
    }

}


#endif
#ifndef GLHELPERS_HPP
#define GLHELPERS_HPP
#include <glad/glad.h>
#include "dmath.hpp"

using DMath::Color;
using DMath::ByteColor;
using DMath::Vec3;
using DMath::Vec2;
using DMath::Mat4;
using DMath::BoundBox;

#define SHADER_INLINE(shader)  #shader

//#define DEBUG
#ifdef DEBUG
    #define log_printf printf
#else
    #define log_printf ;//
#endif

//#define SHOW_ERRORS
#ifdef SHOW_ERRORS
    #define err_printf printf
#else 
    #define err_printf ;//
#endif

#include <cstdio> 
#include <vector>
#include <map>
#include <string> 
#include <cstring>
#include <ostream>
#include <iostream>

namespace DGL {
    inline void flush() {glFlush();}
    inline void finish() {glFinish();}
    
    inline void clear_depth_buffer() {
        glClear(GL_DEPTH_BUFFER_BIT);
    }
    inline void clear_color_buffer(float r=0, float g=0, float b=0, float a=0) {
        glClearColor(r,g,b,a);
        glClear(GL_COLOR_BUFFER_BIT);
    } 
    inline void clear_buffers(float r=0, float g=0, float b=0, float a=0) {
        clear_color_buffer(r,g,b,a);
        clear_depth_buffer();
    }
    inline void cull_face(bool enable=true, GLuint face=GL_BACK) {
        if(enable) {
            glEnable(GL_CULL_FACE);
            glCullFace(face);
        } else glDisable(GL_CULL_FACE);
    }
    inline void depth_test(bool enable=true) {
        if(enable) glEnable(GL_DEPTH_TEST);
        else glDisable(GL_DEPTH_TEST);
    }
    inline void depth_func(GLuint func=GL_LESS) { glDepthFunc(func); }
  

    inline void viewport(GLint x, GLint y, GLsizei width, GLsizei height) { glViewport(x, y, width, height); }
    

    
    class CPUTextureBuffer {
        public:
            uint8_t *buffer=NULL;
            size_t buffer_size;
            uint32_t width=0;
            uint32_t height=0;
            uint32_t channels=1;
            
        static inline CPUTextureBuffer FROM_POINTER(uint32_t width, uint32_t height, uint32_t channels,void *pointer) {
          CPUTextureBuffer t(width,height,channels);
          t.buffer=(uint8_t*)pointer;
          return t;
        }

        inline size_t get_pixel_index(uint32_t x,uint32_t y,uint32_t channel=0) {
            if(x>width) { err_printf("ERRO, acessando pixel além da largura \n");  return 0; }
            if(y>height) { err_printf("ERRO, acessando pixel além da altura \n");  return 0;  }
            auto i=((y * width + x)*channels)+channel;
            if(i>buffer_size) {
                err_printf("ERRO, pesquisando indice de pixel além do limite do array \n");  return 0; 
            }
            return i;

        }
        inline Color get_pixel_color(uint32_t x,uint32_t y) { 
            size_t i=get_pixel_index(x,y);
            uint8_t alpha=255;
            if(channels==4) alpha=buffer[i+3]; 
            return Color::FROM_BYTE_COMPONENTS(buffer[i+0],buffer[i+1],buffer[i+2],alpha);
        }
        inline void put_pixel_color(uint32_t x,uint32_t y,Color color) {
            size_t i=get_pixel_index(x,y);
            auto c=color.to_bytes();
            buffer[i+0]=c.r; buffer[i+1]=c.g; buffer[i+2]=c.b;
            if(channels==4) buffer[i+3]=c.a;
        }
        inline ByteColor get_pixel(uint32_t x,uint32_t y) { 
            size_t i=get_pixel_index(x,y);
            return ByteColor(buffer[i+0],buffer[i+1],buffer[i+2],(channels==4 ? buffer[i+3] : 255));
        }
        inline void put_pixel(uint32_t x,uint32_t y,ByteColor c) {
            size_t i=get_pixel_index(x,y);
            buffer[i+0]=c.r;
            buffer[i+1]=c.g;
            buffer[i+2]=c.b;
            if(channels==4) buffer[i+3]=c.a;
        }
        inline void put_pixel_color(uint32_t x,uint32_t y,uint8_t v) { 
            buffer[get_pixel_index(x,y)]=v;
        }
        inline void free() {
            if(buffer) delete [] buffer;
            buffer=NULL;
        }
        CPUTextureBuffer() { }
        CPUTextureBuffer(uint32_t width,uint32_t height,uint32_t channels=4) {
            this->width=width;
            this->height=height;
            this->channels=channels;
            this->buffer_size=width*height*channels;
        }
        inline void alloc() { 
            buffer_size=width*height*channels;
            buffer=new uint8_t[buffer_size];
            memset(buffer,255,buffer_size);
        }
        inline CPUTextureBuffer extract_quad(uint32_t x,uint32_t y,uint32_t w,uint32_t h) {
            CPUTextureBuffer quad(w,h,channels);
            quad.alloc();
            for(uint32_t i=0;i<w;i++) {
                for(uint32_t j=0;j<h;j++) { 
                    quad.put_pixel(i,j,get_pixel(x+(i%width),y+(j%height)));
                }
            }
            return quad;
        }
        inline CPUTextureBuffer resized(uint32_t w,uint32_t h,uint32_t channels=4) {
            auto img=CPUTextureBuffer(w,h,channels);
            img.alloc();
            auto img_factor=Vec2(1.0,1.0)/Vec2(w,h); 
            for(uint32_t y=0;y<h;y++) { 
                for(uint32_t x=0;x<w;x++) {
                    auto pos=Vec2(x,y)*img_factor*Vec2(width,height);
                    img.put_pixel(x,y,// da pra colocar uma interpolacao aqui mas nao to afim87
                        get_pixel(pos.x,pos.y)
                    );
                }
            }
            return img;
        }
       

   };


    class Texture {
        public:
        unsigned int id=0;
        bool is_cubemap=false;
        Texture(unsigned int id) {this->id=id;}
        Texture() { id=0; }

        inline void bind(GLuint texture_unit=0) {
            if(!id) {  err_printf("trying to bind a null texture\n");   }
            glActiveTexture(GL_TEXTURE0+texture_unit);
            if(is_cubemap) glBindTexture(GL_TEXTURE_CUBE_MAP, id);
            else glBindTexture(GL_TEXTURE_2D, id);
        }
        inline void unbind() { 
            if(is_cubemap) glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
            else glBindTexture(GL_TEXTURE_2D, 0);
        }
        inline void configure(bool smoth=false,bool mipmap=false, bool clamp=false) {
            bind();
            auto target= is_cubemap ? GL_TEXTURE_CUBE_MAP : GL_TEXTURE_2D;
         
            glTexParameteri(target, GL_TEXTURE_WRAP_S, clamp ? GL_CLAMP_TO_EDGE : GL_REPEAT);
            glTexParameteri(target, GL_TEXTURE_WRAP_T, clamp ? GL_CLAMP_TO_EDGE : GL_REPEAT);
            //if(is_cubemap) glTexParameteri(target, GL_TEXTURE_WRAP_R, clamp ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        
            glTexParameteri(target, GL_TEXTURE_MIN_FILTER, smoth ? GL_LINEAR  : GL_NEAREST);
            glTexParameteri(target, GL_TEXTURE_MAG_FILTER, smoth ? GL_LINEAR : GL_NEAREST); 
            if(mipmap) glGenerateMipmap(target);
        
        } 
        inline bool is_texture() { return id!=0 || glIsTexture( id); }
        inline void set_image(const GLvoid *data,GLsizei width,GLsizei height,GLuint channels_format=GL_RGB,GLuint byte_format=GL_UNSIGNED_BYTE)  {
            log_printf("Loading texture id %d with %d pixels\n",id,width*height);
            glTexImage2D(GL_TEXTURE_2D, 0, channels_format, width, height, 0, channels_format, byte_format, data);
        }
        inline void set_cubemap_image(GLuint face,const GLvoid *data,GLsizei width,GLsizei height,GLuint channels_format=GL_RGB,GLuint byte_format=GL_UNSIGNED_BYTE) {
            
             glTexImage2D(face, 0, channels_format, width, height, 0, channels_format, byte_format, data);

        }
        inline void create() {
            glGenTextures(1, &id);
            log_printf("Texture id: %d created\n",id);
        }
        inline void create_cubemap() {
            glGenTextures(1, &id);
            log_printf("Cubemap texture id: %d created\n",id);
            is_cubemap=true;
        }
        inline void delete_texture() {
            if(!is_texture()) {
                err_printf("trying to delete a null texture\n");
                return;
            }
            log_printf("Texture id: %d deleted\n",id);
            glDeleteTextures(1, &id);
            id=0;
        }

        static inline Texture create_texture_from_array(void * data, GLsizei width, GLsizei height,GLuint channels_format=GL_RGB,GLuint byte_format=GL_UNSIGNED_BYTE) {
            log_printf("Creating texture from array\n");
            Texture texture;
            texture.create();
            texture.bind();
            texture.set_image(data,width,height,channels_format,byte_format);
            texture.configure();
            texture.unbind();
            return texture;
        }
        static inline Texture create_blank_texture() { 
            uint8_t data[4]={255,255,255};
            return create_texture_from_array(data, 1, 1);
        }
        static inline Texture LOAD_FROM_BUFFER(CPUTextureBuffer buffer,bool smoth=false,bool mipmap=false, bool clamp=false) { 
            log_printf("Sending CPUTextureBuffer to gpu...\n");
            GLuint channels_format=GL_LUMINANCE;
            if(buffer.channels==3) channels_format=GL_RGB;
            if(buffer.channels==4) channels_format=GL_RGBA;

            Texture texture;
            texture.create();
            texture.bind();
            texture.set_image(buffer.buffer,buffer.width,buffer.height,channels_format,GL_UNSIGNED_BYTE);
            texture.configure(smoth,mipmap,clamp);
            texture.unbind();
            return texture;
        } 
        static inline Texture LOAD_CUBEMAP_FROM_BUFFER(CPUTextureBuffer buffer,bool smoth=true,bool mipmap=false, bool clamp=false) {
            log_printf("Sending CPUTextureBuffer to gpu as cubemap...\n");
            GLuint channels_format=GL_LUMINANCE;
            if(buffer.channels==3) channels_format=GL_RGB;
            if(buffer.channels==4) channels_format=GL_RGBA;
            auto factor=Vec2((float)buffer.width/4.0f,(float)buffer.height/3.0f);
            
            auto get_part=[&](int x,int y) { 
                auto face=buffer.extract_quad(
                    (uint32_t) x*factor.x, (uint32_t) y*factor.y,
                    (uint32_t)factor.x,(uint32_t)factor.y
                );
                uint32_t big_res= factor.x>factor.y ? factor.x : factor.y;
                auto resized=face.resized(big_res,big_res,face.channels);
                face.free();
                return resized; 
            };
            std::map<uint32_t,DMath::Vec2i> coordinates={
                {GL_TEXTURE_CUBE_MAP_NEGATIVE_X,{0,1}},
                {GL_TEXTURE_CUBE_MAP_POSITIVE_X,{3,1}},
                {GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,{1,2}},
                {GL_TEXTURE_CUBE_MAP_POSITIVE_Y,{1,0}},
                {GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,{1,1}},
                {GL_TEXTURE_CUBE_MAP_POSITIVE_Z,{1,2}},
            };
            Texture texture;
            texture.create_cubemap();
            texture.bind();
            for(auto& c : coordinates) {
                
                auto buffer=get_part(c.second.x,c.second.y);

                texture.set_cubemap_image(c.first,buffer.buffer,buffer.width,buffer.height,channels_format,GL_UNSIGNED_BYTE);
                buffer.free();
                            
                //std::cout << "printando " << c.first << " - " << std::endl; 
               // texture.set_cubemap_image(c.first,buffer.buffer,buffer.width,buffer.height,channels_format,GL_UNSIGNED_BYTE);

            }
            texture.configure(smoth,mipmap,clamp);
            texture.unbind();
            return texture;
        }   
    };

    class Shader {
        public:
        GLuint id=0,type=0;
        Shader() {id=0;type=0;}
        Shader(GLuint shader_type=GL_VERTEX_SHADER) { 
            type=shader_type;
        }
        static inline Shader create_from_id(GLuint shader_id, GLuint shader_type) {
            Shader shader(shader_id);
            shader.type=shader_type;
            return shader;
        }
        inline void set_source(const char* source) { glShaderSource(id, 1, &source, NULL); }
        inline void is_shader() { glIsShader( id); }
        inline bool has_compiled() {
            int success=0;
            glGetShaderiv(id, GL_COMPILE_STATUS,&success);
            return success==GL_TRUE;
        }
        inline bool compile() {   
            log_printf("Compiling shader id: %d\n",id); 
            glCompileShader(id); 
            if(!has_compiled()) {
                int length;
                glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
                char* log=new char[length];
                glGetShaderInfoLog(id, length, &length, log);
                err_printf("Shader compilation error:\n %s\n", log);
                delete[] log;
                return false;
            }
            return true;
        }
        inline void create() {
            id=glCreateShader(type); 
            log_printf("Shader id: %d created\n",id); 
        }
        inline void delete_shader() { 
            log_printf("Shader id: %d deleted\n",id); 
            glDeleteShader(id); 
            id=0;
        }
    };

    class ShaderProgram {
        public:
        GLuint id=0;
        std::map<std::string,GLint> uniforms;
        std::map<std::string,GLint> attributes;
        ShaderProgram(GLuint id) { this->id=id; }
        ShaderProgram() { id=0; }

        inline bool is_program() { return id!=0 || glIsProgram(id); }
        inline void use() {  
            if(!is_program()) {
                err_printf("trying to use a null shader program\n");
                return;
            }
            glUseProgram(id); 
        }
        inline void bind() { use(); }
        inline void unbind() { glUseProgram(0); }
        inline bool link() {
            log_printf("linking %d shader program\n", id);
            glLinkProgram(id);
            int success=0;
            glGetProgramiv(id, GL_LINK_STATUS, &success);
            if(success==GL_FALSE) {
                int length;
                glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
                char* log=new char[length];
                glGetProgramInfoLog(id, length, &length, log);
                log_printf("%s\n", log);
                delete[] log;
                return false;
            }
            return true;
        }
        inline bool link(const Shader& vertex_shader, const Shader& fragment_shader) { 
            log_printf("linking shaders %d %d \n", vertex_shader.id, fragment_shader.id);
            attach_shader(vertex_shader);
            attach_shader(fragment_shader);
            return link();
        }
        inline void create() {
            id=glCreateProgram();
            log_printf("Shader program id: %d created\n",id);
        }
        inline void delete_program() { 
            attributes.clear();
            uniforms.clear();
            glDeleteProgram(id);
            id=0;
            log_printf("Shader program id: %d deleted\n",id);
        }
        inline void attach_shader(const Shader& shader) { glAttachShader(id, shader.id); }
        inline void detach_shader(const Shader& shader) { glDetachShader(id, shader.id); }
        
        inline void bind_attribute_location(const char* name, GLuint location) { glBindAttribLocation(id, location, name); }
        static inline ShaderProgram compile_shaders_and_link_program(const char* vertex_shader_source, const char* fragment_shader_source) {
            ShaderProgram program;
            program.create();
            Shader vertex_shader(GL_VERTEX_SHADER);
            vertex_shader.create();
            vertex_shader.set_source(vertex_shader_source);
            vertex_shader.compile(); 
            Shader fragment_shader(GL_FRAGMENT_SHADER);
            fragment_shader.create();
            fragment_shader.set_source(fragment_shader_source);
            fragment_shader.compile();
            
            /*program.attach_shader(vertex_shader);
            program.attach_shader(fragment_shader);*/
            program.link(vertex_shader, fragment_shader);
            vertex_shader.delete_shader();
            fragment_shader.delete_shader();

            return program;
        }
        inline GLint uniform_location(const char* name) {
            if(uniforms.count(name)) return uniforms[name];
            GLint location=glGetUniformLocation(id,name);
            uniforms[name]=location;
            return location;
        }
        inline GLint attribute_location(const char* name) {
            if(attributes.count(name)) return attributes[name];
            GLint location=glGetAttribLocation(id,name);
            attributes[name]=location;
            return location;
        }
        /** overload uniform functions */
        inline void uniform(GLint location, GLfloat x) { glUniform1f(location, x); }
        inline void uniform(GLint location, GLfloat x, GLfloat y) { glUniform2f(location, x, y); }
        inline void uniform(GLint location, GLfloat x, GLfloat y, GLfloat z) { glUniform3f(location, x, y, z); }
        inline void uniform(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w) { glUniform4f(location, x, y, z, w); }
        inline void uniform(GLint location, GLint x) { glUniform1i(location, x); }
        inline void uniform(GLint location, GLint x, GLint y) { glUniform2i(location, x, y); }
        inline void uniform(GLint location, GLint x, GLint y, GLint z) { glUniform3i(location, x, y, z); }
        inline void uniform(GLint location, GLint x, GLint y, GLint z, GLint w) { glUniform4i(location, x, y, z, w); }
        inline void uniform(GLint location, const GLfloat* v, GLsizei count) { glUniform1fv(location, count, v); }

        inline void uniform_matrix2f(GLint location, const GLfloat* v, GLsizei count=1, GLboolean transpose=GL_FALSE) { glUniformMatrix2fv(location, count, transpose, v); }
        inline void uniform_matrix3f(GLint location, const GLfloat* v, GLsizei count=1, GLboolean transpose=GL_FALSE) { glUniformMatrix3fv(location, count, transpose, v); }        
        inline void uniform_matrix4f(GLint location, const GLfloat* v, GLsizei count=1, GLboolean transpose=GL_FALSE) { glUniformMatrix4fv(location, count, transpose, v); }
        inline void uniform_color(GLint location,const Color& color) { uniform(location,color.r,color.g,color.b,color.a);};
        inline void uniform_vec3(GLint location,const Vec3& v) { uniform(location,v.x,v.y,v.z);};
        inline void uniform_vec2(GLint location,const Vec2& v) { uniform(location,v.x,v.y);};
        inline void uniform_mat4(GLint location,const Mat4& m) { uniform_matrix4f(location,(GLfloat*) m.m);};

      /** overload uniform functions */
        inline void uniform(const char* name, GLfloat x) {glUniform1f(uniform_location(name), x); }
        inline void uniform(const char* name, GLfloat x, GLfloat y) { glUniform2f(uniform_location(name), x, y); }
        inline void uniform(const char* name, GLfloat x, GLfloat y, GLfloat z) { glUniform3f(uniform_location(name), x, y, z); }
        inline void uniform(const char* name, GLfloat x, GLfloat y, GLfloat z, GLfloat w) { glUniform4f(uniform_location(name), x, y, z, w); }
        inline void uniform(const char* name, GLint x) { glUniform1i(uniform_location(name), x); }
        inline void uniform(const char* name, GLint x, GLint y) { glUniform2i(uniform_location(name), x, y); }
        inline void uniform(const char* name, GLint x, GLint y, GLint z) { glUniform3i(uniform_location(name), x, y, z); }
        inline void uniform(const char* name, GLint x, GLint y, GLint z, GLint w) { glUniform4i(uniform_location(name), x, y, z, w); }
        inline void uniform(const char* name, const GLfloat* v, GLsizei count) { glUniform1fv(uniform_location(name), count, v); }
        inline void uniform_color(const char*name,const Color& color) { uniform_color(uniform_location(name),color);};
        inline void uniform_vec3(const char*name,const Vec3& v) { uniform_vec3(uniform_location(name),v);};
        inline void uniform_vec2(const char*name,const Vec2& v) { uniform_vec2(uniform_location(name),v);};

        inline void uniform_matrix2f(const char* name, const GLfloat* v, GLsizei count=1, GLboolean transpose=GL_FALSE) { glUniformMatrix2fv(uniform_location(name), count, transpose, v); }
        inline void uniform_matrix3f(const char* name, const GLfloat* v, GLsizei count=1, GLboolean transpose=GL_FALSE) { glUniformMatrix3fv(uniform_location(name), count, transpose, v); }        
        inline void uniform_matrix4f(const char* name, const GLfloat* v, GLsizei count=1, GLboolean transpose=GL_FALSE) { glUniformMatrix4fv(uniform_location(name), count, transpose, v); }
        inline void uniform_mat4(const char* name,const Mat4& m) { uniform_mat4(uniform_location(name),m);};


        
    };
    class Buffer {
        public:
        GLuint id=0;
        GLuint type=GL_ARRAY_BUFFER;
        GLsizei size=0;
        Buffer(GLuint id,GLuint type) { this->id=id; this->type=type; }
        Buffer() { id=0; type=GL_ARRAY_BUFFER; size=0; }

        inline void bind() { 
            if(!is_buffer()) {
                err_printf("trying to bind a null buffer\n");
                return;
            }
            glBindBuffer(type, id); 
        }
        inline void unbind() { glBindBuffer(type, 0); }
        inline bool is_buffer() { return id!=0 || glIsBuffer(id); }
        inline void create() {
            glGenBuffers(1, &id); 
            log_printf("Buffer id: %d created\n",id); 
        }
        inline void delete_buffer() {
            if(!is_buffer()) {
                err_printf("trying to delete a null buffer\n");
                return;
            }
            glDeleteBuffers(1, &id); 
            log_printf("Buffer id: %d deleted\n",id); 
            id=0;
            size=0;
        }
        inline void set_data(GLsizeiptr size, const GLvoid* data, GLuint usage=GL_STATIC_DRAW) { 
            this->size=size;
            glBufferData(type, size, data, usage);
        }
    };/*
    struct AttributePointer {
        public:
        GLuint index=0;
        GLint size=0;
        GLuint type=0;
        GLboolean normalized=0;
        GLsizei stride=0;
        const GLvoid * pointer=0;
        AttributePointer(GLuint index, GLint size, GLuint type, GLboolean normalized, GLsizei stride, const GLvoid * pointer) {
            this->index=index;
            this->size=size;
            this->type=type;
            this->normalized=normalized;
            this->stride=stride;
            this->pointer=pointer;
        }
        AttributePointer() {
            this->index=0;
            this->size=0;
            this->type=0;
            this->normalized=0;
            this->stride=0;
            this->pointer=0;
        }
    };*/
    // #define MAX_VERTEX_ATTRIBUTES 8
    class VBO : public  Buffer { 
        public:
        BoundBox bound_box=BoundBox();
       /* AttributePointer attributes[MAX_VERTEX_ATTRIBUTES];
        unsigned int attribute_count=0;
        */


        VBO(GLuint id) : Buffer(id,GL_ARRAY_BUFFER) {}
        VBO() : Buffer() {id=0; type=GL_ARRAY_BUFFER; size=0;}
        inline void enable_vertex_attribute(GLuint index) { glEnableVertexAttribArray(index); }
        inline void disable_vertex_attribute(GLuint index) { glDisableVertexAttribArray(index); }
        inline void set_vertex_attribute_value(GLuint index, GLfloat x) { glVertexAttrib1f(index, x); }
        inline void set_vertex_attribute_value(GLuint index, GLfloat x, GLfloat y) { glVertexAttrib2f(index, x, y); }
        inline void set_vertex_attribute_value(GLuint index, GLfloat x, GLfloat y, GLfloat z) { glVertexAttrib3f(index, x, y, z); }
        inline void set_vertex_attribute_value(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) { glVertexAttrib4f(index, x, y, z, w); }
        inline void set_attribute_pointer(GLuint index, GLint size, GLuint type, GLboolean normalized, GLsizei stride, const GLvoid * pointer) {
            glVertexAttribPointer(index, size, type, normalized, stride, pointer);
        }/*
        inline void set_attribute_pointer(AttributePointer p) {
            glVertexAttribPointer(p.index, p.size, p.type, p.normalized, p.stride, p.pointer);
        }*/
        /*
        inline void add_attribute_pointer(AttributePointer p) {
            attributes[attribute_count]=p;
            attribute_count++;
            if(attribute_count>=MAX_VERTEX_ATTRIBUTES) {
                log_printf("VBO::add_attribute_pointer: maximum number of attributes reached\n");
                return;
            }           
        }
        inline void set_attribute_pointers(a) {
             for (auto& p : attributes) set_attribute_pointer(p);
        }
        */
        inline void draw(GLsizei count=0,GLuint mode=GL_TRIANGLES,GLint first=0) {
            if(!is_buffer()) {
                err_printf("trying to draw with a null buffer\n");
                return;
            }
            if(count==0) count=this->size;
            glDrawArrays(mode, first, count);
        }
    };
    class EBO : public Buffer {
        public:
        EBO(GLuint id) : Buffer(id,GL_ELEMENT_ARRAY_BUFFER) {}
        EBO() : Buffer() {id=0; type=GL_ELEMENT_ARRAY_BUFFER; size=0;}
        inline void draw(GLsizei count=0,GLuint mode=GL_TRIANGLES,void* first=0) {
            if(count==0) count=this->size;
            glDrawElements(mode, count, GL_UNSIGNED_INT,  first);
        }
    }; 

    class GPUMesh {
        public:
        VBO vbo;
        EBO ebo;
        bool has_ebo=false; 
        GPUMesh(VBO v, EBO e) {
            vbo=v;
            ebo=e;
            has_ebo=true;
        }
        GPUMesh() {  }
        bool is_valid() {
            return vbo.is_buffer() && (has_ebo ? ebo.is_buffer() : true);
        }
        bool delete_ebo() {
            if(!has_ebo) return false;
            ebo.delete_buffer();
            has_ebo=false;
            return true;
        }
        void delete_buffers() {
            ebo.delete_buffer();
            if(has_ebo) vbo.delete_buffer();
        }
        static inline GPUMesh FROM_VBO(VBO v) {
            GPUMesh mesh= GPUMesh(v, EBO());
            mesh.has_ebo=false;
            return mesh;
        } 
        void draw(GLuint mode=GL_TRIANGLES,void* first=0,GLsizei count=0) {
            vbo.bind();
            if(has_ebo)  {
                ebo.bind();
                ebo.draw(count,mode,first);
                ebo.unbind();
            } else {
                vbo.draw();
            }
            vbo.unbind();
        }
    };

}

#endif

#include  <GLFW/glfw3.h>

#include "dsystem.hpp"
#include  "dmath.hpp"

#include <stdlib.h> /* timing */
#include <string.h>
#include <sys/time.h> /** timing */


#define INPUT_MAX_KEYS 20

#include <glad/glad.h>
namespace DSystem {

    using namespace DMath;

    static bool running=false;
    static GLFWwindow* window;
    namespace Time {
        static long initial_time=0;
        static long last_update_time=0;
        static double _delta=0.0;

        static inline long getSysMicrotime(){
            struct timeval currentTime;
            gettimeofday(&currentTime, NULL);
            return currentTime.tv_sec * (int)1e6 + currentTime.tv_usec;
        }
        static void init() {        
            initial_time=getSysMicrotime();
            last_update_time=initial_time;
        }
        static void update() {
            long now_micro=getSysMicrotime();

            _delta=(float)((now_micro-last_update_time)/1e6f);
            last_update_time=now_micro;
            /*
            if(delta_average==0) {
                delta_average=delta;
            } else {
                // linear interpolation
                delta_average=delta_average + 0.01 * (delta - delta_average);
            }*/
        }
        double delta() { return _delta;}
        double elapsed() { return (getSysMicrotime()-initial_time)/1e6f;}
        double elapsed_since(double time) {return elapsed()-time;}
        double fps_approx();
    }
    namespace Input {
        // estrutura para guardar os eventos do teclado
        typedef struct {
            KeyStatus action; // PRESSED,PRESING OU RELEASED
            int key; // GLFW_KEY_ESCAPE exemplo
        } KeyEvent;
        // buffer para armazenar as teclas pressionadas
        static KeyEvent events_buffer[INPUT_MAX_KEYS]={}; 
        static size_t event_buffer_count=0;

        // buffer para armazenar os estados da tecla lido no frame anterior
        KeyEvent events[INPUT_MAX_KEYS]={};
        size_t event_count=0;

        static void update() {
            // copia do buffer para o estado
            memcpy(events,events_buffer,sizeof(KeyEvent)*INPUT_MAX_KEYS);
            event_count=event_buffer_count;
            // limpa o buffer
            memset(events_buffer,0,sizeof(KeyEvent)*INPUT_MAX_KEYS);
            event_buffer_count=0;
        }
        void register_key(int key,KeyStatus status) {
            if(event_buffer_count<INPUT_MAX_KEYS && (status==RELEASED || status==PRESSED)) {
                events_buffer[event_buffer_count].key=key;
                events_buffer[event_buffer_count].action=status;
                event_buffer_count++;
            }
        }
        KeyStatus get_status(int key) {
            for(size_t i=0;i<event_count;i++) {
                if(events[i].key==key) return events[i].action;
            }
            if(glfwGetKey(DSystem::window,key)==GLFW_PRESS) return PRESSING;
            else return NOT_PRESSED;
        }
        bool released(int key) {return get_status(key)==RELEASED;}
        bool pressed(int key) {return get_status(key)==PRESSED;}
        bool pressing(int key) {return get_status(key)==PRESSING;}
    }
    
    static void error_callback(int error, const char* description) {
        fprintf(stderr, "Error: %s\n", description);
    }
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        // guarda os eventos no buffer
        if(action==GLFW_PRESS || action==GLFW_RELEASE) {
            Input::register_key(key, action==GLFW_PRESS ? Input::PRESSED : Input::RELEASED); 
        }
    }


    static int __winsize[2]={800,600};

    bool init(const char* title) {
        glfwSetErrorCallback(error_callback);
        
        if (!glfwInit())
            exit(EXIT_FAILURE);

        /*if(antialiasing) glfwWindowHint(GLFW_SAMPLES, 4);*/
        glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);
        int monitors_count;
        GLFWmonitor ** monitors=glfwGetMonitors(&monitors_count);
        static char default_window_title[10]= "GROTA 3D";
        if(!title) title=default_window_title;
            /// if you want full screen put monitors[0] on the fist null parameter    
        window = glfwCreateWindow(__winsize[0],__winsize[1],title , NULL, NULL);
        if (!window) {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

       // glfwSetKeyCallback(window, key_callback);

        glfwMakeContextCurrent(window);
        if (!gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress)) {
            printf("Error Loading OpenGL With GLAD\r\n");
            return -1;
        }    

    /*
        gladLoadGLESLoader((GLADloadproc)glfwGetProcAddress);
        if(!gladLoadGL()) {
            printf("Error Loading OpenGL With GLAD!\n");
            return 0;
        }*/
        /*if(antialiasing) glEnable(GL_MULTISAMPLE); */
        glfwSwapInterval(1);
        running=true;
        Time::init();
        //Input::init();
        return true;
    }
    bool update() {
        //Sleep(10); 
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        glfwGetFramebufferSize(window, &__winsize[0], &__winsize[1]);
        /*if(window_show_fps) {
            //char window_title[100];
            //snprintf(window_title,100," FPS: %d",time_fps());
            //glutSetWindowTitle(window_title);
        }*/
        Input::update();
        Time::update();
        return (!glfwWindowShouldClose(window) && running);
    }
    void stop() { running=false;}
    void destroy() {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
    Vec2 window_size() {
        return Vec2(__winsize[0],__winsize[1]);
    }
}
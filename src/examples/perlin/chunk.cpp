
#include "../../glhelpers.hpp"


int render_distance=10; 
int load_distance=15;
int mip_distance=5;

#include <algorithm>
#define CHUNK_SIZE 32

struct Chunk {
    public:
    VBO terrain;
    Texture texture;
    int pos_x=0, pos_y=0;
    int subdivisions=0;
    float peak_height=-1000;
    bool loaded=false;
    void unload() {
        if(!loaded) return;
        if(terrain.id) terrain.delete_buffer();
        if(texture.id) texture.delete_texture();
        loaded=false;
    }
    void load(int subdivide=0) {
        if(loaded && subdivisions==subdivide) return; 
        
        subdivisions=subdivide;
        int chunk_divisions=pow(2,subdivisions);
        if(chunk_divisions>=CHUNK_SIZE/4) chunk_divisions=CHUNK_SIZE/4;
       // printf("SUBDIVISIONS %d\n",subdivisions);

        int chunk_res=CHUNK_SIZE/chunk_divisions; 
        int texture_res=chunk_res;
        chunk_res++;

        auto globalpos=global_position();

        unload(); 
       // printf("alocatting map..\n"); 
        unsigned char* mapa = new unsigned char[chunk_res*chunk_res];
        memset(mapa, 0, chunk_res*chunk_res);

       // printf("Generating map...\n");
        int x, y;
        for(y=0; y<chunk_res; y++) for(x=0; x<chunk_res; x++) {
            auto voxel=generate_voxel((x*chunk_divisions)+(globalpos.x), (y*chunk_divisions)+(globalpos.z));
            if(voxel.altitude>peak_height) peak_height=voxel.altitude;
            mapa[(y * chunk_res + x)] = voxel.altitude*255;

        }

       // printf("Generating vertice buffer...\n");
        VertexData *vertices= new VertexData[chunk_res*chunk_res*6];
     
        int i=0;
        for(y=0; y<chunk_res-1; y++) for(x=0; x<chunk_res-1; x++) {
            double prop=1.0/(float)chunk_res;
            auto pt=Vec2(x, y)*prop;
            auto get_height=[&](int x,int y) {
                return (double) mapa[(y * chunk_res + x)]/chunk_divisions;
            };
            auto calc_normal=[&](int x,int y) {
                
                Vec3 R=Vec3(x-1-(chunk_res/2), get_height(x-1,y), y-(chunk_res/2))*chunk_divisions;  
                Vec3 L=Vec3(x+1-(chunk_res/2), get_height(x+1,y), y-(chunk_res/2))*chunk_divisions;
                Vec3 B=Vec3(x-(chunk_res/2), get_height(x,y-1), y-1-(chunk_res/2))*chunk_divisions;  
                Vec3 T=Vec3(x-(chunk_res/2), get_height(x,y+1), y+1-(chunk_res/2))*chunk_divisions; 
           
                return Vec3::cross(R-L, T-B).normalized(); 
            };
            auto genv=[&](int x,int y) {
                VertexData v;
                v.vertex=Vec3(x-(chunk_res/2), get_height(x,y) , y-(chunk_res/2))*chunk_divisions;
                v.normal=calc_normal(x,y);
                v.uv=Vec2(x, y)*prop;
                return v;
            }; 
            vertices[i++]=genv(x,y);
            vertices[i++]=genv(x+1,y+1);
            vertices[i++]=genv(x+1,y);
            vertices[i++]=genv(x,y+1);
            vertices[i++]=genv(x+1,y+1);
            vertices[i++]=genv(x,y);
        }
        terrain=LOAD_MESH(vertices, chunk_res*chunk_res*6);
        free(vertices);
        delete [] mapa;
        
        CPUTextureBuffer tbuffer(texture_res,texture_res,3); 
        tbuffer.alloc();

        for(y=0; y<texture_res; y++) for(x=0; x<texture_res; x++) {
            VoxelInfo voxel=generate_voxel((x*chunk_divisions)+(globalpos.x), (y*chunk_divisions)+(globalpos.z));
            tbuffer.put_pixel_color(x,y,voxel.color);
        } 
         texture= tbuffer.send_to_gpu();
        tbuffer.free();

        loaded=true;
    }
    
    inline Vec3 global_position() {
        return Vec3(pos_x,0,pos_y)*CHUNK_SIZE;
    }
};

#include <vector>
using std::vector;
vector<Chunk> chunks;


inline int player_to_chunk_coord(float player_coord) {
    return lround((((player_coord))/(float)CHUNK_SIZE));
}

inline Vec3 chunk_global_position(int pos_x,int pos_y) {
    return Vec3(pos_x,0,pos_y)*CHUNK_SIZE;
}

 
void load_chunks(Vec3 player_pos) {
    player_pos.y=0;
    int chunk_load_radius=render_distance;
    int chk_x=player_to_chunk_coord(player_pos.x);
    int chk_y=player_to_chunk_coord(player_pos.z);

    for(int y=-chunk_load_radius+chk_y;y<chunk_load_radius+chk_y+1;y++) {
        for(int x=-chunk_load_radius+chk_x;x<chunk_load_radius+chk_x+1;x++) {
            bool _break=false;
            //std::cout << "chunk X " << x << " Y " << y << std::endl;

            float chunk_distance=Vec3::distance(chunk_global_position(x,y),player_pos);
           int load_level=(int)(chunk_distance/(float)CHUNK_SIZE)/mip_distance;
           //load_level=0;
           // int load_level=0;
            if(chunk_distance>render_distance*CHUNK_SIZE) continue;
            bool has_chunk=false;
            for(auto &ck:chunks) {
                if(ck.pos_x==x && ck.pos_y==y) {
                    ck.load(load_level);
                    has_chunk=true; 
                    break; 
                    _break=true;
                }
            }
            if(!has_chunk) {
                Chunk new_chunk;
                new_chunk.pos_x=x;
                new_chunk.pos_y=y;
                new_chunk.load(load_level); 
                chunks.push_back(new_chunk);
                _break=true;
            }
            if(_break) break;
        }
    }
     /** REMOVE DO ARRAY TODOS OS CHUNKS QUE ESTAO LONGES, E DESCARREGA ELES DA GPU PRIMERIRO*/
    chunks.erase(
        std::remove_if(chunks.begin(), chunks.end(),
            [&](Chunk & ck) {
                    if(Vec3::distance(ck.global_position(),player_pos)>load_distance*CHUNK_SIZE) {
                        ck.unload();
                        return true;
                    }
                    return false; 
                 }),
    chunks.end());

   // std::cout << "--" << chunks.size() << " chunks in the vector..\n";
}

void unload_all_chunks() {
     for(auto &ck:chunks)  ck.unload();
}
 








#include "../glhelpers.hpp"

int render_distance=5; 
int load_distance=8;
int mip_distance=10;

#include <algorithm>
#define CHUNK_SIZE 16
#include <memory>

#include "mesh_renderer.hpp"
class Chunk {
    public: 
    DGL::VBO terrain;
    DGL::Texture texture;
    int32_t pos_x=0, pos_y=0;
    uint32_t subdivisions=0;
    float peak_height=-1000;
    bool loaded=false; 
    uint32_t size=32;

    
    inline Vec3 global_position() {
        return Vec3(pos_x,0,pos_y)*CHUNK_SIZE;
    }

    inline void unload() {
        if(!loaded) return;
        if(terrain.id) terrain.delete_buffer();
        if(texture.id) texture.delete_texture();
        loaded=false;
    }
    inline void load_terrain() {
        peak_height=0;
       // printf("chegou aqui load_terrain\n");
        if(terrain.id) terrain.delete_buffer(); 
        Vec3 chunk_pos=global_position();
        uint32_t chunk_res=size;
        MeshRenderer::Mesh mesh;
        mesh.vertices.resize(chunk_res*chunk_res);
        mesh.normals.resize(chunk_res*chunk_res);
        mesh.uvs.resize(chunk_res*chunk_res);
        mesh.triangles.resize((chunk_res-1)*(chunk_res-1)*2); 

        auto get_index=[&](uint32_t x,uint32_t y) {return (y*chunk_res)+x;};
        
        float factor=(1.0/chunk_res);
        for(auto y=0;y<chunk_res;y++) 
        for(auto x=0;x<chunk_res;x++) {
            //std::cout << "printando " << x << "x" << y << std::endl;
            auto idx=get_index(x,y); //index
            
           mesh.uvs[idx]=Vec2(x,y)*factor; // texture coordinate

            auto get_vert=[&](float x, float y) {
                Vec3 vt=Vec3(x,0,y)*(float)size; // vertice
              //  vt.y=terrain_altitude(vt.x+chunk_pos.x,vt.y+chunk_pos.z);
                return vt;
            };
           
            auto vert=get_vert(x,y);
           // printf("varrendo %f,%f,%f \n",vert.x,vert.y,vert.z);
            if(vert.y>peak_height) peak_height=vert.y;
            mesh.vertices[idx]=vert; 
            
            Vec3 R=get_vert(x-1,y);
            Vec3 L=get_vert(x+1,y);
            Vec3 B=get_vert(x,y-1);  
            Vec3 T=get_vert(x,y+1);  
            mesh.normals[idx]=Vec3::cross(R-L, T-B).normalized();  
        }
           
        for(auto y=0;y<chunk_res-1;y++) for(auto x=0;x<chunk_res-1;x++)  { 
           // std::cout << "indexando  " << x << "x" << y << std::endl;
            auto idx=get_index_tri(x,y);
            // triangle zero of this quad
            uint32_t vt1=get_index(x,y)+1;
            uint32_t vt2=get_index(x+1,y)+1;
            uint32_t vt3=get_index(x,y+1)+1;
            mesh.triangles[idx*2]={{{vt1,vt1,vt1},{vt2,vt2,vt2},{vt3,vt3,vt3}}};
            //std::cout << "indexando 2 tri  " << x << "x" << y << std::endl;

            vt1=get_index(x,y+1)+1;
            vt2=get_index(x+1,y)+1;
            vt3=get_index(x+1,y+1)+1;
            mesh.triangles[(idx*2)+1]={{{vt1,vt1,vt1},{vt2,vt2,vt2},{vt3,vt3,vt3}}};

        }
        
        //std::cout << "criando mesha  " << std::endl;
        terrain=mesh.send_to_gpu();
        mesh.clear(); 
    }
    inline void load(int subdivide=0) {
        if(loaded && subdivisions==subdivide) return; 
        load_terrain();
        subdivisions=subdivide;
        /*
        int chunk_divisions=pow(2,subdivisions);
        if(chunk_divisions>=CHUNK_SIZE/4) chunk_divisions=CHUNK_SIZE/4;
       // printf("SUBDIVISIONS %d\n",subdivisions);

        int chunk_res=CHUNK_SIZE/chunk_divisions; 
        int texture_res=chunk_res;
        chunk_res++;


        unload();*/ 
       // printf("alocatting map..\n"); 
       /* unsigned char* mapa = new unsigned char[chunk_res*chunk_res];
        memset(mapa, 0, chunk_res*chunk_res);
*/
       // printf("Generating map...\n");
      /*  int x, y;
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
        */
        /*
        CPUTextureBuffer tbuffer(texture_res,texture_res,3); 
        tbuffer.alloc();

        for(uint32_t y=0; y<texture_res; y++) for(uint32_t x=0; x<texture_res; x++) {
            VoxelInfo voxel=generate_voxel((x*chunk_divisions)+(globalpos.x), (y*chunk_divisions)+(globalpos.z));
            tbuffer.put_pixel_color(x,y,voxel.color);
        } 
        texture= tbuffer.send_to_gpu();
        tbuffer.free(); 
        
        delete [] mapa;*/
        loaded=true;
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
 







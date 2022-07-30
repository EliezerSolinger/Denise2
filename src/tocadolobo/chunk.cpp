
#include "../glhelpers.hpp"

int render_distance=20; 
int load_distance=30;
int mip_distance=10;

#include <algorithm>
#define CHUNK_SIZE 16
#include <memory>

#include "mesh_renderer.hpp"

class Chunk {
    public: 
    DGL::GPUMesh terrain;
    DGL::Texture texture;
    int32_t pos_x=0, pos_y=0;
    uint32_t subdivisions=0;
    float peak_height=-1000;
    bool loaded=false;  
    
    inline Vec3 global_position() {
        return Vec3(pos_x,0,pos_y)*CHUNK_SIZE;
    }

    inline void unload() {
        if(!loaded) return;
        if(terrain.is_valid()) terrain.delete_buffers();
        if(texture.is_texture()) texture.delete_texture();
        loaded=false;
    }
    inline void reload_terrain() {
        peak_height=0;
       // printf("chegou aqui load_terrain\n");
      //  if(terrain.id) terrain.delete_buffer(); 
        Vec3 globalpos=global_position();
        uint32_t chunk_res=(CHUNK_SIZE/2)+1;
        
        if(terrain.is_valid()) terrain.delete_buffers();

        MeshRenderer::Mesh mesh;
        mesh.vertices.resize(chunk_res*chunk_res);
        mesh.normals.resize(chunk_res*chunk_res);
        mesh.uvs.resize(chunk_res*chunk_res);


        auto get_index=[&](uint32_t x,uint32_t y) {return (y*chunk_res)+x;};
        
        float factor=(1.0/(chunk_res-1));
        for(auto y=0;y<chunk_res;y++) 
         for(auto x=0;x<chunk_res;x++) { 
            auto idx=get_index(x,y); //index
            
           mesh.uvs[idx]=Vec2(x,y)*factor; // texture coordinate

            auto vert=[&](float _x, float _y) {
                Vec3 vt=Vec3(_x,0,_y)*factor*(float)CHUNK_SIZE; 
                vt.y=(terrain_altitude(vt.x+globalpos.x,vt.z+globalpos.z)-0.5)*100; 
                return vt;
            };
           
            auto v=vert(x,y); 
            if(v.y>peak_height) peak_height=v.y;
            mesh.vertices[idx]=v; 
              
            mesh.normals[idx]=
                Vec3::cross(
                    vert(x-1,y)-vert(x+1,y), 
                    vert(x,y+1)-vert(x,y-1)
                ).normalized();

        } 
       
        mesh.triangles.resize((chunk_res-1)*(chunk_res-1)*2); 
        
        auto get_index_tri=[&](uint32_t _x,uint32_t _y) {return (_y*(chunk_res-1))+_x;};

        for(auto y=0;y<chunk_res-1;y++) for(auto x=0;x<chunk_res-1;x++)  { 
            //std::cout << "indexando  " << x << "x" << y << std::endl;
            auto idx=get_index_tri(x,y);
            // triangle zero of this quad
            uint32_t vt1=get_index(x,y)+1;
            uint32_t vt2=get_index(x+1,y)+1;
            uint32_t vt3=get_index(x,y+1)+1;
            mesh.triangles[idx*2]={{{vt1,vt1,vt1},{vt2,vt2,vt2},{vt3,vt3,vt3}}};
            //std::cout << "indexando 2 tri  " << x << "x" 677777777777777777777777777777777777777777777777700000000000000<< y << std::endl;

            vt1=get_index(x,y+1)+1;
            vt2=get_index(x+1,y)+1;
            vt3=get_index(x+1,y+1)+1;
            mesh.triangles[(idx*2)+1]={{{vt1,vt1,vt1},{vt2,vt2,vt2},{vt3,vt3,vt3}}};

        } 
        //std::cout << "criando mesha  " << std::endl;
        terrain=mesh.send_to_gpu();
        mesh.clear(); 
    }
    inline void reload_texture() {
        if(texture.is_texture()) texture.delete_texture();
        auto globalpos=global_position();
        auto texture_res=CHUNK_SIZE;
        CPUTextureBuffer tbuffer(texture_res,texture_res,3); 
        tbuffer.alloc();

        for(uint32_t y=0; y<texture_res; y++) for(uint32_t x=0; x<texture_res; x++) {
            VoxelInfo voxel=generate_voxel(x+(globalpos.x), (y)+(globalpos.z));
            tbuffer.put_pixel_color(x,y,voxel.color);
        } 
        texture= Texture::LOAD_FROM_BUFFER(tbuffer);
        tbuffer.free();  
    }
    inline void load(int subdivide=0) {
        if(loaded && subdivisions==subdivide) return; 
        reload_terrain();
        reload_texture();
        subdivisions=subdivide;
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
 







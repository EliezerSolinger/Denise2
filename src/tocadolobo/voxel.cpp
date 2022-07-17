#define SEED_MAPA 0
#define SEED_BIOMA 1
#define TERRAIN_SIZE 1024
extern "C" {
    #include "perlin.c"
}

enum Tipo {
    AGUA,
    TERRA,
    AREIA,
    ARVORE,
    NEVE,
    PEDRA
};


struct VoxelInfo {
    float altitude=0;
    Color color=Color(0,0,0,0);
    Tipo tipo=AGUA;   
};

float terrain_altitude(float x, float y) {
    return perlin2d(x, y, 0.005, 3,SEED_BIOMA);
}

VoxelInfo generate_voxel(int x, int y) {
    VoxelInfo info;
    x+=1000;
    y+=1000;
    float h=terrain_altitude(x, y);  
    info.altitude=h;     
    h=h*255;
    
    Tipo tipo = AGUA;
    if(h>=56+90) tipo = AREIA;
    if(h>=56+90) {
        srand(x*y);
        if(perlin2d(x, y, 0.006, 2,SEED_BIOMA)>0.68) tipo = NEVE;
        else if(perlin2d(x, y, 0.006, 2,SEED_BIOMA)<0.4) tipo = AREIA;
        else tipo = TERRA;
        // deixa espaços em branco que nao existem arvores no mapa
        if(perlin2d(x, y, 0.9, 4,SEED_MAPA)>0.55) {
            if(x%3==rand()%3 && y%3==rand()%3)  tipo = ARVORE;
        }
        
    }
    if(h>=65+170) {
        tipo = PEDRA;
    }
    

    float r=1, g=1, b=1;
    if(tipo==AGUA) r=0.5, g=0.5, b=1;
    if(tipo==AREIA) r=0.76, g=0.7, b=0.5;
    if(tipo==TERRA) r=0.3, g=0.4, b=0.2;
    if(tipo==NEVE) r=0.9, g=0.9, b=0.9;
    if(tipo==PEDRA) r=0.5, g=0.5, b=0.5;

    if(tipo==ARVORE) {
        r=0.3, g=0.4, b=0.2;
        if(h >= 65+90) r=0.5, g=0.5, b=0.5;
    }

    //return {h, Color(r,g,b), tipo};
    info.color=Color(r,g,b);
    info.tipo=tipo;
    return info;
}



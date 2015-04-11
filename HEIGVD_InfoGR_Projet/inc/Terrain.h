//
//  terrain.h
//  HeghtMaps_3
//
//  Created by Leeroy Brun on 02.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#ifndef __HeghtMaps_3__terrain__
#define __HeghtMaps_3__terrain__

#include "main.h"
#include "vec3f.h"
#include "PngImage.h"
#include "Game.h"
#include "Textures.h"

class Terrain {
private:
    int w; //Width
    int l; //Length
    float scale;
    float scaleFactor;
    float** hs; //Heights
    Vec3f** normals;
    bool computedNormals; //Whether normals is up-to-date
public:
    Terrain(int w2, int l2);
    
    ~Terrain();
    
    int width();
    
    int length();
    
    float getScale();
    
    float getScaleFactor();
    void  setScaleFactor(float _scaleFactor);
    
    //Sets the height at (x, z) to y
    void setHeight(int x, int z, float y);
    
    //Returns the height at (x, z)
    float getHeight(int x, int z);
    float getRealHeight(int x, int z);
    
    //Computes the normals, if they haven't been computed yet
    void computeNormals();
    
    // Draw the terrain
    void draw();
    
    //Returns the normal at (x, z)
    Vec3f getNormal(int x, int z);
};

Terrain* loadTerrain(const char* filename, float maxHeight);

#endif /* defined(__HeghtMaps_3__terrain__) */

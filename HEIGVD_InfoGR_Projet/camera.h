//
//  Camera.h
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 06.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#ifndef __HEIGVD_InfoGR_Projet__Camera__
#define __HEIGVD_InfoGR_Projet__Camera__

#include "main.h"
#include <math.h>

/*
 
 // angle of rotation for the camera direction
 float camAngle=0.0;
 // actual vector representing the camera's direction
 float camLx=0.0f, camLz=-1.0f;
 // XZ position of the camera
 float camX=0.0f,camZ=5.0f;
 
 float deltaAngle = 0.0f;
 float deltaMove = 0;
 
 */

class Camera {
private:
    float angle=0.0;
    float lx=0.0f, lz=-1.0f;
    float x=0.0f, y=0.0f, z=5.0f;
    float deltaAngle = 0.0f;
    float deltaMove = 0;
public:
    Camera(float _x = 0, float _y = 0, float _z = 0, float _angle = 0);
    
    ~Camera();

    void init();

    void lookAt();
    
    float getAngle();
    float getX();
    float getY();
    float getZ();
    void setY(float _y);
    
    void computePos();
    
    void pressKey(int key, int xx, int yy);
    void releaseKey(int key, int x, int y);
};

#endif /* defined(__HEIGVD_InfoGR_Projet__Camera__) */

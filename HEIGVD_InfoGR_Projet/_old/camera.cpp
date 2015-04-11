//
//  camera.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 17.02.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "camera.h"

// angle of rotation for the camera direction
float camAngle=0.0;
// actual vector representing the camera's direction
float camLx=0.0f, camLz=-1.0f;
// XZ position of the camera
float camX=0.0f,camZ=5.0f;

float deltaAngle = 0.0f;
float deltaMove = 0;

void computePos(float deltaMove) {
    camX += deltaMove * camLx * 0.1f;
    camZ += deltaMove * camLz * 0.1f;
}

void computeDir(float deltaAngle) {
    camAngle += deltaAngle;
    camLx = sin(camAngle);
    camLz = -cos(camAngle);
}

void camComputePos() {
    if (deltaMove)
        computePos(deltaMove);
    if (deltaAngle)
        computeDir(deltaAngle);
}

void camDefineLookAt() {
    glLoadIdentity();
    
    gluLookAt(camX, 1.0f, camZ,
              camX+camLx, 1.0f, camZ+camLz,
              0.0f, 1.0f, 0.0f);
}

void camPressKey(int key, int xx, int yy) {
    
    switch (key) {
        case GLUT_KEY_LEFT : deltaAngle = -0.01f; break;
        case GLUT_KEY_RIGHT : deltaAngle = 0.01f; break;
        case GLUT_KEY_UP : deltaMove = 0.5f; break;
        case GLUT_KEY_DOWN : deltaMove = -0.5f; break;
    }
}

void camReleaseKey(int key, int x, int y) {
    
    switch (key) {
        case GLUT_KEY_LEFT :
        case GLUT_KEY_RIGHT : deltaAngle = 0.0f;break;
        case GLUT_KEY_UP :
        case GLUT_KEY_DOWN : deltaMove = 0;break;
    }
}
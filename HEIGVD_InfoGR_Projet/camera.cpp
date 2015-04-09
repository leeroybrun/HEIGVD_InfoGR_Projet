//
//  Camera.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 06.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "Camera.h"

Camera::Camera(float _x, float _y,  float _z, float _angle){
    x = _x;
    y = _y;
    z = _z;
    angle = _angle;
}

Camera::~Camera(){
    
}

float Camera::getAngle()
{
    return angle;
}

float Camera::getX()
{
    return x;
}

float Camera::getY()
{
    return y;
}

float Camera::getZ()
{
    return z;
}

void Camera::setY(float _y)
{
    y = _y;
}

void Camera::computePos() {
    //if (deltaMove)
    //{
        this->x += this->deltaMove * this->lx * 0.1f;
        this->z += this->deltaMove * this->lz * 0.1f;
    //}
    //if (deltaAngle)
    //{
        this->angle += deltaAngle;
        this->lx = sin(this->angle);
        this->lz = -cos(this->angle);
    //}
}

void Camera::lookAt() {
    glLoadIdentity();
    
    //int realX = (x * terrainScale) + (terrainSize/2);
    
    gluLookAt(x, y, z,
              0.01+x+lx, y, 0.01+z+lz,
              0.0f, 1.0f, 0.0f);
}

void Camera::pressKey(int key, int xx, int yy) {
    
    switch (key) {
        case GLUT_KEY_LEFT : deltaAngle = -0.01f; break;
        case GLUT_KEY_RIGHT : deltaAngle = 0.01f; break;
        case GLUT_KEY_UP : deltaMove = 1.5f; break;
        case GLUT_KEY_DOWN : deltaMove = -1.5f; break;
    }
}

void Camera::releaseKey(int key, int x, int y) {
    
    switch (key) {
        case GLUT_KEY_LEFT :
        case GLUT_KEY_RIGHT : deltaAngle = 0.0f;break;
        case GLUT_KEY_UP :
        case GLUT_KEY_DOWN : deltaMove = 0;break;
    }
}
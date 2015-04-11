//
//  Camera.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 06.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "Camera.h"

Camera::Camera(Vec3f _pos) : pos(_pos){}

Camera::~Camera(){
    
}

void Camera::init() {
    glutSetCursor(GLUT_CURSOR_NONE);
    glutWarpPointer(Game::window->width/2, Game::window->height/2);
}

float Camera::getX()
{
    return pos[0];
}

float Camera::getY()
{
    return pos[1];
}

float Camera::getZ()
{
    return pos[2];
}

void Camera::setY(float _y)
{
    pos[1] = _y;
}

void Camera::setMoveSpeed(float _moveSpeed) {
    currMoveSpeed = _moveSpeed;
}
void Camera::setRotateSpeed(float _rotateSpeed) {
    currRotateSpeed = _rotateSpeed;
}

void Camera::computePos() {
    if(currMoveSpeed != 0) {
        move(currMoveSpeed);
    }
    if(currRotateSpeed != 0) {
        rotate(currRotateSpeed);
    }
}

void Camera::lookAt() {
    glLoadIdentity();
    
    gluLookAt(pos[0], pos[1], pos[2],
              target[0], target[1], target[2],
              up[0], up[1], up[2]);
}

void Camera::move(float speed)
{
    Vec3f vVector = target - pos;	// Get the view vector
    
    // forward positive cameraspeed and backward negative -cameraspeed.
    pos[0]  = pos[0] + vVector[0] * speed;
    pos[2]  = pos[2]  + vVector[2] * speed;
    target[0] = target[0] + vVector[0] * speed;
    target[2] = target[2] + vVector[2] * speed;
}

void Camera::rotate(float speed)
{
    Vec3f vVector = target - pos;	// Get the view vector
    
    target[2] = (float)(pos[2] + sin(speed)*vVector[0] + cos(speed)*vVector[2]);
    target[0] = (float)(pos[0] + cos(speed)*vVector[0] - sin(speed)*vVector[2]);
}

void Camera::mouseMotion(float x, float y){
    int mid_x = Game::window->width/2;
    int mid_y = Game::window->height/2;
    float angle_y  = 0.0f;
    float angle_z  = 0.0f;
    
    if( (x == mid_x) && (y == mid_y) ) return;
    
    glutWarpPointer(mid_x, mid_y);
    
    // Get the direction from the mouse cursor, set a resonable maneuvering speed
    angle_y = (float)( (mid_x - x) ) / 1000;
    angle_z = (float)( (mid_y - y) ) / 1000;
    
    // The higher the value is the faster the camera looks around.
    target[1] += angle_z * 100;
    
    // limit the rotation around the x-axis
    if((target[1] - pos[1]) > 8)  target[1] = pos[1] + 8;
    if((target[1] - pos[1]) <-8)  target[1] = pos[1] - 8;
    
    rotate(-angle_y); // Rotate
}

void Camera::pressKey(int key, int xx, int yy) {
    
    switch (key) {
        case GLUT_KEY_LEFT : setRotateSpeed(-CAMERA_ROTATE_SPEED); break;
        case GLUT_KEY_RIGHT : setRotateSpeed(CAMERA_ROTATE_SPEED); break;
        case GLUT_KEY_UP : setMoveSpeed(CAMERA_MOVE_SPEED); break;
        case GLUT_KEY_DOWN : setMoveSpeed(-CAMERA_MOVE_SPEED); break;
    }
}

void Camera::releaseKey(int key, int x, int y) {
    
    switch (key) {
        case GLUT_KEY_LEFT : setRotateSpeed(0); break;
        case GLUT_KEY_RIGHT : setRotateSpeed(0); break;
        case GLUT_KEY_UP : setMoveSpeed(0); break;
        case GLUT_KEY_DOWN : setMoveSpeed(0); break;
    }
}
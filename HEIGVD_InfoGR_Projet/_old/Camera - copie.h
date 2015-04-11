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
#include "vec3f.h"
#include <math.h>
#include "Game.h"

#define CAMERA_MOVE_SPEED	0.08f //0.02
#define CAMERA_ROTATE_SPEED	0.1f // 0.05

class Camera {
private:
    Vec3f pos = Vec3f(0, 0, 5);
    Vec3f target = Vec3f(0, 0, 1);
    Vec3f up = Vec3f(0, 1, 0);
    float currMoveSpeed = 0;
    float currRotateSpeed = 0;
public:
    Camera(Vec3f pos);
    
    ~Camera();

    void init();

    void lookAt();
    
    void setMoveSpeed(float _moveSpeed);
    void setRotateSpeed(float _rotateSpeed);
    
    float getX();
    float getY();
    float getZ();
    void setY(float _y);
    
    void computePos();
    
    void move(float speed);
    void rotate(float speed);
    
    void mouseMotion(float x, float y);
    void pressKey(int key, int xx, int yy);
    void releaseKey(int key, int x, int y);
};

#endif /* defined(__HEIGVD_InfoGR_Projet__Camera__) */

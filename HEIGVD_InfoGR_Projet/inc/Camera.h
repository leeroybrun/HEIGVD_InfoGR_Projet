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
#include "Keyboard.h"
#include "Stats.h"

#define CAMERA_MOVE_SPEED	5.0f //0.02
#define CAMERA_JUMP_SPEED	6.0f //0.02
#define CAMERA_JUMP_HEIGHT	20.0f // 0.05

enum JumpDirection {
    Up,
    Down
};

class Camera {
private:
    Vec3f pos = Vec3f(0, 0, 5);
    Vec3f target = Vec3f(0, 0, 1);
    Vec3f direction = Vec3f(0, 0, -1);
    Vec3f up = Vec3f(0, 1, 0);
    
    bool _isOnFloor   = true;
    
    bool isJumping   = false;
    JumpDirection jumpDir  = Up;
    float jumpStartY = 0;
    
    bool firstMouseMove = true;
    GLfloat lastMouseX = 400, lastMouseY = 300;
    GLfloat yaw = -90.0f, pitch = 0;
public:
    Camera(Vec3f pos);
    
    ~Camera();
    
    void init();
    
    void lookAt();
    
    float getX();
    float getY();
    float getZ();
    void setY(float _y);
    
    Vec3f getPosition();
    Vec3f getDirection();
    
    bool isOnFloor();
    
    void jump();
    void doMovement();
    
    void pressKey(unsigned char key, int xx, int yy);
    void mouseMotion(float x, float y);
};

#endif /* defined(__HEIGVD_InfoGR_Projet__Camera__) */

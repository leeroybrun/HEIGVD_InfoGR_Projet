//
//  GameObject.h
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 10.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#ifndef __HEIGVD_InfoGR_Projet__GameObject__
#define __HEIGVD_InfoGR_Projet__GameObject__

#include "main.h"
#include "vec3f.h"

#define GRAVITY 3

struct Size3f {
    Size3f(float _x, float _y, float _z): x(_z), y(_y), z(_z){};
    
    float x;
    float y;
    float z;
};

enum TypeGameObjectPos {
    TopLeft,
    Center
};

class GameObject
{
public:
    GameObject(TypeGameObjectPos typePos, Vec3f pos, Size3f size, float scale = 1, bool applyGravity = false);
    
    Vec3f getPos(TypeGameObjectPos typePos);
    void setPos(TypeGameObjectPos typePos, Vec3f pos);
    
    Vec3f getVelocity();
    void setVelocity(Vec3f _velocity);
    
    void move(float speed);
    bool detectCollision(GameObject &obj2);
    void drawCollisionBox();
protected:
    Size3f size = {0, 0, 0};
    Vec3f topLeftPos = {0, 0, 0};
    Vec3f centerPos = {0, 0, 0};
    Vec3f velocity = {0, 0, 0};
    bool applyGravity = false;
    float scale = 1;
private:
    
};

#endif /* defined(__HEIGVD_InfoGR_Projet__GameObject__) */

//
//  GameObject.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 10.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "GameObject.h"

GameObject::GameObject(TypeGameObjectPos typePos, Vec3f pos, Size3f size, float scale, bool applyGravity)
{
    setPos(typePos, pos);
    this->scale = scale;
    this->size = size;
    this->applyGravity = applyGravity;
}

Vec3f GameObject::getPos(TypeGameObjectPos typePos)
{
    if(typePos == TopLeft) {
        return topLeftPos;
    } else if(typePos == Center) {
        return centerPos;
    } else {
        return Vec3f();
    }
}

void GameObject::setPos(TypeGameObjectPos typePos, Vec3f pos)
{
    if(typePos == TopLeft) {
        topLeftPos = pos;
        centerPos = { pos.getX()+size.x, pos.getY()+size.y, pos.getZ()+size.z };
    } else if(typePos == Center) {
        centerPos = pos;
        topLeftPos = { pos.getX()-size.x, pos.getY()-size.y, pos.getZ()-size.z };
    }
}

Vec3f GameObject::getVelocity()
{
    return velocity;
}

void GameObject::setVelocity(Vec3f _velocity)
{
    velocity = _velocity;
}

void GameObject::move(float speed)
{
    if(applyGravity) {
        velocity[1] -= GRAVITY*0.01;
    }
    
    topLeftPos += speed * velocity;
    centerPos += speed * velocity;
    /*topLeftPos += velocity * speed;
    centerPos += velocity * speed;*/
}

bool GameObject::detectCollision(GameObject &obj2)
{
    // Collision sur l'axe X ?
    bool collisionX = topLeftPos.getX() + size.x >= obj2.topLeftPos.getX() &&
    obj2.topLeftPos.getX() + obj2.size.x >= topLeftPos.getX();
    
    // Collision sur l'axe Y ?
    bool collisionY = topLeftPos.getY() + size.y >= obj2.topLeftPos.getY() &&
    obj2.topLeftPos.getY() + obj2.size.y >= topLeftPos.getY();
    
    // Collision sur l'axe Z ?
    bool collisionZ = topLeftPos.getZ() + size.z >= obj2.topLeftPos.getZ() &&
    obj2.topLeftPos.getZ() + obj2.size.z >= topLeftPos.getZ();
    
    // Collision only if on both axes
    return collisionX && collisionY && collisionZ;
}

void GameObject::drawCollisionBox()
{
    glPushMatrix();
    glTranslatef(topLeftPos.getX(), topLeftPos.getY(), topLeftPos.getZ());
    //glScaled(scale, scale, scale);
    
    // Face en face de nous
    glBegin(GL_POLYGON);
    glVertex3f(0, 0, 0);
    glVertex3f(0, -size.y, 0);
    glVertex3f(size.x, -size.y, 0);
    glVertex3f(size.x, size.y, 0);
    glEnd();
    
    glPopMatrix();
}
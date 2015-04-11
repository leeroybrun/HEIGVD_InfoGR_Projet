//
//  Snowman.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 10.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "Snowman.h"

Snowman::Snowman(Vec3f pos, float scale, bool applyGravity) : GameObject(Center, pos, Size3f(1*scale, 1.5*scale, 1*scale), scale, applyGravity)
{
    
}

void Snowman::draw() {
    glPushMatrix();
    glTranslatef(centerPos.getX(), centerPos.getY(), centerPos.getZ());
    glScaled(scale, scale, scale);
    
    Game::textures->drawTexture("snow");
    
    // Draw Body
    glTranslatef(0.0f ,-0.25f, 0.0f);
    glutSolidSphere(0.5f,20,20);
    
    // Draw Head
    glTranslatef(0.0f, 0.75f, 0.0f);
    glutSolidSphere(0.25f,20,20);
    
    // Draw Eyes
    glPushMatrix();
    glTranslatef(0.05f, 0.10f, 0.18f);
    glutSolidSphere(0.05f,10,10);
    glTranslatef(-0.1f, 0.0f, 0.0f);
    glutSolidSphere(0.05f,10,10);
    glPopMatrix();
    
    // Draw Nose
    glutSolidCone(0.08f,0.5f,10,2);
    glPopMatrix();
}
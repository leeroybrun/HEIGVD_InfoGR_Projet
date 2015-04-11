//
//  Skydome.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 09.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "Skydome.h"

void Skydome::init()
{
    sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricOrientation(sphere, GLU_INSIDE);
    gluQuadricTexture(sphere, GL_TRUE);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    
    material = new Material(
                               color4(1,1,1, 1),
                               color4(1,1,1, 1),
                               color4(1,1,1, 1),
                               color4(0,0,0, 1),
                               0);
}

void Skydome::draw()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    //glLoadIdentity();
    
    material->apply();
    Game::textures->drawTexture("skydome");
    gluSphere(sphere, 900, 16, 16);
    
    glPopMatrix();
}
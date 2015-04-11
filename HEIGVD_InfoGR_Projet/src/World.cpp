//
//  World.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 09.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "World.h"

void World::init() {
    skydome = new Skydome();
    skydome->init();
}

void World::drawWater()
{
    glPushMatrix();
    Game::textures->drawTexture("water");
    glBegin(GL_QUADS);
    glTexCoord2f(1, 0);
    glVertex3f(1000.0f, 2.0f, -1000.0f);   // Bottom Right
    glTexCoord2f(0, 0);
    glVertex3f(-1000.0f, 2.0f, -1000.0f);  // Bottom Left
    glTexCoord2f(0, 1);
    glVertex3f(-1000.0f, 2.0f, 1000.0f);   // Top Left
    glTexCoord2f(1, 1);
    glVertex3f(1000.0f, 2.0f, 1000.0f);    // Top Right
    glEnd();
    glPopMatrix();
}

void World::drawSkydome()
{
    skydome->draw();
}

void World::drawSnowMan()
{
    glPushMatrix();

    Game::textures->drawTexture("snow");
    
    // Draw Body
    glTranslatef(0.0f ,0.5f, 0.0f);
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

void World::drawRandomObjects()
{
    if(snowmansPos == NULL) {
        snowmansPos = new Vec3f*[NB_SNOWMANS];
        
        int max = 200;
        int min = -200;
        
        for(int i = 0; i < NB_SNOWMANS; i++) {
            float randX = rand()%(max-min + 1) + min;
            float randZ = rand()%(max-min + 1) + min;
            float randY = Game::terrain->getRealHeight(randX, randZ);
            if(randY > 10) { randY -= 5; }
            if(randY > 25) { randY -= 15; }
            
            printf("Snowman(%f; %f; %f)\n", randX, randY, randZ);
            
            snowmansPos[i] = new Vec3f(randX, randY, randZ);
            
            snowmans[i] = new Snowman(Vec3f(randX, randY, randZ), 7, true);
            
            addCollisionObject(snowmans[i]);
        }
    }
    
    for(int i = 0; i < NB_SNOWMANS; i++) {
        snowmans[i]->draw();
        snowmans[i]->drawCollisionBox();
        /*glPushMatrix();
        glTranslatef(snowmansPos[i]->getX(), snowmansPos[i]->getY(), snowmansPos[i]->getZ());
        glScaled(7, 7, 7);
        drawSnowMan();
        glPopMatrix();*/
    }
}

void World::drawFog() {
    GLfloat density = 0.35;
    GLfloat fogColor[4] = {0.5, 0.5, 0.3, 1.0};
    
    glEnable (GL_FOG);
    glFogi (GL_FOG_MODE, GL_EXP);
    glFogfv (GL_FOG_COLOR, fogColor);
    glFogf (GL_FOG_DENSITY, density);
    glHint (GL_FOG_HINT, GL_NICEST);
}

void World::addCollisionObject(GameObject *object)
{
    collObjects.push_back(object);
}

bool World::detectCollisions(GameObject *object)
{
    bool collision = false;
    for(int i = 0; i < collObjects.size(); i++) {
        if(object->detectCollision(*collObjects[i])) {
            collision = true;
        }
    }
    
    return collision;
}
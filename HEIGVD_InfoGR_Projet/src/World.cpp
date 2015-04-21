//
//  World.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 09.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "World.h"

// ------------------------------------------------------------------
//  Classe World
//
//  Cette classe contient la gestion du monde.
//
//  Elle permet de gérer les objets qui apparaissent dans le monde,
//  le skydome, l'eau et de détecter la collision entre un GameObject
//  donné et un des objets du monde.
// ------------------------------------------------------------------

// Initialise le monde
void World::init() {
    skydome = new Skydome();
    skydome->init();
    
    srand(time(0));
}

// Dessine l'eau
void World::drawWater()
{
    int nbTexRepeat = 8;
    glPushMatrix();
    Game::textures->drawTexture("water");
    glBegin(GL_QUADS);
    glTexCoord2f(nbTexRepeat, 0);
    glVertex3f(1000.0f, 2.0f, -1000.0f);   // Bottom Right
    glTexCoord2f(0, 0);
    glVertex3f(-1000.0f, 2.0f, -1000.0f);  // Bottom Left
    glTexCoord2f(0, nbTexRepeat);
    glVertex3f(-1000.0f, 2.0f, 1000.0f);   // Top Left
    glTexCoord2f(nbTexRepeat, nbTexRepeat);
    glVertex3f(1000.0f, 2.0f, 1000.0f);    // Top Right
    glEnd();
    glPopMatrix();
}

// Dessine le skydome
void World::drawSkydome()
{
    skydome->draw();
}

// Affiche aléatoirement des objets dans le monde
void World::drawRandomObjects()
{
    // Si la display list n'a pas encore été créée, on la crée
    if(objListId == 0)
    {
        int max = 200;
        int min = -200;
        
        // On crée aléatoirement des bonhommes de neige
        for(int i = 0; i < NB_SNOWMANS; i++) {
            float randX = rand()%(max-min + 1) + min;
            float randZ = rand()%(max-min + 1) + min;
            float randY = Game::terrain->getHeightAtRealPos(randX, randZ);
            
            snowmans[i] = new Snowman(Vec3f(randX, randY, randZ), 7, 0);
            
            addCollisionObject(snowmans[i]);
            
            snowmans[i]->draw();
        }
        
        // On crée aléatoirement des vaches
        for(int i = 0; i < NB_COWS; i++) {
            float randX = rand()%(max-min + 1) + min;
            float randZ = rand()%(max-min + 1) + min;
            float randY = Game::terrain->getHeightAtRealPos(randX, randZ);
            
            cows[i] = new Cow(Vec3f(randX, randY, randZ), 7, 0);
            
            addCollisionObject(cows[i]);
            
            cows[i]->draw();
        }
        
        // On crée aléatoirement des cerfs
        for(int i = 0; i < NB_DEERS; i++) {
            float randX = rand()%(max-min + 1) + min;
            float randZ = rand()%(max-min + 1) + min;
            float randY = Game::terrain->getHeightAtRealPos(randX, randZ);
            
            deers[i] = new Deer(Vec3f(randX, randY, randZ), 7, 0);
            
            addCollisionObject(deers[i]);
            
            deers[i]->draw();
        }
        
        // Création d'une display list pour l'affichage de ces éléments sur la map
        objListId = glGenLists(1);
        glNewList(objListId, GL_COMPILE);
        
        // On dessine les bonhommes de neige
        for(int i = 0; i < NB_SNOWMANS; i++) {
            snowmans[i]->draw();
        }
        
        // On dessine les vaches
        for(int i = 0; i < NB_COWS; i++) {
            cows[i]->draw();
        }
        
        // On dessine les cerfs
        for(int i = 0; i < NB_DEERS; i++) {
            deers[i]->draw();
        }
        
        glEndList();
    }
    
    // Affichage de la display list
    glCallList(objListId);
}

// On dessine le brouillard
void World::drawFog() {
    GLfloat fogColor[] = {0.7f, 0.7f, 0.7f, 1};
    glFogfv(GL_FOG_COLOR, fogColor);
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, 250.0f);
    glFogf(GL_FOG_END, 1000.0f);
}

// Ajout d'un objet avec lequel il faut gérer les collisions à la liste
void World::addCollisionObject(GameObject *object)
{
    collObjects.push_back(object);
}

// Détection de collision entre un des objets du monde et un objet passé en paramètre
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

// Retourne la liste des objets de collision
std::vector<GameObject*> World::getCollObjects()
{
    return collObjects;
}
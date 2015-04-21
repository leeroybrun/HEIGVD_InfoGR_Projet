//
//  Debug.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 06.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "Debug.h"

// ------------------------------------------------------------------
//  Classe Debug
//
//  Cette classe permet de gérer l'affichage ou non des différentes
//  informations de debug.
// ------------------------------------------------------------------

// ------------------------------------------------------------------
//  Affichage des boites de collision
// ------------------------------------------------------------------

bool Debug::shouldShowCollBoxes()
{
    return _shouldShowCollBoxes;
}

void Debug::setShouldShowCollBoxes(bool isDebug)
{
    _shouldShowCollBoxes = isDebug;
}

void Debug::toggleShouldShowCollBoxes()
{
    _shouldShowCollBoxes = !_shouldShowCollBoxes;
}

// Affichage des boites de collision pour tous les objets du monde
void Debug::showCollBoxes() {
    std::vector<GameObject*> objects = Game::world->getCollObjects();
    
    for(int i = 0; i < objects.size(); i++)
    {
        objects[i]->drawCollisionBox();
    }
}



// ------------------------------------------------------------------
//  Affichage des axes
// ------------------------------------------------------------------

bool Debug::shouldShowAxes()
{
    return _shouldShowAxes;
}

void Debug::setShouldShowAxes(bool isDebug)
{
    _shouldShowAxes = isDebug;
}

void Debug::toggleShouldShowAxes()
{
    _shouldShowAxes = !_shouldShowAxes;
}

void Debug::showAxes() {
    static char label[100];
    
    glPushMatrix();
    
    Game::materials->applyMaterial("black");
    
    Vec3f axesVec = Game::camera->getPosition() + Game::camera->getDirection() * 10;
    
    glTranslatef(axesVec.getX(), axesVec.getY(), axesVec.getZ());
    
    // Axe x
    GlutHelper::renderBitmapString(1, 0, 0, GLUT_BITMAP_HELVETICA_12, "x");
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1, 0.0, 0.0);
    glEnd();
    
    // Axe y
    GlutHelper::renderBitmapString(0, 1, 0, GLUT_BITMAP_HELVETICA_12, "y");
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1, 0.0);
    glEnd();
    
    // Axe z
    GlutHelper::renderBitmapString(0, 0, 1, GLUT_BITMAP_HELVETICA_12, "z");
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1);
    glEnd();
    
    Game::materials->restorePrevMaterial();
    
    glPopMatrix();
}

// ------------------------------------------------------------------
//  Affichage des infos de debug
// ------------------------------------------------------------------

bool Debug::shouldShowDebugInfos()
{
    return _shouldShowDebugInfos;
}

void Debug::setShouldShowDebugInfos(bool isDebug)
{
    _shouldShowDebugInfos = isDebug;
}

void Debug::toggleShouldShowDebugInfos()
{
    _shouldShowDebugInfos = !_shouldShowDebugInfos;
}

void Debug::showDebugInfos()
{
    Game::scrInfos->set("01_camX", "Camera X : %f", Game::camera->getX());
    Game::scrInfos->set("02_camY", "Camera Y : %f", Game::camera->getY());
    Game::scrInfos->set("03_camZ", "Camera Z : %f", Game::camera->getZ());
    
    Game::scrInfos->set("09_sep", "------------------------");
    
    Game::scrInfos->set("10_terrW", "Terrain width: %d", Game::terrain->width());
    Game::scrInfos->set("11_terrL", "Terrain length: %d", Game::terrain->length());
    Game::scrInfos->set("12_terrScale", "Terrain scale: %f", Game::terrain->getScale());
    
    Game::scrInfos->set("13_sep", "------------------------");
    
    Game::scrInfos->set("14_fps", "FPS: %d", Game::stats->getFPS());
    
    Game::scrInfos->set("16_sep", "------------------------");
    
    Game::scrInfos->set("17_nbDays", "Jours passes: %d", Game::stats->getNbDays());
    
    std::string dayPeriod = "jour";
    
    if(Game::stats->getDayPeriod() == 1)
    {
        dayPeriod = "coucher de soleil";
    }
    else if(Game::stats->getDayPeriod() == 2)
    {
        dayPeriod = "nuit";
    }
    else if(Game::stats->getDayPeriod() == 3)
    {
        dayPeriod = "leve de soleil";
    }
    
    Game::scrInfos->set("18_dayPeriod", "Periode de la journee: %s", dayPeriod.c_str());
    
    Game::materials->applyMaterial("black");
    
    Game::scrInfos->draw();
    
    Game::materials->restorePrevMaterial();
}
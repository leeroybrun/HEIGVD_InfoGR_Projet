//
//  Debug.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 06.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "Debug.h"

// Utile pour dessiner les noms des axes
void dessinChar (char *s)      // Dessine un bitmap HELVETICA_12
{
    unsigned int i;
    for (i = 0; i < strlen(s); i++)
        glutBitmapCharacter (GLUT_BITMAP_HELVETICA_12, s[i]);
};

Debug::Debug() {
    _isDebug = false;
}

Debug::Debug(bool isDebug) {
    _isDebug = isDebug;
}

bool Debug::isDebug() {
    return _isDebug;
}

void Debug::setIsDebug(bool isDebug) {
    _isDebug = isDebug;
}

void Debug::showAxes() {
    static char label[100];
    
    glPushMatrix();
    
    Vec3f axesVec = Game::camera->getPosition() + Game::camera->getDirection() * 10;
    
    glTranslatef(axesVec.getX(), axesVec.getY(), axesVec.getZ());
    
    // Axe x
    sprintf (label, "x");  // texte
    glRasterPos3d(1, 0.0, 0.0);
    dessinChar (label);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1, 0.0, 0.0);
    glEnd();
    
    // Axe y
    sprintf (label, "y");  // texte
    glRasterPos3d(0.0, 1, 0.0);
    dessinChar (label);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1, 0.0);
    glEnd();
    
    // Axe z
    sprintf (label, "z");  // texte
    glRasterPos3d(0.0, 0.0, 1);
    dessinChar (label);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1);
    glEnd();
    
    glPopMatrix();
}

void Debug::showDebugInfos()
{
    Game::scrInfos->set("01_camX", "Camera X : %f", Game::camera->getX());
    Game::scrInfos->set("02_camY", "Camera Y : %f", Game::camera->getY());
    Game::scrInfos->set("03_camZ", "Camera Z : %f", Game::camera->getZ());
    //Game::scrInfos->set("04_camAngle", "Camera angle : %f", Game::camera->getAngle());
    
    //Game::scrInfos->set("05_sep1", "------------------------");
    
    //Game::scrInfos->set("06_camTerrX", "Terrain x: %f", terrainX);
    //Game::scrInfos->set("07_camTerrY", "Terrain y: %f", terrainY);
    //Game::scrInfos->set("08_camTerrZ", "Terrain z: %f", terrainZ);
    
    Game::scrInfos->set("09_sep", "------------------------");
    
    Game::scrInfos->set("10_terrW", "Terrain width: %d", Game::terrain->width());
    Game::scrInfos->set("11_terrL", "Terrain length: %d", Game::terrain->length());
    Game::scrInfos->set("12_terrScale", "Terrain scale: %f", Game::terrain->getScale());
    
    Game::scrInfos->set("13_sep", "------------------------");
    
    Game::scrInfos->set("14_fps", "FPS: %d", Game::stats->getFPS());
    
    Game::scrInfos->drawScreenInfos(Game::window->width, Game::window->height);
}
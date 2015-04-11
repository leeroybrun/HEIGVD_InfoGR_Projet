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

void Debug::showAxes(float baseX = 0, float baseY = 0, float baseZ = 0) {
    static char label[100];
    
    // Axe x
    sprintf (label, "x");  // texte
    glRasterPos3d(baseX+2, baseY+0.0, baseZ+0.0);
    dessinChar (label);
    glBegin(GL_LINES);
    glVertex3f(baseX+0.0, baseY+0.0, baseZ+0.0);
    glVertex3f(baseX+2, baseY+0.0, baseZ+0.0);
    glEnd();
    
    // Axe y
    sprintf (label, "y");  // texte
    glRasterPos3d(baseX+0.0, baseY+2, baseZ+0.0);
    dessinChar (label);
    glBegin(GL_LINES);
    glVertex3f(baseX+0.0, baseY+0.0, baseZ+0.0);
    glVertex3f(baseX+0.0, baseY+2, baseZ+0.0);
    glEnd();
    
    // Axe z
    sprintf (label, "z");  // texte
    glRasterPos3d(baseX+0.0, baseY+0.0, baseZ+2);
    dessinChar (label);
    glBegin(GL_LINES);
    glVertex3f(baseX+0.0, baseY+0.0, baseZ+0.0);
    glVertex3f(baseX+0.0, baseY+0.0, baseZ+2);
    glEnd();
}
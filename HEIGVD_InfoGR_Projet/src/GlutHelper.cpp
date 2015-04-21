//
//  GlutHelper.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 14.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "GlutHelper.h"

// ------------------------------------------------------------------
//  Classe GlutHelper
//
//  Cette classe contient des méthodes statiques qui sont de grandes
//  utilité lorsque l'on travaille avec glut/openGL.
// ------------------------------------------------------------------

void GlutHelper::renderBitmapString(float x, float y, void *font, std::string str) {
    glRasterPos2f(x, y);
    for (unsigned int i = 0; i<str.length(); i++) {
        glutBitmapCharacter(font, str[i]);
    }
}

void GlutHelper::renderBitmapString(float x, float y, float z, void *font, std::string str) {
    glRasterPos3f(x, y, z);
    for (unsigned int i = 0; i<str.length(); i++) {
        glutBitmapCharacter(font, str[i]);
    }
}

void GlutHelper::renderBitmapString(float x, float y, void *font, char *string) {
    char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void GlutHelper::renderBitmapString(float x, float y, float z, void *font, char *string) {
    char *c;
    glRasterPos3f(x, y, z);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}
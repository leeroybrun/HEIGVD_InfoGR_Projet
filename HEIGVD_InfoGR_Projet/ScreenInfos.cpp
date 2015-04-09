//
//  screenInfos.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 17.02.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "ScreenInfos.h"

// http://www.lighthouse3d.com/tutorials/glut-tutorial/bitmap-fonts-and-orthogonal-projections/

void renderBitmapString(
                        float x,
                        float y,
                        void *font,
                        std::string str) {
    
    glRasterPos2f(x, y);
    for (unsigned int i = 0; i<str.length(); i++) {
        glutBitmapCharacter(font, str[i]);
    }
}

void renderBitmapString(
                        float x,
                        float y,
                        void *font,
                        char *string) {
    
    char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void renderBitmapString(
                        float x,
                        float y,
                        float z,
                        void *font,
                        char *string) {
    
    char *c;
    glRasterPos3f(x, y,z);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void ScreenInfos::setOrthographicProjection(int w, int h) {
    
    // switch to projection mode
    glMatrixMode(GL_PROJECTION);
    
    // save previous matrix which contains the
    //settings for the perspective projection
    glPushMatrix();
    
    // reset matrix
    glLoadIdentity();
    
    // set a 2D orthographic projection
    gluOrtho2D(0, w, h, 0);
    
    // switch back to modelview mode
    glMatrixMode(GL_MODELVIEW);
}

void ScreenInfos::restorePerspectiveProjection() {
    
    glMatrixMode(GL_PROJECTION);
    // restore previous projection matrix
    glPopMatrix();
    
    // get back to modelview mode
    glMatrixMode(GL_MODELVIEW);
}

void ScreenInfos::set(std::string key, const char *format, ...) {
    char str[100];
    std::string str2;
    
    va_list argptr;
    va_start(argptr, format);
    vsprintf(str, format, argptr);
    str2 = str;
    va_end(argptr);
    
    if(infos.insert(std::make_pair(key, str2)).second == false) {
        infos[key] = str2;
    }
}

void ScreenInfos::drawScreenInfos(int w, int h) {
    setOrthographicProjection(w, h);
    
    int x = 5;
    int y = 15;
    
    glPushMatrix();
    glLoadIdentity();
    
    typedef std::map<std::string, std::string>::iterator it_type;
    for(it_type iterator = infos.begin(); iterator != infos.end(); iterator++) {
        renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_12, iterator->second);
        y += 20;
    }
    
    
    glPopMatrix();
    
    restorePerspectiveProjection();
}
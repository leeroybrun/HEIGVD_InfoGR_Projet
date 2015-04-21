//
//  color4.h
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 20.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#ifndef HEIGVD_InfoGR_Projet_color4_h
#define HEIGVD_InfoGR_Projet_color4_h

struct color4f {
    color4f(GLfloat _r = 0, GLfloat _g = 0, GLfloat _b = 0, GLfloat _a = 1): r(_r), g(_g), b(_b), a(_a){};
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
};

#endif

//
//  Material.h
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 09.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#ifndef __HEIGVD_InfoGR_Projet__Material__
#define __HEIGVD_InfoGR_Projet__Material__

#include "main.h"

struct color4 {
    color4(GLfloat _r = 0, GLfloat _g = 0, GLfloat _b = 0, GLfloat _a = 1): r(_r), g(_g), b(_b), a(_a){};
    GLfloat r;
    GLfloat g;
    GLfloat b;
    GLfloat a;
};

class Material
{
private:
    color4 ambient;
    color4 diffuse;
    color4 specular;
    color4 emission;
    float  shininess;
    
public:
    Material();
    Material(color4 _ambient,
             color4 _diffuse,
             color4 _specular,
             color4 _emission,
             float _shininess );
    
    void apply();
    
};

#endif /* defined(__HEIGVD_InfoGR_Projet__Material__) */

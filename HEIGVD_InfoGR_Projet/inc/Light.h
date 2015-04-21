//
//  Light.h
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 09.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#ifndef __HEIGVD_InfoGR_Projet__Light__
#define __HEIGVD_InfoGR_Projet__Light__

#include "main.h"
#include <stdexcept>
#include "vec3f.h"
#include "color4f.h"

struct LightPos {
    LightPos(GLfloat _x = 0, GLfloat _y = 0, GLfloat _z = 0, GLfloat _t = 1): x(_x), y(_y), z(_z), t(_t){};
    GLfloat x;
    GLfloat y;
    GLfloat z;
    GLfloat t;
};

class Light
{
private:
    int num = 0;
    color4f ambient;
    color4f diffuse;
    color4f specular;
    LightPos pos;
    
public:
    Light();
    Light(int _num,
          color4f _ambient,
          color4f _diffuse,
          color4f _specular,
          LightPos _pos);
    
    void setPos(LightPos _pos);
    void enable();
    void disable();
    void apply();
    
};

#endif /* defined(__HEIGVD_InfoGR_Projet__Light__) */

//
//  Snowman.h
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 10.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#ifndef __HEIGVD_InfoGR_Projet__Cow__
#define __HEIGVD_InfoGR_Projet__Cow__

#include "main.h"
#include "vec3f.h"
#include "glm.h"
#include "Game.h"
#include "Textures.h"
#include "GameObject.h"

class Cow : public GameObject
{
public:
    Cow(Vec3f pos, float scale, float gravity);
    void draw();
private:
    GLMmodel *model = NULL;
};

#endif /* defined(__HEIGVD_InfoGR_Projet__Cow__) */

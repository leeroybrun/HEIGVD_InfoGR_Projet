//
//  Snowman.h
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 10.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#ifndef __HEIGVD_InfoGR_Projet__Snowman__
#define __HEIGVD_InfoGR_Projet__Snowman__

#include "main.h"
#include "vec3f.h"
#include "Game.h"
#include "Textures.h"
#include "GameObject.h"

class Snowman : public GameObject
{
public:
    Snowman(Vec3f pos, float scale, bool applyGravity);
    void draw();
private:
};

#endif /* defined(__HEIGVD_InfoGR_Projet__Snowman__) */

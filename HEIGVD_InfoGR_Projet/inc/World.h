//
//  World.h
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 09.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#ifndef __HEIGVD_InfoGR_Projet__World__
#define __HEIGVD_InfoGR_Projet__World__

#include "main.h"
#include <vector>
#include "Game.h"
#include "Material.h"
#include "Textures.h"
#include "Skydome.h"
#include "Terrain.h"
#include "GameObject.h"
#include "Snowman.h"

#define NB_SNOWMANS 10

class World
{
private:
    Skydome *skydome;
    Vec3f **snowmansPos = NULL;
    Snowman *snowmans[NB_SNOWMANS];
    std::vector<GameObject*> collObjects;
public:
    void init();
    void drawWater();
    void drawSnowMan();
    void drawRandomObjects();
    void drawSkydome();
    void drawFog();
    
    void addCollisionObject(GameObject *object);
    bool detectCollisions(GameObject *object);
};

#endif /* defined(__HEIGVD_InfoGR_Projet__World__) */

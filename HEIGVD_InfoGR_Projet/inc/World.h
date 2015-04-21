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
#include <ctime>
#include "Game.h"
#include "Material.h"
#include "Textures.h"
#include "Skydome.h"
#include "Terrain.h"
#include "GameObject.h"
#include "Snowman.h"
#include "Cow.h"
#include "Deer.h"

#define NB_SNOWMANS 10
#define NB_COWS 1
#define NB_DEERS 1

class World
{
private:
    Skydome *skydome;
    Vec3f **snowmansPos = NULL;
    Snowman *snowmans[NB_SNOWMANS];
    
    Vec3f **cowsPos = NULL;
    Cow *cows[NB_COWS];
    
    Vec3f **deersPos = NULL;
    Deer *deers[NB_DEERS];
    
    GLuint objListId = 0;
    
    std::vector<GameObject*> collObjects;
public:
    void init();
    void drawWater();
    void drawRandomObjects();
    void drawSkydome();
    void drawFog();
    
    void addCollisionObject(GameObject *object);
    bool detectCollisions(GameObject *object);
    
    std::vector<GameObject*> getCollObjects();
};

#endif /* defined(__HEIGVD_InfoGR_Projet__World__) */

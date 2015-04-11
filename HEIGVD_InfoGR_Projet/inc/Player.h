//
//  Player.h
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 10.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#ifndef __HEIGVD_InfoGR_Projet__Player__
#define __HEIGVD_InfoGR_Projet__Player__

#include "main.h"
#include "Game.h"
#include "Camera.h"
#include "Terrain.h"
#include "Snowman.h"
#include "World.h"

#define PLAYER_INIT_THROW_SPEED 2

class Player
{
private:
    Snowman *snowman;
    float throwSpeed = PLAYER_INIT_THROW_SPEED;
public:
    void init();
    void drawThrownObjects();
    void throwSnowman();
    
    void pressKey(unsigned char key, int xx, int yy);
    void releaseKey(unsigned char key, int xx, int yy);
};

#endif /* defined(__HEIGVD_InfoGR_Projet__Player__) */

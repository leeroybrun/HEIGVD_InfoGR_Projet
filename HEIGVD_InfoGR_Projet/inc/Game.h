//
//  Game.h
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 09.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#ifndef __HEIGVD_InfoGR_Projet__Game__
#define __HEIGVD_InfoGR_Projet__Game__

#include "main.h"

#define WIN_W   800
#define WIN_H   600

#define TERRAIN_SCALE_FACTOR   500
#define TERRAIN_HEIGHT_FACTOR   60

#define ROOT_PATH "/Users/leeroybrun/Google Drive/HEIG-VD/Cours/2014-2015/Infographie/Exercices/HEIGVD_InfoGR_Projet/HEIGVD_InfoGR_Projet/"
#define ABSOLUTE_PATH(x) ROOT_PATH x

class Textures;
class Camera;
class Terrain;
class ScreenInfos;
class Debug;
class Stats;
class World;
class Keyboard;
class Player;
class Materials;
class Scores;

struct Window
{
    Window(int w, int h): width(w), height(h){};
    int width = WIN_W;
    int height = WIN_H;
};

class Game
{
private:
    
public:
    static Textures *textures;
    static Camera *camera;
    static Terrain *terrain;
    static ScreenInfos *scrInfos;
    static Debug *debug;
    static Stats *stats;
    static World *world;
    static Window *window;
    static Keyboard *keyboard;
    static Player *player;
    static Materials *materials;
    static Scores *scores;
};

#endif /* defined(__HEIGVD_InfoGR_Projet__Game__) */

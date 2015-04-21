//
//  Game.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 09.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

// ------------------------------------------------------------------
//  Classe Game
//
//  Cette classe contient des propriétés statiques vers tous les
//  objets importants du jeu. Elle permet d'accéder à l'instance
//  en cours de chaque classe du jeu.
// ------------------------------------------------------------------

#include "Game.h"

Textures *Game::textures;
Terrain *Game::terrain;
Camera *Game::camera;
ScreenInfos *Game::scrInfos;
Debug *Game::debug;
Stats *Game::stats;
World *Game::world;
Window *Game::window;
Keyboard *Game::keyboard;
Player *Game::player;
Materials *Game::materials;
Scores *Game::scores;

//
//  keyboard.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 17.02.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "keyboard.h"

// ------------------------------------------------------------------
//  Classe Keyboard
//
//  Cette classe contient la gestion des touches clavier pressées.
//
//  Elle permet de savoir si une touche du clavier est actuellement
//  pressée ou non.
// ------------------------------------------------------------------

Keyboard::Keyboard()
{
    
}

void Keyboard::pressKey(int key, int xx, int yy) {
    keys[key] = true;
}

void Keyboard::releaseKey(int key, int x, int y) {
    keys[key] = false;
}

bool Keyboard::getKeyState(int key)
{
    return keys[key];
}

void Keyboard::pressSpeKey(int key, int xx, int yy) {
    speKeys[key] = true;
}

void Keyboard::releaseSpeKey(int key, int x, int y) {
    speKeys[key] = false;
}

bool Keyboard::getSpeKeyState(int key)
{
    return speKeys[key];
}
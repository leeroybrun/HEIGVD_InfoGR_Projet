//
//  keyboard.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 17.02.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "keyboard.h"


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
//
//  keyboard.h
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 17.02.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#ifndef __HEIGVD_InfoGR_Projet__keyboard__
#define __HEIGVD_InfoGR_Projet__keyboard__

#include "main.h"

class Keyboard
{
private:
    bool keys[1024] = { false };
public:
    Keyboard();
    void pressKey(int key, int xx, int yy);
    void releaseKey(int key, int x, int y);
    bool getKeyState(int key);
};

#endif /* defined(__HEIGVD_InfoGR_Projet__keyboard__) */

//
//  keyboard.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 17.02.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "keyboard.h"

void processNormalKeys(unsigned char key, int x, int y) {
    // ESCAPE
    if (key == 27) {
        exit(0);
    }
}

void processSpecialKeys(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_F1 :
            
            break;
    }
}
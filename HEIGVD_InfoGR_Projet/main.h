//
//  main.h
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 06.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#ifndef HEIGVD_InfoGR_Projet_main_h
#define HEIGVD_InfoGR_Projet_main_h

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>

#define WIN_W   800
#define WIN_H   600

#include "Material.h"
#include "Terrain.h"
#include "Camera.h"
#include "Menu.h"
#include "Keyboard.h"
#include "ScreenInfos.h"
#include "Debug.h"
#include "Textures.h"

#endif

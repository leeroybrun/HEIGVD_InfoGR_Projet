//
//  camera.h
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 17.02.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#ifndef __HEIGVD_InfoGR_Projet__camera__
#define __HEIGVD_InfoGR_Projet__camera__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <GLUT/GLUT.h>
#include <cmath>

void camComputePos();
void camDefineLookAt();
void camPressKey(int key, int xx, int yy);
void camReleaseKey(int key, int x, int y);

#endif /* defined(__HEIGVD_InfoGR_Projet__camera__) */

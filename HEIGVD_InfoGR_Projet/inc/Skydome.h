//
//  Skydome.h
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 09.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#ifndef __HEIGVD_InfoGR_Projet__Skydome__
#define __HEIGVD_InfoGR_Projet__Skydome__

#include "main.h"
#include "Game.h"
#include "Textures.h"
#include "Camera.h"
#include "Material.h"

class Skydome
{
private:
    GLUquadricObj *sphere;
    Material *material;
public:
    void init();
    
    void draw();
};

#endif /* defined(__HEIGVD_InfoGR_Projet__Skydome__) */

//
//  Material.h
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 09.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#ifndef __HEIGVD_InfoGR_Projet__Material__
#define __HEIGVD_InfoGR_Projet__Material__

#include "main.h"
#include "color4f.h"

class Material
{
private:
    color4f ambient;
    color4f diffuse;
    color4f specular;
    color4f emission;
    float  shininess;
    
public:
    Material();
    Material(color4f _ambient,
             color4f _diffuse,
             color4f _specular,
             color4f _emission,
             float _shininess );
    
    void apply();
    
};

#endif /* defined(__HEIGVD_InfoGR_Projet__Material__) */

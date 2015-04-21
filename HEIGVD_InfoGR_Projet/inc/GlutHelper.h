//
//  GlutHelper.h
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 14.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#ifndef HEIGVD_InfoGR_Projet_GlutHelper_h
#define HEIGVD_InfoGR_Projet_GlutHelper_h

#include "main.h"

class GlutHelper
{
public:
    static void renderBitmapString(float x, float y, void *font, std::string str);
    
    void renderBitmapString(float x, float y, float z, void *font, std::string str);
    
    static void renderBitmapString(float x, float y, void *font, char *string);
    
    static void renderBitmapString(float x, float y, float z, void *font, char *string);
};

#endif

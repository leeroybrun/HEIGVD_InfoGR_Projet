//
//  screenInfos.h
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 17.02.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#ifndef __HEIGVD_InfoGR_Projet__screenInfos__
#define __HEIGVD_InfoGR_Projet__screenInfos__

#include "main.h"
#include "Game.h"
#include "Materials.h"
#include "GlutHelper.h"
#include <map>

class ScreenInfos
{
private:
    
    std::map<std::string, std::string> infos;
    
public:
    ScreenInfos(){};
    ~ScreenInfos(){};
    
    void setOrthographicProjection();
    void restorePerspectiveProjection();
    
    void set(std::string key, const char *format, ...) ;
    
    void draw();

};

#endif /* defined(__HEIGVD_InfoGR_Projet__screenInfos__) */

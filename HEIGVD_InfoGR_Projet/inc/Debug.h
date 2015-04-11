//
//  Debug.h
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 06.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#ifndef __HEIGVD_InfoGR_Projet__Debug__
#define __HEIGVD_InfoGR_Projet__Debug__

#include "main.h"
#include "Game.h"
#include "Camera.h"
#include "ScreenInfos.h"
#include "Terrain.h"

class Debug
{
private:
    bool _isDebug = false;
    
public:
    Debug();
    Debug(bool isDebug);
    
    bool isDebug();
    void setIsDebug(bool isDebug);
    
    void showAxes();
    
    void showDebugInfos();
};

#endif /* defined(__HEIGVD_InfoGR_Projet__Debug__) */

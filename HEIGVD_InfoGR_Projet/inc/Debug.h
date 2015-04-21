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
#include <vector>
#include "Game.h"
#include "Camera.h"
#include "World.h"
#include "ScreenInfos.h"
#include "Terrain.h"
#include "GameObject.h"

class Debug
{
private:
    bool _shouldShowCollBoxes = false;
    bool _shouldShowAxes = false;
    bool _shouldShowDebugInfos = false;
    
public:
    bool shouldShowCollBoxes();
    void setShouldShowCollBoxes(bool isDebug);
    void toggleShouldShowCollBoxes();
    
    bool shouldShowAxes();
    void setShouldShowAxes(bool isDebug);
    void toggleShouldShowAxes();
    
    bool shouldShowDebugInfos();
    void setShouldShowDebugInfos(bool isDebug);
    void toggleShouldShowDebugInfos();
    
    void showCollBoxes();
    void showAxes();
    void showDebugInfos();
};

#endif /* defined(__HEIGVD_InfoGR_Projet__Debug__) */

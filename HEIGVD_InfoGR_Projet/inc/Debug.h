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

class Debug
{
private:
    bool _isDebug = false;
    
public:
    Debug();
    Debug(bool isDebug);
    
    bool isDebug();
    void setIsDebug(bool isDebug);
    
    void showAxes(float baseX, float baseY, float baseZ);
};

#endif /* defined(__HEIGVD_InfoGR_Projet__Debug__) */

//
//  Stats.h
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 09.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#ifndef __HEIGVD_InfoGR_Projet__Stats__
#define __HEIGVD_InfoGR_Projet__Stats__

#include "main.h"

class Stats
{
private:
    int frameCount, currentTime, previousTime, fps, deltaTime;
public:
    int getFPS(){ return fps; };
    int getDeltaTime(){ return deltaTime; };
    void computeStats();
};

#endif /* defined(__HEIGVD_InfoGR_Projet__Stats__) */

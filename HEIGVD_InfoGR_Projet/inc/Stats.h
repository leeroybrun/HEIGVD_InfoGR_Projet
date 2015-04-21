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
    int frameCount, currentTime, previousTime, fps, deltaTime, nbDays;
    int dayPeriod; // 0 = jour, 1 = coucher soleil, 2 = nuit, 3 = levé de soleil
public:
    void setDayPeriod(int _dayPeriod){ dayPeriod = _dayPeriod; };
    int getDayPeriod(){ return dayPeriod; };
    
    void setNbDays(int _nbDays){ nbDays = _nbDays; };
    int getNbDays(){ return nbDays; };
    
    int getFPS(){ return fps; };
    int getCurrentTime(){ return currentTime; };
    int getDeltaTime(){ return deltaTime; };
    void computeStats();
};

#endif /* defined(__HEIGVD_InfoGR_Projet__Stats__) */

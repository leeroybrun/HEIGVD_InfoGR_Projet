//
//  Stats.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 09.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "Stats.h"

void Stats::computeStats()
{
    //  Increase frame count
    frameCount++;
    
    //  Get the number of milliseconds since glutInit called
    //  (or first call to glutGet(GLUT ELAPSED TIME)).
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    
    //  Calculate time passed (in seconds)
    deltaTime = (currentTime - previousTime) / 1000;
    
    if(deltaTime > 1)
    {
        //  calculate the number of frames per second
        fps = frameCount / deltaTime;
        
        //  Set time
        previousTime = currentTime;
        
        //  Reset frame count
        frameCount = 0;
    }
}
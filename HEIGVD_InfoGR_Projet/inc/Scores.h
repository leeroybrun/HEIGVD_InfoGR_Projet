//
//  Scores.h
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 13.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#ifndef HEIGVD_InfoGR_Projet_Scores_h
#define HEIGVD_InfoGR_Projet_Scores_h

#include "main.h"
#include "Game.h"
#include "Stats.h"
#include "ScreenInfos.h"
#include "Materials.h"
#include "GlutHelper.h"

#define SCORES_DISPLAY_TIME 1500

class Scores
{
private:
    int points = 0;
    
    int drawScoresTextStartTime = 0;
    std::string scoresText = "";
public:
    void init();
    void addPoints(int newPoints);
    void drawScoresText(std::string text);
    void draw();
};

#endif

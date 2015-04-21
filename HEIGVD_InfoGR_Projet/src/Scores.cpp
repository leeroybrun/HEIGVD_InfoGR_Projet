//
//  Scores.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 13.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "Scores.h"

// ------------------------------------------------------------------
//  Classe Scores
//
//  Cette classe permet de gérer le calcul et l'affichage des scores
//  du joueur. Lorsque l'on ajoute des points au score, un texte
//  s'affiche automatiquement au milieu de l'écran avec le nombre
//  de points que l'utilisateur a gagné.
// ------------------------------------------------------------------

void Scores::init()
{
    points = 0;
    drawScoresTextStartTime = 0;
    scoresText = "";
}

void Scores::addPoints(int newPoints)
{
    points += newPoints;
    
    drawScoresText("+" + std::to_string(newPoints) + " points!");
}

void Scores::draw()
{
    Game::scrInfos->setOrthographicProjection();
    
    glPushMatrix();
    glLoadIdentity();
    
    Game::materials->applyMaterial("black");
    
    GlutHelper::renderBitmapString(Game::window->width-100, Game::window->height-50, GLUT_BITMAP_HELVETICA_12, "Points: "+ std::to_string(points));
    
    if(drawScoresTextStartTime != 0) {
        if(Game::stats->getCurrentTime() > drawScoresTextStartTime + SCORES_DISPLAY_TIME)
        {
            drawScoresTextStartTime = 0;
            scoresText = "";
        } else {
            GlutHelper::renderBitmapString(Game::window->width/2-50, Game::window->height/2, GLUT_BITMAP_HELVETICA_18, scoresText);
        }
    }
    
    glPopMatrix();
    
    Game::scrInfos->restorePerspectiveProjection();
}

void Scores::drawScoresText(std::string text)
{
    drawScoresTextStartTime = Game::stats->getCurrentTime();
    scoresText = text;
}
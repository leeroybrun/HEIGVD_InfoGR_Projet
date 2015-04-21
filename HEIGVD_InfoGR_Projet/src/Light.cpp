//
//  Light.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 09.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "Light.h"

// ------------------------------------------------------------------
//  Classe Light
//
//  Cette classe permet de gérer une lumière et de l'appliquer
//  facilement à la scène.
// ------------------------------------------------------------------

// Initialise une nouvelle lumière avec les valeurs par défaut
Light::Light()
{
    Light(0, color4f(0.2, 0.2, 0.2, 1.0), color4f(0.8, 0.8, 0.8, 1.0), color4f(0.0, 0.0, 0.0, 1.0), LightPos(0, 30, 0, 0));
}

// Initialise une nouvelle lumière avec les valeurs passées en paramètre
Light::Light(int _num,
             color4f _ambient,
             color4f _diffuse,
             color4f _specular,
             LightPos _pos) : num(_num), ambient(_ambient), diffuse(_diffuse), specular(_specular), pos(_pos)
{
    if(_num < 0 || _num > 8) {
        throw std::invalid_argument("Un no de lumiere doit etre compris entre 0 et 8");
    }
}

void Light::setPos(LightPos _pos){
    pos = _pos;
}

void Light::enable(){
    glEnable(GL_LIGHT0+num);
}
void Light::disable(){
    glDisable(GL_LIGHT0+num);
}

// Applique la lumière
void Light::apply()
{
    glLightfv(GL_LIGHT0+num, GL_AMBIENT, &(ambient.r));
    glLightfv(GL_LIGHT0+num, GL_DIFFUSE,  &(diffuse.r));
    glLightfv(GL_LIGHT0+num, GL_SPECULAR, &(specular.r));
    glLightfv(GL_LIGHT0+num, GL_POSITION, &(pos.x));
}
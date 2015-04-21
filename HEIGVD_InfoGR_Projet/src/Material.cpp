//
//  Material.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 09.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "Material.h"

// ------------------------------------------------------------------
//  Classe Material
//
//  Cette classe contient la gestion d'un material.
//
//  Elle permet de définir un material et de l'appliquer facilement
//  à une scène.
// ------------------------------------------------------------------

// Initialise un nouveau material avec les valeurs par défaut
Material::Material()
{
    Material(color4f(0.2, 0.2, 0.2, 1.0), color4f(0.8, 0.8, 0.8, 1.0), color4f(0.0, 0.0, 0.0, 1.0), color4f(0.0, 0.0, 0.0, 1.0), 0);
}

// Initialise un nouveau material avec les valeurs passées en paramètre
Material::Material(color4f _ambient,
                   color4f _diffuse,
                   color4f _specular,
                   color4f _emission,
                   float _shininess) : ambient(_ambient), diffuse(_diffuse), specular(_specular), emission(_emission), shininess(_shininess)
{}

// Applique le matérial
void Material::apply()
{    
    glMaterialfv(GL_FRONT, GL_AMBIENT, &(ambient.r));
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &(diffuse.r));
    glMaterialfv(GL_FRONT, GL_SPECULAR, &(specular.r));
    glMaterialfv(GL_FRONT, GL_EMISSION, &(emission.r) );
    glMaterialf (GL_FRONT, GL_SHININESS, shininess);
}
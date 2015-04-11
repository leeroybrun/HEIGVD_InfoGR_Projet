//
//  Material.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 09.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "Material.h"

Material::Material()
{
    Material(color4(0.2, 0.2, 0.2, 1.0), color4(0.8, 0.8, 0.8, 1.0), color4(0.0, 0.0, 0.0, 1.0), color4(0.0, 0.0, 0.0, 1.0), 0);
}

Material::Material(color4 _ambient,
                   color4 _diffuse,
                   color4 _specular,
                   color4 _emission,
                   float _shininess) : ambient(_ambient), diffuse(_diffuse), specular(_specular), emission(_emission), shininess(_shininess)
{}

void Material::apply()
{    
    glMaterialfv(GL_FRONT, GL_AMBIENT, &(ambient.r));
    glMaterialfv(GL_FRONT, GL_DIFFUSE, &(diffuse.r));
    glMaterialfv(GL_FRONT, GL_SPECULAR, &(specular.r));
    glMaterialfv(GL_FRONT, GL_EMISSION, &(emission.r) );
    glMaterialf (GL_FRONT, GL_SHININESS, shininess);
}
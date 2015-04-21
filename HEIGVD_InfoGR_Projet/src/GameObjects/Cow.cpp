//
//  Cow.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 10.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "Cow.h"

// ------------------------------------------------------------------
//  Classe Cow
//
//  Cette classe contient la gestion d'une vache.
//
//  Celle-ci est chargée depuis un fichier .obj grâce à la librairie
//  GLM.
//
//  Elle dérive de GameObject pour la gestion du mouvement et des
//  collisions, et ne contient qu'une seule méthode spécifique
//  draw() pour l'affichage de l'objet.
// ------------------------------------------------------------------

Cow::Cow(Vec3f pos, float scale, float gravity) : GameObject(Center, pos, Size3f(1, 1.5, 1), scale, gravity)
{
    // Charge une vache depuis le fichier .obj
    model = glmReadOBJ(ABSOLUTE_PATH("data/obj/cow/cartoon_cow.obj"));
    if (!model) {
        printf("Impossible de lire le modèle '%s'...\n", ABSOLUTE_PATH("data/obj/cow/cartoon_cow.obj"));
        exit(0);
    }
    glmUnitize(model);
    glmVertexNormals(model, 90.0, GL_TRUE);
}

// Dessine une vache
void Cow::draw() {
    glPushMatrix();
    if (model)
    {
        glTranslatef(centerPos.getX(), centerPos.getY(), centerPos.getZ());
        glScaled(scale, scale, scale);
        glmDraw(model, GLM_NONE | GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE);
    }
    glPopMatrix();
}
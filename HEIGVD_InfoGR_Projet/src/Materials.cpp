//
//  Texture.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 08.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "Materials.h"

// ------------------------------------------------------------------
//  Classe Materials
//
//  Cette classe contient la gestion des matériaux du jeu.
//
//  Elle permet de définir différents matériaux et de leur donner un
//  nom. On peut ensuite facilement appliquer un material d'après
//  son nom.
//
//  Elle permet également de restaurer le matériel précédent facilement
//  après l'application d'un nouveau matériel.
// ------------------------------------------------------------------

// Initialise la classe de matériaux
void Materials::init()
{
    
}

// Ajoute un material à la liste
void Materials::addMaterial(std::string name, Material *material)
{
    // Ajout de l'objet à la map des matières
    this->materials.insert(std::make_pair(name, material));
}

// Applique un material d'après le nom
void Materials::applyMaterial(std::string name)
{
    materialsMap::const_iterator pos = materials.find(name);
    
    if (pos == materials.end()) {
        printf("Material \"%s\" not found...", name.c_str());
        return;
    } else {
        prevMaterial = currMaterial; // Sauvegarde le material précédent
        pos->second->apply();
        currMaterial = name; // Défini le material courant
    }
}

// Restaure le matérial précédent
void Materials::restorePrevMaterial()
{
    applyMaterial(prevMaterial);
}
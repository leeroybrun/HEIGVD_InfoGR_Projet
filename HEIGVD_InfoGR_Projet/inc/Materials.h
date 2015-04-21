//
//  Materials.h
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 08.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#ifndef __HEIGVD_InfoGR_Projet__Materials__
#define __HEIGVD_InfoGR_Projet__Materials__

#include "main.h"
#include "Material.h"
#include <map>
#include <vector>

// Type qui permet de stocker une map (tableau associatif) de matériaux
typedef std::map<std::string, Material*> materialsMap;

// Classe Materials, permet d'enregistrer et appliquer facilement des matériaux
class Materials
{
private:
    materialsMap materials;
    std::string currMaterial = "";
    std::string prevMaterial = "";
public:
    void init();
    void addMaterial(std::string name, Material* material);
    void applyMaterial(std::string name);
    void restorePrevMaterial();
};

#endif /* defined(__HEIGVD_InfoGR_Projet__Materials__) */

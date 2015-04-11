//
//  Texture.h
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 08.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#ifndef __HEIGVD_InfoGR_Projet__Texture__
#define __HEIGVD_InfoGR_Projet__Texture__

#include "main.h"
#include <map>
#include <vector>

// Classe texture, qui stocke les données sur une texture chargée
class Texture
{
private:
    std::string filename;
    GLuint texId;
    std::string name;
public:
    Texture(std::string filename, GLuint texId, std::string name);
    
    std::string getFilename(){ return filename; }
    GLuint getId(){ return texId; }
    std::string getName(){ return name; }
};

// Type qui permet de stocker une map (tableau associatif) de textures à charger
typedef std::map<std::string, std::string> texturesMapLoad;

// Type qui permet de stocker une map (tableau associatif) de textures
typedef std::map<std::string, Texture*> texturesMap;

// Classe Textures, permet de charger plusieurs textures et des les appliquer facilement
class Textures
{
private:
    void loadTexture(std::string filename);
    texturesMap textures;
public:
    void init();
    void enable();
    void disable();
    void loadTextures(texturesMapLoad filenames);
    void resetCurrentTexture();
    void drawTexture(std::string name);
};

#endif /* defined(__HEIGVD_InfoGR_Projet__Texture__) */

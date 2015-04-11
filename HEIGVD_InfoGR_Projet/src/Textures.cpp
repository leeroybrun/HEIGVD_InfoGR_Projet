//
//  Texture.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 08.04.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "Textures.h"
#include "lodepng.h"

Texture::Texture(std::string _filename, GLuint _texId, std::string _name)
{
    filename = _filename;
    texId = _texId;
    name = _name;
}

void Textures::init()
{
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glEnable(GL_TEXTURE_2D);
    //glShadeModel(GL_FLAT);
}

void Textures::enable()
{
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

void Textures::disable()
{
    glDisable(GL_TEXTURE_2D);
}

void Textures::loadTextures(texturesMapLoad filenames)
{
    // On genère des identifiants pour les textures que l'on va charger
    GLuint textureName[filenames.size()];
    glGenTextures((int)filenames.size(), textureName);
    
    // Boucle sur toutes les textures
    int i = 0;
    for(texturesMapLoad::iterator iterator = filenames.begin(); iterator != filenames.end(); iterator++) {
        // On bind la texture que l'on va charger à son ID généré plus haut
        glBindTexture(GL_TEXTURE_2D, textureName[i]);
        
        // Chargement de la texture
        this->loadTexture(iterator->second);
        
        glBindTexture(GL_TEXTURE_2D, 0);
        
        // En enregistre les infos de la texture dans un nouvel objet
        Texture *texture = new Texture(iterator->second, textureName[i], iterator->first);
        
        // Ajout de l'objet à la map des textures
        this->textures.insert(std::make_pair(iterator->first, texture));
        
        i++;
    }
}

void Textures::drawTexture(std::string name)
{
    texturesMap::const_iterator pos = textures.find(name);
    
    if (pos == textures.end()) {
        printf("Texture \"%s\" not found...", name.c_str());
        return;
    } else {
        glBindTexture(GL_TEXTURE_2D, pos->second->getId());
    }
}

void Textures::resetCurrentTexture()
{
    glDisable(GL_TEXTURE);
    glBindTexture(GL_TEXTURE_2D, 0);
    glEnable(GL_TEXTURE);
}

void Textures::loadTexture(std::string filename)
{
    unsigned width, height;
    std::vector<unsigned char>image;
    
    unsigned error = lodepng::decode(image, width, height, filename);
    
    if(error) {
        printf("PNG decoding error : %u : %s", error, lodepng_error_text(error));
    }
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
    
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA,
                      width, height,
                      GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
}
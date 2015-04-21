//
//  screenInfos.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 17.02.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "ScreenInfos.h"

// ------------------------------------------------------------------
//  Classe ScreenInfos
//
//  Cette classe contient la gestion des informations à afficher
//  à l'écran (pour le debug).
//
//  Elle permet de définir des informations à afficher à l'écran
//  et de les mettre à jour facilement. On peut ensuite les afficher
//  facilement grâce à la méthode draw();
// ------------------------------------------------------------------

// Les méthodes setOrthographicProjection et restorePerspectiveProjection sont inspirée du tutoriel :
//    http://www.lighthouse3d.com/tutorials/glut-tutorial/bitmap-fonts-and-orthogonal-projections/

void ScreenInfos::setOrthographicProjection() {
    
    // switch to projection mode
    glMatrixMode(GL_PROJECTION);
    
    // save previous matrix which contains the
    //settings for the perspective projection
    glPushMatrix();
    
    // reset matrix
    glLoadIdentity();
    
    // set a 2D orthographic projection
    gluOrtho2D(0, Game::window->width, Game::window->height, 0);
    
    // switch back to modelview mode
    glMatrixMode(GL_MODELVIEW);
}

void ScreenInfos::restorePerspectiveProjection() {
    
    glMatrixMode(GL_PROJECTION);
    // restore previous projection matrix
    glPopMatrix();
    
    // get back to modelview mode
    glMatrixMode(GL_MODELVIEW);
}

// Défini une valeur en fonction de sa clé (nom)
// Le format de la méthode est (clé, format, valeurs)
// Exemple: ->set("nb_fps", "FPS: %d", fpsVal)
void ScreenInfos::set(std::string key, const char *format, ...) {
    char str[100];
    std::string str2;
    
    // On utilise vsprintf pour transformer le char* format à l'aide des arguments passés en paramètre
    // On place ensite le char* dans un string pour plus de facilité
    va_list argptr;
    va_start(argptr, format);
    vsprintf(str, format, argptr);
    str2 = str;
    va_end(argptr);
    
    // On essaie de l'insérer dans le map (tableau associatif)
    if(infos.insert(std::make_pair(key, str2)).second == false) {
        // Si l'insertion a échoué, c'est que cette valeur existait déjà. On la met donc à jour
        infos[key] = str2;
    }
}

// Dessine les infos à l'écran (en haut à gauche)
void ScreenInfos::draw() {
    setOrthographicProjection();
    
    Game::materials->applyMaterial("black"); // Du noir pour l'affichage
    
    int x = 5;  // Position x de départ
    int y = 15; // Position y de départ
    
    glPushMatrix();
    glLoadIdentity();
    
    // Boucle sur toutes les infos du map (tableau associatif)
    typedef std::map<std::string, std::string>::iterator it_type;
    for(it_type iterator = infos.begin(); iterator != infos.end(); iterator++) {
        GlutHelper::renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_12, iterator->second);
        y += 20; // On ajoute 20 au y pour l'affichage de la prochaine info
    }
    
    Game::materials->restorePrevMaterial();
    
    glPopMatrix();
    
    restorePerspectiveProjection();
}
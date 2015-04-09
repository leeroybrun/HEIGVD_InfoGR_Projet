//
//  menus.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 17.02.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "menu.h"

int menIdPolyMode;

// Gestion des menus
// menu principal
void mainMenu(int value){
    static int isFillPolygonMode = 1;
    
    switch(value){
        case 1:
            if(isFillPolygonMode) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glutChangeToMenuEntry(1, "Mode Polygon : Line", 1);
                isFillPolygonMode = 0;
            } else {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                glutChangeToMenuEntry(1, "Mode Polygon : Fill", 1);
                isFillPolygonMode = 1;
            }
            
            break;
        case 2:
            glutChangeToMenuEntry(2, "Translation On", 2);
            
            break;
        case 3:
            exit(0);
            break;
    };
    glutPostRedisplay();
};

// fonction du menu Couleur
void menuPolyMode(int value){
    switch(value){
        case 1:
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            glutChangeToMenuEntry(1, "Sommets ✓", 1);
            glutChangeToMenuEntry(2, "Fil-de-fer", 2);
            glutChangeToMenuEntry(3, "Facettes pleines", 3);
            break;
        case 2:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glutChangeToMenuEntry(1, "Sommets", 1);
            glutChangeToMenuEntry(2, "Fil-de-fer ✓", 2);
            glutChangeToMenuEntry(3, "Facettes pleines", 3);
            break;
        case 3:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glutChangeToMenuEntry(1, "Sommets", 1);
            glutChangeToMenuEntry(2, "Fil-de-fer", 2);
            glutChangeToMenuEntry(3, "Facettes pleines ✓", 3);
            break;
    };
};

void createMenus(void) {
    // Création du sous-menu Couleur
    // Attention : les sous-menus sont crée toujours avant les menus
    menIdPolyMode = glutCreateMenu(menuPolyMode);
    glutAddMenuEntry("Sommets", 1);
    glutAddMenuEntry("Fil-de-fer", 2);
    glutAddMenuEntry("Facettes pleines ✓", 3);
    
    // Creation du menu principal
    glutCreateMenu(mainMenu);
    glutAddMenuEntry("Hello",1);
    glutAddMenuEntry("Translation On ",2);
    glutAddSubMenu("Mode Polygone", menIdPolyMode); // Ajute un sous-menu
    glutAddMenuEntry("Quitter",3);
    glutAttachMenu(GLUT_RIGHT_BUTTON); // attache le menu au clic gauche de la souris
};
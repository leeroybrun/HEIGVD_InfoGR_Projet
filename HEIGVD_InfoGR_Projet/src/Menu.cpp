//
//  menus.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 17.02.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "menu.h"

void MenuEntry::toggleSelected()
{
    if(type == Toggle)
    {
        selected = !selected;
    }
}

TypeMenuEntry MenuEntry::getType()
{
    return type;
}

char* MenuEntry::getText()
{
    return text;
}

int MenuEntry::getValue()
{
    return value;
}

int MenuEntry::getPos()
{
    return pos;
}

Menu* MenuEntry::getMenu()
{
    return submenu;
}

bool MenuEntry::isSelected()
{
    return selected;
}

void Menu::create()
{
    menuId = glutCreateMenu(changeFunc);
    
    for(int i = 0; i < entries.size(); i++) {
        std::string text = entries[i]->getText();
        
        if(entries[i]->getType() == Simple) {
            glutAddMenuEntry(text.c_str(), entries[i]->getValue());
        } else if(entries[i]->getType() == Toggle) {
            if(entries[i]->isSelected()) {
                text = "[✓] "+ text;
            } else {
                text = "[   ] "+ text;
            }
            
            glutAddMenuEntry(text.c_str(), entries[i]->getValue());
        } else if(entries[i]->getType() == Submenu) {
            glutAddSubMenu(text.c_str(), entries[i]->getMenu()->getId());
        }
    }
}

void Menu::update()
{
    for(int i = 0; i < entries.size(); i++) {
        std::string text = entries[i]->getText();
        
        if(entries[i]->getType() == Toggle) {
            if(entries[i]->isSelected()) {
                text = "[✓] "+ text;
            } else {
                text = "[   ] "+ text;
            }
            
            
            glutChangeToMenuEntry(entries[i]->getPos(), text.c_str(), entries[i]->getValue());
        }
    }
}

void Menu::addEntry(char* text, TypeMenuEntry type, int value, bool selected)
{
    entries.push_back(new MenuEntry((int)entries.size()+1, text, type, value, selected));
}

void Menu::addSubMenu(char* text, Menu *submenu)
{
    entries.push_back(new MenuEntry((int)entries.size()+1, text, submenu));
}

MenuEntry* Menu::getEntryFromValue(int value)
{
    MenuEntry* entry = NULL;
    
    for(int i = 0; i < entries.size(); i++) {
        if(entries[i]->getValue() == value) {
            entry = entries[i];
        }
    }
    
    return entry;
}

void Menu::toggleEntryFromValue(int value)
{
    for(int i = 0; i < entries.size(); i++) {
        if(entries[i]->getValue() == value && entries[i]->getType() == Toggle) {
            entries[i]->toggleSelected();
        }
    }
}

int Menu::getId()
{
    return menuId;
}

void Menu::attach(int key)
{
    glutAttachMenu(key);
}

/*int menIdPolyMode;

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
};*/

Menu *polygonModeMenu;
Menu *mainMenu;

void changeMainMenu(int value)
{
    switch (value) {
        case 1:
            
            break;
            
        default:
            break;
    }
    printf("Main menu selected: %d\n", value);
}

void changePolygonModeMenu(int value)
{
    printf("Polygons menu selected: %d\n", value);
    switch (value) {
        case 1:
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            break;
            
        case 2:
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            break;
            
        case 3:
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            break;
            
        default:
            break;
    }
    
    polygonModeMenu->toggleEntryFromValue(value);
    polygonModeMenu->update();
}

void createMenus(void) {
    polygonModeMenu = new Menu(changePolygonModeMenu);
    polygonModeMenu->addEntry("Sommets", Toggle, 1, false);
    polygonModeMenu->addEntry("Fils-de-fer", Toggle, 2, false);
    polygonModeMenu->addEntry("Facettes", Toggle, 3, true);
    polygonModeMenu->create();
    
    mainMenu = new Menu(changeMainMenu);
    mainMenu->addEntry("Test simple", Simple, 1, false);
    mainMenu->addEntry("Test toggle", Toggle, 2, false);
    mainMenu->addSubMenu("Mode de polygones", polygonModeMenu);
    mainMenu->create();
    mainMenu->attach(GLUT_RIGHT_BUTTON);
    
    
    /*// Création du sous-menu Couleur
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
    glutAttachMenu(GLUT_RIGHT_BUTTON); // attache le menu au clic gauche de la souris*/
};
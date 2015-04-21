//
//  menus.cpp
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 17.02.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#include "menu.h"

// ------------------------------------------------------------------
//  Classe MenuEntry
//
//  Cela représente une entrée de menu.
//  Elle peut être de type Simple, Toggle, ToggleGroup ou Submenu.
//
//  Le type Simple affiche une entrée de menu simple.
//
//  Le type Toggle permet d'avoir une entrée de menu de menu
//  sélectionnable avec l'affichage d'une case à cocher si l'entrée
//  est activée ou non.
//
//  Le type ToggleGroup permet d'insérer un ToggleGroup dans un menu
//  (voir la classe MenuEntriesToggleGroup pour plus de détails).
//
//  Le type Submenu permet d'insérer un sous menu dans un menu.
// ------------------------------------------------------------------

// Inverse le booléen "selected" si il s'agit d'une entrée de menu de type Toggle
void MenuEntry::toggleSelected()
{
    if(type == Toggle)
    {
        selected = !selected;
    }
}

// Défini le booléen selected
void MenuEntry::setSelected(bool _selected)
{
    if(type == Toggle)
    {
        selected = _selected;
    }
}

// Retourne le type de l'entrée de menu
TypeMenuEntry MenuEntry::getType()
{
    return type;
}

// Retourne le texte de l'entrée de menu
std::string MenuEntry::getText()
{
    std::string text2 = text;
    
    // Si il s'agit d'un Toggle, on y ajoute l'affichage d'une "case" pour représenter le coché/non coché
    if(type == Toggle)
    {
        if(isSelected()) {
            text2 = "[✓] "+ text2;
        } else {
            text2 = "[   ] "+ text2;
        }
    }
    
    return text2;
}

// Retourne le valeur de l'entrée de menu
int MenuEntry::getValue()
{
    return value;
}

// Retourne le position de l'entrée de menu
int MenuEntry::getPos()
{
    return pos;
}

// Retourne le menu (sous-menu) associé à une entrée de menu
Menu* MenuEntry::getMenu()
{
    return submenu;
}

// Retourne le toggle group associé à une entrée de menu
MenuEntriesToggleGroup* MenuEntry::getToggleGroup()
{
    return toggleGroup;
}

// Retourne la valeur selected
bool MenuEntry::isSelected()
{
    return selected;
}

// ------------------------------------------------------------------
//  Classe MenuEntriesToggleGroup
//
//  Permet de gérer un "toggle group". Cela permet d'avoir une liste
//  d'entrées de menu de type "toggle" où une seule peut être cochée
//  à la fois. Même principe que des champs "radio" en HTML
// ------------------------------------------------------------------

// Ajoute une entrée de menu au ToogleGroup
// Ne peut pas spécifier de type, car l'entrée sera de toute façon de type "toggle"
void MenuEntriesToggleGroup::addEntry(char* text, int value, bool selected)
{
    entries.push_back(new MenuEntry((int)entries.size()+1, text, Toggle, value, selected));
}

// Met la valeur "selected" à true de l'entrée dont la valeur est passée en paramètre, et toutes les autres à false
void MenuEntriesToggleGroup::toggleFromValue(int value)
{
    bool valueInToggleGroup = false;
    
    // On commence par vérifier si la valeur fournie existe bien dans le toggle group
    // Si ce n'est pas le cas, nous n'avons pas besoin de changer les valeurs selected de ce toggle group
    for(int i = 0; i < entries.size(); i++) {
        if(entries[i]->getValue() == value) {
            valueInToggleGroup = true;
        }
    }
    
    // Si la valeur existe bien dans ce toggle group, on va mettre toutes les valeurs selected des entrées à false, sauf celle donc la valeur vaut "value"
    if(valueInToggleGroup)
    {
        for(int i = 0; i < entries.size(); i++) {
            if(entries[i]->getValue() == value) {
                entries[i]->setSelected(true);
            } else {
                entries[i]->setSelected(false);
            }
        }
    }
}

// Retourne les entrées de menu de ce toggle group
std::vector <MenuEntry*> MenuEntriesToggleGroup::getEntries()
{
    return entries;
}

// ------------------------------------------------------------------
//  Classe MenuEntriesToggleGroup
//
//  Permet de gérer un menu ou sous-menu.
//  On peut y ajouter des MenuEntry qui seront affichées dans le menu
// ------------------------------------------------------------------

// Crée le menu dans GLUT ainsi que toutes ses entrées
// Attention! Ceci est à appeler uniquement lorsque toutes les entrées de menu ont été ajoutées à celui-ci
void Menu::create()
{
    menuId = glutCreateMenu(changeFunc);
    
    for(int i = 0; i < entries.size(); i++) {
        switch (entries[i]->getType()) {
            case Simple:
            case Toggle:
                glutAddMenuEntry(entries[i]->getText().c_str(), entries[i]->getValue());
                break;
                
            case Submenu:
                glutAddSubMenu(entries[i]->getText().c_str(), entries[i]->getMenu()->getId());
                break;
                
            case ToggleGroup:
                std::vector <MenuEntry*> groupEntries = entries[i]->getToggleGroup()->getEntries();
                for(int j = 0; j < groupEntries.size(); j++) {
                    glutAddMenuEntry(groupEntries[j]->getText().c_str(), groupEntries[j]->getValue());
                }
                break;
        }
    }
}

// Met à jour les entrées du menu
// Cela sert surtout à mettre à jour les champs "toggle" en fonction de leur valeur selected
void Menu::update()
{
    for(int i = 0; i < entries.size(); i++) {
        switch (entries[i]->getType()) {
                
            // Rien à mettre à jour pour les valeurs simples et sous-menus
            case Simple:
            case Submenu:
                break;
                
            // Pour les toggle on met à jour le texte
            case Toggle:
                glutChangeToMenuEntry(entries[i]->getPos(), entries[i]->getText().c_str(), entries[i]->getValue());
                break;
                
            // Pour les ToggleGroup on met à jour les textes de toutes les entrées qu'il contient
            case ToggleGroup:
                std::vector <MenuEntry*> groupEntries = entries[i]->getToggleGroup()->getEntries();
                for(int j = 0; j < groupEntries.size(); j++) {
                    glutChangeToMenuEntry(groupEntries[j]->getPos(), groupEntries[j]->getText().c_str(), groupEntries[j]->getValue());
                }
                break;
        }
    }
}

// Retourne la position du prochain élément dans le menu
int Menu::getNextPos()
{
    // Si le menu est vide, la position sera 1 (premier élément)
    int pos = 1;
    
    // Menu pas vide
    if((int)entries.size() > 0)
    {
        MenuEntry *prevEntry = entries[(int)entries.size()-1];
        
        // L'élément précédent est un toggle group, on va donc calculer la position de l'élément suivant en fonction de la position du toggle group + dernier élément de celui-ci
        if(prevEntry->getType() == ToggleGroup)
        {
            pos = prevEntry->getPos() + prevEntry->getToggleGroup()->getEntries()[prevEntry->getToggleGroup()->getEntries().size()-1]->getPos();
        
        // Sinon, on prend juste la taille actuelle du menu + 1
        } else {
            pos = (int)entries.size()+1;
        }
    }
    
    return pos;
}

// Ajoute une entrée Simple/Toggle au menu
void Menu::addEntry(char* text, TypeMenuEntry type, int value, bool selected)
{
    entries.push_back(new MenuEntry(getNextPos(), text, type, value, selected));
}

// Ajoute un sous-menu au menu
void Menu::addSubMenu(char* text, Menu *submenu)
{
    entries.push_back(new MenuEntry(getNextPos(), text, submenu));
}

// Ajoute un ToggleGroup au menu
void Menu::addToggleGroup(MenuEntriesToggleGroup *toggleGroup)
{
    entries.push_back(new MenuEntry(getNextPos(), toggleGroup));
}

// Obtient l'entrée du menu en fonction de sa valeur
MenuEntry* Menu::getEntryFromValue(int value)
{
    MenuEntry* entry = NULL;
    
    for(int i = 0; i < entries.size(); i++) {
        switch (entries[i]->getType()) {
            
            // Pour les sous-menu, on ne fait rien
            // On ne s'intéresse pas aux entrées du sous-menu, mais uniquement du menu en cours
            case Submenu:
                break;
            
            // Pour les entrées Simple/Toggle, on compare la valeur fournie avec la valeur de l'élément courant
            case Simple:
            case Toggle:
                if(entries[i]->getValue() == value) {
                    entry = entries[i];
                }
                break;
            
            // Pour les ToggleGroup, on passe sur chaque entrée qu'il contient pour comparer sa valeur
            case ToggleGroup:
                std::vector <MenuEntry*> groupEntries = entries[i]->getToggleGroup()->getEntries();
                for(int j = 0; j < groupEntries.size(); j++) {
                    if(groupEntries[j]->getValue() == value) {
                        entry = groupEntries[j];
                    }
                }
                break;
        }
    }
    
    return entry;
}

// On inverse la valeur "selected" d'un élément en fonction de la valeur fournie
void Menu::toggleEntryFromValue(int value)
{
    for(int i = 0; i < entries.size(); i++) {
        switch (entries[i]->getType()) {
            
            // Rien à faire pour les entrées simples et les sous-menus
            case Simple:
            case Submenu:
                break;
                
            // Pour les Toggle, on vérifie si la valeur de l'élément courant correspond à la valeur fournie
            case Toggle:
                if(entries[i]->getValue() == value) {
                    entries[i]->toggleSelected();
                }
                break;
            
            // Pour les ToggleGroup on va appeler la méthode toggleFromValue
            // Tous les éléments seront passés à selected = false, sauf l'élément dont la valeur vaut la valeur fournie
            case ToggleGroup:
                entries[i]->getToggleGroup()->toggleFromValue(value);
                break;
        }
    }
}

// Retourne l'ID fourni par GLUT pour le menu
int Menu::getId()
{
    return menuId;
}

// Attache le menu à un bouton de la souris/touche clavier
void Menu::attach(int key)
{
    glutAttachMenu(key);
}
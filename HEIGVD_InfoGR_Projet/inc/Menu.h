//
//  menus.h
//  HEIGVD_InfoGR_Projet
//
//  Created by Leeroy Brun on 17.02.15.
//  Copyright (c) 2015 Leeroy Brun. All rights reserved.
//

#ifndef __HEIGVD_InfoGR_Projet__menus__
#define __HEIGVD_InfoGR_Projet__menus__

#include "main.h"
#include <vector>

enum TypeMenuEntry {
    Simple,
    Toggle,
    Submenu
};

class Menu;

class MenuEntry
{
public:
    MenuEntry(int _pos, char* _text, Menu *_submenu): pos(_pos), text(_text), submenu(_submenu), type(Submenu){}
    MenuEntry(int _pos, char* _text, TypeMenuEntry _type, int _value, bool _selected): pos(_pos), text(_text), type(_type), value(_value), selected(_selected){};
    void toggleSelected();
    TypeMenuEntry getType();
    char* getText();
    int getValue();
    int getPos();
    Menu* getMenu();
    bool isSelected();
    
private:
    TypeMenuEntry type;
    char* text;
    bool selected = false;
    int pos;
    int value;
    Menu *submenu;
};

class Menu
{
private:
    int menuId = 0;
    std::vector <MenuEntry*> entries;
    void (*changeFunc)(int); // (int value)
public:
    Menu(void (*_changeFunc)(int)) : changeFunc(_changeFunc){};
    void create();
    void update();
    void addEntry(char* text, TypeMenuEntry type, int value, bool selected);
    MenuEntry* getEntryFromValue(int value);
    void toggleEntryFromValue(int value);
    void addSubMenu(char* text, Menu *submenu);
    void attach(int key);
    int getId();
};

void createMenus(void);

#endif /* defined(__HEIGVD_InfoGR_Projet__menus__) */

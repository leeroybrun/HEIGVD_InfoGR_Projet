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
    Submenu,
    ToggleGroup
};

class Menu;
class MenuEntriesToggleGroup;

class MenuEntry
{
public:
    MenuEntry(int _pos, char* _text, Menu *_submenu): pos(_pos), text(_text), submenu(_submenu), type(Submenu){}
    MenuEntry(int _pos, MenuEntriesToggleGroup *_toggleGroup): pos(_pos), toggleGroup(_toggleGroup), type(ToggleGroup){}
    MenuEntry(int _pos, char* _text, TypeMenuEntry _type, int _value, bool _selected): pos(_pos), text(_text), type(_type), value(_value), selected(_selected){};
    TypeMenuEntry getType();
    std::string getText();
    int getValue();
    int getPos();
    Menu* getMenu();
    MenuEntriesToggleGroup* getToggleGroup();
    bool isSelected();
    void setSelected(bool _selected);
    void toggleSelected();
    
private:
    TypeMenuEntry type;
    char* text;
    bool selected = false;
    int pos;
    int value;
    Menu *submenu;
    MenuEntriesToggleGroup *toggleGroup;
};

class MenuEntriesToggleGroup
{
public:
    MenuEntriesToggleGroup(){};
    void addEntry(char* text, int value, bool selected);
    std::vector <MenuEntry*> getEntries();
    void toggleFromValue(int value);
private:
    std::vector <MenuEntry*> entries;
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
    int getNextPos();
    void addEntry(char* text, TypeMenuEntry type, int value, bool selected = false);
    MenuEntry* getEntryFromValue(int value);
    void toggleEntryFromValue(int value);
    void addSubMenu(char* text, Menu *submenu);
    void addToggleGroup(MenuEntriesToggleGroup *toggleGroup);
    void attach(int key);
    int getId();
};

void createMenus(void);

#endif /* defined(__HEIGVD_InfoGR_Projet__menus__) */

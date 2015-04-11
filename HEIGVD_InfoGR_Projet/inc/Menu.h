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

struct MenuEntry
{
    MenuEntry(char* _text, bool _selected): text(_text), selected(_selected){};
    char* text;
    bool selected = false;
};

class Menu
{
private:
    std::vector <MenuEntry> entries;
public:
    int create();
    void addEntry(char* text, bool selected);
    void addSubMenu(Menu *submenu);
};

void createMenus(void);

#endif /* defined(__HEIGVD_InfoGR_Projet__menus__) */

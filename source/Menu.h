#pragma once

#ifndef MENU_H
#define MENU_h

#include <vector>
#include<SDL2/SDL.h>
#include "MenuOption.h"


class Menu
{
public:
	Menu(void);
	~Menu(void);

	std::vector<MenuOption*> lMO; 

	// ----- ID aktywnego buttona
	int activeMenuOption;
	int numOfMenuOptions;

	virtual void Update();
	virtual void Draw(SDL_Renderer* rR);

	// ----- 0 = TOP, 1 = RIGHT, 2 = BOTTOM, 3 = LEFT
	virtual void updateActiveButton(int iDir);
};

#endif
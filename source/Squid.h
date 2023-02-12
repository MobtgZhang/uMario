#pragma once

#ifndef SQUID_H
#define SQUID_H

#include "Minion.h"

class Squid : public Minion
{
private:
	int moveXDistance, moveYDistance;
public:
	Squid(int iXPos, int iYPos);
	~Squid(void);
	
	void Update();
	void Draw(SDL_Renderer* rR, CImg* iIMG);

	void minionPhysics();
	void collisionWithPlayer(bool TOP);

	void changeBlockID();
};

#endif
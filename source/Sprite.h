#pragma once

#ifndef SPRITE_H
#define SPRITE_H

#include "Img.h"
#include <string>
#include <vector>

class Sprite
{
private:
	std::vector<CImg*> tSprite;
	std::vector<unsigned int> iDelay;

	bool bRotate;

	int iCurrentFrame;
	int iStartFrame;
	int iEndFrame;

	unsigned long lTimePassed;

public:
	Sprite(void);
	Sprite(SDL_Renderer* rR, std::vector<std::string> tSprite, std::vector<unsigned int> iDelay, bool bRotate);
	~Sprite(void);

	void Update();

	/* ----- get & set ----- */
	CImg* getTexture();
	CImg* getTexture(int iID);
};

#endif


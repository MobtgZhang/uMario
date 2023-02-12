#pragma once

#ifndef BUBBLE_H
#define BUBBlE_H


#include "Img.h"

class Bubble
{
private:
	int iXPos, iYPos;

	bool bDestoy; // -- DELETE BUBBLE
	int iBlockID;
public:
	Bubble(int iXPos, int iYPos);
	~Bubble(void);

	void Update();
	void Draw(SDL_Renderer* rR, CImg* iIMG);
	
	int getBlockID();
	bool getDestroy();
};

#endif
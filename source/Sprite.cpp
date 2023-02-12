#include "Sprite.h"

/* ******************************************** */

Sprite::Sprite(void) { }

Sprite::Sprite(SDL_Renderer* rR, std::vector<std::string> sSprite, std::vector<unsigned int> iDelay, bool bRotate) {
	this->iDelay = iDelay;
	this->bRotate = bRotate;

	this->iCurrentFrame = 0;
	this->iStartFrame = 0;
	this->iEndFrame = sSprite.size() - 1;

	for(int i = 0; i < this->iEndFrame + 1; i++) {
		this->tSprite.push_back(new CImg(sSprite[i], rR));
	}

	this->lTimePassed = 0;
}

Sprite::~Sprite(void) {
	for(std::vector<CImg*>::iterator i = tSprite.begin(); i != tSprite.end(); i++) {
		delete (*i);
	}
}

/* ******************************************** */

void Sprite::Update() {
	if(SDL_GetTicks() - iDelay[iCurrentFrame] > lTimePassed) {
		lTimePassed = SDL_GetTicks();

		if(iCurrentFrame == iEndFrame) {
			iCurrentFrame = 0;
		} else {
			++iCurrentFrame;
		}
	}
}

/* ******************************************** */

CImg* Sprite::getTexture() {
	return tSprite[iCurrentFrame];
}

CImg* Sprite::getTexture(int iID) {
	return tSprite[iID];
}
#include "Flower.h"
#include "Application.h"

/* ******************************************** */

Flower::Flower(int iXPos, int fYPos, int iX, int iY) {
	this->fXPos = (float)iXPos;
	this->fYPos = (float)fYPos;

	this->iBlockID = 6;
	this->moveSpeed = 2;
	this->inSpawnState = true;
	this->minionSpawned = true;
	this->inSpawnY = 32;
	this->moveDirection = false;
	this->collisionOnlyWithPlayer = true;

	this->iX = iX;
	this->iY = iY;
}

Flower::~Flower(void) {

}

/* ******************************************** */

void Flower::Update() {
	if (inSpawnState) {
		if (inSpawnY <= 0) {
			inSpawnState = false;
		} else {
			if (fYPos > -5) {
				inSpawnY -= 2;
				fYPos -= 2;
			} else {
				inSpawnY -= 1;
				fYPos -= 1;
			}
		}
	}
}

bool Flower::updateMinion() {
	return minionSpawned;
}

void Flower::Draw(SDL_Renderer* rR, CImg* iIMG) {
	if(minionState >= 0) {
		iIMG->Draw(rR, (int)fXPos + (int)Application::getMap()->getXPos(), (int)fYPos + 2, false);
		if (inSpawnState) {
			Application::getMap()->getBlock(Application::getMap()->getLevelType() == 0 || Application::getMap()->getLevelType() == 4 ? 9 : 56)->getSprite()->getTexture()->Draw(rR, (int)fXPos + (int)Application::getMap()->getXPos(), (int)fYPos + (32 - inSpawnY) - Application::getMap()->getMapBlock(iX, iY)->getYPos() + 2, false);
		}
	}
}

/* ******************************************** */

void Flower::collisionWithPlayer(bool TOP) {
	if(!inSpawnState && minionState >= 0) {
		Application::getMap()->getPlayer()->setPowerLVL(Application::getMap()->getPlayer()->getPowerLVL() + 1);
		minionState = -1;
	}
}

void Flower::setMinionState(int minionState) { }
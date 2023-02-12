#include "Mushroom.h"
#include "Application.h"

/* ******************************************** */

Mushroom::Mushroom(int iXPos, int fYPos, bool powerUP, int iX, int iY) {
	this->fXPos = (float)iXPos;
	this->fYPos = (float)fYPos - 2;

	this->iBlockID = powerUP ? 2 : Application::getMap()->getLevelType() == 1 ? 25 : 3;
	this->moveSpeed = 2;
	this->inSpawnState = true;
	this->minionSpawned = true;
	this->inSpawnY = 30;
	this->moveDirection = false;
	this->powerUP = powerUP;
	this->collisionOnlyWithPlayer = true;

	this->minionState = 0;

	this->iX = iX;
	this->iY = iY;
}

Mushroom::~Mushroom(void) {

}

/* ******************************************** */

void Mushroom::Update() {
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
	} else {
		updateXPos();
	}
}

bool Mushroom::updateMinion() {
	if (!inSpawnState) {
		minionPhysics();
	}

	return minionSpawned;
}

void Mushroom::Draw(SDL_Renderer* rR, CImg* iIMG) {
	if(minionState >= 0) {
		iIMG->Draw(rR, (int)fXPos + (int)Application::getMap()->getXPos(), (int)fYPos + 2, false);
		if (inSpawnState) {
			Application::getMap()->getBlock(Application::getMap()->getLevelType() == 0 || Application::getMap()->getLevelType() == 4 ? 9 : 56)->getSprite()->getTexture()->Draw(rR, (int)fXPos + (int)Application::getMap()->getXPos(), (int)fYPos + (32 - inSpawnY) - Application::getMap()->getMapBlock(iX, iY)->getYPos() + 2, false);
		}
	}
}

/* ******************************************** */

void Mushroom::collisionWithPlayer(bool TOP) {
	if(!inSpawnState && minionState == 0) {
		if(powerUP) {
			Application::getMap()->getPlayer()->setPowerLVL(Application::getMap()->getPlayer()->getPowerLVL() + 1);
		} else {
			Application::getMap()->getPlayer()->setNumOfLives(Application::getMap()->getPlayer()->getNumOfLives() + 1);
			Application::getMap()->addPoints((int)fXPos, (int)fYPos, "1UP", 10, 14);
			CCFG::getMusic()->PlayChunk(CCFG::getMusic()->cONEUP);
		}
		minionState = -1;
	}
}

void Mushroom::setMinionState(int minionState) {
	
}
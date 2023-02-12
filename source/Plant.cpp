#include "Plant.h"
#include "Application.h"

/* ******************************************** */

Plant::Plant(int fXPos, int fYPos, int iBlockID) {
	this->fXPos = (float)fXPos + 2;
	this->fYPos = (float)fYPos + 6;

	this->iHitBoxX = 28;
	this->iHitBoxY = 38;

	this->iBlockID = iBlockID;

	this->bWait = true;
	this->iTime = SDL_GetTicks();

	this->lockPlant = false;

	// -- true = TOP, false = BOT
	this->moveDirection = true;

	this->iLength = 50;

	this->X = Application::getMap()->getBlockIDX((int)fXPos);
	this->Y = Application::getMap()->getBlockIDY((int)fYPos);
}

Plant::~Plant(void) {

}

/* ******************************************** */

void Plant::Update() {
	lockPlant = Application::getMap()->getPlayer()->getXPos() - Application::getMap()->getXPos() >= fXPos - 48 && Application::getMap()->getPlayer()->getXPos() - Application::getMap()->getXPos() <= fXPos + iHitBoxX + 48;

	if(bWait) {
		if((!lockPlant || !moveDirection) && iTime + (moveDirection ? 1000 : 985) <= SDL_GetTicks()) {
			bWait = false;
		} else if(lockPlant && moveDirection) {
			iTime = SDL_GetTicks();
		}
	} else if(moveDirection) {
		if(iLength > 0) {
			fYPos -= 1;
			iLength -= 1;
		} else {
			moveDirection = false;
			iLength = 50;
			bWait = true;
			iTime = SDL_GetTicks();
		}
	} else {
		if(iLength > 0) {
			fYPos += 1;
			iLength -= 1;
		} else if(!lockPlant) {
			moveDirection = true;
			iLength = 50;
			bWait = true;
			iTime = SDL_GetTicks();
		}
	}
}

void Plant::Draw(SDL_Renderer* rR, CImg* iIMG) {
	iIMG->Draw(rR, (int)(fXPos + Application::getMap()->getXPos()) - 2, (int)fYPos - 6, false);

	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 2; j++) {
			Application::getMap()->getBlock(Application::getMap()->getMapBlock(X + j, Y - i)->getBlockID())->Draw(rR, (int)((X + j) * 32 + Application::getMap()->getXPos()), CCFG::GAME_HEIGHT - 32 * (Y - i) - 16);
		}
	}
}

void Plant::minionPhysics() {

}

/* ******************************************** */

void Plant::collisionWithPlayer(bool onTOP) {
	if(Application::getMap()->getPlayer()->getStarEffect()) {
		minionState = -1;
		points(200);
	} else {
		Application::getMap()->playerDeath(true, false);
	}
}

void Plant::collisionEffect() { }

void Plant::lockMinion() {
	if(moveDirection) {
		fYPos += 50 - iLength;
	} else {
		fYPos += iLength;
	}
	moveDirection = true;
	iLength = 50;
	lockPlant = true;
	bWait = true;
	iTime = SDL_GetTicks();
}

void Plant::setMinionState(int minionState) {
	if(minionState < 0) {
		this->minionState = -1;
		points(200);
	} else {
		this->minionState = minionState;
	}
}

/* ******************************************** */
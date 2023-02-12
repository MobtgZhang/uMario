#include "Goombas.h"
#include "Application.h"

/* ******************************************** */

Goombas::Goombas(int iX, int iY, int iBlockID, bool moveDirection) {
	this->fXPos = (float)iX;
	this->fYPos = (float)iY;
	this->iBlockID = iBlockID;
	this->moveDirection = moveDirection;
	this->moveSpeed = 1;
}

Goombas::~Goombas(void) {

}

/* ******************************************** */

void Goombas::Update() {
	if (minionState == 0) {
		updateXPos();
	} else if(minionState == -2) {
		Minion::minionDeathAnimation();
	} else if (SDL_GetTicks() - 500 >= (unsigned)deadTime) {
		minionState = -1;
	}
}

void Goombas::Draw(SDL_Renderer* rR, CImg* iIMG) {
	if(minionState != -2) {
		iIMG->Draw(rR, (int)fXPos + (int)Application::getMap()->getXPos(), (int)fYPos + 2, false);
	} else {
		iIMG->DrawVert(rR, (int)fXPos + (int)Application::getMap()->getXPos(), (int)fYPos + 2);
	}
}

/* ******************************************** */

void Goombas::collisionWithPlayer(bool TOP) {
	if(Application::getMap()->getPlayer()->getStarEffect()) {
		setMinionState(-2);
	} else if(TOP) {
		if(minionState == 0) {
			minionState = 1;
			iBlockID = Application::getMap()->getLevelType() == 0 || Application::getMap()->getLevelType() == 4 ? 1 : Application::getMap()->getLevelType() == 1 ? 9 : 11;
			deadTime = SDL_GetTicks();
			Application::getMap()->getPlayer()->resetJump();
			Application::getMap()->getPlayer()->startJump(1);
			points(100);
			CCFG::getMusic()->PlayChunk(CCFG::getMusic()->cSTOMP);
		}
	} else {
		Application::getMap()->playerDeath(true, false);
	}
}

/* ******************************************** */

void Goombas::setMinionState(int minionState) {
	this->minionState = minionState;

	if (this->minionState == 1) {
		deadTime = SDL_GetTicks();
	}

	Minion::setMinionState(minionState);
}
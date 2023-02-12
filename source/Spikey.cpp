#include "Spikey.h"
#include "Application.h"

/* ******************************************** */

Spikey::Spikey(int iXPos, int iYPos) {
	this->fXPos = (float)iXPos;
	this->fYPos = (float)iYPos + 6;

	this->iHitBoxX = 32;
	this->iHitBoxY = 26;

	this->iBlockID = 52;

	this->startJump(1);

	this->moveSpeed = 0;
}

Spikey::~Spikey(void) {

}

/* ******************************************** */

void Spikey::Update() {
	if (minionState == 0) {
		updateXPos();
	} else if(minionState == -2) {
		Minion::minionDeathAnimation();
	}
}

void Spikey::Draw(SDL_Renderer* rR, CImg* iIMG) {
	if(minionState != -2) {
		iIMG->Draw(rR, (int)fXPos + (int)Application::getMap()->getXPos(), (int)fYPos - 4, !moveDirection);
	} else {
		iIMG->DrawVert(rR, (int)fXPos + (int)Application::getMap()->getXPos(), (int)fYPos + 2);
	}
}

void Spikey::minionPhysics() {
	if (jumpState == 1) {
		physicsState1();
	} else {
		if (!Application::getMap()->checkCollisionLB((int)fXPos + 2, (int)fYPos + 2, iHitBoxY, true) && !Application::getMap()->checkCollisionRB((int)fXPos - 2, (int)fYPos + 2, iHitBoxX, iHitBoxY, true) && !onAnotherMinion) {
			physicsState2();
		} else {
			jumpState = 0;
			onAnotherMinion = false;

			if(iBlockID == 52) {
				iBlockID = 51;
				moveDirection = fXPos + iHitBoxX/2 > Application::getMap()->getPlayer()->getXPos() - Application::getMap()->getXPos() + Application::getMap()->getPlayer()->getHitBoxX()/2;
				moveSpeed = 1;
			}
		}
	}
}

/* ******************************************** */

void Spikey::collisionWithPlayer(bool TOP) {
	if(Application::getMap()->getPlayer()->getStarEffect()) {
		setMinionState(-2);
	} else {
		Application::getMap()->playerDeath(true, false);
	}
}
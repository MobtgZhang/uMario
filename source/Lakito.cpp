#include "Lakito.h"
#include "Application.h"
#include <cstdlib>
#include <ctime>

/* ******************************************** */

Lakito::Lakito(int iXPos, int iYPos, int iMaxXPos) {
	this->fXPos = (float)iXPos + 16;
	this->fYPos = (float)iYPos;

	this->iMaxXPos = iMaxXPos;
	this->followPlayer = false;
	this->end = false;

	this->iBlockID = 50;

	this->collisionOnlyWithPlayer = true;
	this->iHitBoxX = 32;
	this->iHitBoxY = 26;

	this->moveDirection = true;

	this->nextSpikeyFrameID = 128;

	this->minionSpawned = true;

	srand((unsigned)time(NULL));
}

Lakito::~Lakito(void) {

}

/* ******************************************** */

void Lakito::Update() {
	if(minionState == -2) {
		Minion::minionDeathAnimation();
	} else {
		if(fXPos > iMaxXPos) {
			end = true;
		}
		
		if(end) {
			fXPos -= 1;

			if(fXPos < -iHitBoxX) {
				minionState = -1;
			}

			return;
		}

		if(fXPos < -Application::getMap()->getXPos() - 64) {
			fXPos = -Application::getMap()->getXPos() - 32;
		}
		
		if(fXPos <= Application::getMap()->getPlayer()->getXPos() - Application::getMap()->getXPos() + Application::getMap()->getPlayer()->getHitBoxX()/2 + 32*Application::getMap()->getPlayer()->getMoveSpeed() && Application::getMap()->getPlayer()->getMove() && Application::getMap()->getPlayer()->getMoveDirection()) {
			moveSpeed = Application::getMap()->getPlayer()->getMoveSpeed() + (fXPos < Application::getMap()->getPlayer()->getXPos() - Application::getMap()->getXPos() + Application::getMap()->getPlayer()->getHitBoxX()/2 + 32*Application::getMap()->getPlayer()->getMoveSpeed());
			fXPos += moveSpeed;
			followPlayer = true;
			moveDirection = true;
		} else {
			if(followPlayer) {
				if(moveSpeed > 0) {
					fXPos += moveSpeed;
					--moveSpeed;
				} else {
					followPlayer = false;
				}
			} else {
				if(!moveDirection) {
					fXPos -= 1;

					if(fXPos < Application::getMap()->getPlayer()->getXPos() - Application::getMap()->getXPos() + Application::getMap()->getPlayer()->getHitBoxX()/2 - 128) {
						moveDirection = true;
					}
				} else {
					fXPos += 1;
					if(fXPos > Application::getMap()->getPlayer()->getXPos() - Application::getMap()->getXPos() + Application::getMap()->getPlayer()->getHitBoxX()/2 + 128) {
						moveDirection = false;
					}
				}
			}
		}

		if(nextSpikeyFrameID < rand()%85) {
			iBlockID = 49;
		}

		if(nextSpikeyFrameID <= 0) {
			Application::getMap()->addSpikey((int)fXPos, (int)(fYPos - 32));
			nextSpikeyFrameID = 135 + rand()%175;
			iBlockID = 50;
		} else {
			--nextSpikeyFrameID;
		}
	}
}

void Lakito::Draw(SDL_Renderer* rR, CImg* iIMG) {
	if(minionState != -2) {
		iIMG->Draw(rR, (int)fXPos + (int)Application::getMap()->getXPos(), (int)fYPos - 16, !moveDirection);
	} else {
		iIMG->DrawVert(rR, (int)fXPos + (int)Application::getMap()->getXPos(), (int)fYPos - 16);
	}
}

void Lakito::minionPhysics() { }

/* ******************************************** */

void Lakito::collisionWithPlayer(bool TOP) {
	if(Application::getMap()->getPlayer()->getStarEffect() || TOP) {
		setMinionState(-2);
	} else if(!end) {
		Application::getMap()->playerDeath(true, false);
	}
}
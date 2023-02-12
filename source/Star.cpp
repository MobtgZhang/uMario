#include "Star.h"
#include "Application.h"

/* ******************************************** */

Star::Star(int iXPos, int iYPos, int iX, int iY) {
	this->fXPos = (float)iXPos + 2;
	this->fYPos = (float)iYPos;

	this->collisionOnlyWithPlayer = true;

	this->moveDirection = false;
	this->moveSpeed = 3;

	this->inSpawnState = true;
	this->minionSpawned = true;
	this->inSpawnY = 30;
	this->startJumpSpeed = 4;

	this->iX = iX;
	this->iY = iY;

	this->iBlockID = 24;

	this->iHitBoxX = 28;
	this->iHitBoxY = 32;
}

Star::~Star(void) {

}

/* ******************************************** */

void Star::Update() {
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
		if(jumpState == 0) {
			startJump(1);
			jumpDistance = 32;
		}
		updateXPos();
	}
}

bool Star::updateMinion() {
	if (!inSpawnState) {
		minionPhysics();
	}

	return minionSpawned;
}

void Star::minionPhysics() {
	if (jumpState == 1) {
		if(minionState == 0) {
			updateYPos(-4 + (currentJumpDistance > 64 ? 2 : 0));
			currentJumpDistance += 2;

			if (jumpDistance <= currentJumpDistance) {
				jumpState = 2;
			}
		}
	} else {
		if (!Application::getMap()->checkCollisionLB((int)fXPos + 2, (int)fYPos + 2, iHitBoxY, true) && !Application::getMap()->checkCollisionRB((int)fXPos - 2, (int)fYPos + 2, iHitBoxX, iHitBoxY, true)) {
			Minion::physicsState2();
		} else {
			jumpState = 0;
		}
	}
}

void Star::Draw(SDL_Renderer* rR, CImg* iIMG) {
	iIMG->Draw(rR, (int)fXPos + (int)Application::getMap()->getXPos(), (int)fYPos + 2, false);
	if (inSpawnState) {
		Application::getMap()->getBlock(Application::getMap()->getLevelType() == 0 || Application::getMap()->getLevelType() == 4 ? 9 : 56)->getSprite()->getTexture()->Draw(rR, (int)fXPos + (int)Application::getMap()->getXPos() - 2, (int)fYPos + (32 - inSpawnY) - Application::getMap()->getMapBlock(iX, iY)->getYPos(), false);
	}
}

/* ******************************************** */

void Star::collisionWithPlayer(bool TOP) {
	if(!inSpawnState) {
		Application::getMap()->getPlayer()->setStarEffect(true);
		minionState = -1;
	}
}

void Star::setMinionState(int minionState) { }
#include "Spring.h"
#include "Application.h"

/* ******************************************** */

Spring::Spring(int iXPos, int iYPos) {
	this->fXPos = (float)iXPos;
	this->fYPos = (float)iYPos + 2;

	this->iHitBoxX = 32;
	this->iHitBoxY = 72;

	this->iBlockID = Application::getMap()->getLevelType() == 0 || Application::getMap()->getLevelType() == 4 ? 37 : 40;

	this->minionState = 0;
	this->nextFrameID = 4;
	this->inAnimation = false;
}

Spring::~Spring(void) {

}

/* ******************************************** */

void Spring::Update() {
	if(inAnimation) {
		if(CCFG::keySpace) {
			extraJump = true;
			Application::getMap()->getPlayer()->resetJump();
			Application::getMap()->getPlayer()->setNextFallFrameID(16);
		} else {
			Application::getMap()->getPlayer()->stopMove();
		}

		Application::getMap()->getPlayer()->setMarioSpriteID(5);
		if(nextFrameID <= 0) {
			switch(minionState) {
				case 0:
					iBlockID = iBlockID == 37 ? 38 : 41;
					minionState = 1;
					Application::getMap()->getPlayer()->setYPos(Application::getMap()->getPlayer()->getYPos() + 16.0f);
					break;
				case 1:
					iBlockID = iBlockID == 38 ? 39 : 42;
					minionState = 2;
					Application::getMap()->getPlayer()->setYPos(Application::getMap()->getPlayer()->getYPos() + 16.0f);
					break;
				case 2:
					iBlockID = iBlockID == 39 ? 38 : 41;
					minionState = 3;
					Application::getMap()->getPlayer()->setYPos(Application::getMap()->getPlayer()->getYPos() - 16.0f);
					break;
				case 3:
					iBlockID = iBlockID == 38 ? 37 : 40;
					minionState = 0;
					Application::getMap()->getPlayer()->setYPos(Application::getMap()->getPlayer()->getYPos() - 16.0f);
					Application::getMap()->getPlayer()->resetJump();
					Application::getMap()->getPlayer()->startJump(4 + (extraJump ? 5 : 0));
					Application::getMap()->getPlayer()->setSpringJump(true);
					Application::getMap()->getPlayer()->startMove();
					if(extraJump) Application::getMap()->getPlayer()->setCurrentJumpSpeed(10.5f);
					inAnimation = false;
					break;
			}
			nextFrameID = 4;
		} else {
			--nextFrameID;
		}
	}
}

void Spring::Draw(SDL_Renderer* rR, CImg* iIMG) {
	iIMG->Draw(rR, (int)fXPos + (int)Application::getMap()->getXPos(), (int)fYPos, false);
}

void Spring::minionPhysics() { }

/* ******************************************** */

void Spring::collisionWithPlayer(bool TOP) {
	if(!inAnimation) {
		if(TOP && Application::getMap()->getPlayer()->getJumpState() == 2) {
			Application::getMap()->getPlayer()->stopMove();
			Application::getMap()->getPlayer()->resetJump();
			Application::getMap()->getPlayer()->setNextFallFrameID(16);
			inAnimation = true;
			extraJump = false;
			CCFG::keySpace = false;
		} else {
			if(Application::getMap()->getPlayer()->getMoveDirection()) {
				Application::getMap()->getPlayer()->setXPos((float)Application::getMap()->getPlayer()->getXPos() - Application::getMap()->getPlayer()->getMoveSpeed());
			} else {
				Application::getMap()->getPlayer()->setXPos((float)Application::getMap()->getPlayer()->getXPos() + Application::getMap()->getPlayer()->getMoveSpeed());
			}
		}
	}
}

void Spring::setMinionState(int minionState) { }
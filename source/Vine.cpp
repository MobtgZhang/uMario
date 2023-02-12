#include "Vine.h"
#include "Application.h"

/* ******************************************** */

Vine::Vine(int iXPos, int iYPos, int minionState, int iBlockID) {
	this->fXPos = (float)iXPos*32 + 4;
	this->fYPos = (float)(CCFG::GAME_HEIGHT - 16 - iYPos*32);

	this->iX = iXPos;
	this->iY = iYPos;

	this->minionState = minionState;
	this->iBlockID = iBlockID;

	this->moveSpeed = 0;

	this->collisionOnlyWithPlayer = true;

	this->jumpDistance = 0;
	this->minionSpawned = true;

	this->iHitBoxX = 24;
	this->iHitBoxY = -32;
}

Vine::~Vine(void) {

}

/* ******************************************** */

void Vine::Update() {
	if(minionState == 0) {
		if(CCFG::GAME_HEIGHT + 16 - iY * 32 >= jumpDistance) {
			jumpDistance += 2;
			iHitBoxY += 2;
			fYPos -= 2;
		}
	} else {
		if(jumpDistance < 256) {
			jumpDistance += 2;
			iHitBoxY += 2;
			fYPos -= 2;
		}
	}
}

void Vine::Draw(SDL_Renderer* rR, CImg* iIMG) {
	if(jumpDistance < 32) {
		Application::getMap()->getMinionBlock(iBlockID - 1)->Draw(rR, (int)(iX*32 + Application::getMap()->getXPos()), (int)(CCFG::GAME_HEIGHT - 16 - iY*32 - jumpDistance));
	} else {
		Application::getMap()->getMinionBlock(iBlockID - 1)->Draw(rR, (int)(iX*32 + Application::getMap()->getXPos()), (int)(CCFG::GAME_HEIGHT - 16 - iY*32 - jumpDistance));
		for(int i = 0; i < jumpDistance/32 - 1; i++) {
			iIMG->Draw(rR, (int)(iX*32 + Application::getMap()->getXPos()), (int)(CCFG::GAME_HEIGHT + 16 - iY*32 + i*32 - jumpDistance), false);
		}
	}
	Application::getMap()->getBlock(Application::getMap()->getMapBlock((int)iX, (int)iY)->getBlockID())->getSprite()->getTexture()->Draw(rR, (int)(iX*32 + Application::getMap()->getXPos()), (int)(CCFG::GAME_HEIGHT - iY*32 - 16 - Application::getMap()->getMapBlock((int)iX, (int)iY)->getYPos()));
}

void Vine::minionPhysics() { }

/* ******************************************** */

void Vine::collisionWithPlayer(bool TOP) {
	if(minionState == 0) {
		Application::getMap()->setInEvent(true);

		Application::getMap()->getEvent()->resetData();
		Application::getMap()->getPlayer()->resetJump();
		Application::getMap()->getPlayer()->stopMove();

		Application::getMap()->getEvent()->eventTypeID = Application::getMap()->getEvent()->eNormal;

		Application::getMap()->getEvent()->iSpeed = 2;

		Application::getMap()->getEvent()->newLevelType = Application::getMap()->getLevelType();
		Application::getMap()->getEvent()->newCurrentLevel = Application::getMap()->getCurrentLevelID();
		Application::getMap()->getEvent()->newMoveMap = true;
		Application::getMap()->getEvent()->iDelay = 0;
		Application::getMap()->getEvent()->inEvent = false;

		Application::getMap()->getEvent()->newMoveMap = true;
		Application::getMap()->getEvent()->newUnderWater = false;

		if(fXPos + iHitBoxX/2 > Application::getMap()->getPlayer()->getXPos() - Application::getMap()->getXPos()) {
			Application::getMap()->getEvent()->vOLDDir.push_back(Application::getMap()->getEvent()->eRIGHT);
			Application::getMap()->getEvent()->vOLDLength.push_back(Application::getMap()->getPlayer()->getHitBoxX() - 4);
		} else {
			Application::getMap()->getEvent()->vOLDDir.push_back(Application::getMap()->getEvent()->eLEFT);
			Application::getMap()->getEvent()->vOLDLength.push_back(Application::getMap()->getPlayer()->getHitBoxX() - 4);
		}

		for(int i = 0; i < Application::getMap()->getPlayer()->getYPos() + Application::getMap()->getPlayer()->getHitBoxY(); i += 32) {
			Application::getMap()->getEvent()->vOLDDir.push_back(Application::getMap()->getEvent()->eVINE1);
			Application::getMap()->getEvent()->vOLDLength.push_back(16);
			Application::getMap()->getEvent()->vOLDDir.push_back(Application::getMap()->getEvent()->eVINE2);
			Application::getMap()->getEvent()->vOLDLength.push_back(16);
		}

		switch(Application::getMap()->getCurrentLevelID()) {
			case 4: {
				Application::getMap()->getEvent()->newMapXPos = -270*32;
				Application::getMap()->getEvent()->newPlayerXPos = 128;
				Application::getMap()->getEvent()->newPlayerYPos = CCFG::GAME_HEIGHT - Application::getMap()->getPlayer()->getHitBoxY();
				Application::getMap()->getEvent()->vOLDDir.push_back(Application::getMap()->getEvent()->eVINESPAWN);
				Application::getMap()->getEvent()->vOLDLength.push_back(274);

				break;
			}
			case 8: {
				Application::getMap()->getEvent()->newMapXPos = -270*32;
				Application::getMap()->getEvent()->newPlayerXPos = 128;
				Application::getMap()->getEvent()->newPlayerYPos = CCFG::GAME_HEIGHT - Application::getMap()->getPlayer()->getHitBoxY();
				Application::getMap()->getEvent()->vOLDDir.push_back(Application::getMap()->getEvent()->eVINESPAWN);
				Application::getMap()->getEvent()->vOLDLength.push_back(274);

				break;
			}
			case 13: {
				Application::getMap()->getEvent()->newMapXPos = -310*32;
				Application::getMap()->getEvent()->newPlayerXPos = 128;
				Application::getMap()->getEvent()->newPlayerYPos = CCFG::GAME_HEIGHT - Application::getMap()->getPlayer()->getHitBoxY();
				Application::getMap()->getEvent()->newLevelType = 0;

				Application::getMap()->getEvent()->vOLDDir.push_back(Application::getMap()->getEvent()->eVINESPAWN);
				Application::getMap()->getEvent()->vOLDLength.push_back(314);
				break;
			}
			case 17: {
				Application::getMap()->getEvent()->newMapXPos = -325*32;
				Application::getMap()->getEvent()->newPlayerXPos = 128;
				Application::getMap()->getEvent()->newPlayerYPos = CCFG::GAME_HEIGHT - Application::getMap()->getPlayer()->getHitBoxY();
				Application::getMap()->getEvent()->newLevelType = 0;

				Application::getMap()->getEvent()->vOLDDir.push_back(Application::getMap()->getEvent()->eVINESPAWN);
				Application::getMap()->getEvent()->vOLDLength.push_back(329);
				break;
			}
			case 21: {
				Application::getMap()->getEvent()->newMapXPos = -390*32;
				Application::getMap()->getEvent()->newPlayerXPos = 128;
				Application::getMap()->getEvent()->newPlayerYPos = CCFG::GAME_HEIGHT - Application::getMap()->getPlayer()->getHitBoxY();
				Application::getMap()->getEvent()->newLevelType = 4;

				Application::getMap()->getEvent()->vOLDDir.push_back(Application::getMap()->getEvent()->eVINESPAWN);
				Application::getMap()->getEvent()->vOLDLength.push_back(394);
				break;
			}
		}

		Application::getMap()->getEvent()->vOLDDir.push_back(Application::getMap()->getEvent()->eNOTHING);
		Application::getMap()->getEvent()->vOLDLength.push_back(60);

		for(int i = 0; i < 64; i += 32) {
			Application::getMap()->getEvent()->vNEWDir.push_back(Application::getMap()->getEvent()->eVINE1);
			Application::getMap()->getEvent()->vNEWLength.push_back(16);
			Application::getMap()->getEvent()->vNEWDir.push_back(Application::getMap()->getEvent()->eVINE2);
			Application::getMap()->getEvent()->vNEWLength.push_back(16);
		}
		
	} else {

	}
}
#include "BulletBillSpawner.h"
#include "Application.h"
#include <cstdlib>
#include <ctime>

/* ******************************************** */

BulletBillSpawner::BulletBillSpawner(int iXPos, int iYPos, int minionState) {
	this->fXPos = (float)iXPos;
	this->fYPos = (float)iYPos;

	this->moveSpeed = 0;

	this->collisionOnlyWithPlayer = true;

	this->minionState = minionState;

	this->iBlockID = 0;
	this->minionSpawned = minionState != 0;

	srand((unsigned)time(NULL));

	this->nextBulletBillFrameID = 12;
}

BulletBillSpawner::~BulletBillSpawner(void) {

}

/* ******************************************** */

void BulletBillSpawner::Update() {
	if(nextBulletBillFrameID <= 0) {
		if(minionState == 0) {
			if(fXPos > -Application::getMap()->getXPos() - 64 && fXPos < -Application::getMap()->getXPos() + CCFG::GAME_WIDTH + 64 + iHitBoxX) {
				if(!(Application::getMap()->getPlayer()->getXPos() - Application::getMap()->getXPos() + Application::getMap()->getPlayer()->getHitBoxX()/2 > fXPos - 96 && Application::getMap()->getPlayer()->getXPos() - Application::getMap()->getXPos() + Application::getMap()->getPlayer()->getHitBoxX()/2 < fXPos + 96)) {
					Application::getMap()->addBulletBill((int)fXPos, (int)fYPos - 14, true, minionState);
					nextBulletBillFrameID = 145 + rand()%145;
				}
			}
		} else {
			Application::getMap()->addBulletBill((int)(-Application::getMap()->getXPos() + CCFG::GAME_WIDTH + iHitBoxX * 2), (int)fYPos - rand()%9*32 - 16, true, minionState);
			nextBulletBillFrameID = 80 + rand()%96;
		}
	} else {
		if(!(Application::getMap()->getPlayer()->getXPos() - Application::getMap()->getXPos() + Application::getMap()->getPlayer()->getHitBoxX()/2 > fXPos - 96 && Application::getMap()->getPlayer()->getXPos() - Application::getMap()->getXPos() + Application::getMap()->getPlayer()->getHitBoxX()/2 < fXPos + 96)) {
			--nextBulletBillFrameID;
		}
	}
}

void BulletBillSpawner::minionPhysics() { }

/* ******************************************** */
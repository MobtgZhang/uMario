#include "BulletBill.h"
#include "Application.h"

/* ******************************************** */

BulletBill::BulletBill(int iXPos, int iYPos, bool moveDirection, int minionState) {
	this->fXPos = (float)iXPos;
	this->fYPos = (float)iYPos - 2;

	this->moveDirection = Application::getMap()->getPlayer()->getXPos() - Application::getMap()->getXPos() + Application::getMap()->getPlayer()->getHitBoxX()/32 < fXPos + iHitBoxX/32;
	this->moveSpeed = 4;

	this->iHitBoxY = 30;

	this->collisionOnlyWithPlayer = true;

	this->iBlockID = Application::getMap()->getCurrentLevelID() == 22 ? 60 : 59;

	this->minionSpawned = true;

	this->minionState = minionState;

	this->currentJumpSpeed = (float)Application::getMap()->getBlockIDX((int)(fXPos + 16));
	this->currentFallingSpeed = (float)Application::getMap()->getBlockIDY((int)(fYPos));

	this->currentJumpDistance = (float)(Application::getMap()->getCurrentLevelID() == 17 ? 73*32 : 0); // -- MIN X
	this->jumpState = Application::getMap()->getCurrentLevelID() == 17 ? 303*32 : Application::getMap()->getMapWidth()*32; // -- MAX X

	CCFG::getMusic()->PlayChunk(CCFG::getMusic()->cBULLETBILL);
}

BulletBill::~BulletBill(void) {

}

/* ******************************************** */

void BulletBill::Update() {
	if(minionState != -2) {
		fXPos += moveDirection ? -moveSpeed : moveSpeed;

		if(fXPos + iHitBoxX < currentJumpDistance || fXPos > jumpState) {
			minionState = -1;
		}
	} else {
		Minion::minionDeathAnimation();
	}
}

void BulletBill::Draw(SDL_Renderer* rR, CImg* iIMG) {
	if(minionState != -2) {
		iIMG->Draw(rR, (int)fXPos + (int)Application::getMap()->getXPos(), (int)fYPos + 2, moveDirection);
	} else {
		iIMG->DrawVert(rR, (int)fXPos + (int)Application::getMap()->getXPos(), (int)fYPos);
	}

	if(minionState == 0) Application::getMap()->getBlock(145)->getSprite()->getTexture()->Draw(rR,(int)(currentJumpSpeed*32 + Application::getMap()->getXPos()), (int)(CCFG::GAME_HEIGHT - 16 - currentFallingSpeed*32) + 32);
}

void BulletBill::minionPhysics() { }

/* ******************************************** */

void BulletBill::collisionWithPlayer(bool TOP) {
	if(Application::getMap()->getPlayer()->getStarEffect() || TOP) {
		setMinionState(-2);
	} else {
		Application::getMap()->playerDeath(true, false);
	}
}
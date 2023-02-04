#include "Pipe.h"
#include "Application.h"

/* ******************************************** */

Pipe::Pipe(int iType, int iLX, int iLY, int iRX, int iRY, int newPlayerPosX, int newPlayerPosY, int newCurrentLevel, int newLevelType, bool newMoveMap, int iDelay, int iSpeed, bool newUnderWater) {
	this->iType = iType;
	
	this->iLX = iLX;
	this->iLY = iLY;
	this->iRX = iRX;
	this->iRY = iRY;

	this->newPlayerPosX = newPlayerPosX;
	this->newPlayerPosY = newPlayerPosY;

	this->newCurrentLevel = newCurrentLevel;
	this->newLevelType = newLevelType;
	this->newMoveMap = newMoveMap;
	this->newUnderWater = newUnderWater;

	this->iDelay = iDelay;

	this->iSpeed = iSpeed;
}


Pipe::~Pipe(void) {

}

/* ******************************************** */

void Pipe::checkUse() {
	if(iType == 0 || iType == 2) {
		if(Application::getMap()->getPlayer()->getSquat() && -(int)Application::getMap()->getXPos() + Application::getMap()->getPlayer()->getXPos() >= iLX * 32 + 4 && -(int)Application::getMap()->getXPos() + Application::getMap()->getPlayer()->getXPos() + Application::getMap()->getPlayer()->getHitBoxX() < (iRX + 1) * 32 - 4) {
			setEvent();
		}
	} else {
		if(!Application::getMap()->getPlayer()->getSquat() && Application::getMap()->getBlockIDX(-(int)Application::getMap()->getXPos() + Application::getMap()->getPlayer()->getXPos() + Application::getMap()->getPlayer()->getHitBoxX() / 2 + 2) == iRX - 1 && Application::getMap()->getBlockIDY(Application::getMap()->getPlayer()->getYPos() + Application::getMap()->getPlayer()->getHitBoxY() + 2) == iRY - 1) {
			setEvent();
		}
	}
}

/* ******************************************** */

void Pipe::setEvent() {
	Application::getMap()->getEvent()->resetData();
	Application::getMap()->getPlayer()->stopMove();
	Application::getMap()->getPlayer()->resetJump();

	CCFG::getMusic()->PlayChunk(CCFG::getMusic()->cPIPE);

	Application::getMap()->getEvent()->eventTypeID = Application::getMap()->getEvent()->eNormal;

	Application::getMap()->getEvent()->newCurrentLevel = newCurrentLevel;
	Application::getMap()->getEvent()->newLevelType = newLevelType;
	Application::getMap()->getEvent()->newMoveMap = newMoveMap;

	Application::getMap()->getEvent()->iSpeed = iSpeed;
	Application::getMap()->getEvent()->iDelay = iDelay;

	Application::getMap()->getEvent()->inEvent = false;

	Application::getMap()->getEvent()->newUnderWater = newUnderWater;

	Application::getMap()->getEvent()->newMapXPos = (newPlayerPosX <= 32 * 2 ? 0 : -(newPlayerPosX - 32 * 2));
	Application::getMap()->getEvent()->newPlayerXPos = (newPlayerPosX <= 32 * 2 ? newPlayerPosX : 32 * 2);
	Application::getMap()->getEvent()->newPlayerYPos = newPlayerPosY;

	if(iType == 0) { // VERTICAL -> NONE
		Application::getMap()->getEvent()->newPlayerYPos -= Application::getMap()->getPlayer()->getPowerLVL() > 0 ? 32 : 0;
		Application::getMap()->getEvent()->vOLDDir.push_back(Application::getMap()->getEvent()->eBOT);
		Application::getMap()->getEvent()->vOLDLength.push_back(Application::getMap()->getPlayer()->getHitBoxY());

		Application::getMap()->getEvent()->vOLDDir.push_back(Application::getMap()->getEvent()->eNOTHING);
		Application::getMap()->getEvent()->vOLDLength.push_back(35);

		for(int i = 0; i < 3; i++) {
			Application::getMap()->getEvent()->reDrawX.push_back(iLX);
			Application::getMap()->getEvent()->reDrawY.push_back(iLY - i);
			Application::getMap()->getEvent()->reDrawX.push_back(iRX);
			Application::getMap()->getEvent()->reDrawY.push_back(iRY - i);
		}
	} else if(iType == 1) {
		Application::getMap()->getEvent()->newPlayerXPos += 32 - Application::getMap()->getPlayer()->getHitBoxX() / 2;

		Application::getMap()->getEvent()->vOLDDir.push_back(Application::getMap()->getEvent()->eRIGHT);
		Application::getMap()->getEvent()->vOLDLength.push_back(Application::getMap()->getPlayer()->getHitBoxX());

		Application::getMap()->getEvent()->vOLDDir.push_back(Application::getMap()->getEvent()->eNOTHING);
		Application::getMap()->getEvent()->vOLDLength.push_back(35);

		Application::getMap()->getEvent()->vNEWDir.push_back(Application::getMap()->getEvent()->ePLAYPIPETOP);
		Application::getMap()->getEvent()->vNEWLength.push_back(1);

		Application::getMap()->getEvent()->vNEWDir.push_back(Application::getMap()->getEvent()->eNOTHING);
		Application::getMap()->getEvent()->vNEWLength.push_back(35);

		Application::getMap()->getEvent()->vNEWDir.push_back(Application::getMap()->getEvent()->eTOP);
		Application::getMap()->getEvent()->vNEWLength.push_back(Application::getMap()->getPlayer()->getHitBoxY());

		for(int i = 0; i < 3; i++) {
			Application::getMap()->getEvent()->reDrawX.push_back(iLX + i);
			Application::getMap()->getEvent()->reDrawY.push_back(iLY);
			Application::getMap()->getEvent()->reDrawX.push_back(iRX + i);
			Application::getMap()->getEvent()->reDrawY.push_back(iRY);

			Application::getMap()->getEvent()->reDrawX.push_back(Application::getMap()->getBlockIDX(Application::getMap()->getEvent()->newPlayerXPos - Application::getMap()->getEvent()->newMapXPos));
			Application::getMap()->getEvent()->reDrawY.push_back(Application::getMap()->getBlockIDY(newPlayerPosY) - 1 - i);
			Application::getMap()->getEvent()->reDrawX.push_back(Application::getMap()->getBlockIDX(Application::getMap()->getEvent()->newPlayerXPos - Application::getMap()->getEvent()->newMapXPos) + 1);
			Application::getMap()->getEvent()->reDrawY.push_back(Application::getMap()->getBlockIDY(newPlayerPosY) - 1 - i);
		}
	} else { // -- VERT -> VERT
		Application::getMap()->getEvent()->newPlayerXPos -= Application::getMap()->getPlayer()->getPowerLVL() > 0 ? 32 : 0 - Application::getMap()->getPlayer()->getHitBoxX()/2;
		Application::getMap()->getEvent()->vOLDDir.push_back(Application::getMap()->getEvent()->eBOT);
		Application::getMap()->getEvent()->vOLDLength.push_back(Application::getMap()->getPlayer()->getHitBoxY());

		Application::getMap()->getEvent()->vOLDDir.push_back(Application::getMap()->getEvent()->eNOTHING);
		Application::getMap()->getEvent()->vOLDLength.push_back(55);

		for(int i = 0; i < 3; i++) {
			Application::getMap()->getEvent()->reDrawX.push_back(iLX);
			Application::getMap()->getEvent()->reDrawY.push_back(iLY - i);
			Application::getMap()->getEvent()->reDrawX.push_back(iRX);
			Application::getMap()->getEvent()->reDrawY.push_back(iRY - i);

			Application::getMap()->getEvent()->reDrawX.push_back(Application::getMap()->getBlockIDX(Application::getMap()->getEvent()->newPlayerXPos - Application::getMap()->getEvent()->newMapXPos));
			Application::getMap()->getEvent()->reDrawY.push_back(Application::getMap()->getBlockIDY(newPlayerPosY) - 1 - i);
			Application::getMap()->getEvent()->reDrawX.push_back(Application::getMap()->getBlockIDX(Application::getMap()->getEvent()->newPlayerXPos - Application::getMap()->getEvent()->newMapXPos) + 1);
			Application::getMap()->getEvent()->reDrawY.push_back(Application::getMap()->getBlockIDY(newPlayerPosY) - 1 - i);
		}

		Application::getMap()->getEvent()->vNEWDir.push_back(Application::getMap()->getEvent()->ePLAYPIPETOP);
		Application::getMap()->getEvent()->vNEWLength.push_back(1);

		Application::getMap()->getEvent()->vNEWDir.push_back(Application::getMap()->getEvent()->eNOTHING);
		Application::getMap()->getEvent()->vNEWLength.push_back(35);

		Application::getMap()->getEvent()->vNEWDir.push_back(Application::getMap()->getEvent()->eTOP);
		Application::getMap()->getEvent()->vNEWLength.push_back(Application::getMap()->getPlayer()->getHitBoxY());
	}

	Application::getMap()->setInEvent(true);
}
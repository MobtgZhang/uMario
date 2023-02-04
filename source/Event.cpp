#include "Event.h"
#include "Application.h"

/* ******************************************** */

Event::Event(void) {
	this->iDelay = 0;
	this->newUnderWater = false;
	this->endGame = false;
	this->iTime = 0;
	this->bState = true;
	this->stepID = 0;
}

Event::~Event(void) {

}

/* ******************************************** */

void Event::Draw(SDL_Renderer* rR) {
	for(unsigned int i = 0; i < reDrawX.size(); i++) {
		if(reDrawX[i] < Application::getMap()->getMapWidth())
			Application::getMap()->getBlock(Application::getMap()->getMapBlock(reDrawX[i], reDrawY[i])->getBlockID())->Draw(rR, 32 * reDrawX[i] + (int)Application::getMap()->getXPos(), CCFG::GAME_HEIGHT - 32 * reDrawY[i] - 16);
	}
}

/* ******************************************** */

void Event::Animation() {
	switch(eventTypeID) {
		case eNormal: {
			Normal();
			break;
		}
		case eEnd: {
			Normal();
			end();
			break;
		}
		case eBossEnd: {
			Normal();
			break;
		}
		default:
			Normal();
			break;
	}
}

void Event::Normal() {
	if(bState) {
		if(vOLDDir.size() > stepID) {
			if(vOLDLength[stepID] > 0) {
				switch(vOLDDir[stepID]) {
					case eTOP: // TOP
						Application::getMap()->getPlayer()->setYPos((float)Application::getMap()->getPlayer()->getYPos() - iSpeed);
						vOLDLength[stepID] -= iSpeed;
						break;
					case eBOT:
						Application::getMap()->getPlayer()->setYPos((float)Application::getMap()->getPlayer()->getYPos() + iSpeed);
						vOLDLength[stepID] -= iSpeed;
						break;
					case eRIGHT:
						Application::getMap()->getPlayer()->setXPos((float)Application::getMap()->getPlayer()->getXPos() + iSpeed);
						vOLDLength[stepID] -= iSpeed;
						Application::getMap()->getPlayer()->moveAnimation();
						Application::getMap()->getPlayer()->setMoveDirection(true);
						break;
					case eRIGHTEND:
						Application::getMap()->setXPos((float)Application::getMap()->getXPos() - iSpeed);
						vOLDLength[stepID] -= iSpeed;
						Application::getMap()->getPlayer()->moveAnimation();
						Application::getMap()->getPlayer()->setMoveDirection(true);
						break;
					case eLEFT:
						Application::getMap()->getPlayer()->setXPos((float)Application::getMap()->getPlayer()->getXPos() - iSpeed);
						vOLDLength[stepID] -= iSpeed;
						Application::getMap()->getPlayer()->moveAnimation();
						Application::getMap()->getPlayer()->setMoveDirection(false);
						break;
					case eBOTRIGHTEND: // BOT & RIGHT
						Application::getMap()->getPlayer()->setYPos((float)Application::getMap()->getPlayer()->getYPos() + iSpeed);
						Application::getMap()->setXPos((float)Application::getMap()->getXPos() - iSpeed);
						vOLDLength[stepID] -= iSpeed;
						Application::getMap()->getPlayer()->moveAnimation();
						break;
					case eENDBOT1:
						Application::getMap()->getPlayer()->setYPos((float)Application::getMap()->getPlayer()->getYPos() + iSpeed);
						vOLDLength[stepID] -= iSpeed;
						Application::getMap()->getPlayer()->setMarioSpriteID(10);
						break;
					case eENDBOT2:
						vOLDLength[stepID] -= iSpeed;
						Application::getMap()->getPlayer()->setMoveDirection(false);
						break;
					case eENDPOINTS:
						if(Application::getMap()->getMapTime() > 0) {
							Application::getMap()->setMapTime(Application::getMap()->getMapTime() - 1);
							Application::getMap()->getPlayer()->setScore(Application::getMap()->getPlayer()->getScore() + 50);
							if(CCFG::getMusic()->musicStopped) {
								CCFG::getMusic()->PlayMusic(CCFG::getMusic()->mSCORERING);
							}
						} else {
							vOLDLength[stepID] = 0;
							CCFG::getMusic()->StopMusic();
						}
						Application::getMap()->getFlag()->UpdateCastleFlag();
						break;
					case eDEATHNOTHING:
						vOLDLength[stepID] -= iSpeed;
						Application::getMap()->getPlayer()->setMarioSpriteID(0);
						break;
					case eDEATHTOP: // DEATH TOP
						Application::getMap()->getPlayer()->setYPos((float)Application::getMap()->getPlayer()->getYPos() - iSpeed);
						vOLDLength[stepID] -= iSpeed;
						Application::getMap()->getPlayer()->setMarioSpriteID(0);
						break;
					case eDEATHBOT: // DEATH BOT
						Application::getMap()->getPlayer()->setYPos((float)Application::getMap()->getPlayer()->getYPos() + iSpeed);
						vOLDLength[stepID] -= iSpeed;
						Application::getMap()->getPlayer()->setMarioSpriteID(0);
						break;
					case eNOTHING: // NOTHING YAY
						vOLDLength[stepID] -= 1;
						break;
					case ePLAYPIPERIGHT:
						Application::getMap()->getPlayer()->setXPos((float)Application::getMap()->getPlayer()->getXPos() + iSpeed);
						vOLDLength[stepID] -= 1;
						CCFG::getMusic()->PlayChunk(CCFG::getMusic()->cPIPE);
						break;
					case eLOADINGMENU:
						vOLDLength[stepID] -= 1;

						if(vOLDLength[stepID] < 2) {
							Application::getMap()->setInEvent(false);
							inEvent = false;
							Application::getMap()->getPlayer()->stopMove();
							
							CCFG::getMM()->getLoadingMenu()->loadingType = true;
							CCFG::getMM()->getLoadingMenu()->updateTime();
							CCFG::getMM()->setViewID(CCFG::getMM()->eGameLoading);
						}
						break;
					case eGAMEOVER:
						vOLDLength[stepID] -= 1;

						if(vOLDLength[stepID] < 2) {
							Application::getMap()->setInEvent(false);
							inEvent = false;
							Application::getMap()->getPlayer()->stopMove();
							
							CCFG::getMM()->getLoadingMenu()->loadingType = false;
							CCFG::getMM()->getLoadingMenu()->updateTime();
							CCFG::getMM()->setViewID(CCFG::getMM()->eGameLoading);

							CCFG::getMusic()->PlayChunk(CCFG::getMusic()->cGAMEOVER);
						}
						break;
					case eBOSSEND1:
						for(int i = Application::getMap()->getMapWidth() - 1; i > 0; i--) {
							if(Application::getMap()->getMapBlock(i, 6)->getBlockID() == 82) {
								Application::getMap()->getMapBlock(i, 6)->setBlockID(0);
								break;
							}
						}
						//Application::getMap()->getMapBlock(Application::getMap()->getBlockIDX((int)(Application::getMap()->getPlayer()->getXPos() + Application::getMap()->getPlayer()->getHitBoxX()/2 - Application::getMap()->getXPos()) + vOLDLength[stepID] - 1), 6)->setBlockID(0);
						Application::getMap()->clearPlatforms();
						CCFG::getMusic()->PlayChunk(CCFG::getMusic()->cBRIDGEBREAK);
						vOLDLength[stepID] = 0;
						Application::getMap()->getPlayer()->setMoveDirection(false);
						break;
					case eBOSSEND2:
						//Application::getMap()->getMapBlock(Application::getMap()->getBlockIDX((int)(Application::getMap()->getPlayer()->getXPos() + Application::getMap()->getPlayer()->getHitBoxX()/2 - Application::getMap()->getXPos())) - 1, 5)->setBlockID(0);
						//Application::getMap()->getMapBlock(Application::getMap()->getBlockIDX((int)(Application::getMap()->getPlayer()->getXPos() + Application::getMap()->getPlayer()->getHitBoxX()/2 - Application::getMap()->getXPos())) - 1, 4)->setBlockID(0);
						for(int i = Application::getMap()->getMapWidth() - 1; i > 0; i--) {
							if(Application::getMap()->getMapBlock(i, 5)->getBlockID() == 79) {
								Application::getMap()->getMapBlock(i, 5)->setBlockID(0);
								break;
							}
						}
						for(int i = Application::getMap()->getMapWidth() - 1; i > 0; i--) {
							if(Application::getMap()->getMapBlock(i, 4)->getBlockID() == 76) {
								Application::getMap()->getMapBlock(i, 4)->setBlockID(0);
								break;
							}
						}
						CCFG::getMusic()->PlayChunk(CCFG::getMusic()->cBRIDGEBREAK);
						vOLDLength[stepID] = 0;
						break;
					case eBOSSEND3:
						for(int i = Application::getMap()->getMapWidth() - 1; i > 0; i--) {
							if(Application::getMap()->getMapBlock(i, 4)->getBlockID() == 76) {
								Application::getMap()->getMapBlock(i, 4)->setBlockID(0);
								break;
							}
						}
						//Application::getMap()->getMapBlock(Application::getMap()->getBlockIDX((int)(Application::getMap()->getPlayer()->getXPos() + Application::getMap()->getPlayer()->getHitBoxX()/2 - Application::getMap()->getXPos())) - vOLDLength[stepID], 4)->setBlockID(0);
						CCFG::getMusic()->PlayChunk(CCFG::getMusic()->cBRIDGEBREAK);
						Application::getMap()->getPlayer()->setMoveDirection(true);
						vOLDLength[stepID] = 0;
						break;
					case eBOSSEND4:
						CCFG::getMusic()->PlayChunk(CCFG::getMusic()->cBOWSERFALL);
						vOLDLength[stepID] = 0;
						break;
					case eBOTRIGHTBOSS: // BOT & RIGHT
						Application::getMap()->getPlayer()->moveAnimation();
						Application::getMap()->getPlayer()->playerPhysics();
						Application::getMap()->setXPos((float)Application::getMap()->getXPos() - iSpeed);
						vOLDLength[stepID] -= iSpeed;
						break;
					case eBOSSTEXT1:
						Application::getMap()->addText(vOLDLength[stepID], CCFG::GAME_HEIGHT - 16 - 9*32, "THANK YOU MARIOz");
						vOLDLength[stepID] = 0;
						break;
					case eBOSSTEXT2:
						Application::getMap()->addText(vOLDLength[stepID] + 16, CCFG::GAME_HEIGHT - 16 - 7*32, "BUT OUR PRINCESS IS IN");
						Application::getMap()->addText(vOLDLength[stepID] + 16, CCFG::GAME_HEIGHT - 16 - 6*32, "ANOTHER CASTLEz");
						vOLDLength[stepID] = 0;
						break;
					case eENDGAMEBOSSTEXT1:
						Application::getMap()->addText(vOLDLength[stepID], CCFG::GAME_HEIGHT - 16 - 9*32, "THANK YOU MARIOz");
						vOLDLength[stepID] = 0;
						break;
					case eENDGAMEBOSSTEXT2:
						Application::getMap()->addText(vOLDLength[stepID] + 16, CCFG::GAME_HEIGHT - 16 - 7*32, "YOUR QUEST IS OVER.");
						vOLDLength[stepID] = 0;
						break;
					case eMARIOSPRITE1:
						Application::getMap()->getPlayer()->setMarioSpriteID(1);
						vOLDLength[stepID] = 0;
						break;
					case eVINE1:
						Application::getMap()->getPlayer()->setYPos((float)Application::getMap()->getPlayer()->getYPos() - iSpeed);
						vOLDLength[stepID] -= iSpeed;
						Application::getMap()->getPlayer()->setMarioSpriteID(10);
						break;
					case eVINE2:
						Application::getMap()->getPlayer()->setYPos((float)Application::getMap()->getPlayer()->getYPos() - iSpeed);
						vOLDLength[stepID] -= iSpeed;
						Application::getMap()->getPlayer()->setMarioSpriteID(11);
						break;
					case eVINESPAWN:
						Application::getMap()->addVine(vOLDLength[stepID], 0, 1, newLevelType == 0 || newLevelType == 4 ? 34 : 36);
						vOLDLength[stepID] = 0;
						break;
				}
			} else {
				++stepID;
				iTime = SDL_GetTicks();
			}
		} else {
			if(!endGame) {
				if(SDL_GetTicks() >= iTime + iDelay) {
					bState = false;
					stepID = 0;
					newLevel();
					Application::getMap()->getPlayer()->stopMove();
					if(inEvent) {
						CCFG::getMM()->getLoadingMenu()->updateTime();
						CCFG::getMM()->getLoadingMenu()->loadingType = true;
						CCFG::getMM()->setViewID(CCFG::getMM()->eGameLoading);
						Application::getMap()->startLevelAnimation();
					}

					CCFG::keySpace = false;
				}
			} else {
				Application::getMap()->resetGameData();
				CCFG::getMM()->setViewID(CCFG::getMM()->eMainMenu);
				Application::getMap()->setInEvent(false);
				Application::getMap()->getPlayer()->stopMove();
				inEvent = false;
				CCFG::keySpace = false;
				endGame = false;
				stepID = 0;
			}
		}
	} else {
		if(vNEWDir.size() > stepID) {
			if(vNEWLength[stepID] > 0) {
				switch(vNEWDir[stepID]) {
					case eTOP: // TOP
						Application::getMap()->getPlayer()->setYPos((float)Application::getMap()->getPlayer()->getYPos() - iSpeed);
						vNEWLength[stepID] -= iSpeed;
						break;
					case eBOT:
						Application::getMap()->getPlayer()->setYPos((float)Application::getMap()->getPlayer()->getYPos() + iSpeed);
						vNEWLength[stepID] -= iSpeed;
						break;
					case eRIGHT:
						Application::getMap()->getPlayer()->setXPos((float)Application::getMap()->getPlayer()->getXPos() + iSpeed);
						vNEWLength[stepID] -= iSpeed;
						Application::getMap()->getPlayer()->moveAnimation();
						break;
					case eLEFT:
						Application::getMap()->getPlayer()->setXPos((float)Application::getMap()->getPlayer()->getXPos() - iSpeed);
						vNEWLength[stepID] -= iSpeed;
						Application::getMap()->getPlayer()->moveAnimation();
						break;
					case ePLAYPIPETOP:
						vNEWLength[stepID] -= 1;
						CCFG::getMusic()->PlayChunk(CCFG::getMusic()->cPIPE);
						break;
					case eNOTHING: // NOTHING YAY
						vNEWLength[stepID] -= 1;
						break;
					case eVINE1:
						Application::getMap()->getPlayer()->setYPos((float)Application::getMap()->getPlayer()->getYPos() - iSpeed);
						vNEWLength[stepID] -= iSpeed;
						Application::getMap()->getPlayer()->setMarioSpriteID(10);
						break;
					case eVINE2:
						Application::getMap()->getPlayer()->setYPos((float)Application::getMap()->getPlayer()->getYPos() - iSpeed);
						vNEWLength[stepID] -= iSpeed;
						Application::getMap()->getPlayer()->setMarioSpriteID(11);
						break;
				}
			} else {
				++stepID;
			}
		} else {
			Application::getMap()->setInEvent(false);
			Application::getMap()->getPlayer()->stopMove();
			CCFG::getMusic()->changeMusic(true, true);
			inEvent = false;
			CCFG::keySpace = false;
			Application::resetKeys();
		}
	}
}

void Event::end() {
	if(Application::getMap()->getFlag() != NULL && Application::getMap()->getFlag()->iYPos < CCFG::GAME_HEIGHT - 16 - 3*32 - 4) {
		Application::getMap()->getFlag()->Update();
	}
}

void Event::newLevel() {
	Application::getMap()->setXPos((float)newMapXPos);
	Application::getMap()->getPlayer()->setXPos((float)newPlayerXPos);
	Application::getMap()->getPlayer()->setYPos((float)newPlayerYPos);
	Application::getMap()->setMoveMap(newMoveMap);
	if(Application::getMap()->getCurrentLevelID() != newCurrentLevel) {
		CCFG::getMM()->getLoadingMenu()->updateTime();
		CCFG::getMM()->getLoadingMenu()->loadingType = true;
		CCFG::getMM()->setViewID(CCFG::getMM()->eGameLoading);
		Application::getMap()->getPlayer()->setCoins(0);
	}
	Application::getMap()->setCurrentLevelID(newCurrentLevel);
	Application::getMap()->setLevelType(newLevelType);
	if(newUnderWater) {
		Application::getMap()->getPlayer()->resetRun();
	}
	Application::getMap()->setUnderWater(newUnderWater);

	Application::getMap()->lockMinions();
}

/* ******************************************** */

void Event::resetData() {
	vNEWDir.clear();
	vNEWLength.clear();
	vOLDDir.clear();
	vOLDLength.clear();
	resetRedraw();

	this->eventTypeID = eNormal;

	this->bState = true;
	this->stepID = 0;
	this->inEvent = false;
	this->endGame = false;
	this->newUnderWater = false;
}

void Event::resetRedraw() {
	reDrawX.clear();
	reDrawY.clear();
}
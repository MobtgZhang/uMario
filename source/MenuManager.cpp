#include "MenuManager.h"
#include "Application.h"

/* ******************************************** */

MenuManager::MenuManager(void) {
	this->currentGameState = eMainMenu;

	this->oMainMenu = new MainMenu();
	this->oLoadingMenu = new LoadingMenu();
	this->oAboutMenu = new AboutMenu();
	this->oConsole = new Console();
	this->oOptionsMenu = new OptionsMenu();
	this->oLE = new LevelEditor();
	this->oPauseMenu = new PauseMenu();
}


MenuManager::~MenuManager(void) {
	delete activeOption;
	delete oMainMenu;
	delete oLoadingMenu;
	delete oAboutMenu;
	delete oLE;
	delete oConsole;
}

/* ******************************************** */

void MenuManager::Update() {
	switch(currentGameState) {
		case eMainMenu:
			oMainMenu->Update();
			Application::getMap()->UpdateBlocks();
			break;
		case eGameLoading:
			oLoadingMenu->Update();
			break;
		case eGame:
			Application::getMap()->Update();
			Application::getMap()->UpdateMinionsCollisions();
			if(CCFG::displayConsole) oLE->Update();
			break;
		case eAbout:
			Application::getMap()->UpdateMinions();
			Application::getMap()->UpdateMinionBlokcs();
			Application::getMap()->UpdateBlocks();
			oAboutMenu->Update();
			break;
		case eOptions:
			oOptionsMenu->Update();
			break;
		case ePasue:
			oPauseMenu->Update();
			break;
	}
}

void MenuManager::Draw(SDL_Renderer* rR) {
	switch(currentGameState) {
		case eMainMenu:
			Application::getMap()->DrawMap(rR);
			Application::getMap()->getPlayer()->Draw(rR);
			Application::getMap()->DrawGameLayout(rR);
			oMainMenu->Draw(rR);
			break;
		case eGameLoading:
			oLoadingMenu->Draw(rR);
			break;
		case eGame:
			Application::getMap()->Draw(rR);
			if(CCFG::displayConsole) oLE->Draw(rR);
			break;
		case eAbout:
			Application::getMap()->DrawMap(rR);
			//Application::getMap()->getPlayer()->Draw(rR);
			Application::getMap()->DrawMinions(rR);
			oAboutMenu->Draw(rR);
			break;
		case eOptions:
			Application::getMap()->DrawMap(rR);
			Application::getMap()->DrawMinions(rR);
			Application::getMap()->getPlayer()->Draw(rR);
			Application::getMap()->DrawGameLayout(rR);
			oOptionsMenu->Draw(rR);
			break;
		case ePasue:
			Application::getMap()->DrawMap(rR);
			Application::getMap()->DrawMinions(rR);
			Application::getMap()->getPlayer()->Draw(rR);
			Application::getMap()->DrawGameLayout(rR);
			oPauseMenu->Draw(rR);
			break;
	}
	//-- CRT EFFECT
	if(CCFG::crtEffect){
		SDL_SetRenderDrawBlendMode(rR, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(rR, 0, 0, 0, CCFG::getMusic()->getVolume());
		for(int i = 0; i < CCFG::GAME_WIDTH; i += 2) {
			SDL_RenderDrawLine(rR, i, 0, i, CCFG::GAME_WIDTH);
		}
		for(int i = 0; i < CCFG::GAME_HEIGHT; i += 2) {
			SDL_RenderDrawLine(rR, 0, i, CCFG::GAME_WIDTH, i);
		}
	}
	
	if(CCFG::displayConsole){
		oConsole->Draw(rR);
	}
	Application::getMap()->setBackgroundColor(rR);
}

void MenuManager::setBackgroundColor(SDL_Renderer* rR) {
	switch(currentGameState) {
		case eMainMenu:
			Application::getMap()->setBackgroundColor(rR);
			break;
		case eGameLoading:
			SDL_SetRenderDrawColor(rR, 0, 0, 0, 255);
			break;
		case eGame:
			Application::getMap()->setBackgroundColor(rR);
			break;
		case eAbout:
			oAboutMenu->setBackgroundColor(rR);
			break;
	}
}

/* ******************************************** */

void MenuManager::enter() {
	switch(currentGameState) {
		case eMainMenu:
			oMainMenu->enter();
			break;
		case eGame:
			Application::getMap()->setDrawLines(!Application::getMap()->getDrawLines());
			break;
		case eAbout:
			oAboutMenu->enter();
			break;
		case eOptions:
			oOptionsMenu->enter();
			break;
		case ePasue:
			oPauseMenu->enter();
			break;
	}
}

void MenuManager::escape() {
	switch(currentGameState) {
		case eGame:
			
			break;
		case eAbout:
			oAboutMenu->enter();
			break;
		case eOptions:
			oOptionsMenu->escape();
			break;
		case ePasue:
			oPauseMenu->escape();
			break;
		case eMainMenu:
			oMainMenu->escape();
			break;
	}
}

void MenuManager::setKey(int keyID) {
	switch(currentGameState) {
		case eOptions:
			oOptionsMenu->setKey(keyID);
			break;
	}
}

void MenuManager::keyPressed(int iDir) {
	switch(currentGameState) {
		case eMainMenu:
			oMainMenu->updateActiveButton(iDir);
			break;
		case eOptions:
			oOptionsMenu->updateActiveButton(iDir);
			break;
		case ePasue:
			oPauseMenu->updateActiveButton(iDir);
			break;
	}
}

void MenuManager::resetActiveOptionID(gameState ID) {
	switch(ID) {
		case eMainMenu:
			oMainMenu->activeMenuOption = 0;
			break;
		case eOptions:
			oOptionsMenu->activeMenuOption = 0;
			break;
		case ePasue:
			oPauseMenu->activeMenuOption = 0;
			break;
	}
}

/* ******************************************** */

int MenuManager::getViewID() {
	return currentGameState;
}

void MenuManager::setViewID(gameState viewID) {
	this->currentGameState = viewID;
}

CImg* MenuManager::getActiveOption() {
	return activeOption;
}

void MenuManager::setActiveOption(SDL_Renderer* rR) {
	activeOption = new CImg("active_option", rR);
}

LoadingMenu* MenuManager::getLoadingMenu() {
	return oLoadingMenu;
}

AboutMenu* MenuManager::getAboutMenu() {
	return oAboutMenu;
}

Console* MenuManager::getConsole() {
	return oConsole;
}

LevelEditor* MenuManager::getLE() {
	return oLE;
}

OptionsMenu* MenuManager::getOptions() {
	return oOptionsMenu;
}
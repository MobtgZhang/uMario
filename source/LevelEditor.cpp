#include "LevelEditor.h"
#include "CFG.h"
#include "Application.h"

/* ******************************************** */

LevelEditor::LevelEditor(void) {
	this->rBlock.h = this->rBlock.w = 32;
	this->currentBlockID = 0;
}

LevelEditor::~LevelEditor(void) {

}

/* ******************************************** */

void LevelEditor::Update() {
	if(Application::mouseRightPressed) {
		rDrag.w = Application::mouseX - rDrag.x;
		rDrag.h = Application::mouseY - rDrag.y;
	} else {
		rBlock.x = Application::mouseX - (-(int)Application::getMap()->getXPos() + Application::mouseX)%32;
		rBlock.y = Application::mouseY - (Application::mouseY - 16)%32;
		rBlock.w = rBlock.h = 32;

		rDrag.x = Application::mouseX;
		rDrag.y = Application::mouseY;
	}

	editMap();
}

void LevelEditor::Draw(SDL_Renderer* rR) {
	SDL_SetRenderDrawBlendMode(rR, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(rR, 255, 255, 255, 128);
	SDL_SetTextureAlphaMod(Application::getMap()->getBlock(currentBlockID)->getSprite()->getTexture()->getIMG(), 225);
	
	if(Application::mouseRightPressed) {
		drawStruct(rR);

		SDL_SetRenderDrawColor(rR, 242, 242, 242, 78);
		SDL_RenderFillRect(rR, &rDrag);
		SDL_SetRenderDrawColor(rR, 255, 255, 255, 235);
		SDL_RenderDrawRect(rR, &rDrag);
	} else {
		Application::getMap()->getBlock(currentBlockID)->getSprite()->getTexture()->Draw(rR, rBlock.x, rBlock.y);
		SDL_RenderDrawRect(rR, &rBlock);
	}

	SDL_SetTextureAlphaMod(Application::getMap()->getBlock(currentBlockID)->getSprite()->getTexture()->getIMG(), 255);
	SDL_SetRenderDrawColor(rR, 255, 255, 255, 255);
	SDL_SetRenderDrawBlendMode(rR, SDL_BLENDMODE_NONE);
}

/* ******************************************** */

void LevelEditor::mouseWheel(int Y) {
	if(Y > 0) {
		if(currentBlockID > 0) {
			currentBlockID -= Y;
		}
	} else {
		if(currentBlockID < 100) {
			currentBlockID -= Y;
		}
	}
}

void LevelEditor::editMap() {
	if(Application::mouseLeftPressed) {
		Application::getMap()->getMapBlock((int)(((-Application::getMap()->getXPos() + Application::mouseX) - (int)((-Application::getMap()->getXPos() + Application::mouseX))%32)/32), (CCFG::GAME_HEIGHT - Application::mouseY + 16)/32)->setBlockID(currentBlockID);
	}
}

/* ******************************************** */

void LevelEditor::drawStruct(SDL_Renderer* rR) {
	int W = Application::mouseX - Application::mouseX%32 - rDrag.x + rDrag.x%32;
	int H = Application::mouseY - (Application::mouseY - 16)%32 - rDrag.y + rDrag.y%32;
	W += W > 0 ? 32 : 0;
	H += H > 0 ? 32 : -32;

	for(int i = 0, k = 0; k < (W > 0 ? W : -W); k += 32, i += W > 0 ? 32 : -32) {
		for(int j = 0, m = 0; m < (H > 0 ? H : -H); m += 32, j += H > 0 ? 32 : -32) {
			Application::getMap()->getBlock(currentBlockID)->getSprite()->getTexture()->Draw(rR, rBlock.x + i, rBlock.y + j);
		}
	}
}
#ifndef CFG_H
#define CFG_H

#include "Text.h"
#include "MenuManager.h"
#include "Music.h"

class CCFG
{
private:
	static MenuManager* oMM;
	static Text* oText;
	static CImg* tSMBLOGO;
	static Music* oMusic;
public:
	CCFG(void);
	~CCFG(void);

	static int GAME_WIDTH, GAME_HEIGHT;

	static bool keySpace;

	static int keyIDA, keyIDS, keyIDD, keyIDSpace, keyIDShift;

	static std::string getKeyString(int keyID);

	static CImg* getSMBLOGO();

	static Text* getText();

	static MenuManager* getMM();
	static Music* getMusic();

	static bool canMoveBackward;

	static bool displayConsole;

	static bool crtEffect;
};

#endif

#ifndef UI_END_GAME_DIALOGUE_H
#define UI_END_GAME_DIALOGUE_H
#pragma once

#include "cocos2d.h"
#include "../Classes/Scenes/GameScene.h"
#include "../Classes/Scenes/MainMenuScene.h"
#include "../Classes/UIElements/UIDialogue.h"

class UIEndGameDialogue: public UIDialogue
{
protected:
	virtual bool init() override;

	void menuNoCallback(Ref* pSender) override;
	void menuYesCallback(Ref* pSender) override;

public:
	CREATE_FUNC(UIEndGameDialogue);
};

#endif // !UI_END_GAME_DIALOGUE_H

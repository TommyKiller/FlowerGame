#ifndef UI_MAIN_MENU_H
#define UI_MAIN_MENU_H
#pragma once

#include "cocos2d.h"
#include "../Classes/Level.h"
#include "../Classes/Scenes/GameScene.h"

class UIMainMenu: public cocos2d::Menu
{
protected:
	virtual bool init() override;

public:
	CREATE_FUNC(UIMainMenu);
};

#endif // !UI_MAIN_MENU_h

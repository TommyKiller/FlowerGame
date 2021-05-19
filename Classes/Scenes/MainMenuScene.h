#ifndef MAIN_MENU_SCENE_H
#define MAIN_MENU_SCENE_H
#pragma once

#include "cocos2d.h"
#include "../Classes/UIElements/UIMainMenu.h"

class MainMenuScene : public cocos2d::Scene
{
protected:
    virtual bool init() override;

public:
    CREATE_FUNC(MainMenuScene);
};

#endif // !MAIN_MENU_SCENE_H

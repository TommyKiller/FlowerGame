#ifndef GAME_END_TRIGGER_H
#define GAME_END_TRIGGER_H
#pragma once

#include "cocos2d.h"
#include "../Classes/Scenes/GameScene.h"
#include "../Classes/UIElements/UIEndGameDialogue.h"

class GameEndTrigger : public cocos2d::Node
{
private:
	int _flower_cost;

protected:
	GameEndTrigger(int flower_cost);

public:
	static GameEndTrigger* create(GameScene* scene, int flower_cost);

	void onTrigger(cocos2d::EventCustom* event);
};

#endif // !GAME_END_TRIGGER_H

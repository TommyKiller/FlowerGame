#ifndef COLLECT_CASH_TRIGGER_H
#define COLLECT_CASH_TRIGGER_H
#pragma once

#include "cocos2d.h"
#include "../Classes/Scenes/GameScene.h"

class CollectCashTrigger : public cocos2d::Node
{
public:
	static CollectCashTrigger* create(GameScene* scene);

	void onTrigger(cocos2d::EventCustom* event);
};

#endif // !COLLECT_CASH_TRIGGER_H

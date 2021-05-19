#ifndef FLOWER_BUY_TRIGGER_H
#define FLOWER_BUY_TRIGGER_H
#pragma once

#include "cocos2d.h"
#include "../Classes/Scenes/GameScene.h"

class FlowerBuyTrigger : public cocos2d::Node
{
private:
	int _flower_cost;

protected:
	FlowerBuyTrigger(int flower_cost);

public:
	static FlowerBuyTrigger* create(GameScene* scene, int flower_cost);

	void onTrigger(cocos2d::EventMouse* event);
};

#endif // !FLOWER_BUY_TRIGGER_H

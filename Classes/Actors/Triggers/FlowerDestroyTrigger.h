#ifndef FLOWER_DESTROY_TRIGGER_H
#define FLOWER_DESTROY_TRIGGER_H
#pragma once

#include "cocos2d.h"
#include "../Classes/Scenes/GameScene.h"

class FlowerDestroyTrigger : public cocos2d::Node
{
public:
	static FlowerDestroyTrigger* create(GameScene* scene);

	void onTrigger(cocos2d::EventCustom* event);
};

#endif // !FLOWER_DESTROY_TRIGGER_H

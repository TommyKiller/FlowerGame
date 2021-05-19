#ifndef SNAKE_DESTROY_TRIGGER_H
#define SNAKE_DESTROY_TRIGGER_H
#pragma once

#include "cocos2d.h"
#include "../Classes/Scenes/GameScene.h"

class SnakeDestroyTrigger : public cocos2d::Node
{
public:
	static SnakeDestroyTrigger* create(GameScene* scene);

	bool onTrigger(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif // !SNAKE_DESTROY_TRIGGER_H

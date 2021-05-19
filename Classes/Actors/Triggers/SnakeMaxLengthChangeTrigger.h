#ifndef SNAKE_MAX_LENGTH_CHANGE_TRIGGER_H
#define SNAKE_MAX_LENGTH_CHANGE_TRIGGER_H
#pragma once

#include "cocos2d.h"
#include "../Classes/Scenes/GameScene.h"

class SnakeMaxLengthChangeTrigger : public cocos2d::Node
{
private:
	int _starting_max_length;
	int _max_length_multiplier;

protected:
	SnakeMaxLengthChangeTrigger(int starting_max_length, int max_length_multiplier);

public:
	static SnakeMaxLengthChangeTrigger* create(GameScene* scene, int starting_max_length, int max_length_multiplier);

	void onTrigger(cocos2d::EventCustom* event);
};

#endif // !SNAKE_MAX_LENGTH_CHANGE_TRIGGER_H

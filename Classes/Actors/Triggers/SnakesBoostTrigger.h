#ifndef SNAKES_BOOST_TRIGGER_H
#define SNAKES_BOOST_TRIGGER_H
#pragma once

#include "cocos2d.h"
#include "../Classes/Scenes/GameScene.h"

class SnakesBoostTrigger : public cocos2d::Node
{
private:
	bool _active;
	int _speed_multiplier;
	int _boost_duration;

protected:
	SnakesBoostTrigger(int speed_multiplier, int boost_duration);

public:
	static SnakesBoostTrigger* create(GameScene* scene, int speed_multiplier, int boost_duration);

	void onTrigger(cocos2d::EventCustom* event);
};

#endif // !SNAKES_BOOST_TRIGGER_H

#ifndef FLOWER_ACTOR_H
#define	FLOWER_ACTOR_H
#pragma once

#include "cocos2d.h"

class FlowerActor : public cocos2d::Sprite
{
private:
	static int _flowers_count;

private:
	int _time_to_grow;
	int _income;

public:
	inline static const std::string FLOWER_GROWN = "flowerGrown";

private:
	FlowerActor(cocos2d::Vec2 position, int time_to_grow, int income);

protected:
	virtual bool init() override;

public:
	static FlowerActor* create(cocos2d::Vec2 position, int time_to_grow, int income);
	static int getFlowersCount();

public:
	int getIncome();
	int getTimeToGrow();

	~FlowerActor();
};

#endif // !FLOWER_ACTOR_H

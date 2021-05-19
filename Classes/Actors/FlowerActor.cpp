#include "../Classes/Actors/FlowerActor.h"

int FlowerActor::_flowers_count = 0;

FlowerActor::FlowerActor(cocos2d::Vec2 position, int time_to_grow, int income) :
	_time_to_grow(time_to_grow), _income(income)
{
	setPosition(position);
	_flowers_count++;
}

bool FlowerActor::init()
{
	if (!initWithFile("Seed.png"))
	{
		return false;
	}

	setScale(0.3);
	cocos2d::Vector<cocos2d::FiniteTimeAction*> actions;
	actions.pushBack(cocos2d::DelayTime::create(_time_to_grow));
	actions.pushBack(cocos2d::CallFunc::create([this]() {
		setTexture("Flower.png");
		cocos2d::EventCustom event(FLOWER_GROWN);
		event.setUserData(this);
		getEventDispatcher()->dispatchEvent(&event);
	}));
	runAction(cocos2d::Sequence::create(actions));

	return true;
}

FlowerActor::~FlowerActor()
{
	_flowers_count--;
}

FlowerActor* FlowerActor::create(cocos2d::Vec2 position, int time_to_grow, int income)
{
	FlowerActor* pFlowerActor = new FlowerActor(position, time_to_grow, income);

	if (pFlowerActor->init())
	{
		pFlowerActor->autorelease();

		return pFlowerActor;
	}

	CC_SAFE_DELETE(pFlowerActor);
	return NULL;
}

int FlowerActor::getFlowersCount()
{
	return _flowers_count;
}

int FlowerActor::getIncome()
{
	return _income;
}

int FlowerActor::getTimeToGrow()
{
	return _time_to_grow;
}

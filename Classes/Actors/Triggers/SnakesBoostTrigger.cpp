#include "../Classes/Actors/Triggers/SnakesBoostTrigger.h"

SnakesBoostTrigger::SnakesBoostTrigger(int speed_multiplier, int boost_duration):
	_active(false), _speed_multiplier(speed_multiplier), _boost_duration(boost_duration)
{}

SnakesBoostTrigger* SnakesBoostTrigger::create(GameScene* scene, int speed_multiplier, int boost_duration)
{
	SnakesBoostTrigger* pBoostSnakesTrigger = new SnakesBoostTrigger(speed_multiplier, boost_duration);

	if (pBoostSnakesTrigger->init())
	{
		pBoostSnakesTrigger->autorelease();

		scene->addChild(pBoostSnakesTrigger);
		auto listener = cocos2d::EventListenerCustom::create(GameScene::ACTOR_DESTROYED_FLOWER, CC_CALLBACK_1(SnakesBoostTrigger::onTrigger, pBoostSnakesTrigger));
		scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, pBoostSnakesTrigger);

		return pBoostSnakesTrigger;
	}

	CC_SAFE_DELETE(pBoostSnakesTrigger);
	return NULL;
}

void SnakesBoostTrigger::onTrigger(cocos2d::EventCustom* event)
{
	if (!_active)
	{
		auto scene = dynamic_cast<GameScene*>(getScene());
		cocos2d::Vector<cocos2d::FiniteTimeAction*> actions;
		actions.pushBack(cocos2d::CallFunc::create([scene, this]()
			{
				Settings::SNAKE_MOVEMENT_SPEED *= _speed_multiplier;
				for (const auto& snake : scene->getAll<SnakeActor>())
				{
					snake->setSpeed(snake->getSpeed() * _speed_multiplier);
				}
				_active = true;
			}));
		actions.pushBack(cocos2d::DelayTime::create(_boost_duration));
		actions.pushBack(cocos2d::CallFunc::create([scene, this]()
			{
				Settings::SNAKE_MOVEMENT_SPEED /= _speed_multiplier;
				for (const auto& snake : scene->getAll<SnakeActor>())
				{
					snake->setSpeed(snake->getSpeed() / _speed_multiplier);
				}
				_active = false;
			}));
		runAction(cocos2d::Sequence::create(actions));
	}
}

#include "../Classes/Actors/Triggers/SnakeDestroyTrigger.h"

SnakeDestroyTrigger* SnakeDestroyTrigger::create(GameScene* scene)
{
	SnakeDestroyTrigger* pSnakeDestroyTrigger = new SnakeDestroyTrigger();

	if (pSnakeDestroyTrigger->init())
	{
		pSnakeDestroyTrigger->autorelease();

		scene->addChild(pSnakeDestroyTrigger);
		auto listener = cocos2d::EventListenerTouchOneByOne::create();
		listener->onTouchBegan = CC_CALLBACK_2(SnakeDestroyTrigger::onTrigger, pSnakeDestroyTrigger);
		scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, pSnakeDestroyTrigger);

		return pSnakeDestroyTrigger;
	}

	CC_SAFE_DELETE(pSnakeDestroyTrigger);
	return NULL;
}

bool SnakeDestroyTrigger::onTrigger(cocos2d::Touch* touch, cocos2d::Event* event)
{
	auto scene = dynamic_cast<GameScene*>(getScene());

	auto snakes = scene->getAll<SnakeActor>();
	for (int i = 0; i < snakes.size(); i++)
	{
		bool collides = false;

		for (const auto& area : snakes[i]->getArea())
		{
			if (area.containsPoint(touch->getLocation()))
			{
				collides = true;
			}
		}

		if (collides)
		{
			if (!snakes[i]->removeSegment())
			{
				scene->removeSnake(snakes[i]);
			}
		}
	}

	return true;
}

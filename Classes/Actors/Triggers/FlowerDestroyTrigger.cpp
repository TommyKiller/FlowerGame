#include "../Classes/Actors/Triggers/FlowerDestroyTrigger.h"

FlowerDestroyTrigger* FlowerDestroyTrigger::create(GameScene* scene)
{
	FlowerDestroyTrigger* pDestroyFlowerTrigger = new FlowerDestroyTrigger();

	if (pDestroyFlowerTrigger->init())
	{
		pDestroyFlowerTrigger->autorelease();

		scene->addChild(pDestroyFlowerTrigger);
		auto listener = cocos2d::EventListenerCustom::create(SnakeActor::ACTOR_MOVED_SNAKE, CC_CALLBACK_1(FlowerDestroyTrigger::onTrigger, pDestroyFlowerTrigger));
		scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, pDestroyFlowerTrigger);

		return pDestroyFlowerTrigger;
	}

	CC_SAFE_DELETE(pDestroyFlowerTrigger);
	return NULL;
}

void FlowerDestroyTrigger::onTrigger(cocos2d::EventCustom* event)
{
	auto snake = static_cast<SnakeActor*>(event->getUserData());
	auto scene = dynamic_cast<GameScene*>(getScene());

	for (const auto& area : snake->getArea())
	{
		auto collision = scene->checkArea<FlowerActor>(area);
		if (collision)
		{
			scene->removeFlower(collision);
		}
	}
}

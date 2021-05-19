#include "../Classes/Actors/Triggers/FlowerBuyTrigger.h"

FlowerBuyTrigger::FlowerBuyTrigger(int flower_cost):
	_flower_cost(flower_cost)
{}

FlowerBuyTrigger* FlowerBuyTrigger::create(GameScene* scene, int flower_cost)
{
	FlowerBuyTrigger* pBuyFlowerTrigger = new FlowerBuyTrigger(flower_cost);

	if (pBuyFlowerTrigger->init())
	{
		pBuyFlowerTrigger->autorelease();

		scene->addChild(pBuyFlowerTrigger);
		auto listener = cocos2d::EventListenerMouse::create();
		listener->onMouseDown = CC_CALLBACK_1(FlowerBuyTrigger::onTrigger, pBuyFlowerTrigger);
		scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, pBuyFlowerTrigger);

		return pBuyFlowerTrigger;
	}

	CC_SAFE_DELETE(pBuyFlowerTrigger);
	return NULL;
}

void FlowerBuyTrigger::onTrigger(cocos2d::EventMouse* event)
{
	if (event->getMouseButton() == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT)
	{
		auto scene = dynamic_cast<GameScene*>(getScene());
		auto player = scene->getPlayer();
		if (player->hasCash(_flower_cost) && scene->spawnFlower(event->getLocationInView()))
			player->withdrawCash(_flower_cost);
	}
}

#include "../Classes/Actors/Triggers/CollectCashTrigger.h"

CollectCashTrigger* CollectCashTrigger::create(GameScene* scene)
{
	CollectCashTrigger* pCollectCashTrigger = new CollectCashTrigger();

	if (pCollectCashTrigger->init())
	{
		pCollectCashTrigger->autorelease();

		scene->addChild(pCollectCashTrigger);
		auto listener = cocos2d::EventListenerCustom::create(GameScene::ACTOR_SPAWNED_COIN, CC_CALLBACK_1(CollectCashTrigger::onTrigger, pCollectCashTrigger));
		scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, pCollectCashTrigger);

		return pCollectCashTrigger;
	}

	CC_SAFE_DELETE(pCollectCashTrigger);
	return NULL;
}

void CollectCashTrigger::onTrigger(cocos2d::EventCustom* event)
{
	auto coin = static_cast<CoinActor*>(event->getUserData());
	auto player = dynamic_cast<GameScene*>(coin->getScene())->getPlayer();
	player->depositCash(coin->getDenomination());
}

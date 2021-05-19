#include "../Classes/Actors/Triggers/GameEndTrigger.h"

GameEndTrigger::GameEndTrigger(int flower_cost) :
	_flower_cost(flower_cost)
{}

GameEndTrigger* GameEndTrigger::create(GameScene* scene, int flower_cost)
{
	GameEndTrigger* pGameEndTrigger = new GameEndTrigger(flower_cost);

	if (pGameEndTrigger->init())
	{
		pGameEndTrigger->autorelease();

		scene->addChild(pGameEndTrigger);
		auto listener = cocos2d::EventListenerCustom::create(GameScene::ACTOR_DESTROYED_FLOWER, CC_CALLBACK_1(GameEndTrigger::onTrigger, pGameEndTrigger));
		scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, pGameEndTrigger);

		return pGameEndTrigger;
	}

	CC_SAFE_DELETE(pGameEndTrigger);
	return NULL;
}

void GameEndTrigger::onTrigger(cocos2d::EventCustom* event)
{
	auto scene = dynamic_cast<GameScene*>(getScene());
	if ((FlowerActor::getFlowersCount() == 0) && (scene->getPlayer()->getCash() < _flower_cost))
	{
		scene->stopAllActions();
		scene->addChild(UIEndGameDialogue::create());
	}
}

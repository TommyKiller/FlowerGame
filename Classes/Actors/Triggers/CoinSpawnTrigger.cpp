#include "../Classes/Actors/Triggers/CoinSpawnTrigger.h"

CoinSpawnTrigger::CoinSpawnTrigger(int coin_spawn_interval) :
	_coin_spawn_interval(coin_spawn_interval)
{}

CoinSpawnTrigger* CoinSpawnTrigger::create(GameScene* scene, int coin_spawn_interval)
{
	CoinSpawnTrigger* pCoinSpawnTrigger = new CoinSpawnTrigger(coin_spawn_interval);

	if (pCoinSpawnTrigger->init())
	{
		pCoinSpawnTrigger->autorelease();

		scene->addChild(pCoinSpawnTrigger);
		auto listener = cocos2d::EventListenerCustom::create(FlowerActor::FLOWER_GROWN, CC_CALLBACK_1(CoinSpawnTrigger::onTrigger, pCoinSpawnTrigger));
		scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, scene);

		return pCoinSpawnTrigger;
	}

	CC_SAFE_DELETE(pCoinSpawnTrigger);
	return NULL;
}

void CoinSpawnTrigger::onTrigger(cocos2d::EventCustom* event)
{
	auto flower = static_cast<FlowerActor*>(event->getUserData());

	cocos2d::Vector<cocos2d::FiniteTimeAction*> actions;
	actions.pushBack(cocos2d::DelayTime::create(_coin_spawn_interval));
	actions.pushBack(cocos2d::CallFunc::create([flower]()
		{
			cocos2d::Vec2 position = flower->getPosition();
			position.x -= 10;
			position.y += flower->getBoundingBox().size.height / 2;
			dynamic_cast<GameScene*>(flower->getScene())->spawnCoin(position, flower->getIncome());
		}));
	auto coin_spawn = cocos2d::RepeatForever::create(cocos2d::Sequence::create(actions));

	flower->runAction(coin_spawn);
}

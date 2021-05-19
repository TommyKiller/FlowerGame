#include "../Classes/Actors/Triggers/SnakeMaxLengthChangeTrigger.h"

SnakeMaxLengthChangeTrigger::SnakeMaxLengthChangeTrigger(int starting_max_length, int max_length_multiplier):
	_starting_max_length(starting_max_length), _max_length_multiplier(max_length_multiplier)
{}

SnakeMaxLengthChangeTrigger* SnakeMaxLengthChangeTrigger::create(GameScene* scene, int starting_max_length, int max_length_multiplier)
{
	SnakeMaxLengthChangeTrigger* pSnakeMaxLengthChangeTrigger = new SnakeMaxLengthChangeTrigger(starting_max_length, max_length_multiplier);

	if (pSnakeMaxLengthChangeTrigger->init())
	{
		pSnakeMaxLengthChangeTrigger->autorelease();

		scene->addChild(pSnakeMaxLengthChangeTrigger);
		auto listener = cocos2d::EventListenerCustom::create(GameScene::ACTOR_SPAWNED_FLOWER, CC_CALLBACK_1(SnakeMaxLengthChangeTrigger::onTrigger, pSnakeMaxLengthChangeTrigger));
		scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, pSnakeMaxLengthChangeTrigger);
		listener = cocos2d::EventListenerCustom::create(GameScene::ACTOR_DESTROYED_FLOWER, CC_CALLBACK_1(SnakeMaxLengthChangeTrigger::onTrigger, pSnakeMaxLengthChangeTrigger));
		scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, pSnakeMaxLengthChangeTrigger);

		return pSnakeMaxLengthChangeTrigger;
	}

	CC_SAFE_DELETE(pSnakeMaxLengthChangeTrigger);
	return NULL;
}

void SnakeMaxLengthChangeTrigger::onTrigger(cocos2d::EventCustom* event)
{
	GameScene* scene = dynamic_cast<GameScene*>(getScene());
	std::vector<FlowerActor*> flowers = scene->getAll<FlowerActor>();

	if (flowers.size() >= 2)
	{
		SnakeActor::setMaxLength(_starting_max_length * _max_length_multiplier);
	}
	else
	{
		SnakeActor::setMaxLength(_starting_max_length);
	}
}

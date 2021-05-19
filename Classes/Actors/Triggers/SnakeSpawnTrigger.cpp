#include "../Classes/Actors/Triggers/SnakeSpawnTrigger.h"

SnakeSpawnTrigger* SnakeSpawnTrigger::create(GameScene* scene, float snake_spawn_initial_interval, int snake_spawn_interval_modifier, int snake_spawn_interval_modification_interval)
{
	SnakeSpawnTrigger* pSnakeSpawnTrigger = new SnakeSpawnTrigger(snake_spawn_initial_interval, snake_spawn_interval_modifier, snake_spawn_interval_modification_interval);

	if (pSnakeSpawnTrigger->init())
	{
		pSnakeSpawnTrigger->autorelease();

		scene->addChild(pSnakeSpawnTrigger);
		auto listener = cocos2d::EventListenerCustom::create(GameScene::ACTOR_SPAWNED_FLOWER, CC_CALLBACK_1(SnakeSpawnTrigger::onTrigger, pSnakeSpawnTrigger));
		scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, pSnakeSpawnTrigger);

		return pSnakeSpawnTrigger;
	}

	CC_SAFE_DELETE(pSnakeSpawnTrigger);
	return NULL;
}

SnakeSpawnTrigger::SnakeSpawnTrigger(float snake_spawn_initial_interval, int snake_spawn_interval_modifier, int snake_spawn_interval_modification_interval):
	_snake_spawn_initial_interval(snake_spawn_initial_interval), _snake_spawn_interval_modifier(snake_spawn_interval_modifier), _snake_spawn_interval_modification_interval(snake_spawn_interval_modification_interval)
{}

void SnakeSpawnTrigger::onTrigger(cocos2d::EventCustom* event)
{
	auto flower = static_cast<FlowerActor*>(event->getUserData());
	auto spawner = SnakeSpawner::create(_snake_spawn_initial_interval);
	flower->addChild(spawner);
	cocos2d::Vector<cocos2d::FiniteTimeAction*> actions;
	actions.pushBack(cocos2d::DelayTime::create(_snake_spawn_interval_modification_interval));
	actions.pushBack(cocos2d::CallFunc::create([spawner, this]()
		{
			float interval = spawner->getSpawnInterval() - (_snake_spawn_interval_modifier / 100.f);
			spawner->setSpawnInterval(interval);
		}));
	auto sequence = cocos2d::Sequence::create(actions);
	spawner->runAction(cocos2d::RepeatForever::create(sequence));
}

SnakeSpawnTrigger::SnakeSpawner::SnakeSpawner(float snake_spawn_interval):
	_snake_spawn_interval(snake_spawn_interval)
{}

void SnakeSpawnTrigger::SnakeSpawner::onEnter()
{
	Node::onEnter();

	spawn(0.0f);
}

SnakeSpawnTrigger::SnakeSpawner* SnakeSpawnTrigger::SnakeSpawner::create(float _snake_spawn_interval)
{
	SnakeSpawner* pSnakeSpawner = new SnakeSpawner(_snake_spawn_interval);

	if (pSnakeSpawner->init())
	{
		pSnakeSpawner->autorelease();

		return pSnakeSpawner;
	}

	CC_SAFE_DELETE(pSnakeSpawner);
	return NULL;
}

void SnakeSpawnTrigger::SnakeSpawner::spawn(float dt)
{
	auto scene = dynamic_cast<GameScene*>(getScene());
	scene->spawnSnake();
	//this->scheduleOnce(CC_SCHEDULE_SELECTOR(SnakeSpawner::spawn), _snake_spawn_interval);
}

float SnakeSpawnTrigger::SnakeSpawner::getSpawnInterval()
{
	return _snake_spawn_interval;
}

void SnakeSpawnTrigger::SnakeSpawner::setSpawnInterval(float value)
{
	_snake_spawn_interval = value;
}

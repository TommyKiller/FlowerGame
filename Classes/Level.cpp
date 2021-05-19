#include "../Classes/Level.h"

void Level::setupTriggers(GameScene* scene)
{
	CoinSpawnTrigger::create(scene, Settings::COIN_SPAWN_INTERVAL);
	FlowerBuyTrigger::create(scene, Settings::FLOWER_COST);
	GameEndTrigger::create(scene, Settings::FLOWER_COST);
	CollectCashTrigger::create(scene);
	SnakeSpawnTrigger::create(scene, Settings::SNAKE_SPAWN_INTERVAL, Settings::SNAKE_SPAWN_INTERVAL_MODIFIER, Settings::SNAKE_SPAWN_INTERVAL_MODIFICATION_INTERVAL);
	FlowerDestroyTrigger::create(scene);
	SnakesBoostTrigger::create(scene, Settings::BONUS_SPEED_MULTIPLIER, Settings::BONUS_SPEED_DURATION);
	SnakeDestroyTrigger::create(scene);
	SnakeMaxLengthChangeTrigger::create(scene, Settings::SNAKE_MAX_LENGTH, Settings::SNAKE_MAX_LENGTH_MULTIPLIER);
}

GameScene* Level::setupLevel(GameScene* scene)
{
	setupTriggers(scene);

	return scene;
}

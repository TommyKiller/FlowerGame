#ifndef COIN_SPAWN_TRIGGER_H
#define	COIN_SPAWN_TRIGGER_H
#pragma once

#include "cocos2d.h"
#include "../Classes/Scenes/GameScene.h"

class CoinSpawnTrigger : public cocos2d::Node
{
private:
	int _coin_spawn_interval;

private:
	CoinSpawnTrigger(int coin_spawn_interval);

public:
	static CoinSpawnTrigger* create(GameScene* scene, int coin_spawn_interval);

	void onTrigger(cocos2d::EventCustom* event);
};

#endif // !COIN_SPAWN_TRIGGER_H

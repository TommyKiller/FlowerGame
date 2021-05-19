#ifndef SNAKE_SPAWN_TRIGGER_H
#define SNAKE_SPAWN_TRIGGER_H
#pragma once

#include "cocos2d.h"
#include "../Classes/Scenes/GameScene.h"

class SnakeSpawnTrigger : public cocos2d::Node
{
private:
	class SnakeSpawner: public cocos2d::Node
	{
	private:
		float _snake_spawn_interval;

	protected:
		SnakeSpawner(float snake_spawn_interval);

		void onEnter() override;

	public:
		static SnakeSpawner* create(float snake_spawn_interval);

		void spawn(float dt);

		float getSpawnInterval();
		void setSpawnInterval(float value);
	};

private:
	int _snake_spawn_interval_modification_interval;
	int _snake_spawn_interval_modifier;
	float _snake_spawn_initial_interval;

protected:
	SnakeSpawnTrigger(float snake_spawn_initial_interval, int snake_spawn_interval_modifier, int snake_spawn_interval_modification_interval);

public:
	static SnakeSpawnTrigger* create(GameScene* scene, float snake_spawn_initial_interval, int snake_spawn_interval_modifier, int snake_spawn_interval_modification_interval);

	void onTrigger(cocos2d::EventCustom* event);
};

#endif // !SNAKE_SPAWN_TRIGGER_H

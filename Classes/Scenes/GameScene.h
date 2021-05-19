#ifndef GAME_SCENE_H
#define GAME_SCENE_H
#pragma once

#include <memory>
#include <string>
#include "cocos2d.h"
#include "../Classes/Settings.h"
#include "../Classes/Actors/Actors.h"
#include "../Classes/UIElements/UIGameUserInterface.h"

class GameScene : public cocos2d::Scene
{
private:
	inline static const std::string _LAYER_BACKGROUND = "layerBackground";
	inline static const std::string _LAYER_FOREGROUND = "layerForeground";
	inline static const std::string _LAYER_UI = "layerUI";

public:
	inline static const std::string ACTOR_SPAWNED_COIN = "actorSpawnedCoin";
	inline static const std::string ACTOR_SPAWNED_SNAKE = "actorSpawnedSnake";
	inline static const std::string ACTOR_SPAWNED_FLOWER = "actorSpawnedFlower";
	inline static const std::string ACTOR_DESTROYED_FLOWER = "actorDestroyedFlower";
	inline static const std::string ACTOR_DESTROYED_SNAKE = "actorDestroyedSnake";
	
private:
	void initBackground();
	void initForeground();
	void initPlayer();
	void initUI();

	void dispatchEventActorSpawned(cocos2d::Node* actor, std::string event_type);

protected:
	virtual bool init() override;

public:
	CREATE_FUNC(GameScene);

	FlowerActor* spawnFlower(cocos2d::Vec2 position);
	CoinActor* spawnCoin(cocos2d::Vec2 position, int denomination);
	SnakeActor* spawnSnake();

	void removeFlower(FlowerActor* flower);
	void removeSnake(SnakeActor* snake);

	PlayerActor* getPlayer();
	template<class TActor>
	std::vector<TActor*> getAll()
	{
		std::vector<TActor*> actors;
		for (const auto& child : getChildByName(_LAYER_FOREGROUND)->getChildren())
		{
			auto actor = dynamic_cast<TActor*>(child);
			if (actor)
			{
				actors.push_back(actor);
			}
		}

		return actors;
	}

	cocos2d::Node* checkArea(cocos2d::Rect area);

	template<class TActor>
	TActor* checkArea(cocos2d::Rect area)
	{
		for (const auto& child : getChildByName(_LAYER_FOREGROUND)->getChildren())
		{
			auto actor = dynamic_cast<TActor*>(child);

			if (actor)
			{
				auto box = actor->getBoundingBox();
				if (box.containsPoint(cocos2d::Vec2(area.getMinX(), area.getMinY())) ||
					box.containsPoint(cocos2d::Vec2(area.getMinX(), area.getMaxY())) ||
					box.containsPoint(cocos2d::Vec2(area.getMaxX(), area.getMaxY())) ||
					box.containsPoint(cocos2d::Vec2(area.getMaxX(), area.getMinY())))
					return actor;
			}
		}

		return nullptr;
	}
};

#endif // !GAME_SCENE_H

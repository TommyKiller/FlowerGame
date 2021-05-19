#ifndef LEVEL_H
#define LEVEL_H

#include "../Classes/Scenes/GameScene.h"
#include "../Classes/Actors/Triggers/Triggers.h"

class Level
{
private:
	static void setupTriggers(GameScene* scene);

public:
	static GameScene* setupLevel(GameScene* scene);

};

#endif // !LEVEL_H

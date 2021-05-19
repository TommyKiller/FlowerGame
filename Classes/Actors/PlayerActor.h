#ifndef PLAYER_ACTOR_H
#define PLAYER_ACTOR_H

#include "cocos2d.h"

class PlayerActor: public cocos2d::Node
{
private:
	int _cash;

public:
	inline static const std::string CASH_CHANGED = "cashChanged";

private:
	void setCash(int cash);

public:
	CREATE_FUNC(PlayerActor);

public:
	int getCash();
	bool hasCash(int amount);
	void depositCash(int amount);
	bool withdrawCash(int amount);
};

#endif // !PLAYER_ACTOR_H

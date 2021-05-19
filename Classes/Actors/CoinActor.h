#ifndef COIN_ACTOR_H
#define	COIN_ACTOR_H
#pragma once

#include <string>
#include "cocos2d.h"

class CoinActor : public cocos2d::Node
{
private:
	int _denomination;

private:
	CoinActor(int denomination);

protected:
	virtual bool init() override;

public:
	static CoinActor* create(int denomination);

	int getDenomination();
};

#endif // !COIN_ACTOR_H

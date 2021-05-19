#include "../Classes/Actors/PlayerActor.h"

void PlayerActor::setCash(int cash)
{
	_cash = cash;

	cocos2d::EventCustom event(CASH_CHANGED);
	event.setUserData(&_cash);
	cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
}

int PlayerActor::getCash()
{
	return _cash;
}

bool PlayerActor::hasCash(int amount)
{
	return _cash >= amount;
}

void PlayerActor::depositCash(int amount)
{
	setCash(_cash + amount);
}

bool PlayerActor::withdrawCash(int amount)
{
	if (hasCash(amount))
	{
		setCash(_cash - amount);

		return true;
	}
	else return false;
}

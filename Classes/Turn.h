#ifndef TURN_H
#define TURN_H

#include "cocos2d.h"

struct Turn
{
public:
	Turn(cocos2d::Vec2 position, cocos2d::Vec2 direction);

	cocos2d::Vec2 position;
	cocos2d::Vec2 direction;
};

#endif // !TURN_H

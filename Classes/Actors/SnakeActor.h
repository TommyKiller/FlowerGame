#ifndef SNAKE_ACTOR_H
#define SNAKE_ACTOR_H
#pragma once

#include <queue>
#include "cocos2d.h"
#include "../Classes/MathUtils.h"
#include "../Classes/Turn.h"

inline static const cocos2d::Vec2 LEFT	= cocos2d::Vec2(-1.0, 0.0);
inline static const cocos2d::Vec2 RIGHT = cocos2d::Vec2( 1.0, 0.0);
inline static const cocos2d::Vec2 UP	= cocos2d::Vec2( 0.0, 1.0);
inline static const cocos2d::Vec2 DOWN	= cocos2d::Vec2( 0.0,-1.0);

class SnakeActorSegment;

class SnakeActor : public cocos2d::Sprite
{
private:
	inline static int _MAX_LENGTH = 5;

private:
	SnakeActorSegment* _head;
	SnakeActorSegment* _tail;
	int _speed;
	int _length;

public:
	inline static const std::string ACTOR_MOVED_SNAKE = "actorMovedSnake";

private:
	bool checkDirection(float dt, cocos2d::Vec2 direction);
	cocos2d::Vec2 randomizeDirection();

protected:
	SnakeActor(int speed);

	void update(float dt) override;

	virtual bool init() override;

public:
	static void setMaxLength(int length);

public:
	static SnakeActor* create(int speed);

	void addSegment();
	bool removeSegment();

	int getSpeed();;
	int getLength();
	void setSpeed(int speed);

	void setPosition(const cocos2d::Vec2& position) override;
	void setScene(cocos2d::Node* scene);

	cocos2d::Rect getBoundingBox() const override;
	std::vector<cocos2d::Rect> getArea();

	~SnakeActor();
};

class SnakeActorSegment
{
private:
	cocos2d::Vec2 _direction;
	cocos2d::Sprite* _sprite;
	SnakeActorSegment* _parent;
	SnakeActorSegment* _child;
	std::queue<Turn> _turns;

private:
	void setParent(SnakeActorSegment* segment);
	void removeParent();

public:
	SnakeActorSegment(std::string texture_filename);

	cocos2d::Vec2 getDirection();
	void setDirection(cocos2d::Vec2 direction);
	void updatePosition();

	std::queue<Turn> getTurns();
	void setTurns(std::queue<Turn> turns);
	void resetTurns();
	void addTurn(Turn turn);
	void turn(float dt, float speed);

	cocos2d::Sprite* getSprite();
	SnakeActorSegment* getChild();
	SnakeActorSegment* getParent();

	void setChild(SnakeActorSegment* segment);
	void removeChild();

	~SnakeActorSegment();

};

#endif // !SNAKE_ACTOR_H

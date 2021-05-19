#include "../Classes/Actors/SnakeActor.h"

bool SnakeActor::checkDirection(float dt, cocos2d::Vec2 direction)
{
	if ((_head->getDirection() + direction) == cocos2d::Vec2::ZERO)
		return false;

	cocos2d::Vec2 position = _head->getSprite()->getPosition() + (direction * getSpeed() * dt);
	cocos2d::Size visible_size = cocos2d::Director::getInstance()->getVisibleSize();
	if (position.x < 0 || position.x > visible_size.width ||
		position.y < 0 || position.y > visible_size.height)
	{
		return false;
	}

	return true;
}

cocos2d::Vec2 SnakeActor::randomizeDirection()
{
	int direction = cocos2d::RandomHelper::random_int(0, 3);

	switch (direction)
	{
	case 0:
		return LEFT;
		break;
	case 1:
		return RIGHT;
		break;
	case 2:
		return UP;
		break;
	case 3:
		return DOWN;
		break;
	default:
		return cocos2d::Vec2::ZERO;
		break;
	}
}

SnakeActor::SnakeActor(int speed) :
	_speed(speed), _length(0), _head(nullptr), _tail(nullptr)
{}

void SnakeActor::update(float dt)
{
	Sprite::update(dt);
	SnakeActorSegment* segment;

	// Turning
	int rnd = cocos2d::RandomHelper::random_int(0, 99);

	if (!checkDirection(dt, _head->getDirection()) || rnd < 1)
	{
		cocos2d::Vec2 direction;
		do
		{
			direction = randomizeDirection();
		} while (!checkDirection(dt, direction));

		_head->addTurn(Turn(_head->getSprite()->getPosition(), direction));
	}

	//Move
	segment = _head;
	do
	{
		segment->turn(dt, getSpeed());
		cocos2d::Vec2 position = segment->getSprite()->getPosition();
		position.x += segment->getDirection().x * getSpeed() * dt;
		position.y += segment->getDirection().y * getSpeed() * dt;
		segment->getSprite()->setPosition(position);
		segment = segment->getChild();
	} while (segment);

	cocos2d::EventCustom event(SnakeActor::ACTOR_MOVED_SNAKE);
	event.setUserData(this);
	getEventDispatcher()->dispatchEvent(&event);
}

bool SnakeActor::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	_head = new SnakeActorSegment("SnakeActorHead.png");
	_head->setDirection(randomizeDirection());
	_length++;

	_tail = new SnakeActorSegment("SnakeActorTail.png");
	_tail->setDirection(_head->getDirection());
	_length++;
	_head->setChild(_tail);

	cocos2d::Vector<cocos2d::FiniteTimeAction*> actions;
	actions.pushBack(cocos2d::DelayTime::create(3));
	actions.pushBack(cocos2d::CallFunc::create([this]()
		{
			if (_length < _MAX_LENGTH)
			{
				addSegment();
			}
		}));
	auto action = cocos2d::RepeatForever::create(cocos2d::Sequence::create(actions));
	runAction(action);

	scheduleUpdate();

	return true;
}

void SnakeActor::setMaxLength(int length)
{
	_MAX_LENGTH = length;
}

SnakeActor* SnakeActor::create(int speed)
{
	SnakeActor* pSnakeActor = new SnakeActor(speed);

	if (pSnakeActor->init())
	{
		pSnakeActor->autorelease();

		return pSnakeActor;
	}

	CC_SAFE_DELETE(pSnakeActor);
	return NULL;
}

void SnakeActor::addSegment()
{
	if (_tail)
	{
		// Create segment
		SnakeActorSegment* segment = new SnakeActorSegment("SnakeActorSegment.png");
		getScene()->addChild(segment->getSprite());

		// Placing new segment
		_tail->getParent()->setChild(segment);
		segment->setDirection(_tail->getDirection());
		segment->updatePosition();

		// Placing tail
		segment->setChild(_tail);
		_tail->setDirection(segment->getDirection());
		_tail->updatePosition();

		segment->setTurns(_tail->getTurns());
		_tail->resetTurns();
	}
	else
	{
		_tail = new SnakeActorSegment("SnakeActorTail.png");
		getScene()->addChild(_tail->getSprite());

		// Placing tail
		_head->setChild(_tail);
		_tail->setDirection(_head->getDirection());
		_tail->updatePosition();
	}

	_length++;
}

bool SnakeActor::removeSegment()
{
	if (_tail)
	{
		getBoundingBox();

		if (_tail->getParent() != _head)
		{
			auto segment = _tail->getParent()->getParent();
			auto delete_segment = segment->getChild();
			segment->setChild(_tail);
			_tail->setDirection(delete_segment->getDirection());
			_tail->updatePosition();
			_tail->setTurns(delete_segment->getTurns());
			delete delete_segment;
		}
		else
		{
			_head->removeChild();
			delete _tail;
			_tail = nullptr;
		}

		_length--;
		return true;
	}

	return false;
}

int SnakeActor::getSpeed()
{
	return _speed;
}

int SnakeActor::getLength()
{
	return _length;
}

cocos2d::Rect SnakeActor::getBoundingBox() const
{
	return _head->getSprite()->getBoundingBox();
}

std::vector<cocos2d::Rect> SnakeActor::getArea()
{
	std::vector<cocos2d::Rect> areas;
	auto segment = _head;

	while (segment != nullptr)
	{
		areas.push_back(segment->getSprite()->getBoundingBox());
		segment = segment->getChild();
	}

	return areas;
}

SnakeActor::~SnakeActor()
{
	delete _head;
	_head = nullptr;
}

void SnakeActor::setSpeed(int speed)
{
	_speed = speed;
}

void SnakeActor::setPosition(const cocos2d::Vec2& position)
{
	_head->getSprite()->setPosition(position);

	auto segment = _head->getChild();
	while (segment != nullptr)
	{
		segment->updatePosition();
		segment = segment->getChild();
	}
}

void SnakeActor::setScene(cocos2d::Node* scene)
{
	scene->addChild(this);

	auto segment = _head;
	while (segment != nullptr)
	{
		scene->addChild(segment->getSprite());
		segment = segment->getChild();
	}
}

// SnakeActorSegment

void SnakeActorSegment::setParent(SnakeActorSegment* segment)
{
	_parent = segment;
}

void SnakeActorSegment::removeParent()
{
	_parent = nullptr;
}

SnakeActorSegment::SnakeActorSegment(std::string texture_filename) :
	_parent(nullptr), _child(nullptr)
{
	_sprite = cocos2d::Sprite::create(texture_filename);
}

SnakeActorSegment* SnakeActorSegment::getChild()
{
	return _child;
}

SnakeActorSegment* SnakeActorSegment::getParent()
{
	return _parent;
}

void SnakeActorSegment::setChild(SnakeActorSegment* segment)
{
	if (_child)
	{
		_child->removeParent();
	}
	_child = segment;
	segment->setParent(this);
}

void SnakeActorSegment::removeChild()
{
	if (_child)
	{
		_child->removeParent();
		_child = nullptr;
	}
}

SnakeActorSegment::~SnakeActorSegment()
{
	_sprite->removeAllChildrenWithCleanup(true);
	_sprite->removeFromParent();
}

void SnakeActorSegment::setDirection(cocos2d::Vec2 direction)
{
	_direction = direction;
	auto rotation = radians_to_degrees(_direction.getAngle(cocos2d::Vec2(1.0, 0.0)));
	_sprite->setRotation(rotation);
}

void SnakeActorSegment::addTurn(Turn turn)
{
	_turns.push(turn);
}

void SnakeActorSegment::turn(float dt, float speed)
{
	if (!_turns.empty())
	{
		Turn turn = _turns.front();

		cocos2d::Vec2 turn_pos = turn.position;
		cocos2d::Vec2 start_pos = getSprite()->getPosition();
		cocos2d::Vec2 end_pos;
		end_pos.x = start_pos.x * getDirection().x * dt * speed;
		end_pos.y = start_pos.y * getDirection().y * dt * speed;

		if (belongs(start_pos, end_pos, turn_pos))
		{
			getSprite()->setPosition(turn.position);
			setDirection(turn.direction);

			if (_child)
			{
				_child->addTurn(turn);
			}

			_turns.pop();
		}
	}
}

//void SnakeActorSegment::turn(float dt)
//{
//	if (!_turns.empty())
//	{
//		Turn turn = _turns.front();
//		cocos2d::Vec2 position = getSprite()->getPosition();
//
//		if (((turn.position.x - dt <= position.x) || (position.x <= turn.position.x + dt)) &&
//			((turn.position.y - dt <= position.y) || (position.y <= turn.position.y + dt)))
//		{
//			getSprite()->setPosition(turn.position);
//			setDirection(turn.direction);
//
//			if (_child)
//			{
//				_child->addTurn(turn);
//			}
//
//			_turns.pop();
//		}
//	}
//}

void SnakeActorSegment::updatePosition()
{
 	cocos2d::Vec2 position = getParent()->getSprite()->getPosition();
	cocos2d::Size size = getParent()->getSprite()->getBoundingBox().size;
	cocos2d::Vec2 direction = getParent()->getDirection();
	position.x += size.width * direction.x * -1;
	position.y += size.height * direction.y * -1;

	_sprite->setPosition(position);

	/*SnakeActorSegment* segment = this;
	cocos2d::Vec2 position = cocos2d::Vec2::ZERO;

	while (segment->getParent() != nullptr)
	{
		cocos2d::Size size = segment->getParent()->getSprite()->getBoundingBox().size;
		cocos2d::Vec2 direction = segment->getParent()->getDirection();
		position.x += size.width * direction.x * -1;
		position.y += size.height * direction.y * -1;

		segment = segment->getParent();
	}

	position += segment->getSprite()->getPosition();

	_sprite->setPosition(position);*/
}

std::queue<Turn> SnakeActorSegment::getTurns()
{
	return _turns;
}

void SnakeActorSegment::setTurns(std::queue<Turn> turns)
{
	_turns = turns;
}

void SnakeActorSegment::resetTurns()
{
	// TODO
	_turns = std::queue<Turn>();
}

cocos2d::Vec2 SnakeActorSegment::getDirection()
{
	return _direction;
}

cocos2d::Sprite* SnakeActorSegment::getSprite()
{
	return _sprite;
}

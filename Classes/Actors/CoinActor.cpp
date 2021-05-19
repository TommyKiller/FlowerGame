#include "../Classes/Actors/CoinActor.h"

CoinActor::CoinActor(int denomination) :
	_denomination(denomination)
{}

bool CoinActor::init()
{
	if (!Node::init())
	{
		return false;
	}

	// Coin sprite
	auto coin_sprite = cocos2d::Sprite::create("Coin.png");
	coin_sprite->setPosition(getPosition());
	addChild(coin_sprite);

	// Coin label
	std::string text = std::to_string(_denomination) + " GOLD";
	auto coin_label = cocos2d::Label::createWithSystemFont(text, "Marker Felt", 30);
	coin_label->setPosition(getPosition().x, getPosition().y + coin_sprite->getBoundingBox().size.height / 2 + coin_label->getBoundingBox().size.height / 2);
	addChild(coin_label);

	// CoinActor
	setScale(0.3);
	setCascadeOpacityEnabled(true);

	// Actions
	// CoinActor sequence
	cocos2d::Vector<cocos2d::FiniteTimeAction*> coin_sequence_actions;
	cocos2d::Vector<cocos2d::FiniteTimeAction*> coin_spawn_actions;
	auto distance = cocos2d::Vec2(0, 250);
	coin_spawn_actions.pushBack(cocos2d::MoveBy::create(3, distance));
	coin_spawn_actions.pushBack(cocos2d::FadeTo::create(3, 0));
	coin_sequence_actions.pushBack(cocos2d::Spawn::create(coin_spawn_actions));
	coin_sequence_actions.pushBack(cocos2d::CallFunc::create([this]() {
		removeFromParentAndCleanup(true);
	}));
	auto main_sequence = cocos2d::Sequence::create(coin_sequence_actions);
	runAction(main_sequence);
	//// --------
	//// Coin sprite spin
	coin_sprite->runAction(cocos2d::RepeatForever::create(cocos2d::RotateBy::create(1, cocos2d::Vec3(0, 90, 0))));

	return true;
}

CoinActor* CoinActor::create(int denomination)
{
	CoinActor *pCoinActor = new CoinActor(denomination);

	if (pCoinActor->init())
	{
		pCoinActor->autorelease();

		return pCoinActor;
	}

	CC_SAFE_DELETE(pCoinActor);
	return NULL;
}

int CoinActor::getDenomination()
{
	return _denomination;
}

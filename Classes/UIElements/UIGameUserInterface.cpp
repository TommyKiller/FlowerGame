#include "../Classes/UIElements/UIGameUserInterface.h"

bool UIGameUserInterface::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visible_size = cocos2d::Director::getInstance()->getVisibleSize();
	setAnchorPoint(cocos2d::Vec2(0.5, 1.0));
	setPosition(visible_size.width / 2, visible_size.height);

	// Cash label
	_cash_label = cocos2d::Label::createWithTTF("", "fonts/Marker Felt.ttf", 20);
	_cash_label->setAnchorPoint(cocos2d::Vec2(0.0, 1.0));
	_cash_label->setPosition(visible_size.width / -2, 0);
	addChild(_cash_label);

	return true;
}

void UIGameUserInterface::setCashLabelText(std::string cash_value)
{
	_cash_label->setString(cash_value);
}

void UIGameUserInterface::updateCash(cocos2d::EventCustom* event)
{
	int* cash = static_cast<int*>(event->getUserData());
	_cash_label->setString(std::to_string(*cash));
}

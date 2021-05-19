#ifndef UI_GAME_USER_INTERFACE_H
#define UI_GAME_USER_INTERFACE_H
#pragma once

#include "cocos2d.h"

class UIGameUserInterface: public cocos2d::Layer
{
private:
	cocos2d::Label* _cash_label;

protected:
	virtual bool init() override;

public:
	CREATE_FUNC(UIGameUserInterface);

	void setCashLabelText(std::string cash_value);
	void updateCash(cocos2d::EventCustom* event);
};

#endif // !UI_GAME_USER_INTERFACE_H

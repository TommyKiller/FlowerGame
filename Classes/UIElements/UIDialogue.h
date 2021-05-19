#ifndef UI_DIALOGUE_H
#define UI_DIALOGUE_H
#pragma once

#include "cocos2d.h"

class UIDialogue: public cocos2d::Layer
{
protected:
	std::string _font_filename;
	cocos2d::Sprite* _background;
	cocos2d::Label* _label;
	cocos2d::MenuItemFont* _yes;
	cocos2d::MenuItemFont* _no;

protected:
	UIDialogue();

	virtual bool init() override;

	void setBackground(std::string filename);
	void setLabel(std::string text);
	void setFont(std::string font_filename);

	virtual void menuNoCallback(Ref* pSender) = 0;
	virtual void menuYesCallback(Ref* pSender) = 0;
};

#endif // !UI_DIALOGUE_H

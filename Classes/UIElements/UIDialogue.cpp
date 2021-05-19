#include "../Classes/UIElements/UIDialogue.h"

UIDialogue::UIDialogue():
	_font_filename("fonts/arial.ttf"), _background(nullptr), _label(nullptr)
{}

bool UIDialogue::init()
{
	if (!Layer::init())
	{
		return false;
	}

	cocos2d::Vec2 position;
	auto visible_size = cocos2d::Director::getInstance()->getVisibleSize();
	position.x = visible_size.width / 2;
	position.y = visible_size.height / 2;
	setPosition(position);

	// Background
	_background = cocos2d::Sprite::create();
	_background->setPosition(cocos2d::Vec2::ZERO);
	addChild(_background);

	// Label
	_label = cocos2d::Label::create();
	_label->setPosition(cocos2d::Vec2::ZERO);
	addChild(_label);

	// Menu
	_yes = cocos2d::MenuItemFont::create("Yes", CC_CALLBACK_1(UIDialogue::menuYesCallback, this));
	_no = cocos2d::MenuItemFont::create("No", CC_CALLBACK_1(UIDialogue::menuNoCallback, this));
	auto menu = cocos2d::Menu::create(_yes, _no, NULL);
	menu->setPosition(cocos2d::Vec2::ZERO);
	addChild(menu);

	return true;
}

void UIDialogue::setBackground(std::string filename)
{
	_background->setTexture(filename);
}

void UIDialogue::setLabel(std::string text)
{
	_label->setString(text);
}

void UIDialogue::setFont(std::string font_filename)
{
	_yes->setFontNameObj(font_filename);
	_no->setFontNameObj(font_filename);
	_label->setSystemFontName(font_filename);
}

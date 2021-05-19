#include "UIMainMenu.h"

bool UIMainMenu::init()
{
	if (!Menu::init())
	{
		return false;
	}

	auto visible_size = cocos2d::Director::getInstance()->getVisibleSize();
	auto play = cocos2d::MenuItemImage::create("PlayButton.png", "PlayButton.png", [&](Ref* sender) {
		cocos2d::Director::getInstance()->replaceScene(Level::setupLevel(GameScene::create()));
	});
	addChild(play);
	play->setPosition(visible_size.width / 2, visible_size.height / 3 * 2);
	play->setScale(0.85f);
	cocos2d::Vector<cocos2d::FiniteTimeAction*> actions;
	actions.pushBack(cocos2d::TintBy::create(3, 140, 100, 200));
	actions.pushBack(cocos2d::CallFunc::create([play]() {
		if (play->getScale() < 1.15f)
		{
			play->runAction(cocos2d::ScaleTo::create(3, 1.16f));
		}
		else
		{
			play->runAction(cocos2d::ScaleTo::create(3, 0.85f));
		}
	}));
	auto repeat_spawn = cocos2d::RepeatForever::create(cocos2d::Spawn::create(actions));
	play->runAction(repeat_spawn);

	auto close = cocos2d::MenuItemFont::create("Exit", [&](Ref* sender) {
		cocos2d::Director::getInstance()->end();
	});
	addChild(close);
	close->setPosition(visible_size.width / 2, visible_size.height / 3 * 1);

	return true;
}

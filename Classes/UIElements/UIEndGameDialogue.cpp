#include "../Classes/UIElements/UIEndGameDialogue.h"

bool UIEndGameDialogue::init()
{
	if (!UIDialogue::init())
	{
		return false;
	}

	setBackground("EndGameDialogueBackground.png");
	setLabel("Retry?");
	setFont("fonts/Marker Felt.ttf");
	_label->setSystemFontSize(40);
	_no->setPosition(-110, -35);
	_yes->setPosition(110, -35);
	_label->setPosition(0, 50);

	return true;
}

void UIEndGameDialogue::menuNoCallback(Ref* pSender)
{
	cocos2d::Director::getInstance()->replaceScene(MainMenuScene::create());
}

void UIEndGameDialogue::menuYesCallback(Ref* pSender)
{
	cocos2d::Director::getInstance()->replaceScene(Level::setupLevel(GameScene::create()));
}

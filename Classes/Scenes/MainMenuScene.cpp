#include "../Classes/Scenes/MainMenuScene.h"

bool MainMenuScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    auto main_menu = UIMainMenu::create();
    main_menu->setPosition(cocos2d::Vec2::ZERO);
    this->addChild(main_menu);
    return true;
}

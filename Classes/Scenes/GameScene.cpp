#include "../Classes/Scenes/GameScene.h"

void GameScene::initBackground()
{
	cocos2d::Size win_size = cocos2d::Director::getInstance()->getWinSize();
	
	// Background
	auto grass_background = cocos2d::Sprite::create("GrassBackground.png");
	cocos2d::Size content_size = grass_background->getContentSize();
	grass_background->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	grass_background->setPosition(win_size.width / 2, win_size.height / 2);
	grass_background->setScaleX(win_size.width / content_size.width);
	grass_background->setScaleY(win_size.height / content_size.height);

	// Background Layer
	auto layer = cocos2d::Layer::create();
	layer->setName(_LAYER_BACKGROUND);
	layer->addChild(grass_background);
	addChild(layer, 0);
}

void GameScene::initForeground()
{
	auto layer = cocos2d::Layer::create();
	layer->setName(_LAYER_FOREGROUND);
	addChild(layer, 1);
}

void GameScene::initPlayer()
{
	auto player = PlayerActor::create();
	player->setName(Settings::PLAYER_NAME);
	player->depositCash(Settings::PLAYER_INITIAL_CASH);
	addChild(player);
}

void GameScene::initUI()
{
	// UI Layer
	auto layer = cocos2d::Layer::create();
	layer->setName(_LAYER_UI);
	addChild(layer, 2);

	// UI
	auto ui = UIGameUserInterface::create();
	ui->setCashLabelText(std::to_string(getPlayer()->getCash()));
	layer->addChild(ui);

	// UI Event Handling
	auto listener = cocos2d::EventListenerCustom::create(PlayerActor::CASH_CHANGED, CC_CALLBACK_1(UIGameUserInterface::updateCash, ui));
	getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, ui);
}

void GameScene::dispatchEventActorSpawned(cocos2d::Node* actor, std::string event_type)
{
	cocos2d::EventCustom event(event_type);
	event.setUserData(actor);
	getEventDispatcher()->dispatchEvent(&event);
}

bool GameScene::init()
{
	if (!cocos2d::Scene::init())
	{
		return false;
	}

	initBackground();
	initForeground();
	initPlayer();
	initUI();

	return true;
}

FlowerActor* GameScene::spawnFlower(cocos2d::Vec2 position)
{
	position.x += 8;
	position.y += 23;
	auto flower = FlowerActor::create(position, Settings::FLOWER_TIME_TO_GROW, Settings::FLOWER_INCOME);
	auto collision = checkArea(flower->getBoundingBox());
	if (!collision)
	{
		getChildByName(_LAYER_FOREGROUND)->addChild(flower);
		dispatchEventActorSpawned(flower, ACTOR_SPAWNED_FLOWER);

		return flower;
	}

	return nullptr;
}

CoinActor* GameScene::spawnCoin(cocos2d::Vec2 position, int denomination)
{
	auto coin = CoinActor::create(denomination);
	position.y += coin->getBoundingBox().size.height / 3;
	coin->setPosition(position);
	getChildByName(_LAYER_FOREGROUND)->addChild(coin);
	dispatchEventActorSpawned(coin, ACTOR_SPAWNED_COIN);

	return coin;
}

SnakeActor* GameScene::spawnSnake()
{
	auto snake = SnakeActor::create(Settings::SNAKE_MOVEMENT_SPEED);
	do
	{
		auto scene_size = getBoundingBox();
		float x = cocos2d::RandomHelper::random_real(scene_size.getMinX(), scene_size.getMaxX());
		float y = cocos2d::RandomHelper::random_real(scene_size.getMinY(), scene_size.getMaxY());
		snake->setPosition(cocos2d::Vec2(x, y));
	} while (checkArea(snake->getBoundingBox()));

	snake->setScene(getChildByName(_LAYER_FOREGROUND));
	dispatchEventActorSpawned(snake, ACTOR_SPAWNED_SNAKE);

	return snake;
}

void GameScene::removeFlower(FlowerActor* flower)
{
	flower->removeFromParentAndCleanup(true);
	cocos2d::EventCustom event(ACTOR_DESTROYED_FLOWER);
	getEventDispatcher()->dispatchEvent(&event);
}

void GameScene::removeSnake(SnakeActor* snake)
{
	snake->removeFromParentAndCleanup(true);
	cocos2d::EventCustom event(ACTOR_DESTROYED_SNAKE);
	getEventDispatcher()->dispatchEvent(&event);
}

PlayerActor* GameScene::getPlayer()
{
	return dynamic_cast<PlayerActor*>(getChildByName(Settings::PLAYER_NAME));
}

cocos2d::Node* GameScene::checkArea(cocos2d::Rect area)
{
	for (const auto& child : getChildByName(_LAYER_FOREGROUND)->getChildren())
	{
		auto box = child->getBoundingBox();
		if (box.containsPoint(cocos2d::Vec2(area.getMinX(), area.getMinY())) ||
			box.containsPoint(cocos2d::Vec2(area.getMinX(), area.getMaxY())) ||
			box.containsPoint(cocos2d::Vec2(area.getMaxX(), area.getMaxY())) ||
			box.containsPoint(cocos2d::Vec2(area.getMaxX(), area.getMinY())))
			return child;
	}

	return nullptr;
}

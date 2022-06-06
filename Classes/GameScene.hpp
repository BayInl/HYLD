#pragma once
//#pragma execution_character_set("utf-8")
#include "cocos2d.h"
USING_NS_CC;
#define HERO_SPEED 4  // 必须是4的倍数（因为要乘0.75，模拟走斜角的速度0.707）
//ccConfig.h 中改 CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL = 1   打开抗锯齿   日后再关吧
//状态：已开启

class GameScene :public Scene {
private:
	std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;
	TMXTiledMap* map = TMXTiledMap::create("MyMap.tmx");
	Sprite* sprite = Sprite::create("CloseNormal.png");
	Sprite* sprite1 = Sprite::create("CloseNormal.png");
	Sprite* sprite2 = Sprite::create("CloseNormal.png");
public:
	static Scene* createScene()
	{
		return create();
	}

	virtual bool GameScene::init()
	{
		if (!Scene::init())
		{
			return false;
		}

		this->scheduleUpdate();

		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		float x = origin.x + visibleSize.width / 2;
		float y = origin.y + visibleSize.height / 2;

		sprite->setPosition(Vec2(x, y));
		sprite->setTag(0);
		addChild(sprite, 1);

		sprite1->setPosition(Vec2(x, y));
		sprite1->setTag(1);
		addChild(sprite1, 1);

		//float xMove = sprite1->getPositionX() - map->getPositionX();
		//float yMove = sprite1->getPositionY() - map->getPositionY();
		auto moveToLeft = MoveBy::create(2, Vec2(-50, 0));
		auto moveToRight = MoveBy::create(2, Vec2(50, 0));
		auto moveToDown = MoveBy::create(2, Vec2(0, -50));
		auto moveToUp = MoveBy::create(2, Vec2(0, 50));

		auto seq = Sequence::create(moveToLeft, moveToDown, moveToRight, moveToUp,
									moveToLeft, moveToDown, moveToRight, moveToUp,
									moveToLeft, moveToDown, moveToRight, moveToUp,
									moveToLeft, moveToDown, moveToRight, moveToUp,
									moveToLeft, moveToDown, moveToRight, moveToUp, nullptr);
		auto rep = Repeat::create(seq, 15);
		sprite1->runAction(seq);

		sprite2->setPosition(Vec2(x, y));
		sprite2->setTag(1);
		addChild(sprite2, 1);

		map->setPosition(Vec2(x - 600, y - 500));
		addChild(map, 0, 99); // with a tag of '99'
		
		auto obstacle = map->getLayer("obstacle");

		SpriteFrame* frame = nullptr;

		Vector<SpriteFrame*> frameVec;
		
		float _width = sprite->getContentSize().width;
		float _height = sprite->getContentSize().height;

		frame = SpriteFrame::create(StringUtils::format("CloseNormal.png"), Rect(0,0,_width,_height));
		frameVec.pushBack(frame);
		frame = SpriteFrame::create(StringUtils::format("CloseSelected.png"), Rect(0, 0, _width, _height));
		frameVec.pushBack(frame);
		//}
		Animation* animationMove = Animation::createWithSpriteFrames(frameVec);
		animationMove->setLoops(-1);
		animationMove->setDelayPerUnit(0.5f);

		Animate* animate = Animate::create(animationMove);

		sprite->runAction(animate);

		////创建菜单
		//auto up = MenuItemFont::create("↑", CC_CALLBACK_1(GameScene::menuClickCallBack, this));
		//up->setPosition(Vec2(940, 100));
		//auto down = MenuItemFont::create("↓", CC_CALLBACK_1(GameScene::menuClickCallBack, this));
		//down->setPosition(Vec2(940, 40));
		//auto left = MenuItemFont::create("←", CC_CALLBACK_1(GameScene::menuClickCallBack, this));
		//left->setPosition(Vec2(880, 40));
		//auto right = MenuItemFont::create("→", CC_CALLBACK_1(GameScene::menuClickCallBack, this));
		//right->setPosition(Vec2(1000, 40));


		//auto menu = Menu::create(up, down, left, right, NULL);
		//menu->setPosition(Point::ZERO);
		//addChild(menu);
		////menu->alignItemsVertically();

		////设置菜单tag
		//up->setTag(1);
		//down->setTag(2);
		//left->setTag(3);
		//right->setTag(4);


		//键盘事件监听器
		auto listener = EventListenerKeyboard::create();
		listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
			log("press");
			keyMap[keyCode] = true;
		};

		listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
			log("release");
			keyMap[keyCode] = false;
		};

		this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		return true;
	}

	//void GameScene::menuClickCallBack(Ref* sender)
	//{
	//	CCLOG("click menuitem");
	//	Node* node = dynamic_cast<Node*>(sender);
	//	int tag = node->getTag();
	//	Node* sprite = this->getChildByTag(0);
	//	if (NULL != node && NULL != sprite)
	//	{
	//		switch (tag)
	//		{
	//		case 1://up
	//		{
	//			//auto jump = jumpto::create(0.5, vec2(sprite->getpositionx(), sprite->getpositiony()), 70, 1);
	//			//sprite->runaction(jump);
	//			auto moveTo = MoveTo::create(0.2, Vec2(sprite->getPositionX(), sprite->getPositionY() + 20.0f));
	//			sprite->runAction(moveTo);
	//		}
	//		break;
	//		case 2://down
	//		{
	//			auto moveTo = MoveTo::create(0.2, Vec2(sprite->getPositionX(), sprite->getPositionY() - 20.0f));
	//			sprite->runAction(moveTo);
	//		}
	//		break;
	//		case 3://left
	//		{
	//			auto moveTo = MoveTo::create(0.2, Vec2(sprite->getPositionX() - 20.0f, sprite->getPositionY()));
	//			sprite->runAction(moveTo);
	//		}
	//		break;
	//		case 4://right
	//		{
	//			auto moveTo = MoveTo::create(0.2, Vec2(sprite->getPositionX() + 20.0f, sprite->getPositionY()));
	//			sprite->runAction(moveTo);
	//		}
	//		break;
	//		default:
	//			break;
	//		}
	//	}
	//}

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	typedef enum {
		Middle,
		Left,
		Right,
		Up,
		Down
	}Direction;

	Point positionToTileCoord(const Point& cocosCoord,const Direction& drt) const//计算坐标
	{
		int x, y;
		if (Left == drt) {
			x = (cocosCoord.x - sprite->getContentSize().width / 2 - map->getPositionX()) /
				map->getTileSize().width;
			y = (((map->getMapSize().height - 1) * map->getTileSize().height) -
					 (cocosCoord.y - map->getPositionY())) / map->getTileSize().height;
		} else if (Right == drt) {
			x = (cocosCoord.x + sprite->getContentSize().width / 2 - map->getPositionX()) /
				map->getTileSize().width;
			y = (((map->getMapSize().height - 1) * map->getTileSize().height) -
					 (cocosCoord.y - map->getPositionY())) / map->getTileSize().height;
		} else if (Up == drt) {
			x = (cocosCoord.x - map->getPositionX()) / map->getTileSize().width;
			y = (((map->getMapSize().height - 1) * map->getTileSize().height) -
					 (cocosCoord.y + sprite->getContentSize().width/2 -
					  map->getPositionY())) / map->getTileSize().height;
		} else if (Down == drt) {
			x = (cocosCoord.x - map->getPositionX()) / map->getTileSize().width;
			y = (((map->getMapSize().height - 1) * map->getTileSize().height) -
					 (cocosCoord.y - sprite->getContentSize().width/2 -
					  map->getPositionY())) / map->getTileSize().height;
		} else {//Middle
			x = (cocosCoord.x - map->getPositionX()) / map->getTileSize().width;
			y = (((map->getMapSize().height - 1) * map->getTileSize().height) -
					 (cocosCoord.y - map->getPositionY())) / map->getTileSize().height;
		}
		return Point(x,y);
	}

	typedef enum {
		Moveble,
		Wall,
		Grass
		//Enemy = 2
	}CollisionType;

	CollisionType checkCollision(const Point& heroPotion,const Direction& drt)
	{
		Point tileCoord = positionToTileCoord(heroPotion,drt);

		//检测是否超出地图边界
		if (tileCoord.x<0 || tileCoord.x>map->getMapSize().width - 1 ||
			tileCoord.y<0 || tileCoord.y>map->getMapSize().height - 1)
			return Wall;//若超出地图边界，逻辑错误了

		//判定目标坐标是否为墙壁
		int tileGid = map->getLayer("obstacle")->
			getTileGIDAt(Point(tileCoord.x, tileCoord.y + 1));//算坐标时y减了一，这里保持同步
		if (tileGid)
			return Wall;

		//判定目标坐标是否为草地
		int tileGidOfGrass = map->getLayer("grass")->
			getTileGIDAt(Point(tileCoord.x, tileCoord.y + 1));//算坐标时y减了一，这里保持同步
		if (tileGidOfGrass)
			return Grass;
		return Moveble;
	}

	void GameScene::update(float delta)
	{
		auto up = cocos2d::EventKeyboard::KeyCode::KEY_W;
		auto down = cocos2d::EventKeyboard::KeyCode::KEY_S;
		auto left = cocos2d::EventKeyboard::KeyCode::KEY_A;
		auto right = cocos2d::EventKeyboard::KeyCode::KEY_D;

		int offsetX = 0;
		int offsetY = 0;
		if (keyMap[left])
		{
			offsetX = -HERO_SPEED;
		}
		if (keyMap[right])
		{
			offsetX = HERO_SPEED;
		}
		if (keyMap[down])
		{
			offsetY = -HERO_SPEED;
		}
		if (keyMap[up])
		{
			offsetY = HERO_SPEED;
		}

		if (offsetX == 0 && offsetY == 0) {
			return;
		} else if (offsetX != 0 && offsetY != 0) {
			offsetX *= 0.75;//0.707斜着走不会太快
			offsetY *= 0.75;
		}

		Point targetPosition = Point(sprite->getPosition().x + offsetX, sprite->getPosition().y + offsetY);

		if (offsetX > 0) {
			if (checkCollision(targetPosition,Right) == Wall) {
				auto moveTo = MoveTo::create(0.02, Vec2(map->getPosition().x + offsetX/20, map->getPosition().y));
				map->runAction(moveTo);
				return;
			}
		}
		if (offsetX < 0) {
			if (checkCollision(targetPosition,Left) == Wall) {
				auto moveTo = MoveTo::create(0.02, Vec2(map->getPosition().x + offsetX/20, map->getPosition().y));
				map->runAction(moveTo);
				return;
			}
		}
		if (offsetY > 0) {
			if (checkCollision(targetPosition,Up) == Wall) {
				auto moveTo = MoveTo::create(0.02, Vec2(map->getPosition().x, map->getPosition().y + offsetY/20));
				map->runAction(moveTo);
				return;
			}
		}
		if (offsetY < 0) {
			if (checkCollision(targetPosition,Down) == Wall) {
				auto moveTo = MoveTo::create(0.02, Vec2(map->getPosition().x, map->getPosition().y + offsetY/20));
				map->runAction(moveTo);
				return;
			}
		}

		auto moveBy = MoveBy::create(0.02, Vec2(-offsetX, -offsetY));
		map->runAction(moveBy);
		sprite1->runAction(moveBy->clone());
	}
};


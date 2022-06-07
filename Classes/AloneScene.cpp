#include"AloneScene.h"
USING_NS_CC;
cocos2d::Scene* AloneScene::createScene()
{
    return AloneScene::create();
}
bool AloneScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    this->scheduleUpdate();
    //this->schedule(CC_SCHEDULE_SELECTOR(AloneScene::update),100);
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    x = origin.x + visibleSize.width / 2;
    y = origin.y + visibleSize.height / 2;
	
    sprite->setPosition(Vec2(x, y));
    sprite->setTag(0);
    addChild(sprite, 1);
	
    sprite1->setPosition(Vec2(x, y));
    sprite1->setTag(1);
    addChild(sprite1, 1);
	
    addChild(hero_player, 1);
    hero_player->setScale(0.8, 0.8);
    hero_player->setPosition(Vec2(x , y ));
    hero_player->Animater();//让它动起来
	
    //骑士的大招武器
    if (typeid(hero_player) == typeid(Knight*))
    {
        this->addChild(sword_bonus, 1);
        sword_bonus->setPosition(hero_player->getPosition() + Vec2(100, 50));
        sword_bonus->setVisible(false);
    }
    //增加武器
    this->addChild(weapon_player, 1);
    weapon_player->setPosition(hero_player->getPosition() + Vec2(70, 30));
    if (typeid(hero_player) == typeid(Berserker*))
        weapon_player->setPosition(hero_player->getPosition() + Vec2(50, -10));

    sprite1->runAction(seq);



    map->setPosition(Vec2(x - 600, y - 500));
    addChild(map, 0, 99); // with a tag of '99'
	
    obstacle = map->getLayer("obstacle");
    frame = nullptr;
	
    _width = sprite->getContentSize().width;
    _height = sprite->getContentSize().height;

    frame = SpriteFrame::create(StringUtils::format("CloseNormal.png"), Rect(0, 0, _width, _height));
    frameVec.pushBack(frame);
    frame = SpriteFrame::create(StringUtils::format("CloseSelected.png"), Rect(0, 0, _width, _height));
    frameVec.pushBack(frame);
	

    animationMove = Animation::createWithSpriteFrames(frameVec);
    animationMove->setLoops(-1);
    animationMove->setDelayPerUnit(0.5f);
	
    animate = Animate::create(animationMove);
    sprite->runAction(animate);
	
    //键盘事件监听器
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        keyMap[keyCode] = true;
    };

    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        keyMap[keyCode] = false;
        if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE)
            Director::getInstance()->popScene();
    };
    auto mouseListener = EventListenerTouchOneByOne::create();
    // 回调函数onTouchBegan():手指第一次碰到屏幕时被调用
    mouseListener->onTouchBegan = CC_CALLBACK_2(AloneScene::onTouchBegan, this);
    // 使用EventDispatcher处理触摸和其他键盘事件
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, weapon_player);
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    return true;
}

bool AloneScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
    if (typeid(hero_player) == typeid(Berserker*)) //玩家操控狂战士时，执行这个
    {
        //对于hammer，凡是正在执行attack()的，均需要参与碰撞检测
        weapon_player->attack();
        hero_player->setEnergyOnePlus();
    }
    if (typeid(hero_player) == typeid(Wizard*)) //玩家操控法师时，执行这个
    {
        // 获取触摸点的坐标，计算偏移量
        Vec2 touchLocation = touch->getLocation();
        Vec2 offset = touchLocation - weapon_player->getPosition();
        if (abs(offset.getAngle() / 3.14f * 180) > 80 && weapon_player->isDirectRight())
            return true;
        if (abs(offset.getAngle() / 3.14f * 180) < 100 && !(weapon_player->isDirectRight()))
            return true;
        // 创建攻击物
        auto projectile = Light::create();
        if (weapon_player->isDirectRight())
        {
            projectile->setPosition(weapon_player->getPosition() - Vec2(3, 30));
        }
        else
        {
            projectile->setPosition(weapon_player->getPosition() - Vec2(-3, 30));
        }
        projectile->setRotation(-offset.getAngle() / 3.14f * 180);
        this->addChild(projectile);
        //偏移量转化为单位向量
        offset.normalize();
        //获得了一个指向触屏方向的长度为567的向量
        auto shootAmount = offset * 567;
        //目标位置
        auto realDest = shootAmount + projectile->getPosition();
        //将攻击物移动到目标位置，然后将它从场景中移除
        auto actionMove = MoveTo::create(1.5f, realDest);
        auto actionRemove = RemoveSelf::create();
        projectile->runAction(Sequence::create(actionMove, actionRemove, nullptr));
        //武器攻击但不参与碰撞检测
        weapon_player->attack();
        hero_player->setEnergyOnePlus();
    }
    if (typeid(hero_player) == typeid(Scientist*)) //玩家操控科学家时，执行这个
    {
        // 获取触摸点的坐标，计算偏移量
        Vec2 touchLocation = touch->getLocation();
        Vec2 offset = touchLocation - weapon_player->getPosition();
        if (abs(offset.getAngle() / 3.14f * 180) > 70 && weapon_player->isDirectRight())
            return true;
        if (abs(offset.getAngle() / 3.14f * 180) < 110 && !(weapon_player->isDirectRight()))
            return true;
        // 创建攻击物
        auto projectile = Bullet::create();
        if (weapon_player->isDirectRight())
        {
            projectile->setPosition(weapon_player->getPosition() - Vec2(3, 30));
        }
        else
        {
            projectile->setPosition(weapon_player->getPosition() - Vec2(-3, 30));
        }
        projectile->setRotation(-offset.getAngle() / 3.14f * 180);
        this->addChild(projectile);
        //偏移量转化为单位向量
        offset.normalize();
        //获得了一个指向触屏方向的长度为432的向量
        auto shootAmount = offset * 432;
        //目标位置
        auto realDest = shootAmount + projectile->getPosition();
        //将攻击物移动到目标位置，然后将它从场景中移除
        auto actionMove = MoveTo::create(0.36f, realDest);
        auto actionRemove = RemoveSelf::create();
        projectile->runAction(Sequence::create(actionMove, actionRemove, nullptr));
        //武器攻击但不参与碰撞检测
        weapon_player->attack();
        hero_player->setEnergyOnePlus();
    }
    if (typeid(hero_player) == typeid(Knight*)) //玩家操控骑士时，执行这个
    {
        //对于sword和sword_bonus，凡是正在执行attack()的，均需要参与碰撞检测
        if (weapon_player->isVisible())
        {
            weapon_player->attack();
            hero_player->setEnergyOnePlus();
        }
        else if (hero_player->getEnergy() == 0)
        {
            sword_bonus->setVisible(false);
            weapon_player->setVisible(true);
            weapon_player->attack();
            hero_player->setEnergyOnePlus();
        }
        else
        {
            sword_bonus->attack();
            hero_player->SuperSkill();
        }
    }
    return true;
}

Point AloneScene::positionToTileCoord(const Point& cocosCoord, const Direction& drt) const{
    int x, y;
    if (Left == drt) {
        x = (cocosCoord.x - sprite->getContentSize().width / 2 - map->getPositionX()) /
            map->getTileSize().width;
        y = (((map->getMapSize().height - 1) * map->getTileSize().height) -
            (cocosCoord.y - map->getPositionY())) / map->getTileSize().height;
    }
    else if (Right == drt) {
        x = (cocosCoord.x + sprite->getContentSize().width / 2 - map->getPositionX()) /
            map->getTileSize().width;
        y = (((map->getMapSize().height - 1) * map->getTileSize().height) -
            (cocosCoord.y - map->getPositionY())) / map->getTileSize().height;
    }
    else if (Up == drt) {
        x = (cocosCoord.x - map->getPositionX()) / map->getTileSize().width;
        y = (((map->getMapSize().height - 1) * map->getTileSize().height) -
            (cocosCoord.y + sprite->getContentSize().width / 2 -
                map->getPositionY())) / map->getTileSize().height;
    }
    else if (Down == drt) {
        x = (cocosCoord.x - map->getPositionX()) / map->getTileSize().width;
        y = (((map->getMapSize().height - 1) * map->getTileSize().height) -
            (cocosCoord.y - sprite->getContentSize().width / 2 -
                map->getPositionY())) / map->getTileSize().height;
    }
    else {//Middle
        x = (cocosCoord.x - map->getPositionX()) / map->getTileSize().width;
        y = (((map->getMapSize().height - 1) * map->getTileSize().height) -
            (cocosCoord.y - map->getPositionY())) / map->getTileSize().height;
    }
    return Point(x, y);
}
AloneScene::CollisionType AloneScene::checkCollision(const Point& heroPotion, const Direction& drt) {
    Point tileCoord = positionToTileCoord(heroPotion, drt);

    //检测是否超出地图边界
    if (tileCoord.x<0 || tileCoord.x>map->getMapSize().width - 1 ||
        tileCoord.y<0 || tileCoord.y>map->getMapSize().height - 2)
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
void AloneScene::update(float delta)
{
    auto up = cocos2d::EventKeyboard::KeyCode::KEY_W;
    auto down = cocos2d::EventKeyboard::KeyCode::KEY_S;
    auto left = cocos2d::EventKeyboard::KeyCode::KEY_A;
    auto right = cocos2d::EventKeyboard::KeyCode::KEY_D;

    int offsetX = 0;
    int offsetY = 0;
    if (keyMap[left]) {
        hero_player->setDirectLeft();
        weapon_player->setDirectLeft();
        weapon_player->setPosition(hero_player->getPosition() + Vec2(-70, 30));
		
        if (typeid(hero_player) == typeid(Knight*))
            sword_bonus->setDirectRight();
        offsetX = -HERO_SPEED;
    }   
    if (keyMap[right]) {
		hero_player->setDirectRight();
		weapon_player->setDirectRight();
        weapon_player->setPosition(hero_player->getPosition() + Vec2(70, 30));
        if (typeid(hero_player) == typeid(Knight*))
		    sword_bonus->setDirectRight();
        offsetX = HERO_SPEED;
    }     
    if (keyMap[down])    
        offsetY = -HERO_SPEED;    
    if (keyMap[up])
        offsetY = HERO_SPEED;
    if (offsetX == 0 && offsetY == 0)
        return;
    else if (offsetX != 0 && offsetY != 0) {
        offsetX *= 0.75;//0.707斜着走不会太快
        offsetY *= 0.75;
    }
    Point targetPosition = Point(sprite->getPosition().x + offsetX, sprite->getPosition().y + offsetY);
    if (checkCollision(targetPosition, Right) == Grass || checkCollision(targetPosition, Left) == Grass || checkCollision(targetPosition, Up) == Grass || checkCollision(targetPosition, Down) == Grass ) {
        CCLOG("is Grass");
    }  
    else {
		if(checkCollision(targetPosition, Right) == Wall || checkCollision(targetPosition, Left) == Wall || checkCollision(targetPosition, Up) == Wall || checkCollision(targetPosition, Down) == Wall)
            CCLOG("is Wall");
        else {
            if (checkCollision(targetPosition, Right) == Moveble || checkCollision(targetPosition, Left) == Moveble || checkCollision(targetPosition, Up) == Moveble || checkCollision(targetPosition, Down) == Moveble)
                CCLOG("is Moveble");
        }

    }
    if (offsetX > 0) {
        if (checkCollision(targetPosition, Right) == Wall) {
            auto moveTo = MoveTo::create(0.02, Vec2(map->getPosition().x + offsetX / 20, map->getPosition().y));
            map->runAction(moveTo);
            return;
        }
    }
    if (offsetX < 0) {
        if (checkCollision(targetPosition, Left) == Wall) {
            auto moveTo = MoveTo::create(0.02, Vec2(map->getPosition().x + offsetX / 20, map->getPosition().y));
            map->runAction(moveTo);
            return;
        }
    }
    if (offsetY > 0) {
        if (checkCollision(targetPosition, Up) == Wall) {
            auto moveTo = MoveTo::create(0.02, Vec2(map->getPosition().x, map->getPosition().y + offsetY / 20));
            map->runAction(moveTo);
            return;
        }
    }
    if (offsetY < 0) {
        if (checkCollision(targetPosition, Down) == Wall) {
            auto moveTo = MoveTo::create(0.02, Vec2(map->getPosition().x, map->getPosition().y + offsetY / 20));
            map->runAction(moveTo);
            return;
        }
    }
    auto moveBy = MoveBy::create(0.02, Vec2(-offsetX, -offsetY));
    map->runAction(moveBy);
    sprite1->runAction(moveBy->clone());

	//上面是移动
	//下面是攻击
    auto attack_normal = cocos2d::EventKeyboard::KeyCode::KEY_J;
	auto attack_special = cocos2d::EventKeyboard::KeyCode::KEY_K;
    if (keyMap[attack_normal]) {
		
    }
	//下面是冲刺
	auto shift = cocos2d::EventKeyboard::KeyCode::KEY_SHIFT;
	if (keyMap[shift]) {
        if (hero_player->isDirectRight()){
            auto moveBy = MoveBy::create(0.5f, Vec2(120, 0));
            auto action = Sequence::create(moveBy, nullptr);
            hero_player->runAction(action);
            weapon_player->runAction(action->clone());
            if (typeid(hero_player) == typeid(Knight*))
                sword_bonus->runAction(action->clone());
        }
        else{
            auto moveBy = MoveBy::create(0.5f, Vec2(-120, 0));
            auto action = Sequence::create(moveBy, nullptr);
            hero_player->runAction(action);
            weapon_player->runAction(action->clone());
            if (typeid(hero_player) == typeid(Knight*))
                sword_bonus->runAction(action->clone());
        }
	}
}
void spriteRun()
{
	
}

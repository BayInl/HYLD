#include "HelloWorldScene.h"


USING_NS_CC;
using namespace cocos2d;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

//����ƶ�  ���뽫���в����������ƶ��ľ���ȫ������ڴ˴������� ////////////////  ATTENTION  /////////////////
inline void HelloWorld::relativeMovement(float duration, const Vec2& deltaPosition)
{
    auto moveBy = MoveBy::create(duration, -deltaPosition);
    if (deltaPosition.x > 0)
        if (checkCollision(hero_player->getPosition(), Right) == Wall) {
            moveBy = MoveBy::create(duration, deltaPosition);
        }
    if (deltaPosition.x < 0)
        if (checkCollision(hero_player->getPosition(), Left) == Wall) {
            moveBy = MoveBy::create(duration, deltaPosition);
        }
    if (deltaPosition.y > 0)
        if (checkCollision(hero_player->getPosition(), Up) == Wall) {
            moveBy = MoveBy::create(duration, deltaPosition);
        }
    if (deltaPosition.y < 0)
        if (checkCollision(hero_player->getPosition(), Down) == Wall) {
            moveBy = MoveBy::create(duration, deltaPosition);
        }
    map->runAction(moveBy);

    //���в��������ߵľ���ȫ�����������
    box0->runAction(moveBy->clone());
    box1->runAction(moveBy->clone());
    box2->runAction(moveBy->clone());
    box3->runAction(moveBy->clone());
}

bool HelloWorld::init()
{
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    this->scheduleUpdate();//����update����

    //Ԥ����
    AudioEngine::preload("Sounds/goldenslaughterer.mp3");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 2. add a menu item with "X" image, which is clicked to quit the program
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // �����˵�
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // 3. add your codes below...
    
    //����һЩ���ӵ�ʵ��
    this->addChild(box0);
    box0->setPosition(Vec2(300, 200));
    this->addChild(box1);
    box1->setPosition(Vec2(500, 300));
    this->addChild(box2);
    box2->setPosition(Vec2(400, 700));
    this->addChild(box3);
    box3->setPosition(Vec2(700, 500));

    //���ӵ�ͼ
    map->setPosition(Vec2(origin.x + visibleSize.width / 2-800,
                          origin.y + visibleSize.height / 2-700));
    addChild(map, -10, 99); // with a tag of '99'
    //��ȡ�ϰ����
    auto obstacle = map->getLayer("obstacle");

    //����һ����ɫ��ʵ��
    this->addChild(hero_player);
    hero_player->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    hero_player->Animater();//����������
    //������ʿ�Ĵ�������
    if (typeid(hero_player) == typeid(Knight*))
    {
        this->addChild(sword_bonus);
        sword_bonus->setPosition(hero_player->getPosition() + Vec2(100, 50));
        sword_bonus->setVisible(false);
    }
    //��������
    this->addChild(weapon_player);
    weapon_player->setPosition(hero_player->getPosition() + Vec2(70, 30));
    if (typeid(hero_player) == typeid(Berserker*))
        weapon_player->setPosition(hero_player->getPosition() + Vec2(50, -10));
   // �����¼��ļ�����
   auto mouseListener = EventListenerTouchOneByOne::create();
   // �ص�����onTouchBegan():��ָ��һ��������Ļʱ������
   mouseListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
   // ʹ��EventDispatcher�����������������¼�
   this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, weapon_player);
   // �����¼�����
   auto keyListener = EventListenerKeyboard::create();
   //if (typeid(hero_player) == typeid(Knight*))
   //    keyListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressedKnight, this);
   //else
   //    keyListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
   keyListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
       log("press");
       key_map[keyCode] = true;
   };
   keyListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
       log("release");
       key_map[keyCode] = false;
   };
   this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

   //���ñ�������
   auto backgroundAudioID = AudioEngine::play2d("Sounds/goldenslaughterer.mp3", true,0.2f);
   AudioEngine::resume(backgroundAudioID);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //�رճ���
    Director::getInstance()->end();

}


//��ʿר�����̼���
void HelloWorld::onKeyPressedKnight(EventKeyboard::KeyCode keyCode, Event* event) 
{
    log("Key with keycode %d pressed", keyCode);
    switch (keyCode)  //�ٿط�ʽ��WSAD
    {
    case EventKeyboard::KeyCode::KEY_D: //����Dʱ��ɫΪ����
    {
        auto moveBy = MoveBy::create(0.5f, Vec2(20, 0));
        auto action = Sequence::create(moveBy, nullptr);
        hero_player->setDirectRight();
        weapon_player->setDirectRight();
        sword_bonus->setDirectRight();
        weapon_player->setPosition(hero_player->getPosition() + Vec2(70, 30));
        sword_bonus->setPosition(hero_player->getPosition() + Vec2(100, 50));
        hero_player->runAction(action);
        weapon_player->runAction(action->clone());
        sword_bonus->runAction(action->clone());
        break;
    }
    case EventKeyboard::KeyCode::KEY_A: //����Aʱ��ɫΪ����
    {
        auto moveBy = MoveBy::create(0.5f, Vec2(-20, 0));
        auto action = Sequence::create(moveBy ,nullptr);
        hero_player->setDirectLeft();
        weapon_player->setDirectLeft();
        sword_bonus->setDirectLeft();
        weapon_player->setPosition(hero_player->getPosition()+Vec2(-70,30));
        sword_bonus->setPosition(hero_player->getPosition() + Vec2(-100, 50));
        hero_player->runAction(action);
        weapon_player->runAction(action->clone());
        sword_bonus->runAction(action->clone());
        break;
    }
    case EventKeyboard::KeyCode::KEY_W:
    {
        auto moveBy = MoveBy::create(0.5f, Vec2(0, 20));
        auto action = Sequence::create(moveBy, nullptr);
        hero_player->runAction(action);
        weapon_player->runAction(action->clone());
        sword_bonus->runAction(action->clone());
        break;
    }
    case EventKeyboard::KeyCode::KEY_S:
    {
        auto moveBy = MoveBy::create(0.5f, Vec2(0, -20));
        auto action = Sequence::create(moveBy, nullptr);
        hero_player->runAction(action);
        weapon_player->runAction(action->clone());
        sword_bonus->runAction(action->clone());
        break;
    }
    case EventKeyboard::KeyCode::KEY_Q:  //����
    {
        if (hero_player->getEnergy() >= ENERGYMAX_KNIGHT)
        {
            sword_bonus->setVisible(true);
            weapon_player->setVisible(false);
        }
        else;
        break;
    }
    case EventKeyboard::KeyCode::KEY_SHIFT: //���
    {
        if(hero_player->isDirectRight())
        {
            auto moveBy = MoveBy::create(0.5f, Vec2(120, 0));
            auto action = Sequence::create(moveBy, nullptr);
            hero_player->runAction(action);
            weapon_player->runAction(action->clone());
            sword_bonus->runAction(action->clone());
        }
        else
        {
            auto moveBy = MoveBy::create(0.5f, Vec2(-120, 0));
            auto action = Sequence::create(moveBy, nullptr);
            hero_player->runAction(action);
            weapon_player->runAction(action->clone());
            sword_bonus->runAction(action->clone());
        }
        break;
    }
    default:
        break;
    }
}

//������ɫ�ļ��̼���
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("Key with keycode %d pressed", keyCode);
    switch (keyCode)  //�ٿط�ʽ��WSAD
    {
    case EventKeyboard::KeyCode::KEY_D: //����Dʱ��ɫΪ����
    {
        auto moveBy = MoveBy::create(0.5f, Vec2(20, 0));
        auto action = Sequence::create(moveBy, nullptr);
        hero_player->setDirectRight();
        weapon_player->setDirectRight();
        weapon_player->setPosition(hero_player->getPosition() + Vec2(70, 30));
        if (typeid(hero_player) == typeid(Berserker*))
            weapon_player->setPosition(hero_player->getPosition() + Vec2(50, -10));
        hero_player->runAction(action);
        weapon_player->runAction(action->clone());
        break;
    }
    case EventKeyboard::KeyCode::KEY_A: //����Aʱ��ɫΪ����
    {
        auto moveBy = MoveBy::create(0.5f, Vec2(-20, 0));
        auto action = Sequence::create(moveBy, nullptr);
        hero_player->setDirectLeft();
        weapon_player->setDirectLeft();
        weapon_player->setPosition(hero_player->getPosition() + Vec2(-70, 30));
        if (typeid(hero_player) == typeid(Berserker*))
            weapon_player->setPosition(hero_player->getPosition() + Vec2(-50, -10));
        hero_player->runAction(action);
        weapon_player->runAction(action->clone());
        break;
    }
    case EventKeyboard::KeyCode::KEY_W:
    {
        auto moveBy = MoveBy::create(0.5f, Vec2(0, 20));
        auto action = Sequence::create(moveBy, nullptr);
        hero_player->runAction(action);
        weapon_player->runAction(action->clone());
        break;
    }
    case EventKeyboard::KeyCode::KEY_S:
    {
        auto moveBy = MoveBy::create(0.5f, Vec2(0, -20));
        auto action = Sequence::create(moveBy, nullptr);
        hero_player->runAction(action);
        weapon_player->runAction(action->clone());
        break;
    }
    case EventKeyboard::KeyCode::KEY_Q:  //����
    {
        if (typeid(hero_player) == typeid(Berserker*))
        {
            if (hero_player->getEnergy() >= ENERGYMAX_BERSERKER)
            {
                hero_player->SuperSkill();
            }
        }
        else if (typeid(hero_player) == typeid(Scientist*))
        {
            if (hero_player->getEnergy() >= ENERGYMAX_SCIENTIST)
            {
                hero_player->SuperSkill();
            }
        }
        else if (typeid(hero_player) == typeid(Wizard*))
        {
            if (hero_player->getEnergy() >= ENERGYMAX_WIZARD)
            {
                hero_player->SuperSkill();
            }
        }
        break;
    }
    case EventKeyboard::KeyCode::KEY_SHIFT: //���
    {
        if (hero_player->isDirectRight())
        {
            auto moveBy = MoveBy::create(0.5f, Vec2(120, 0));
            auto action = Sequence::create(moveBy, nullptr);
            hero_player->runAction(action);
            weapon_player->runAction(action->clone());
        }
        else
        {
            auto moveBy = MoveBy::create(0.5f, Vec2(-120, 0));
            auto action = Sequence::create(moveBy, nullptr);
            hero_player->runAction(action);
            weapon_player->runAction(action->clone());
        }
        break;
    }
    default:
        break;
    }
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* unused_event)
{
    if (typeid(hero_player) == typeid(Berserker*)) //��Ҳٿؿ�սʿʱ��ִ�����
    {
        //����hammer����������ִ��attack()�ģ�����Ҫ������ײ���
        weapon_player->attack();
        hero_player->setEnergyOnePlus();
    }
    if (typeid(hero_player) == typeid(Wizard*)) //��Ҳٿط�ʦʱ��ִ�����
    {
        // ��ȡ����������꣬����ƫ����
        Vec2 touchLocation = touch->getLocation();
        Vec2 offset = touchLocation - weapon_player->getPosition();
        if (abs(offset.getAngle() / 3.14f * 180) > 80 && weapon_player->isDirectRight())
            return true;
        if (abs(offset.getAngle() / 3.14f * 180) < 100 && !(weapon_player->isDirectRight()))
            return true;
        // ����������
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
        //ƫ����ת��Ϊ��λ����
        offset.normalize();
        //�����һ��ָ��������ĳ���Ϊ567������
        auto shootAmount = offset * 567;
        //Ŀ��λ��
        auto realDest = shootAmount + projectile->getPosition();
        //���������ƶ���Ŀ��λ�ã�Ȼ�����ӳ������Ƴ�
        auto actionMove = MoveTo::create(1.5f, realDest);
        auto actionRemove = RemoveSelf::create();
        projectile->runAction(Sequence::create(actionMove, actionRemove, nullptr));
        //������������������ײ���
        weapon_player->attack();
        hero_player->setEnergyOnePlus();
    }
    if(typeid(hero_player)==typeid(Scientist*)) //��Ҳٿؿ�ѧ��ʱ��ִ�����
    {
        // ��ȡ����������꣬����ƫ����
        Vec2 touchLocation = touch->getLocation();
        Vec2 offset = touchLocation - weapon_player->getPosition();
        if (abs(offset.getAngle() / 3.14f * 180) > 70&&weapon_player->isDirectRight())
            return true;
        if (abs(offset.getAngle() / 3.14f * 180) < 110 &&!(weapon_player->isDirectRight()))
            return true;
        // ����������
        auto projectile = Bullet::create();
        if(weapon_player->isDirectRight())
        {
            projectile->setPosition(weapon_player->getPosition() - Vec2(3, 30));
        }
        else
        {
            projectile->setPosition(weapon_player->getPosition() - Vec2(-3, 30));
        }
        projectile->setRotation(-offset.getAngle()/3.14f*180);
        this->addChild(projectile);
        //ƫ����ת��Ϊ��λ����
        offset.normalize();
        //�����һ��ָ��������ĳ���Ϊ432������
        auto shootAmount = offset * 432;
        //Ŀ��λ��
        auto realDest = shootAmount + projectile->getPosition();
        //���������ƶ���Ŀ��λ�ã�Ȼ�����ӳ������Ƴ�
        auto actionMove = MoveTo::create(0.36f, realDest);
        auto actionRemove = RemoveSelf::create();
        projectile->runAction(Sequence::create(actionMove, actionRemove, nullptr));
        //������������������ײ���
        weapon_player->attack();
        hero_player->setEnergyOnePlus();
    }
    if (typeid(hero_player) == typeid(Knight*)) //��Ҳٿ���ʿʱ��ִ�����
    {
        //����sword��sword_bonus����������ִ��attack()�ģ�����Ҫ������ײ���
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

Point HelloWorld::positionToTileCoord(const Point& cocosCoord, const Direction& drt)//��������
{
    int x, y;
    if (Left == drt) {
        x = (cocosCoord.x - hero_player->getContentSize().width / 2 - hero_player->getPositionX()) /
            map->getTileSize().width;
        y = (((map->getMapSize().height - 1) * map->getTileSize().height) -
             (cocosCoord.y - map->getPositionY())) / map->getTileSize().height;
    } else if (Right == drt) {
        x = (cocosCoord.x + hero_player->getContentSize().width / 2 - map->getPositionX()) /
            map->getTileSize().width;
        y = (((map->getMapSize().height - 1) * map->getTileSize().height) -
             (cocosCoord.y - map->getPositionY())) / map->getTileSize().height;
    } else if (Up == drt) {
        x = (cocosCoord.x - map->getPositionX()) / map->getTileSize().width;
        y = (((map->getMapSize().height - 1) * map->getTileSize().height) -
             (cocosCoord.y + hero_player->getContentSize().width / 2 -
              map->getPositionY())) / map->getTileSize().height;
    } else if (Down == drt) {
        x = (cocosCoord.x - map->getPositionX()) / map->getTileSize().width;
        y = (((map->getMapSize().height - 1) * map->getTileSize().height) -
             (cocosCoord.y - hero_player->getContentSize().width / 2 -
              map->getPositionY())) / map->getTileSize().height;
    } else {//Middle
        x = (cocosCoord.x - map->getPositionX()) / map->getTileSize().width;
        y = (((map->getMapSize().height - 1) * map->getTileSize().height) -
             (cocosCoord.y - map->getPositionY())) / map->getTileSize().height;
    }
    return Point(x, y);
}

HelloWorld::CollisionType HelloWorld::checkCollision(const Point& heroPotion, const Direction& drt)
{
    Point tileCoord = positionToTileCoord(heroPotion, drt);

    //����Ƿ񳬳���ͼ�߽�
    if (tileCoord.x<1 || tileCoord.x>map->getMapSize().width - 1 ||
        tileCoord.y<1 || tileCoord.y>map->getMapSize().height - 1)
        return Wall;//��������ͼ�߽磬�߼�������

    //�ж�Ŀ�������Ƿ�Ϊǽ��
    int tileGid = map->getLayer("obstacle")->
        getTileGIDAt(Point(tileCoord.x, tileCoord.y + 1));//������ʱy����һ�����ﱣ��ͬ��
    if (tileGid)
        return Wall;

    //�ж�Ŀ�������Ƿ�Ϊ�ݵ�
    int tileGidOfGrass = map->getLayer("grass")->
        getTileGIDAt(Point(tileCoord.x, tileCoord.y + 1));//������ʱy����һ�����ﱣ��ͬ��
    if (tileGidOfGrass)
        return Grass;
    return Moveble;
}

inline void HelloWorld::update(float delta)
{
    auto up = cocos2d::EventKeyboard::KeyCode::KEY_W;
    auto down = cocos2d::EventKeyboard::KeyCode::KEY_S;
    auto left = cocos2d::EventKeyboard::KeyCode::KEY_A;
    auto right = cocos2d::EventKeyboard::KeyCode::KEY_D;
    auto q = cocos2d::EventKeyboard::KeyCode::KEY_Q;
    auto shift = cocos2d::EventKeyboard::KeyCode::KEY_SHIFT;

    int offsetX = 0;
    int offsetY = 0;
    if (typeid(hero_player) != typeid(Knight*)) 
    {
        if (key_map[left])
        {
            hero_player->setDirectLeft();
            weapon_player->setDirectLeft();
            weapon_player->setPosition(hero_player->getPosition() + Vec2(-70, 30));
            if (typeid(hero_player) == typeid(Berserker*))
                weapon_player->setPosition(hero_player->getPosition() + Vec2(-50, -10));
            relativeMovement 0.02, Vec2(-5, 0));
        }
        if (key_map[right])
        {
            hero_player->setDirectRight();
            weapon_player->setDirectRight();
            weapon_player->setPosition(hero_player->getPosition() + Vec2(70, 30));
            if (typeid(hero_player) == typeid(Berserker*))
                weapon_player->setPosition(hero_player->getPosition() + Vec2(50, -10));
            relativeMovement( 0.02, Vec2(5, 0));
        }
        if (key_map[down])
        {
            relativeMovement( 0.02, Vec2(0, -5));
        }
        if (key_map[up])
        {
            relativeMovement( 0.02, Vec2(0, 5));
        }
        if (key_map[q])
        {
            if (typeid(hero_player) == typeid(Berserker*))
            {
                if (hero_player->getEnergy() >= ENERGYMAX_BERSERKER)
                {
                    hero_player->SuperSkill();
                }
            } else if (typeid(hero_player) == typeid(Scientist*))
            {
                if (hero_player->getEnergy() >= ENERGYMAX_SCIENTIST)
                {
                    hero_player->SuperSkill();
                }
            } else if (typeid(hero_player) == typeid(Wizard*))
            {
                if (hero_player->getEnergy() >= ENERGYMAX_WIZARD)
                {
                    hero_player->SuperSkill();
                }
            }
        }
        if (key_map[shift])
        {
            if (hero_player->isDirectRight())
            {
                relativeMovement(0.02, Vec2(20, 0));
            } else
            {
                relativeMovement(0.02, Vec2(-20, 0));
            }
        }
    }

    //if (offsetX == 0 && offsetY == 0) {
    //    return;
    //} else if (offsetX != 0 && offsetY != 0) {
    //    offsetX *= 0.75;//0.707б���߲���̫��
    //    offsetY *= 0.75;
    //}

    //Point targetPosition = Point(hero_player->getPosition().x + offsetX, hero_player->getPosition().y + offsetY);

    //if (offsetX > 0) {
    //    if (checkCollision(targetPosition, Right) == Wall) {
    //        auto moveTo = MoveTo::create(0.02, Vec2(map->getPosition().x + offsetX / 20, map->getPosition().y));
    //        map->runAction(moveTo);
    //        return;
    //    }
    //}
    //if (offsetX < 0) {
    //    if (checkCollision(targetPosition, Left) == Wall) {
    //        auto moveTo = MoveTo::create(0.02, Vec2(map->getPosition().x + offsetX / 20, map->getPosition().y));
    //        map->runAction(moveTo);
    //        return;
    //    }
    //}
    //if (offsetY > 0) {
    //    if (checkCollision(targetPosition, Up) == Wall) {
    //        auto moveTo = MoveTo::create(0.02, Vec2(map->getPosition().x, map->getPosition().y + offsetY / 20));
    //        map->runAction(moveTo);
    //        return;
    //    }
    //}
    //if (offsetY < 0) {
    //    if (checkCollision(targetPosition, Down) == Wall) {
    //        auto moveTo = MoveTo::create(0.02, Vec2(map->getPosition().x, map->getPosition().y + offsetY / 20));
    //        map->runAction(moveTo);
    //        return;
    //    }
    //}

    //auto moveBy = MoveBy::create(0.02, Vec2(-offsetX, -offsetY));
    //map->runAction(moveBy);

    ////���в��������ߵľ���ȫ�����������
    //box0->runAction(moveBy->clone());
    //box1->runAction(moveBy->clone());
    //box2->runAction(moveBy->clone());
    //box3->runAction(moveBy->clone());
}

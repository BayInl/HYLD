#include "HelloWorldScene.h"


USING_NS_CC;
using namespace cocos2d;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    //预加载
    AudioEngine::preload("Sounds/goldenslaughterer.mp3");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

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

    // 创建菜单
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // 3. add your codes below...
    
    //增加一个角色的实例
    this->addChild(hero_player);
    hero_player->setPosition(Vec2(512, 384));
    hero_player->Animater();//让它动起来

    //增加骑士的大招武器
    if (typeid(hero_player) == typeid(Knight*))
    {
        this->addChild(sword_bonus);
        sword_bonus->setPosition(hero_player->getPosition() + Vec2(100, 50));
        sword_bonus->setVisible(false);
    }

    //增加武器
    this->addChild(weapon_player);
    weapon_player->setPosition(hero_player->getPosition() + Vec2(70, 30));
    if (typeid(hero_player) == typeid(Berserker*))
        weapon_player->setPosition(hero_player->getPosition() + Vec2(50, -10));

   // 定义触摸事件的监听器
   auto mouseListener = EventListenerTouchOneByOne::create();
   // 定义回调函数onTouchBegan():手指第一次碰到屏幕时被调用
   mouseListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
   // 使用EventDispatcher来处理触摸和其他键盘事件
   this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, weapon_player);

   // 键盘事件监听
   auto keyListener = EventListenerKeyboard::create();
   if (typeid(hero_player) == typeid(Knight*))
       keyListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressedKnight, this);
   else
       keyListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
   _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

   //设置背景音乐
   auto backgroundAudioID = AudioEngine::play2d("Sounds/goldenslaughterer.mp3", true);
   AudioEngine::resume(backgroundAudioID);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //关闭程序
    Director::getInstance()->end();

}


//骑士专属键盘监听
void HelloWorld::onKeyPressedKnight(EventKeyboard::KeyCode keyCode, Event* event) 
{
    log("Key with keycode %d pressed", keyCode);
    switch (keyCode)  //操控方式：WSAD
    {
    case EventKeyboard::KeyCode::KEY_D: //按下D时角色为向右
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
    case EventKeyboard::KeyCode::KEY_A: //按下A时角色为向左
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
    case EventKeyboard::KeyCode::KEY_Q:  //大招
    {
        if (hero_player->getEnergy() >= ENERGYMAX_KNIGHT)
        {
            sword_bonus->setVisible(true);
            weapon_player->setVisible(false);
        }
        else;
        break;
    }
    case EventKeyboard::KeyCode::KEY_SHIFT: //冲刺
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

//其它角色的键盘监听
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    log("Key with keycode %d pressed", keyCode);
    switch (keyCode)  //操控方式：WSAD
    {
    case EventKeyboard::KeyCode::KEY_D: //按下D时角色为向右
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
    case EventKeyboard::KeyCode::KEY_A: //按下A时角色为向左
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
    case EventKeyboard::KeyCode::KEY_Q:  //大招
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
    case EventKeyboard::KeyCode::KEY_SHIFT: //冲刺
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
    if(typeid(hero_player)==typeid(Scientist*)) //玩家操控科学家时，执行这个
    {
        // 获取触摸点的坐标，计算偏移量
        Vec2 touchLocation = touch->getLocation();
        Vec2 offset = touchLocation - weapon_player->getPosition();
        if (abs(offset.getAngle() / 3.14f * 180) > 70&&weapon_player->isDirectRight())
            return true;
        if (abs(offset.getAngle() / 3.14f * 180) < 110 &&!(weapon_player->isDirectRight()))
            return true;
        // 创建攻击物
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
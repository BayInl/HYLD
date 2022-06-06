#include "HelloWorldScene.h"

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

bool HelloWorld::init()
{
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
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

    //����һ����ɫ��ʵ��
    this->addChild(hero_player);
    hero_player->setPosition(Vec2(512, 384));
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
   if (typeid(hero_player) == typeid(Knight*))
       keyListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressedKnight, this);
   else
       keyListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
   _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

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
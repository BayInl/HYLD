/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"

//
#include "Heroes.h"
#include "AudioEngine.h"
#include <stdio.h>
//

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

    //Ԥ����
    AudioEngine::preload("SkylightCut.mp3");
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

    // �����˵�
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // 3. add your codes below...
    
    //����һ����ɫ��ʵ��
    this->addChild(hero_player);
    hero_player->setPosition(Vec2(100, 200));
    hero_player->Animater();//����������

    //������ʿ�Ĵ�������
    this->addChild(sword_bonus);
    sword_bonus->setPosition(hero_player->getPosition()+Vec2(100,50));
    sword_bonus->setVisible(false);
    this->addChild(weapon_player);
    weapon_player->setPosition(hero_player->getPosition() + Vec2(70, 30));

    // �����¼�����
   auto keyListener = EventListenerKeyboard::create();
   keyListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressedKnight, this);
   _eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

   // �����ӵ�
   // ���崥���¼��ļ������������������֣�
   // 1.EventListenerTouchOneByOne�������Ͷ�ÿ�������¼�����һ�λص�������
   // 2.EventListenerTouchAllAtOnce�������Ͷ����еĴ����¼�����һ�λص�������
   auto mouseListener = EventListenerTouchOneByOne::create();
   // ����ص�����onTouchBegan():��ָ��һ��������Ļʱ�����á�
   mouseListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
   // ʹ��EventDispatcher��������ָ������¼����紥�������������¼���
   this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, weapon_player);

   //���ñ�������
   auto backgroundAudioID = AudioEngine::play2d("goldenslaughterer.mp3", true);
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
        weapon_player->setScaleX(1.0f);
        sword_bonus->setScaleX(1.0f);
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
        weapon_player->setScaleX(-1.0f);
        sword_bonus->setScaleX(-1.0f);
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
    case EventKeyboard::KeyCode::KEY_SHIFT:
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


bool HelloWorld::onTouchBegan(Touch* touch, Event* unused_event) {
    // 1 - Just an example for how to get the player object
    // ˵��һ����Ϊ�ڶ����������ݸ�addEventListenerWithSceneGraphPriority(eventListener, _player)��_player���󱻷��ʵķ�ʽ��
    // auto node = unused_event->getcurrentTarget();

    // 2.��ȡ����������꣬����������������_player��ƫ������
    Vec2 touchLocation = touch->getLocation();
    Vec2 offset = touchLocation - hero_player->getPosition();

    // 3.��������ڵ�λ�ô���һ���ӵ���������ӵ������С�
    auto projectile = Sprite::create("revolver_projectile.png");
    projectile->setPosition(weapon_player->getPosition());
    this->addChild(projectile);

    // 4.��ƫ����ת��Ϊ��λ������������Ϊ1��������
    offset.normalize();
    // �������1000����ͻ����һ��ָ���û���������ĳ���Ϊ1000��������Ϊʲô��1000�أ���Ϊ����Ӧ�����Գ�����ǰ�ֱ�������Ļ�ı߽硣
    auto shootAmount = offset * 1000;
    // ����������ӵ��ӵ���λ����ȥ�������������һ��Ŀ��λ�á�
    auto realDest = shootAmount + projectile->getPosition();

    // 5.����һ�����������ӵ���2�����ƶ���Ŀ��λ�ã�Ȼ�����ӳ������Ƴ���
    auto actionMove = MoveTo::create(1.0f, realDest);
    auto actionRemove = RemoveSelf::create();
    projectile->runAction(Sequence::create(actionMove, actionRemove, nullptr));
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
        hero_player->setEnergy(0);
    }
    return true;
}
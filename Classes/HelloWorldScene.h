#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Heroes.h"
#include "AudioEngine.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();    

    //建立玩家操控的角色类实例
    //Wizard* hero_player= Wizard::create();
    //Scientist* hero_player = Scientist::create();
    //Knight* hero_player = Knight::create();
    Berserker* hero_player = Berserker::create();

    //建立武器类实例
    Weapons* sword_bonus = SwordBonus::create();
    Weapons* weapon_player = hero_player->bindWeapon();

    //键盘监听，触碰监测
    void onKeyPressedKnight(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char* format, int count);

};

#endif // __HELLOWORLD_SCENE_H__



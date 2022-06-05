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

    //������ҲٿصĽ�ɫ��ʵ��
    //Wizard* hero_player= Wizard::create();
    //Scientist* hero_player = Scientist::create();
    //Knight* hero_player = Knight::create();
    Berserker* hero_player = Berserker::create();

    //����������ʵ��
    Weapons* sword_bonus = SwordBonus::create();
    Weapons* weapon_player = hero_player->bindWeapon();

    //���̼������������
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



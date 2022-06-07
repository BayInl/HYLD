#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Heroes.h"
#include "AudioEngine.h"

//ccConfig.h �и� CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL = 1   �򿪿����   �պ��ٹذ�
//״̬���ѿ���

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();    

    //��Ҳٿص�ʵ��
    //Wizard* hero_player= Wizard::create();
    //Scientist* hero_player = Scientist::create();
    //Knight* hero_player = Knight::create();
    Berserker* hero_player = Berserker::create();

    //����ʵ��
    Weapons* sword_bonus = SwordBonus::create();
    Weapons* weapon_player = hero_player->bindWeapon();

    //�ռ���ʵ��
    BoxHealth* box0=BoxHealth::create();
    BoxCharge* box1= BoxCharge::create();
    BoxHell* box2= BoxHell::create();
    BoxWhat* box3= BoxWhat::create();

    //��ͼʵ��
    TMXTiledMap* map = TMXTiledMap::create("Map/MyMap.tmx");

    //���̼�����ֵ����
    std::map<cocos2d::EventKeyboard::KeyCode, bool> key_map;

    //����
    void onKeyPressedKnight(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);

    typedef enum {
        Middle,
        Left,
        Right,
        Up,
        Down
    }Direction;//����

    typedef enum {
        Moveble,
        Wall,
        Grass
        //Enemy = 2
    }CollisionType;//��ײ����

    //�ƶ�
    void update(float delta);
    void relativeMovement(float duration, const Vec2& deltaPosition);
    //��������
    Point positionToTileCoord(const Point& cocosCoord, const Direction& drt);

    CollisionType HelloWorld::checkCollision(const Point& heroPotion, const Direction& drt);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char* format, int count);

};

#endif // __HELLOWORLD_SCENE_H__



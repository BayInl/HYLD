#pragma once
#include "cocos2d.h"
#include "Heroes.h"
#include "AudioEngine.h"

#define HERO_SPEED 4  // ������4�ı�������ΪҪ��0.75��ģ����б�ǵ��ٶ�0.707��
//ccConfig.h �и� CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL = 1   �򿪿����   �պ��ٹذ�
//״̬���ѿ���

class AloneScene : public cocos2d::Scene
{
private:
    std::map<cocos2d::EventKeyboard::KeyCode, bool> keyMap;
    TMXTiledMap* map = TMXTiledMap::create("MyMap.tmx");
	
    Sprite* sprite = Sprite::create("CloseNormal.png");
    Sprite* sprite1 = Sprite::create("CloseNormal.png");
    Hero* hero_player = Scientist::create();
    Weapons* sword_bonus = SwordBonus::create();
    Weapons* weapon_player = hero_player->bindWeapon();
	
    Size visibleSize;
    Vec2 origin;
    float x ;
    float y ;
    float _width;
    float _height;

    cocos2d::MoveBy *moveToLeft= MoveBy::create(2, Vec2(-50, 0));
    cocos2d::MoveBy *moveToRight= MoveBy::create(2, Vec2(50, 0));
    cocos2d::MoveBy *moveToDown = MoveBy::create(2, Vec2(0, -50));
    cocos2d::MoveBy *moveToUp= MoveBy::create(2, Vec2(0, 50));
    cocos2d::MoveBy* moveBy;
	Sequence *seq = Sequence::create(moveToLeft, moveToDown, moveToRight, moveToUp,
        moveToLeft, moveToDown, moveToRight, moveToUp,
        moveToLeft, moveToDown, moveToRight, moveToUp,
        moveToLeft, moveToDown, moveToRight, moveToUp,
        moveToLeft, moveToDown, moveToRight, moveToUp, nullptr);
    Repeat *rep = Repeat::create(seq, 15);

    TMXLayer *obstacle ;
    SpriteFrame* frame = nullptr;
    Vector<SpriteFrame*> frameVec;
    Animation* animationMove;
    Animate* animate;
    EventListenerKeyboard* listener;
    typedef enum {
        Middle,
        Left,
        Right,
        Up,
        Down
    }Direction;
    typedef enum {
        Moveble,
        Wall,
        Grass
        //Enemy = 2
    }CollisionType;


    Point positionToTileCoord(const Point& cocosCoord, const Direction& drt) const;
    CollisionType checkCollision(const Point& heroPotion, const Direction& drt);//��ײ���
    bool AloneScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    void update(float delta);
public:
    static cocos2d::Scene* createScene();
    virtual bool AloneScene::init();

    //Wizard* hero_player= Wizard::create();
    //Scientist* hero_player = Scientist::create();
    //Knight* hero_player = Knight::create();
    //Berserker* hero_player = Berserker::create();
    //Hero *hero_player = Scientist::create();//��Ҳٿص�ʵ��


    //�ռ���ʵ��
    //BoxHealth* box0 = BoxHealth::create();
    //BoxCharge* box1 = BoxCharge::create();
    //BoxHell* box2 = BoxHell::create();
    //BoxWhat* box3 = BoxWhat::create();
    // a selector callback
    //void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(AloneScene);

    //cocos2d::Vector<cocos2d::SpriteFrame*> AloneScene::getAnimation(const char* format, int count);
    
};




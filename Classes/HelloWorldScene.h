#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Heroes.h"
#include "AudioEngine.h"

//ccConfig.h 中改 CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL = 1   打开抗锯齿   日后再关吧
//状态：已开启

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();    

    //玩家操控的实例
    //Wizard* hero_player= Wizard::create();
    //Scientist* hero_player = Scientist::create();
    //Knight* hero_player = Knight::create();
    Berserker* hero_player = Berserker::create();

    //武器实例
    Weapons* sword_bonus = SwordBonus::create();
    Weapons* weapon_player = hero_player->bindWeapon();

    //收集物实例
    BoxHealth* box0=BoxHealth::create();
    BoxCharge* box1= BoxCharge::create();
    BoxHell* box2= BoxHell::create();
    BoxWhat* box3= BoxWhat::create();

    //地图实例
    TMXTiledMap* map = TMXTiledMap::create("Map/MyMap.tmx");

    //键盘监听键值数组
    std::map<cocos2d::EventKeyboard::KeyCode, bool> key_map;

    //监听
    void onKeyPressedKnight(EventKeyboard::KeyCode keyCode, Event* event);
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);

    typedef enum {
        Middle,
        Left,
        Right,
        Up,
        Down
    }Direction;//方向

    typedef enum {
        Moveble,
        Wall,
        Grass
        //Enemy = 2
    }CollisionType;//碰撞物体

    //移动
    void update(float delta);
    void relativeMovement(float duration, const Vec2& deltaPosition);
    //计算坐标
    Point positionToTileCoord(const Point& cocosCoord, const Direction& drt);

    CollisionType HelloWorld::checkCollision(const Point& heroPotion, const Direction& drt);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    cocos2d::Vector<cocos2d::SpriteFrame*> getAnimation(const char* format, int count);

};

#endif // __HELLOWORLD_SCENE_H__



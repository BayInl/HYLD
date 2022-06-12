#ifndef __BATTLE_H__
#define __BATTLE_H__

#include "cocos2d.h"
#include "Heroes.h"
#include "AudioEngine.h"
#include "GlobalVars.h"
#include "Settlement.h"

#define HERO_WIDTH 70
#define HERO_HEIGHT 90
#define HERO_NPC_NUM 9
#define BOX_NUM 6
#define MAP_INIT_X -800
#define MAP_INIT_Y -700

//ccConfig.h 中改 CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL = 1   打开抗锯齿   日后再关吧
//状态：已开启

class Battle : public cocos2d::Scene
{
private:
    /*****************键位******************/
    cocos2d::EventKeyboard::KeyCode up = cocos2d::EventKeyboard::KeyCode::KEY_W;
    cocos2d::EventKeyboard::KeyCode down = cocos2d::EventKeyboard::KeyCode::KEY_S;
    cocos2d::EventKeyboard::KeyCode left = cocos2d::EventKeyboard::KeyCode::KEY_A;
    cocos2d::EventKeyboard::KeyCode right = cocos2d::EventKeyboard::KeyCode::KEY_D;
    cocos2d::EventKeyboard::KeyCode q = cocos2d::EventKeyboard::KeyCode::KEY_Q;
    cocos2d::EventKeyboard::KeyCode p = cocos2d::EventKeyboard::KeyCode::KEY_P;
    cocos2d::EventKeyboard::KeyCode o = cocos2d::EventKeyboard::KeyCode::KEY_O;
    cocos2d::EventKeyboard::KeyCode shift = cocos2d::EventKeyboard::KeyCode::KEY_SHIFT;
    /***************************************/

    /***************玩家实例****************/
    //Hero* hero_player = Scientist::create();
    //玩家操控的实例
    //Wizard* hero_player = Wizard::create();
    //Scientist* hero_player = Scientist::create();
    Hero* hero_player ;
    //Berserker* hero_player = Berserker::create();
    //武器实例
    Weapons* sword_bonus = SwordBonus::create();
    Weapons* weapon_player ;
    //科学家的武器以及大招
    Bullet* projectile_sci = nullptr;
    BulletBonus* projectiles_sci[8] = { nullptr };
    //女巫的武器以及大招
    Light* projectile_wiz = nullptr;
    LightBonus* projectiles_wiz = nullptr;
    //狂战士大招
    Glove* projectile_ber = nullptr;
    //下面是NPC的
    //科学家的武器以及大招
    Bullet* projectile_sci_npc[HERO_NPC_NUM] = { nullptr };
    BulletBonus* projectiles_sci_npc[HERO_NPC_NUM] = { nullptr };
    //女巫的武器以及大招
    Light* projectile_wiz_npc[HERO_NPC_NUM] = { nullptr };
    LightBonus* projectiles_wiz_npc[HERO_NPC_NUM] = { nullptr };
    //狂战士大招
    Glove* projectile_ber_npc[HERO_NPC_NUM] = {nullptr};
	/*
    武器标签（Tag）说明：
	女巫普通攻击projectile_wiz设置为200
    女巫大招projectiles_wiz设置为201
    科学家普通攻击projectile_sci设置为100
	科学家大招projectiles_sci设置为101~108
    狂战士大招projectile_ber设置为300
    下面是NPC的
    女巫普通攻击projectile_wiz_npc设置为210
    女巫大招projectiles_wiz_npc设置为211
    科学家普通攻击projectile_sci_npc设置为110
    科学家大招projectiles_sci_npc设置为111
    狂战士大招projectile_ber_npc设置为310
    */
    /***************************************/
	
	
	/***************敌人实例****************/
    Hero* hero_npc[HERO_NPC_NUM];
	//武器实例
    Weapons* sword_bonus_npc[HERO_NPC_NUM];
	Weapons* weapon_npc[HERO_NPC_NUM];
	/***************************************/

	
    /***************游戏状态****************/
    bool is_game_over = false;
    bool is_game_pause = false;
    bool is_game_win = false;
	long long int mouse_click_time = 0;	//鼠标点击的时间
    long long int light_time = 0;//光雾攻击间隔
    long long int light_bonus_time = 0;//超级光雾攻击间隔
    long long int npc_attack_time[HERO_NPC_NUM] = { 0 };//npc攻击间隔
    long long int light_time_npc[HERO_NPC_NUM] = { 0 };//npc光雾
    long long int light_bonus_time_npc[HERO_NPC_NUM] = { 0 };//npc超级光雾
    
    /***************************************/

	
    /**************收集物实例***************/
    BoxWhat* boxwhat[BOX_NUM];
    BoxHealth* boxhealth[BOX_NUM];
    BoxCharge* boxcharge[BOX_NUM];
    BoxHell* boxhell[BOX_NUM];
    /***************************************/

	
    /***************地图实例****************/
    TMXTiledMap* map = TMXTiledMap::create("Map/MyMap0.tmx");
    Sprite* safetyZone = Sprite::create("Map/SafetyZone.png");
    Sprite* poisonousSmoke = Sprite::create("Map/poisonousSmoke.png");
    Sprite* returnToSafetyZone = Sprite::create("Map/returnToSafetyZone.png");
    float scale = 1.0f;//地图大小
    /***************************************/
    Size visibleSize;
    Vec2 origin;
    void initNPC();//初始化npc
    void Battle::npc_move();//npc的移动
    void Battle::npc_attack();//npc攻击
    void Battle::npc_move600();//npc的移动在发现敌人时
    void Battle::npc_move_safety_zone();//npc逃往安全区
    void initBox(); //初始化收集物
	//自定义计时器
	void Battle::npc_update(float delta);
    void Battle::safetyZone_update(float delta);
	Vec2 Battle::calculate_distance(const Vec2& a, const Vec2& b);//计算距离
    float Battle::calculate_distance_to_center_of_map(const Vec2& coord);//计算到地图中心的距离
    Vec2 Battle::calculate_vec(const Vec2& a, const Vec2& b);//计算向量
    float Battle::calculate_modulus(const Vec2& a, const Vec2& b);//计算向量的模
    void Battle::attack_sci();//科学家普通子弹的碰撞检测
    void Battle::attack_sci_bonus(BulletBonus* projectiles);//科学家大招子弹的碰撞检测
    void Battle::attack_wiz();//法师普通攻击的碰撞检测
    void Battle::attack_wiz_bonus();//法师大招攻击的碰撞检测
    void Battle::attack_ber();//狂战士大招攻击的检测
    //下面是NPC的
    void Battle::attack_sci_npc();//科学家普通子弹的碰撞检测
    void Battle::attack_sci_bonus_npc(BulletBonus* projectiles,int m);//科学家大招子弹的碰撞检测
    void Battle::attack_wiz_npc();//法师普通攻击和大招攻击的碰撞检测
    void Battle::attack_ber_npc();//狂战士大招攻击的检测
    //收集各种箱子的检测
    void Battle::collect_box();
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void doPause();
    void setPause(bool status);

    //键盘监听键值数组
    std::map<cocos2d::EventKeyboard::KeyCode, bool> key_map;

    //监听
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
    void relativeMovement(float duration, const Vec2& deltaPosition, bool shiftOn);
    //计算坐标
    Point positionToTileCoord(const Point& cocosCoord, const Direction& drt);

    CollisionType Battle::checkCollision(const Point& heroPotion, const Direction& drt);
    int Battle::checkCollision_remote(Item* item);
    void replaceToSettlement();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuPauseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Battle);
};

#endif // __HELLOWORLD_SCENE_H__



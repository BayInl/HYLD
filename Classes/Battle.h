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

//ccConfig.h �и� CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL = 1   �򿪿����   �պ��ٹذ�
//״̬���ѿ���

class Battle : public cocos2d::Scene
{
private:
    /*****************��λ******************/
    cocos2d::EventKeyboard::KeyCode up = cocos2d::EventKeyboard::KeyCode::KEY_W;
    cocos2d::EventKeyboard::KeyCode down = cocos2d::EventKeyboard::KeyCode::KEY_S;
    cocos2d::EventKeyboard::KeyCode left = cocos2d::EventKeyboard::KeyCode::KEY_A;
    cocos2d::EventKeyboard::KeyCode right = cocos2d::EventKeyboard::KeyCode::KEY_D;
    cocos2d::EventKeyboard::KeyCode q = cocos2d::EventKeyboard::KeyCode::KEY_Q;
    cocos2d::EventKeyboard::KeyCode p = cocos2d::EventKeyboard::KeyCode::KEY_P;
    cocos2d::EventKeyboard::KeyCode o = cocos2d::EventKeyboard::KeyCode::KEY_O;
    cocos2d::EventKeyboard::KeyCode shift = cocos2d::EventKeyboard::KeyCode::KEY_SHIFT;
    /***************************************/

    /***************���ʵ��****************/
    //Hero* hero_player = Scientist::create();
    //��Ҳٿص�ʵ��
    //Wizard* hero_player = Wizard::create();
    //Scientist* hero_player = Scientist::create();
    Hero* hero_player ;
    //Berserker* hero_player = Berserker::create();
    //����ʵ��
    Weapons* sword_bonus = SwordBonus::create();
    Weapons* weapon_player ;
    //��ѧ�ҵ������Լ�����
    Bullet* projectile_sci = nullptr;
    BulletBonus* projectiles_sci[8] = { nullptr };
    //Ů�׵������Լ�����
    Light* projectile_wiz = nullptr;
    LightBonus* projectiles_wiz = nullptr;
    //��սʿ����
    Glove* projectile_ber = nullptr;
    //������NPC��
    //��ѧ�ҵ������Լ�����
    Bullet* projectile_sci_npc[HERO_NPC_NUM] = { nullptr };
    BulletBonus* projectiles_sci_npc[HERO_NPC_NUM] = { nullptr };
    //Ů�׵������Լ�����
    Light* projectile_wiz_npc[HERO_NPC_NUM] = { nullptr };
    LightBonus* projectiles_wiz_npc[HERO_NPC_NUM] = { nullptr };
    //��սʿ����
    Glove* projectile_ber_npc[HERO_NPC_NUM] = {nullptr};
	/*
    ������ǩ��Tag��˵����
	Ů����ͨ����projectile_wiz����Ϊ200
    Ů�״���projectiles_wiz����Ϊ201
    ��ѧ����ͨ����projectile_sci����Ϊ100
	��ѧ�Ҵ���projectiles_sci����Ϊ101~108
    ��սʿ����projectile_ber����Ϊ300
    ������NPC��
    Ů����ͨ����projectile_wiz_npc����Ϊ210
    Ů�״���projectiles_wiz_npc����Ϊ211
    ��ѧ����ͨ����projectile_sci_npc����Ϊ110
    ��ѧ�Ҵ���projectiles_sci_npc����Ϊ111
    ��սʿ����projectile_ber_npc����Ϊ310
    */
    /***************************************/
	
	
	/***************����ʵ��****************/
    Hero* hero_npc[HERO_NPC_NUM];
	//����ʵ��
    Weapons* sword_bonus_npc[HERO_NPC_NUM];
	Weapons* weapon_npc[HERO_NPC_NUM];
	/***************************************/

	
    /***************��Ϸ״̬****************/
    bool is_game_over = false;
    bool is_game_pause = false;
    bool is_game_win = false;
	long long int mouse_click_time = 0;	//�������ʱ��
    long long int light_time = 0;//���������
    long long int light_bonus_time = 0;//�������������
    long long int npc_attack_time[HERO_NPC_NUM] = { 0 };//npc�������
    long long int light_time_npc[HERO_NPC_NUM] = { 0 };//npc����
    long long int light_bonus_time_npc[HERO_NPC_NUM] = { 0 };//npc��������
    
    /***************************************/

	
    /**************�ռ���ʵ��***************/
    BoxWhat* boxwhat[BOX_NUM];
    BoxHealth* boxhealth[BOX_NUM];
    BoxCharge* boxcharge[BOX_NUM];
    BoxHell* boxhell[BOX_NUM];
    /***************************************/

	
    /***************��ͼʵ��****************/
    TMXTiledMap* map = TMXTiledMap::create("Map/MyMap0.tmx");
    Sprite* safetyZone = Sprite::create("Map/SafetyZone.png");
    Sprite* poisonousSmoke = Sprite::create("Map/poisonousSmoke.png");
    Sprite* returnToSafetyZone = Sprite::create("Map/returnToSafetyZone.png");
    float scale = 1.0f;//��ͼ��С
    /***************************************/
    Size visibleSize;
    Vec2 origin;
    void initNPC();//��ʼ��npc
    void Battle::npc_move();//npc���ƶ�
    void Battle::npc_attack();//npc����
    void Battle::npc_move600();//npc���ƶ��ڷ��ֵ���ʱ
    void Battle::npc_move_safety_zone();//npc������ȫ��
    void initBox(); //��ʼ���ռ���
	//�Զ����ʱ��
	void Battle::npc_update(float delta);
    void Battle::safetyZone_update(float delta);
	Vec2 Battle::calculate_distance(const Vec2& a, const Vec2& b);//�������
    float Battle::calculate_distance_to_center_of_map(const Vec2& coord);//���㵽��ͼ���ĵľ���
    Vec2 Battle::calculate_vec(const Vec2& a, const Vec2& b);//��������
    float Battle::calculate_modulus(const Vec2& a, const Vec2& b);//����������ģ
    void Battle::attack_sci();//��ѧ����ͨ�ӵ�����ײ���
    void Battle::attack_sci_bonus(BulletBonus* projectiles);//��ѧ�Ҵ����ӵ�����ײ���
    void Battle::attack_wiz();//��ʦ��ͨ��������ײ���
    void Battle::attack_wiz_bonus();//��ʦ���й�������ײ���
    void Battle::attack_ber();//��սʿ���й����ļ��
    //������NPC��
    void Battle::attack_sci_npc();//��ѧ����ͨ�ӵ�����ײ���
    void Battle::attack_sci_bonus_npc(BulletBonus* projectiles,int m);//��ѧ�Ҵ����ӵ�����ײ���
    void Battle::attack_wiz_npc();//��ʦ��ͨ�����ʹ��й�������ײ���
    void Battle::attack_ber_npc();//��սʿ���й����ļ��
    //�ռ��������ӵļ��
    void Battle::collect_box();
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void doPause();
    void setPause(bool status);

    //���̼�����ֵ����
    std::map<cocos2d::EventKeyboard::KeyCode, bool> key_map;

    //����
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
    void relativeMovement(float duration, const Vec2& deltaPosition, bool shiftOn);
    //��������
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



#ifndef __HEROES_H__
#define __HEROES_H__

#include "cocos2d.h"
#include "Weapons.h"


#define ENERGYMAX_KNIGHT 10
#define ENERGYMAX_BERSERKER 8
#define ENERGYMAX_WIZARD 12
#define ENERGYMAX_SCIENTIST 16
#define HEALTH_KNIGHT 35
#define HEALTH_BERSERKER 40
#define HEALTH_WIZARD 20
#define HEALTH_SCIENTIST 30

using namespace cocos2d;

//英雄基类-------------------------------------------------------------------------------------------------
class Hero: public Node
{
    friend class Weapons;
protected:
    Sprite* sprite = nullptr;//精灵对象
    Vector<SpriteFrame*> frames;//精灵帧容器
    int energy = 0;//能量
    int health = 20;//血量
    bool rightdirect = true;//朝向
public:
    int getEnergy();//获得角色的能量值
    void setEnergy(int);//设置角色的能量值
    void setEnergyOnePlus();//给角色的能量值加一
    int getHealth();//获得角色的生命值
    void setHealth(int);//设置角色的生命值
    void setHealthPlus(int);//给角色的生命值增减
    void setDirectLeft();
    void setDirectRight();
    bool isDirectRight();
    Sprite* getSprite();//获取精灵对象
    Vector<SpriteFrame*> Hero::getAnimation(const char* format, int count); //获取精灵的动画
    void bindSprite(Sprite* sprite);//绑定对象
    void Animater(); //让角色在闲置状态下动起来
    //角色的朝向由setScaleX(-1.0f)和(1.0f)决定
    virtual bool SuperSkill()=0;//角色大招（未完成）
};
//-------------------------------------------------------------------------------------------------------------

//骑士类------------------------------------------------------------------------------------------------------
class Knight : public Hero
{
public:
    Knight();
    bool init()override;
    CREATE_FUNC(Knight);
    Weapons* bindWeapon(int); //绑定武器
    bool SuperSkill();
    bool isBonus();
protected:
    SwordBonus* sword_bonus = SwordBonus::create(); //普攻武器
    Sword* sword = Sword::create();     //大招武器
    Sprite* KnightSprite = Sprite::create("knight.png");
    bool bonusstatus = false;
};
//-------------------------------------------------------------------------------------------------------------

//科学家类----------------------------------------------------------------------------------------------------
class Scientist : public Hero
{
public:
    Scientist();
    bool init()override;
    CREATE_FUNC(Scientist);
    bool SuperSkill();
protected:
    Sprite* ScientistSprite = Sprite::create("scientist.png");
};
//-------------------------------------------------------------------------------------------------------------

//法师类------------------------------------------------------------------------------------------------------
class  Wizard : public Hero
{
public:
    Wizard();
    bool init()override;
    CREATE_FUNC(Wizard);
    bool SuperSkill();
protected:
    Sprite* WizardSprite = Sprite::create("wizard.png");
};
//-------------------------------------------------------------------------------------------------------------

//狂战士类------------------------------------------------------------------------------------------------------
class Berserker : public Hero
{
public:
    Berserker();
    bool init()override;
    CREATE_FUNC(Berserker);
    bool SuperSkill();
protected:
    Sprite* BerserkerSprite = Sprite::create("berserker.png");
};
//-------------------------------------------------------------------------------------------------------------

#endif
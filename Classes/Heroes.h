#ifndef __HEROES_H__
#define __HEROES_H__

#include "cocos2d.h"
#include "Weapons.h"

#define ENERGYMAX_KNIGHT 13
#define ENERGYMAX_BERSERKER 8
#define ENERGYMAX_WIZARD 30
#define ENERGYMAX_SCIENTIST 10
#define ENERGYMAX_KNIGHT_NPC 6
#define ENERGYMAX_BERSERKER_NPC 3
#define ENERGYMAX_WIZARD_NPC 15
#define ENERGYMAX_SCIENTIST_NPC 7
#define HEALTH_KNIGHT 77
#define HEALTH_BERSERKER 96
#define HEALTH_WIZARD 55
#define HEALTH_SCIENTIST 66

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
    virtual Weapons* bindWeapon()=0;
	
    int getEnergy();//获得角色的能量值
    void setEnergy(int);//设置角色的能量值
    void setEnergyPlus(int);//给角色的能量值加一
    int getHealth();//获得角色的生命值
    virtual void setHealth()=0;//设置角色的生命值
    virtual void setHealthPlus(int)=0;//给角色的生命值增减
    void setDirectLeft();//设置朝向
    void setDirectRight();
    bool isDirectRight();//检查朝向
    Sprite* getSprite();//获取精灵对象
    Vector<SpriteFrame*> Hero::getAnimation(const char* format, int count); //获取精灵的动画
    void bindSprite(Sprite* sprite);//绑定对象
    void Animater(); //让角色在闲置状态下动起来
    //角色的朝向由setScaleX(-1.0f)和(1.0f)决定
    virtual bool SuperSkill()=0;//角色大招
    virtual const int WhatIam() = 0;
    void setOpacity(uint8_t alpha = 255);//设置精灵透明度
};
//-------------------------------------------------------------------------------------------------------------

//骑士类------------------------------------------------------------------------------------------------------
class Knight : public Hero
{
public:
    Knight();
    bool init()override;
    CREATE_FUNC(Knight);
    Weapons* bindWeapon(); //绑定武器
    void setHealth();
    void setHealthPlus(int);
    bool SuperSkill();
    //Knight返回1
    //Scientist返回2	
    //Wizard返回3
    //Berserker返回4
    const int WhatIam();
protected:
    Sword* sword = Sword::create(); //武器
    Sprite* KnightSprite = Sprite::create("Menus/knight.png");
};
//-------------------------------------------------------------------------------------------------------------

//科学家类----------------------------------------------------------------------------------------------------
class Scientist : public Hero
{
public:
    Scientist();
    bool init()override;
    CREATE_FUNC(Scientist);
    Weapons* bindWeapon(); //绑定武器
    void setHealth();
    void setHealthPlus(int);
    bool SuperSkill();
    //Knight返回1
    //Scientist返回2	
    //Wizard返回3
    //Berserker返回4
    const int WhatIam();
protected:
    Revolver* revolver = Revolver::create(); //武器
    Sprite* ScientistSprite = Sprite::create("Menus/scientist.png"); ;
    SpriteFrameCache* sfc;
};
//-------------------------------------------------------------------------------------------------------------

//法师类------------------------------------------------------------------------------------------------------
class  Wizard : public Hero
{
public:
    Wizard();
    bool init()override;
    CREATE_FUNC(Wizard);
    Weapons* bindWeapon(); //绑定武器
    void setHealth();
    void setHealthPlus(int);
    bool SuperSkill();
    //Knight返回1
    //Scientist返回2	
    //Wizard返回3
    //Berserker返回4
    const int WhatIam();
protected:
    Wand* wand = Wand::create(); //武器
    Sprite* WizardSprite = Sprite::create("Menus/wizard.png");
};
//-------------------------------------------------------------------------------------------------------------

//狂战士类------------------------------------------------------------------------------------------------------
class Berserker : public Hero
{
public:
    Berserker();
    bool init()override;
    CREATE_FUNC(Berserker);
    Weapons* bindWeapon(); //绑定武器
    void setHealth();
    void setHealthPlus(int);
    bool SuperSkill();
    //Knight返回1
    //Scientist返回2	
    //Wizard返回3
    //Berserker返回4
    const int WhatIam();
protected:
    Hammer* hammer = Hammer::create(); //武器
    Sprite* BerserkerSprite = Sprite::create("Menus/fighter.png");
};
//-------------------------------------------------------------------------------------------------------------

#endif

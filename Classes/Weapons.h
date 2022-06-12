#ifndef __WEAPONS_H__
#define __WEAPONS_H__

#include "cocos2d.h"
#include "Item.h"
#include "GlobalVars.h"

using namespace cocos2d;

//武器基类----------------------------------------------------------------------------
class Weapons:public Item
{
	friend class Hero;
protected:
	int damage = 0;//伤害
	bool rightdirect = true;//朝向
	float volume = (switch_sound_ ? volume_ : 0.0f);
public:
	void setDamage(int damage_);//设置武器攻击力
	int getDamage();//获取武器攻击力
	virtual void setDirectLeft();//设置朝向
	virtual void setDirectRight();
	bool isDirectRight();//检查朝向
	Vector<SpriteFrame*> Weapons::getAnimation(const char* format, int count); //武器攻击的动画
	virtual void attack()=0;//攻击
};
//-----------------------------------------------------------------------------------


//魔杖类----------------------------------------------------------------------------
class Wand :public Weapons
{
public:
	Wand();
	bool init()override;
	CREATE_FUNC(Wand);
	void attack();
};
//-----------------------------------------------------------------------------------

//锤子类----------------------------------------------------------------------------
class Hammer :public Weapons
{
public:
	Hammer();
	void Hammer::setDirectRight();
	void Hammer::setDirectLeft();
	bool init()override;
	CREATE_FUNC(Hammer);
	void attack();
};
//-----------------------------------------------------------------------------------

//左轮类----------------------------------------------------------------------------
class Revolver :public Weapons
{
public:
	Revolver();
	bool init()override;
	CREATE_FUNC(Revolver);
	void attack();
};
//-----------------------------------------------------------------------------------

//剑类----------------------------------------------------------------------------
class Sword :public Weapons
{
public:
	Sword();
	bool init()override;
	CREATE_FUNC(Sword);
	void attack();
};
//-----------------------------------------------------------------------------------

//超级剑类----------------------------------------------------------------------------
class SwordBonus:public Weapons
{
public:
	SwordBonus();
	bool init()override;
	CREATE_FUNC(SwordBonus);
	void attack();
};
//-----------------------------------------------------------------------------------

#endif

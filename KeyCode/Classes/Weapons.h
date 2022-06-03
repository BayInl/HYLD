#ifndef __WEAPONS_H__
#define __WEAPONS_H__

#include "cocos2d.h"
#include "Item.h"

using namespace cocos2d;

class Weapons:public Item
{
protected:
	int damage = 0;//伤害
public:
	void SetDamage(int damage_);//设置武器攻击力
	int GetDamage();//获取武器攻击力
	Vec2 GetPosition();//获取武器的位置
	Vector<SpriteFrame*> Weapons::getAnimation(const char* format, int count); //武器攻击的动画
	virtual void attack()=0;//攻击
};

class Sword :public Weapons
{
public:
	Sword();
	bool init()override;
	CREATE_FUNC(Sword);
	void attack();
protected:
	Sprite* SwordSprite = Sprite::create("sword.png");
};

class SwordBonus:public Weapons
{
public:
	SwordBonus();
	bool init()override;
	CREATE_FUNC(SwordBonus);
	void attack();
protected:
	Sprite* SBSprite = Sprite::create("sword_bonus.png");
};

#endif

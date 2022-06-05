#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"

using namespace cocos2d;

//Item基类，即包含包括角色的武器，武器发射的子弹或者法球，道具（包括治疗包，能量包，陷阱）
class Item :public Node
{
protected:
	Sprite* itemsprite = nullptr;
	Vector<SpriteFrame*> frames;
public:
	Sprite* getSprite();//获取精灵对象
	void bindSprite(Sprite* sprite);//绑定对象
};
//---------------------------------------------------------------------------------------------------------


//子弹类--------------------------------------------------------------------------------------------------
class Bullet :public Item
{
protected:
	int damage = 4;
public:
	Bullet();
	bool init()override;
	int getDamage();//获取攻击力
	CREATE_FUNC(Bullet);
};
//---------------------------------------------------------------------------------------------------------

//超级子弹类--------------------------------------------------------------------------------------------------
class BulletBonus :public Item
{
protected:
	int damage = 10;
public:
	BulletBonus();
	bool init()override;
	int getDamage();//获取攻击力
	CREATE_FUNC(BulletBonus);
};
//---------------------------------------------------------------------------------------------------------

//光雾类--------------------------------------------------------------------------------------------------
class Light :public Item
{
protected:
	int damage = 2;
public:
	Light();
	Vector<SpriteFrame*> Light::getAnimation(const char* format, int count);//动画
	bool init()override;
	int getDamage();//获取攻击力
	CREATE_FUNC(Light);
};
//---------------------------------------------------------------------------------------------------------

//超级光雾类--------------------------------------------------------------------------------------------------
class LightBonus :public Item
{
protected:
	int damage = 24;
public:
	LightBonus();
	Vector<SpriteFrame*>  LightBonus::getAnimation(const char* format, int count); //动画
	bool init()override;
	int getDamage();//获取攻击力
	CREATE_FUNC(LightBonus);
};
//---------------------------------------------------------------------------------------------------------

//拳套类--------------------------------------------------------------------------------------------------
class Glove :public Item
{
protected:
	int damage = 18;
public:
	Glove();
	bool init()override;
	int getDamage();//获取攻击力
	CREATE_FUNC(Glove);
};
//---------------------------------------------------------------------------------------------------------

#endif 

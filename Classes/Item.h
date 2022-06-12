#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include "AudioEngine.h"

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
	void setOpacity(uint8_t alpha = 255);//设置精灵透明度
};
//---------------------------------------------------------------------------------------------------------


//子弹类--------------------------------------------------------------------------------------------------
class Bullet :public Item
{
protected:
	int damage = 5;
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
	int damage = 1;
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
	int damage = 2;
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
	int damage = 24;
public:
	Glove();
	bool init()override;
	int getDamage();//获取攻击力
	CREATE_FUNC(Glove);
};
//---------------------------------------------------------------------------------------------------------

//生命箱类--------------------------------------------------------------------------------------------------
class BoxHealth :public Item
{
protected:
	int heal = 12;
public:
	BoxHealth();
	bool init()override;
	int getHeal();//获取治疗量
	CREATE_FUNC(BoxHealth);
};
//---------------------------------------------------------------------------------------------------------

//能量箱类--------------------------------------------------------------------------------------------------
class BoxCharge :public Item
{
protected:
	int charge = 4;
public:
	BoxCharge();
	bool init()override;
	int getCharge();//获取能量值
	CREATE_FUNC(BoxCharge);
};
//---------------------------------------------------------------------------------------------------------

//陷阱箱类--------------------------------------------------------------------------------------------------
class BoxHell :public Item
{
protected:
	int damage = 8;
public:
	BoxHell();
	bool init()override;
	int getDamage();//获取攻击力
	CREATE_FUNC(BoxHell);
};
//---------------------------------------------------------------------------------------------------------

//问号箱类--------------------------------------------------------------------------------------------------
class BoxWhat :public Item
{
protected:
	int damage = 16;
	int heal = 20;
	int charge = 8;
	int judge=0; //判断这个箱子里面是恢复（回复生命和能量）还是陷阱，0是陷阱，1是恢复，默认是0
public:
	BoxWhat();
	bool init()override;
	int getDamage();//获取攻击力
	int getHeal();//获取治疗量
	int getCharge();//获取能量值
	int isWhat(); //随机抽取0和1赋给judge并返回，1是伤害，0是恢复
	CREATE_FUNC(BoxWhat);
};
//---------------------------------------------------------------------------------------------------------

#endif 

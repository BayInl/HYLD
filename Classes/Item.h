#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"

using namespace cocos2d;

//Item���࣬������������ɫ������������������ӵ����߷��򣬵��ߣ��������ư��������������壩
class Item :public Node
{
protected:
	Sprite* itemsprite = nullptr;
	Vector<SpriteFrame*> frames;
public:
	Sprite* getSprite();//��ȡ�������
	void bindSprite(Sprite* sprite);//�󶨶���
};
//---------------------------------------------------------------------------------------------------------


//�ӵ���--------------------------------------------------------------------------------------------------
class Bullet :public Item
{
protected:
	int damage = 4;
public:
	Bullet();
	bool init()override;
	int getDamage();//��ȡ������
	CREATE_FUNC(Bullet);
};
//---------------------------------------------------------------------------------------------------------

//�����ӵ���--------------------------------------------------------------------------------------------------
class BulletBonus :public Item
{
protected:
	int damage = 10;
public:
	BulletBonus();
	bool init()override;
	int getDamage();//��ȡ������
	CREATE_FUNC(BulletBonus);
};
//---------------------------------------------------------------------------------------------------------

//������--------------------------------------------------------------------------------------------------
class Light :public Item
{
protected:
	int damage = 2;
public:
	Light();
	Vector<SpriteFrame*> Light::getAnimation(const char* format, int count);//����
	bool init()override;
	int getDamage();//��ȡ������
	CREATE_FUNC(Light);
};
//---------------------------------------------------------------------------------------------------------

//����������--------------------------------------------------------------------------------------------------
class LightBonus :public Item
{
protected:
	int damage = 24;
public:
	LightBonus();
	Vector<SpriteFrame*>  LightBonus::getAnimation(const char* format, int count); //����
	bool init()override;
	int getDamage();//��ȡ������
	CREATE_FUNC(LightBonus);
};
//---------------------------------------------------------------------------------------------------------

//ȭ����--------------------------------------------------------------------------------------------------
class Glove :public Item
{
protected:
	int damage = 18;
public:
	Glove();
	bool init()override;
	int getDamage();//��ȡ������
	CREATE_FUNC(Glove);
};
//---------------------------------------------------------------------------------------------------------

#endif 

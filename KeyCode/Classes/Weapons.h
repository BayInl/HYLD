#ifndef __WEAPONS_H__
#define __WEAPONS_H__

#include "cocos2d.h"
#include "Item.h"

using namespace cocos2d;

class Weapons:public Item
{
protected:
	int damage = 0;//�˺�
public:
	void SetDamage(int damage_);//��������������
	int GetDamage();//��ȡ����������
	Vec2 GetPosition();//��ȡ������λ��
	Vector<SpriteFrame*> Weapons::getAnimation(const char* format, int count); //���������Ķ���
	virtual void attack()=0;//����
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

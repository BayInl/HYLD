#ifndef __WEAPONS_H__
#define __WEAPONS_H__

#include "cocos2d.h"
#include "Item.h"
#include "GlobalVars.h"

using namespace cocos2d;

//��������----------------------------------------------------------------------------
class Weapons:public Item
{
	friend class Hero;
protected:
	int damage = 0;//�˺�
	bool rightdirect = true;//����
	float volume = (switch_sound_ ? volume_ : 0.0f);
public:
	void setDamage(int damage_);//��������������
	int getDamage();//��ȡ����������
	virtual void setDirectLeft();//���ó���
	virtual void setDirectRight();
	bool isDirectRight();//��鳯��
	Vector<SpriteFrame*> Weapons::getAnimation(const char* format, int count); //���������Ķ���
	virtual void attack()=0;//����
};
//-----------------------------------------------------------------------------------


//ħ����----------------------------------------------------------------------------
class Wand :public Weapons
{
public:
	Wand();
	bool init()override;
	CREATE_FUNC(Wand);
	void attack();
};
//-----------------------------------------------------------------------------------

//������----------------------------------------------------------------------------
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

//������----------------------------------------------------------------------------
class Revolver :public Weapons
{
public:
	Revolver();
	bool init()override;
	CREATE_FUNC(Revolver);
	void attack();
};
//-----------------------------------------------------------------------------------

//����----------------------------------------------------------------------------
class Sword :public Weapons
{
public:
	Sword();
	bool init()override;
	CREATE_FUNC(Sword);
	void attack();
};
//-----------------------------------------------------------------------------------

//��������----------------------------------------------------------------------------
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

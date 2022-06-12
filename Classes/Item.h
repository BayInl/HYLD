#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include "AudioEngine.h"

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
	void setOpacity(uint8_t alpha = 255);//���þ���͸����
};
//---------------------------------------------------------------------------------------------------------


//�ӵ���--------------------------------------------------------------------------------------------------
class Bullet :public Item
{
protected:
	int damage = 5;
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
	int damage = 1;
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
	int damage = 2;
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
	int damage = 24;
public:
	Glove();
	bool init()override;
	int getDamage();//��ȡ������
	CREATE_FUNC(Glove);
};
//---------------------------------------------------------------------------------------------------------

//��������--------------------------------------------------------------------------------------------------
class BoxHealth :public Item
{
protected:
	int heal = 12;
public:
	BoxHealth();
	bool init()override;
	int getHeal();//��ȡ������
	CREATE_FUNC(BoxHealth);
};
//---------------------------------------------------------------------------------------------------------

//��������--------------------------------------------------------------------------------------------------
class BoxCharge :public Item
{
protected:
	int charge = 4;
public:
	BoxCharge();
	bool init()override;
	int getCharge();//��ȡ����ֵ
	CREATE_FUNC(BoxCharge);
};
//---------------------------------------------------------------------------------------------------------

//��������--------------------------------------------------------------------------------------------------
class BoxHell :public Item
{
protected:
	int damage = 8;
public:
	BoxHell();
	bool init()override;
	int getDamage();//��ȡ������
	CREATE_FUNC(BoxHell);
};
//---------------------------------------------------------------------------------------------------------

//�ʺ�����--------------------------------------------------------------------------------------------------
class BoxWhat :public Item
{
protected:
	int damage = 16;
	int heal = 20;
	int charge = 8;
	int judge=0; //�ж�������������ǻָ����ظ��������������������壬0�����壬1�ǻָ���Ĭ����0
public:
	BoxWhat();
	bool init()override;
	int getDamage();//��ȡ������
	int getHeal();//��ȡ������
	int getCharge();//��ȡ����ֵ
	int isWhat(); //�����ȡ0��1����judge�����أ�1���˺���0�ǻָ�
	CREATE_FUNC(BoxWhat);
};
//---------------------------------------------------------------------------------------------------------

#endif 

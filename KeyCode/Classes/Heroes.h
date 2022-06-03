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

//Ӣ�ۻ���-------------------------------------------------------------------------------------------------
class Hero: public Node
{
    friend class Weapons;
protected:
    Sprite* sprite = nullptr;//�������
    Vector<SpriteFrame*> frames;//����֡����
    int energy = 0;//����
    int health = 20;//Ѫ��
    bool rightdirect = true;//����
public:
    int getEnergy();//��ý�ɫ������ֵ
    void setEnergy(int);//���ý�ɫ������ֵ
    void setEnergyOnePlus();//����ɫ������ֵ��һ
    int getHealth();//��ý�ɫ������ֵ
    void setHealth(int);//���ý�ɫ������ֵ
    void setHealthPlus(int);//����ɫ������ֵ����
    void setDirectLeft();
    void setDirectRight();
    bool isDirectRight();
    Sprite* getSprite();//��ȡ�������
    Vector<SpriteFrame*> Hero::getAnimation(const char* format, int count); //��ȡ����Ķ���
    void bindSprite(Sprite* sprite);//�󶨶���
    void Animater(); //�ý�ɫ������״̬�¶�����
    //��ɫ�ĳ�����setScaleX(-1.0f)��(1.0f)����
    virtual bool SuperSkill()=0;//��ɫ���У�δ��ɣ�
};
//-------------------------------------------------------------------------------------------------------------

//��ʿ��------------------------------------------------------------------------------------------------------
class Knight : public Hero
{
public:
    Knight();
    bool init()override;
    CREATE_FUNC(Knight);
    Weapons* bindWeapon(int); //������
    bool SuperSkill();
    bool isBonus();
protected:
    SwordBonus* sword_bonus = SwordBonus::create(); //�չ�����
    Sword* sword = Sword::create();     //��������
    Sprite* KnightSprite = Sprite::create("knight.png");
    bool bonusstatus = false;
};
//-------------------------------------------------------------------------------------------------------------

//��ѧ����----------------------------------------------------------------------------------------------------
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

//��ʦ��------------------------------------------------------------------------------------------------------
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

//��սʿ��------------------------------------------------------------------------------------------------------
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
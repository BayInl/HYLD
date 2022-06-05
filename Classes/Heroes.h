#ifndef __HEROES_H__
#define __HEROES_H__

#include "cocos2d.h"
#include "Weapons.h"

#define ENERGYMAX_KNIGHT 10
#define ENERGYMAX_BERSERKER 6
#define ENERGYMAX_WIZARD 16
#define ENERGYMAX_SCIENTIST 12
#define HEALTH_KNIGHT 70
#define HEALTH_BERSERKER 90
#define HEALTH_WIZARD 50
#define HEALTH_SCIENTIST 60

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
    void setDirectLeft();//���ó���
    void setDirectRight();
    bool isDirectRight();//��鳯��
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
    Weapons* bindWeapon(); //������
    bool SuperSkill();
protected:
    Sword* sword = Sword::create(); //����
    Sprite* KnightSprite = Sprite::create("Heroes/knight.png");
};
//-------------------------------------------------------------------------------------------------------------

//��ѧ����----------------------------------------------------------------------------------------------------
class Scientist : public Hero
{
public:
    Scientist();
    bool init()override;
    CREATE_FUNC(Scientist);
    Weapons* bindWeapon(); //������
    bool SuperSkill();
protected:
    Revolver* revolver = Revolver::create(); //����
    Sprite* ScientistSprite = Sprite::create("Heroes/scientist.png");
};
//-------------------------------------------------------------------------------------------------------------

//��ʦ��------------------------------------------------------------------------------------------------------
class  Wizard : public Hero
{
public:
    Wizard();
    bool init()override;
    CREATE_FUNC(Wizard);
    Weapons* bindWeapon(); //������
    bool SuperSkill();
protected:
    Wand* wand = Wand::create(); //����
    Sprite* WizardSprite = Sprite::create("Heroes/wizard.png");
};
//-------------------------------------------------------------------------------------------------------------

//��սʿ��------------------------------------------------------------------------------------------------------
class Berserker : public Hero
{
public:
    Berserker();
    bool init()override;
    CREATE_FUNC(Berserker);
    Weapons* bindWeapon(); //������
    bool SuperSkill();
protected:
    Hammer* hammer = Hammer::create(); //����
    Sprite* BerserkerSprite = Sprite::create("Heroes/berserker.png");
};
//-------------------------------------------------------------------------------------------------------------

#endif
#ifndef __HEROES_H__
#define __HEROES_H__

#include "cocos2d.h"
#include "Weapons.h"

#define ENERGYMAX_KNIGHT 13
#define ENERGYMAX_BERSERKER 8
#define ENERGYMAX_WIZARD 30
#define ENERGYMAX_SCIENTIST 10
#define ENERGYMAX_KNIGHT_NPC 6
#define ENERGYMAX_BERSERKER_NPC 3
#define ENERGYMAX_WIZARD_NPC 15
#define ENERGYMAX_SCIENTIST_NPC 7
#define HEALTH_KNIGHT 77
#define HEALTH_BERSERKER 96
#define HEALTH_WIZARD 55
#define HEALTH_SCIENTIST 66

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
    virtual Weapons* bindWeapon()=0;
	
    int getEnergy();//��ý�ɫ������ֵ
    void setEnergy(int);//���ý�ɫ������ֵ
    void setEnergyPlus(int);//����ɫ������ֵ��һ
    int getHealth();//��ý�ɫ������ֵ
    virtual void setHealth()=0;//���ý�ɫ������ֵ
    virtual void setHealthPlus(int)=0;//����ɫ������ֵ����
    void setDirectLeft();//���ó���
    void setDirectRight();
    bool isDirectRight();//��鳯��
    Sprite* getSprite();//��ȡ�������
    Vector<SpriteFrame*> Hero::getAnimation(const char* format, int count); //��ȡ����Ķ���
    void bindSprite(Sprite* sprite);//�󶨶���
    void Animater(); //�ý�ɫ������״̬�¶�����
    //��ɫ�ĳ�����setScaleX(-1.0f)��(1.0f)����
    virtual bool SuperSkill()=0;//��ɫ����
    virtual const int WhatIam() = 0;
    void setOpacity(uint8_t alpha = 255);//���þ���͸����
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
    void setHealth();
    void setHealthPlus(int);
    bool SuperSkill();
    //Knight����1
    //Scientist����2	
    //Wizard����3
    //Berserker����4
    const int WhatIam();
protected:
    Sword* sword = Sword::create(); //����
    Sprite* KnightSprite = Sprite::create("Menus/knight.png");
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
    void setHealth();
    void setHealthPlus(int);
    bool SuperSkill();
    //Knight����1
    //Scientist����2	
    //Wizard����3
    //Berserker����4
    const int WhatIam();
protected:
    Revolver* revolver = Revolver::create(); //����
    Sprite* ScientistSprite = Sprite::create("Menus/scientist.png"); ;
    SpriteFrameCache* sfc;
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
    void setHealth();
    void setHealthPlus(int);
    bool SuperSkill();
    //Knight����1
    //Scientist����2	
    //Wizard����3
    //Berserker����4
    const int WhatIam();
protected:
    Wand* wand = Wand::create(); //����
    Sprite* WizardSprite = Sprite::create("Menus/wizard.png");
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
    void setHealth();
    void setHealthPlus(int);
    bool SuperSkill();
    //Knight����1
    //Scientist����2	
    //Wizard����3
    //Berserker����4
    const int WhatIam();
protected:
    Hammer* hammer = Hammer::create(); //����
    Sprite* BerserkerSprite = Sprite::create("Menus/fighter.png");
};
//-------------------------------------------------------------------------------------------------------------

#endif

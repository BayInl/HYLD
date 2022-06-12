#include "Heroes.h"
//英雄基类定义-----------------------------------------------------------------------------------
int Hero::getEnergy()
{
    return energy;
}

void Hero::setEnergy(int n)
{
    energy = n;
}

void Hero::setEnergyPlus(int n)
{
    energy += n;
}

int Hero::getHealth()
{
    return health;
}

void Hero::setDirectLeft()
{
    if (rightdirect) {
        sprite->setScaleX(-1.0f);
        rightdirect = false;
    }
}

void Hero::setDirectRight()
{
	if (!rightdirect) {
		sprite->setScaleX(1.0f);
		rightdirect = true;
	}
}

bool Hero::isDirectRight()
{
    return rightdirect;
}

Sprite* Hero::getSprite()
{
    return this->sprite;
}

void Hero::bindSprite(Sprite* sprite)
{
    this->sprite = sprite;
    this->addChild(sprite);
}

Vector<SpriteFrame*> Hero::getAnimation(const char* format, int count)
{
    auto spritecache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames;
    char str[100] = { 0 };
    for (int i = 0; i <= count; i++)
    {
        sprintf(str, format, i);
        animFrames.pushBack(spritecache->getSpriteFrameByName(str));
    }
    return animFrames;
}

void Hero::Animater() 
{
    auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 8);
    sprite->runAction(RepeatForever::create(Animate::create(animation)));
}

void Hero::setOpacity(uint8_t alpha)
{
    sprite->setOpacity(alpha);
}

//--------------------------------------------------------------------------------------------------


//骑士类定义--------------------------------------------------------------------------------------
Knight::Knight()
{
    log("Trying to create Knight");
    //将帧动画加入角色显示------------------------------------
    auto sfc = SpriteFrameCache::getInstance();
    sfc->addSpriteFramesWithFile("Heroes/KnightWalk.plist");
    frames = getAnimation("knight_walk%d.png", 2);
    sprite = Sprite::createWithSpriteFrame(frames.front());
    setHealth();
    bindSprite(sprite);
    //------------------------------------------------------------
    health = HEALTH_KNIGHT;
    if (KnightSprite == nullptr|| sprite == nullptr)
    {
        log("Failed to create sprite for Knight.");
    }
}

bool Knight::init()
{
    return true;
}

Weapons* Knight::bindWeapon()
{
        return sword;
}

void Knight::setHealth()
{
    health = HEALTH_KNIGHT;
}

void Knight::setHealthPlus(int n)
{
    health += n;
    if (health >= HEALTH_KNIGHT)
        health = HEALTH_KNIGHT;
}

bool Knight::SuperSkill()
{
    return true;
}
//Knight返回1
//Scientist返回2	
//Wizard返回3
//Berserker返回4
const int Knight::WhatIam()
{
    return 1;
}
//--------------------------------------------------------------------------------------------------


//科学家类定义--------------------------------------------------------------------------------------
Scientist::Scientist()
{
    log("Trying to create Scientist");
    //将帧动画加入角色显示------------------------------------
    sfc = SpriteFrameCache::getInstance();
    sfc->addSpriteFramesWithFile("Heroes/ScientistWalk.plist");
    frames = getAnimation("scientist_walk%d.png", 2);
    sprite = Sprite::createWithSpriteFrame(frames.front());
    sprite->setFlippedX(true);
    setHealth();
    bindSprite(sprite); 
    //------------------------------------------------------------
    health = HEALTH_SCIENTIST;
    if (ScientistSprite == nullptr|| sprite == nullptr)
    {
        log("Failed to create sprite for Scientist.");
    }
}

bool Scientist::init()
{
    return true;
}

Weapons* Scientist::bindWeapon()
{
    return revolver;
}

void Scientist::setHealth()
{
    health = HEALTH_SCIENTIST;
}

void Scientist::setHealthPlus(int n)
{
    health += n;
    if (health >= HEALTH_SCIENTIST)
        health = HEALTH_SCIENTIST;
}

bool Scientist::SuperSkill()
{
    revolver->attack();
    setEnergy(0);
    return true;
}
//Knight返回1
//Scientist返回2	
//Wizard返回3
//Berserker返回4
const int Scientist::WhatIam()
{
    return 2;
}
//--------------------------------------------------------------------------------------------------


//法师类定义--------------------------------------------------------------------------------------
Wizard::Wizard()
{
    log("Trying to create Wizard");
    //将帧动画加入角色显示------------------------------------
    auto sfc = SpriteFrameCache::getInstance();
    sfc->addSpriteFramesWithFile("Heroes/WizardWalk.plist");
    frames = getAnimation("wizard_walk%d.png", 2);
    sprite = Sprite::createWithSpriteFrame(frames.front());
    setHealth();
    bindSprite(sprite);
    //------------------------------------------------------------
    health = HEALTH_WIZARD;
    if (WizardSprite == nullptr || sprite == nullptr)
    {
        log("Failed to create sprite for Wizard.");
    }
}

bool Wizard::init()
{
    return true;
}

Weapons* Wizard::bindWeapon()
{
    return wand;
}

void Wizard::setHealth()
{
    health = HEALTH_WIZARD;
}

void Wizard::setHealthPlus(int n)
{
    health += n;
    if (health >= HEALTH_WIZARD)
        health = HEALTH_WIZARD;
}

bool Wizard::SuperSkill()
{
    wand->attack();
    setHealthPlus(20);
    setEnergy(0);
    return true;
}
//Knight返回1
//Scientist返回2	
//Wizard返回3
//Berserker返回4
const int Wizard::WhatIam()
{
    return 3;
}
//--------------------------------------------------------------------------------------------------

//狂战士类定义--------------------------------------------------------------------------------------
Berserker::Berserker()
{
    log("Trying to create Berserker");
    AudioEngine::preload("Sounds/berserker_superskill.mp3");
    //将帧动画加入角色显示------------------------------------
    auto sfc = SpriteFrameCache::getInstance();
    sfc->addSpriteFramesWithFile("Heroes/BerserkerWalk.plist");
    frames = getAnimation("fighter_walk%d.png", 2);
    sprite = Sprite::createWithSpriteFrame(frames.front());
    setHealth();
    bindSprite(sprite);
    //------------------------------------------------------------
    health = HEALTH_BERSERKER;
    if (BerserkerSprite == nullptr || sprite == nullptr)
    {
        log("Failed to create sprite for Berserker.");
    }
}

bool Berserker::init()
{
    return true;
}

Weapons* Berserker::bindWeapon()
{
    return hammer;
}

void Berserker::setHealth()
{
    health = HEALTH_BERSERKER;
}

void Berserker::setHealthPlus(int n)
{
    health += n;
    if (health >= HEALTH_BERSERKER)
        health = HEALTH_BERSERKER;
}

bool Berserker::SuperSkill()
{
    setHealth();
    setEnergy(0);
    return true;
}
//Knight返回1
//Scientist返回2	
//Wizard返回3
//Berserker返回4
const int Berserker::WhatIam()
{
    return 4;
}
//--------------------------------------------------------------------------------------------------

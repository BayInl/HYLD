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

void Hero::setEnergyOnePlus()
{
    energy++;
}

int Hero::getHealth()
{
    return health;
}

void Hero::setHealth(int n)
{
    energy = n;
}

void Hero::setHealthPlus(int n)
{
    energy += n;
}

void Hero::setDirectLeft()
{
    sprite->setScaleX(-1.0f);
    rightdirect = false;
}

void Hero::setDirectRight()
{
    sprite->setScaleX(1.0f);
    rightdirect = true;
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

bool Knight::SuperSkill()
{
    return true;
}
//--------------------------------------------------------------------------------------------------


//科学家类定义--------------------------------------------------------------------------------------
Scientist::Scientist()
{
    log("Trying to create Scientist");
    //将帧动画加入角色显示------------------------------------
    auto sfc = SpriteFrameCache::getInstance();
    sfc->addSpriteFramesWithFile("Heroes/ScientistWalk.plist");
    frames = getAnimation("scientist_walk%d.png", 2);
    sprite = Sprite::createWithSpriteFrame(frames.front());
    sprite->setFlippedX(true);
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

bool Scientist::SuperSkill()
{
    return true;
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

bool Wizard::SuperSkill()
{
    return true;
}
//--------------------------------------------------------------------------------------------------

//狂战士类定义--------------------------------------------------------------------------------------
Berserker::Berserker()
{
    log("Trying to create Berserker");
    //将帧动画加入角色显示------------------------------------
    auto sfc = SpriteFrameCache::getInstance();
    sfc->addSpriteFramesWithFile("Heroes/BerserkerWalk.plist");
    frames = getAnimation("fighter_walk%d.png", 2);
    sprite = Sprite::createWithSpriteFrame(frames.front());
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

bool Berserker::SuperSkill()
{
    return true;
}
//--------------------------------------------------------------------------------------------------
#include "Heroes.h"


//Ӣ�ۻ��ඨ��-----------------------------------------------------------------------------------
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


//��ʿ�ඨ��--------------------------------------------------------------------------------------
Knight::Knight()
{
    log("Trying to create Knight");
    //��֡���������ɫ��ʾ------------------------------------
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
    setEnergy(0);
    return true;
}
//--------------------------------------------------------------------------------------------------


//��ѧ���ඨ��--------------------------------------------------------------------------------------
Scientist::Scientist()
{
    log("Trying to create Scientist");
    //��֡���������ɫ��ʾ------------------------------------
    auto sfc = SpriteFrameCache::getInstance();
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
    Vec2 offset[8] = { Vec2(1, 0), Vec2(1, 1) ,Vec2(1, -1),Vec2(-1, 0) ,Vec2(-1, 1) ,Vec2(-1, -1),Vec2(0, 1),Vec2(0, -1) };
    Vec2 shootAmount[8];
    Vec2 realDest[8];
    // ����������
    BulletBonus* projectiles[8];
    for(int i=0;i<8;i++)
        projectiles[i] = BulletBonus::create();
    if (isDirectRight())
    {
        for (int i = 0; i < 8; i++)
            projectiles[i]->setPosition(sprite->getPosition() );
    }
    else
    {
        for (int i = 0; i < 8; i++)
            projectiles[i]->setPosition(sprite->getPosition() );
    }
    projectiles[1]->setRotation(-45);
    projectiles[2]->setRotation(45);
    projectiles[3]->setRotation(-180);
    projectiles[4]->setRotation(-135);
    projectiles[5]->setRotation(135);
    projectiles[6]->setRotation(-90);
    projectiles[7]->setRotation(90);
    for (int i = 0; i < 8; i++)
        this->addChild(projectiles[i]);
    //�����һ��ָ��������ĳ���Ϊ654������
    for(int i=0;i<8;i++)
        shootAmount[i] = offset[i] * 654;
    //Ŀ��λ��
    for (int i = 0; i < 8; i++)
        realDest[i] = shootAmount[i] + projectiles[i]->getPosition();
    //���������ƶ���Ŀ��λ�ã�Ȼ�����ӳ������Ƴ�
    MoveTo* actionMove[8];
    for (int i = 0; i < 8; i++)
        actionMove[i] = MoveTo::create(0.4f, realDest[i]);
    auto actionRemove = RemoveSelf::create();
    for (int i = 0; i < 8; i++)
        projectiles[i]->runAction(Sequence::create(actionMove[i], actionRemove, nullptr));
    revolver->attack();
    setEnergy(0);
    return true;
}
//--------------------------------------------------------------------------------------------------


//��ʦ�ඨ��--------------------------------------------------------------------------------------
Wizard::Wizard()
{
    log("Trying to create Wizard");
    //��֡���������ɫ��ʾ------------------------------------
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
    Vec2 offset = Vec2(1, 0);
    if(isDirectRight())
        offset = Vec2(1, 0);
    else
        offset = Vec2(-1, 0);
    // ����������
    auto projectile = LightBonus::create();
    projectile->setScale(1.6f, 2.1f);
    if (isDirectRight())
    {
        projectile->setPosition(sprite->getPosition() - Vec2(3, 30));
    }
    else
    {
        projectile->setPosition(sprite->getPosition() - Vec2(-3, 30));
    }
    this->addChild(projectile);
    //�����һ��ָ��������ĳ���Ϊ2500������
    auto shootAmount = offset * 2500;
    //Ŀ��λ��
    auto realDest = shootAmount + projectile->getPosition();
    //���������ƶ���Ŀ��λ�ã�Ȼ�����ӳ������Ƴ�
    auto actionMove = MoveTo::create(12.5f, realDest);
    auto actionRemove = RemoveSelf::create();
    projectile->runAction(Sequence::create(actionMove, actionRemove, nullptr));
    wand->attack();
    setHealthPlus(20);
    setEnergy(0);
    return true;
}
//--------------------------------------------------------------------------------------------------

//��սʿ�ඨ��--------------------------------------------------------------------------------------
Berserker::Berserker()
{
    log("Trying to create Berserker");
    AudioEngine::preload("Sounds/berserker_superskill.mp3");
    //��֡���������ɫ��ʾ------------------------------------
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
    auto berserker_audio = AudioEngine::play2d("Sounds/berserker_superskill.mp3", false, 0.7f);
    AudioEngine::resume(berserker_audio);
    Vec2 offset = Vec2(1, 0);
    if (isDirectRight())
        offset = Vec2(1, 0);
    else
        offset = Vec2(-1, 0);
    // ����������
    auto projectile = Glove::create();
    if (isDirectRight())
    {
        projectile->setPosition(sprite->getPosition() );
    }
    else
    {
        projectile->setPosition(sprite->getPosition() );
    }
    if (isDirectRight())
        ;
    else
        projectile->setScaleX(-1.0f);
    this->addChild(projectile);
    //�����һ��ָ��������ĳ���Ϊ900������
    auto shootAmount = offset * 900;
    //Ŀ��λ��
    auto realDest = shootAmount + projectile->getPosition();
    //���������ƶ���Ŀ��λ�ã�Ȼ�����ӳ������Ƴ�
    auto actionMove = MoveTo::create(1.5f, realDest);
    auto actionRemove = RemoveSelf::create();
    projectile->runAction(Sequence::create(actionMove, actionRemove, nullptr));
    setHealth();
    setEnergy(0);
    return true;
}
//--------------------------------------------------------------------------------------------------
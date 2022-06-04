#include "Weapons.h"

//武器基类定义-----------------------------------------------------
void Weapons::SetDamage(int damage_)
{
	damage = damage_;
}

int Weapons::GetDamage()
{
	return damage;
}

Vec2 Weapons::GetPosition()
{
	return itemsprite->getPosition();
}

Vector<SpriteFrame*> Weapons::getAnimation(const char* format, int count)
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
//----------------------------------------------------------------------------------


//Sword定义----------------------------------------------------------------------
Sword::Sword()
{
	log("Trying to building Sword");
	auto sfc = SpriteFrameCache::getInstance();
	sfc->addSpriteFramesWithFile("Weapons/Sword.plist");
	frames = getAnimation("sword%d.png", 5);
	itemsprite = Sprite::createWithSpriteFrame(frames.front());
	bindSprite(itemsprite);
	SetDamage(5);
	if (itemsprite == nullptr)
	{
		log("Failed to create Sword sprite.");
	}
}

bool Sword::init()
{
	return true;
}

void Sword::attack()
{
	auto animation = Animation::createWithSpriteFrames(frames, 0.4f / 8);
	auto animate = Animate::create(animation);
	auto delay = DelayTime::create(0.2f);
	auto sequence = Sequence::create(animate, delay, nullptr);
	itemsprite->runAction(sequence);
	itemsprite->runAction(sequence->reverse());
}

//-----------------------------------------------------------------------------------

//SwordBonus定义----------------------------------------------------------------
SwordBonus::SwordBonus()
{
	log("Trying to building SB");
	auto sfc = SpriteFrameCache::getInstance();
	sfc->addSpriteFramesWithFile("Weapons/SwordBonus.plist");
	frames = getAnimation("sword_bonus%d.png", 4);
	itemsprite = Sprite::createWithSpriteFrame(frames.front());
	bindSprite(itemsprite);
	SetDamage(15);
	if (itemsprite == nullptr)
	{
		log("Failed to create SwordBonus sprite.");
	}
}

bool SwordBonus::init()
{
	return true;
}

void SwordBonus::attack()
{
	auto animation = Animation::createWithSpriteFrames(frames, 0.5f / 8);
	auto animate = Animate::create(animation);
	auto delay = DelayTime::create(0.25f);
	//auto delaysequence = Sequence::create(delay, nullptr); //不必要的
	auto sequence = Sequence::create(animate, delay, nullptr);
	itemsprite->runAction(sequence);
	itemsprite->runAction(sequence->reverse());
}

//------------------------------------------------------------------------------------
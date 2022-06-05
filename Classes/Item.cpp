#include "Item.h"

//Item����---------------------------------------------------------------------
Sprite* Item::getSprite()
{
    return this->itemsprite;
}

void Item::bindSprite(Sprite* sprite)
{
    this->itemsprite = sprite;
    this->addChild(sprite);
}
//--------------------------------------------------------------------------------

//Bullet����---------------------------------------------------------------------
Bullet::Bullet()
{
	log("Trying to building bullet");
	itemsprite = Sprite::create("Weapons/revolver_projectile.png");
	bindSprite(itemsprite);
	if (itemsprite == nullptr)
	{
		log("Failed to create bullet sprite.");
	}
}

bool Bullet::init()
{
	return true;
}

int Bullet::getDamage()
{
    return damage;
}
//--------------------------------------------------------------------------------

//BulletBonus����---------------------------------------------------------------------
BulletBonus::BulletBonus()
{
	log("Trying to building bulletbonus");
	itemsprite = Sprite::create("Weapons/revolver_projectile_bonus.png");
	bindSprite(itemsprite);
	if (itemsprite == nullptr)
	{
		log("Failed to create bulletbonus sprite.");
	}
}

bool BulletBonus::init()
{
	return true;
}

int BulletBonus::getDamage()
{
	return damage;
}
//--------------------------------------------------------------------------------

//Light����----------------------------------------------------------------
Light::Light()
{
	log("Trying to building L");
	auto sfc = SpriteFrameCache::getInstance();
	sfc->addSpriteFramesWithFile("Weapons/WandLight.plist");
	frames = getAnimation("wand_light%d.png", 4);
	itemsprite = Sprite::createWithSpriteFrame(frames.front());
	bindSprite(itemsprite);
	if (itemsprite == nullptr)
	{
		log("Failed to create L sprite.");
	}
	auto animation = Animation::createWithSpriteFrames(frames, 0.15f / 8);
	itemsprite->runAction(RepeatForever::create(Animate::create(animation)));
}

bool Light::init()
{
	return true;
}

int Light::getDamage()
{
	return damage;
}

Vector<SpriteFrame*> Light::getAnimation(const char* format, int count)
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
//------------------------------------------------------------------------------------

//LightBonus����----------------------------------------------------------------
LightBonus::LightBonus()
{
	log("Trying to building LB");
	auto sfc = SpriteFrameCache::getInstance();
	sfc->addSpriteFramesWithFile("Weapons/WandLightBonus.plist");
	frames = getAnimation("wand_light_bonus%d.png", 4);
	itemsprite = Sprite::createWithSpriteFrame(frames.front());
	bindSprite(itemsprite);
	if (itemsprite == nullptr)
	{
		log("Failed to create LB sprite.");
	}
	auto animation = Animation::createWithSpriteFrames(frames, 0.2f / 8);
	itemsprite->runAction(RepeatForever::create(Animate::create(animation)));
}

bool LightBonus::init()
{
	return true;
}

int LightBonus::getDamage()
{
	return damage;
}

Vector<SpriteFrame*> LightBonus::getAnimation(const char* format, int count)
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
//------------------------------------------------------------------------------------

//Glove����---------------------------------------------------------------------
Glove::Glove()
{
	log("Trying to building glove");
	itemsprite = Sprite::create("Weapons/glove.png");
	bindSprite(itemsprite);
	if (itemsprite == nullptr)
	{
		log("Failed to create glove sprite.");
	}
}

bool Glove::init()
{
	return true;
}

int Glove::getDamage()
{
	return damage;
}
//--------------------------------------------------------------------------------
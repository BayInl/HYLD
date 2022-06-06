#include "Item.h"
#include <time.h>

//Item定义---------------------------------------------------------------------
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

//Bullet定义---------------------------------------------------------------------
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

//BulletBonus定义---------------------------------------------------------------------
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

//Light定义----------------------------------------------------------------
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

//LightBonus定义----------------------------------------------------------------
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

//Glove定义---------------------------------------------------------------------
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

//BoxHealth定义---------------------------------------------------------------------
BoxHealth::BoxHealth()
{
	log("Trying to building boxhealth");
	itemsprite = Sprite::create("BasicItems/boxhealth.png");
	bindSprite(itemsprite);
	if (itemsprite == nullptr)
	{
		log("Failed to create boxhealth sprite.");
	}
}

bool BoxHealth::init()
{
	return true;
}

int BoxHealth::getHeal()
{
	return heal;
}
//--------------------------------------------------------------------------------

//BoxEnergy定义---------------------------------------------------------------------
BoxCharge::BoxCharge()
{
	log("Trying to building BoxCharge");
	itemsprite = Sprite::create("BasicItems/boxenergy.png");
	bindSprite(itemsprite);
	if (itemsprite == nullptr)
	{
		log("Failed to create BoxCharge sprite.");
	}
}

bool BoxCharge::init()
{
	return true;
}

int BoxCharge::getCharge()
{
	return charge;
}
//--------------------------------------------------------------------------------

//BoxHell定义---------------------------------------------------------------------
BoxHell::BoxHell()
{
	log("Trying to building boxhell");
	itemsprite = Sprite::create("BasicItems/boxhell.png");
	bindSprite(itemsprite);
	if (itemsprite == nullptr)
	{
		log("Failed to create boxhell sprite.");
	}
}

bool BoxHell::init()
{
	return true;
}

int BoxHell::getDamage()
{
	return damage;
}
//--------------------------------------------------------------------------------

//BoxWhat定义---------------------------------------------------------------------
BoxWhat::BoxWhat()
{
	log("Trying to building boxwhat");
	itemsprite = Sprite::create("BasicItems/boxwhat.png");
	bindSprite(itemsprite);
	if (itemsprite == nullptr)
	{
		log("Failed to create boxwhat sprite.");
	}
}

bool BoxWhat::init()
{
	return true;
}

int BoxWhat::getDamage()
{
	return damage;
}

int BoxWhat::getHeal()
{
	return heal;
}

int BoxWhat::getCharge()
{
	return charge;
}

int BoxWhat::isWhat()
{
	srand(time(NULL));
	judge = rand() % 2;
	return judge;
}
//--------------------------------------------------------------------------------
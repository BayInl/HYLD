#include "Weapons.h"

//武器基类定义-----------------------------------------------------
void Weapons::setDamage(int damage_)
{
	damage = damage_;
}

int Weapons::getDamage()
{
	return damage;
}

void Weapons::setDirectLeft()
{
	itemsprite->setScaleX(-1.0f);
	rightdirect = false;
}

void Weapons::setDirectRight()
{
	itemsprite->setScaleX(1.0f);
	rightdirect = true;
}

bool Weapons::isDirectRight()
{
	return rightdirect;
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

//Wand定义----------------------------------------------------------------------
Wand::Wand()
{
	log("Trying to building wand");
	AudioEngine::preload("Sounds/wizard_wand.mp3");
	auto sfc = SpriteFrameCache::getInstance();
	sfc->addSpriteFramesWithFile("Weapons/Wand.plist");
	frames = getAnimation("wand%d.png", 6);
	itemsprite = Sprite::createWithSpriteFrame(frames.front());
	bindSprite(itemsprite);
	if (itemsprite == nullptr)
	{
		log("Failed to create wand sprite.");
	}
}

bool Wand::init()
{
	return true;
}

void Wand::attack()
{
	auto weapon_audio = AudioEngine::play2d("Sounds/wizard_wand.mp3", false,1.2f);
	AudioEngine::resume(weapon_audio);
	auto animation = Animation::createWithSpriteFrames(frames, 0.4f / 8);
	auto animate = Animate::create(animation);
	auto sequence = Sequence::create(animate, nullptr);
	itemsprite->runAction(sequence);
}

//-----------------------------------------------------------------------------------


//Hammer定义----------------------------------------------------------------------
Hammer::Hammer()
{
	log("Trying to building hammer");
	AudioEngine::preload("Sounds/berserker_hammer.mp3");
	auto sfc = SpriteFrameCache::getInstance();
	sfc->addSpriteFramesWithFile("Weapons/Hammer.plist");
	frames = getAnimation("hammer%d.png", 4);
	itemsprite = Sprite::createWithSpriteFrame(frames.front());
	itemsprite->setScale(0.7f);
	bindSprite(itemsprite);
	setDamage(5);
	if (itemsprite == nullptr)
	{
		log("Failed to create hammer sprite.");
	}
}

bool Hammer::init()
{
	return true;
}

void Hammer::attack()
{
	auto weapon_audio = AudioEngine::play2d("Sounds/berserker_hammer.mp3", false);
	AudioEngine::resume(weapon_audio);
	auto animation = Animation::createWithSpriteFrames(frames, 0.7f / 8);
	auto animate = Animate::create(animation);
	auto sequence = Sequence::create(animate, nullptr);
	itemsprite->runAction(sequence);
}

void Hammer::setDirectRight()
{
	itemsprite->setScaleX(0.7f);
	rightdirect = true;
}

void Hammer::setDirectLeft()
{
	itemsprite->setScaleX(-0.7f);
	rightdirect = false;
}

//-----------------------------------------------------------------------------------


//Revolver定义----------------------------------------------------------------------
Revolver::Revolver()
{
	log("Trying to building Gun");
	AudioEngine::preload("Sounds/scientist_revolver.mp3");
	auto sfc = SpriteFrameCache::getInstance();
	sfc->addSpriteFramesWithFile("Weapons/Revolver.plist");
	frames = getAnimation("revolver%d.png", 4);
	itemsprite = Sprite::createWithSpriteFrame(frames.front());
	bindSprite(itemsprite);
	if (itemsprite == nullptr)
	{
		log("Failed to create Gun sprite.");
	}
}

bool Revolver::init()
{
	return true;
}

void Revolver::attack()
{
	auto weapon_audio = AudioEngine::play2d("Sounds/scientist_revolver.mp3", false,0.3f);
	AudioEngine::resume(weapon_audio);
	auto animation = Animation::createWithSpriteFrames(frames, 0.3f / 8);
	auto animate = Animate::create(animation);
	auto sequence = Sequence::create(animate, nullptr);
	itemsprite->runAction(sequence);
}

//-----------------------------------------------------------------------------------

//Sword定义----------------------------------------------------------------------
Sword::Sword()
{
	log("Trying to building Sword");
	AudioEngine::preload("Sounds/knight_sword.mp3");
	auto sfc = SpriteFrameCache::getInstance();
	sfc->addSpriteFramesWithFile("Weapons/Sword.plist");
	frames = getAnimation("sword%d.png", 5);
	itemsprite = Sprite::createWithSpriteFrame(frames.front());
	bindSprite(itemsprite);
	setDamage(7);
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
	auto weapon_audio = AudioEngine::play2d("Sounds/knight_sword.mp3", false,1.2f);
	AudioEngine::resume(weapon_audio);
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
	AudioEngine::preload("Sounds/knight_superskill.mp3");
	auto sfc = SpriteFrameCache::getInstance();
	sfc->addSpriteFramesWithFile("Weapons/SwordBonus.plist");
	frames = getAnimation("sword_bonus%d.png", 4);
	itemsprite = Sprite::createWithSpriteFrame(frames.front());
	bindSprite(itemsprite);
	setDamage(30);
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
	auto weapon_audio = AudioEngine::play2d("Sounds/knight_superskill.mp3", false,1.3f);
	AudioEngine::resume(weapon_audio);
	auto animation = Animation::createWithSpriteFrames(frames, 0.5f / 8);
	auto animate = Animate::create(animation);
	auto delay = DelayTime::create(0.25f);
	//auto delaysequence = Sequence::create(delay, nullptr); //不必要的
	auto sequence = Sequence::create(animate, delay, nullptr);
	itemsprite->runAction(sequence);
	itemsprite->runAction(sequence->reverse());
}

//------------------------------------------------------------------------------------
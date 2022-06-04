#include "Item.h"

Sprite* Item::getSprite()
{
    return this->itemsprite;
}

void Item::bindSprite(Sprite* sprite)
{
    this->itemsprite = sprite;
    this->addChild(sprite);
}

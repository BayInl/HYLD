#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"

using namespace cocos2d;

//Item基类，即包含包括角色的武器，武器发射的子弹或者法球，道具（包括治疗包，能量包，陷阱）
class Item :public Node
{
protected:
	Sprite* itemsprite = nullptr;
	Vector<SpriteFrame*> frames;
public:
	Sprite* getSprite();//获取精灵对象
	void bindSprite(Sprite* sprite);//绑定对象
};
//---------------------------------------------------------------------------------------------------------

#endif 

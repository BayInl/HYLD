#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"

using namespace cocos2d;

//Item���࣬������������ɫ������������������ӵ����߷��򣬵��ߣ��������ư��������������壩
class Item :public Node
{
protected:
	Sprite* itemsprite = nullptr;
	Vector<SpriteFrame*> frames;
public:
	Sprite* getSprite();//��ȡ�������
	void bindSprite(Sprite* sprite);//�󶨶���
};
//---------------------------------------------------------------------------------------------------------

#endif 

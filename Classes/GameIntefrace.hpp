#pragma once
#pragma warning(disable:26495)
#include "cocos2d.h"
#include"ChineseWord.h"

USING_NS_CC;
extern ChineseWord Words;
class GameIntefrace : public cocos2d::Scene
{
private:
	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    void _set_background();
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameIntefrace);

};

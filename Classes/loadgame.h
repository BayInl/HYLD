#pragma once
#include "cocos2d.h"
#include "editor-support/cocostudio/SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include"ChineseWord.h"
#include"Battle.h"
#include"OnlineChat.h"
USING_NS_CC;
extern ChineseWord Words;
extern cocos2d::SpriteFrameCache *spritecache;
extern CocosDenshion::SimpleAudioEngine* audio;
class loadgame :public cocos2d::Scene
{
private:
	
	TransitionScene* transition;
	cocos2d::Scene* onlinechat ;
	cocos2d::ui::Button* button_back;
	cocos2d::ui::Button* button_alonegame;
	cocos2d::ui::Button* button_onlinegame;
	
	cocos2d::Label* _label_adver_0;
	
	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
	void _set_background();
	void _set_button_back();
	void Health_game_advice();
	void _set_button_alonegame();
	void _set_button_onlinegame();
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(loadgame);
};


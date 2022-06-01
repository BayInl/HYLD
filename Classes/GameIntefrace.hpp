#pragma once
#pragma warning(disable:26495)
#pragma warning(disable:26451)
#include "cocos2d.h"
#include"ChineseWord.h"
#include "ui/CocosGUI.h"
#include<string.h>

USING_NS_CC;
extern ChineseWord Words;
struct inf_button {
    bool is_turnon = true;
    std::string firstpath;
	std::string secondpath;
	std::string thirdpath;
};
class GameIntefrace : public cocos2d::Scene
{
private:
    //获取声音引擎
	
    cocos2d::Layer* _layer_initial_;

    inf_button flag_setting;
    inf_button music_effect;
    inf_button music_background;
	
    cocos2d::ui::Button* button_set;
    cocos2d::ui::Button* button_set_music_effect;
    cocos2d::ui::Button* button_set_music;
    cocos2d::Label* _label_adver_0;
    DrawNode* _line;
    //cocos2d::ui::
    ChineseWord setting;
	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    void _set_background();//开始界面背景
    void Health_game_advice();//健康游戏忠告
	void _set_button_set();//设置按钮
    void _set_button_music_background();//音效按钮
	
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	
    cocos2d::ActionInterval* spawnOut(cocos2d::Vec2 point, float duration);
    cocos2d::ActionInterval* spawnIn(float duration);
    CREATE_FUNC(GameIntefrace);

};

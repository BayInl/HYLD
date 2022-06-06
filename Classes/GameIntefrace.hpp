#pragma once
#pragma warning(disable:26495)
#pragma warning(disable:26451)
#include "cocos2d.h"
#include"ChineseWord.h"
#include "ui/CocosGUI.h"
#include<string.h>
#include "loadgame.h"
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
    cocos2d::Scene* scene_loadgame;
    TransitionScene* transition;
    cocos2d::Layer* _layer_initial_;
	cocos2d::Layer* _layer_infor_;

    inf_button flag_setting;
    inf_button music_effect;
    inf_button music_background;
    int volume;
	//_layer_initial_
    cocos2d::ui::Button* button_set;
    cocos2d::ui::Button* button_set_music_effect;
    cocos2d::ui::Button* button_set_music;
    cocos2d::ui::Button* button_playgame;
    cocos2d::ui::Button* button_infor;
    cocos2d::ui::Slider* slider_set_volume;

    cocos2d::Label* label_volume_description;
    cocos2d::Label* _label_adver_0;
	
    DrawNode* _line_0;
    ChineseWord setting;
	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    void _set_background(Node* node, const std::string& path);//开始界面背景
    void Health_game_advice();//健康游戏忠告
	void _set_button_set();//设置按钮
    void _set_button_music_background();//背景音乐按钮
    void _set_button_music_effect();//音效按钮
	void _set_button_music_effect_volume();
    void playgame();//开始游戏按钮
    void _set_button_infor();//个人信息按钮

	//_layer_infor_
	cocos2d::ui::Button* button_back;
	cocos2d::ui::TextField *text_name;
    cocos2d::Label* _label_Username_description;
    cocos2d::Label* _label_Numberofwins;
    cocos2d::Label* _label_Numberoftrophies;
    void _set_button_back();
	void Username_description();
	void Numberofwins();
	void Numberoftrophies();
	void _set_text_name();
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	
    cocos2d::ActionInterval* spawnOut(cocos2d::Vec2 point, float duration);
    cocos2d::ActionInterval* spawnIn(Vec2 point,float duration);
    CREATE_FUNC(GameIntefrace);

};

#pragma once
#pragma warning(disable:26495)
#pragma warning(disable:26451)
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include<string.h>
#include"Heroes.h"
#include"loadgame.h"
#include "GlobalVars.h"
USING_NS_CC;
struct inf_button {
    bool is_turnon = true;
    std::string firstpath;
	std::string secondpath;
	std::string thirdpath;
};
class GameIntefrace : public cocos2d::Scene
{
private:
    Hero* myhero;
    SwordBonus *sword_bonus;
    Weapons* weapons;
    cocos2d::Scene* scene_loadgame;
    TransitionScene* transition;
    cocos2d::Layer* _layer_initial_;
	cocos2d::Layer* _layer_infor_;

    inf_button flag_setting;
    inf_button music_effect;
    inf_button music_background;

	//_layer_initial_
    cocos2d::ui::Button* button_set;
    cocos2d::ui::Button* button_set_music_effect;
    cocos2d::ui::Button* button_set_music;
    cocos2d::ui::Button* button_playgame;
    cocos2d::ui::Button* button_infor;
    cocos2d::ui::Slider* slider_set_volume;
    cocos2d::ui::Slider* slider_set_hero;
    cocos2d::ui::Slider* slider_set_npcnum;
    cocos2d::Label* label_npcnum_description;
    cocos2d::Label* label_hero_select;
    cocos2d::Label* label_hero_description;
    cocos2d::Label* label_volume_description;
    cocos2d::Label* _label_adver_0;
    cocos2d::Texture2D* pTexture;
    cocos2d::Sprite* edge;
	
    DrawNode* _line_0;
    ChineseWord setting;
	cocos2d::Size visibleSize = Director::getInstance()->getVisibleSize();
    void _set_background(Node* node, const std::string& path);//��ʼ���汳��
    void Health_game_advice();//������Ϸ�Ҹ�
	void _set_button_set();//���ð�ť
    void _set_button_music_background();//�������ְ�ť
    void _set_button_music_effect();//��Ч��ť
	void _set_button_music_effect_volume();
    void _set_slider_npcnum();
    void playgame();//��ʼ��Ϸ��ť
    void _set_button_infor();//������Ϣ��ť
    void _set_hero();
	void _set_npcnum();

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

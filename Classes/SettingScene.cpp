#include"GameIntefrace.hpp"
#include"SettingScene.hpp"
#include"ChineseWord.h"
#include<cstring>
cocos2d::Scene* SettingScene::createScene()
{
    return SettingScene::create();
}
void SettingScene::_set_background() {

    auto _background = Sprite::create("background.png");
    _background->setAnchorPoint(Vec2(1, 1));
    _background->setContentSize(visibleSize);
    _background->setPosition(Vec2(visibleSize.width, visibleSize.height));
    this->addChild(_background, -1);
}
bool SettingScene::init()
{
    
    //setting.prt_cnWords.at(1001).asInt();
    
    if (!Scene::init())
    {
        return false;
    }
    Director::getInstance()->setGLDefaultValues();
    SettingScene::_set_background();
    ChineseWord setting("Setting_1.xml");
    setting.insertWord("9999", "test");
    if (setting.Store("..\\Resources\\Setting_1.xml") == 1)
        CCLOG("success");
    else
		CCLOG("fail");
    //auto scene = GameIntefrace::createScene();
    //Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
    //Director::getInstance()->popScene();
    auto _setting_sound_effect = MenuItemImage::create("turnon.png", "turnoff.png");
    auto _setting_sound_music = MenuItemImage::create("turnon.png", "turnoff.png");
    auto _menu_seeting_menu = Menu::create(_setting_sound_effect, _setting_sound_music,NULL);
    _menu_seeting_menu->alignItemsVertically();
    this->addChild(_menu_seeting_menu, 1);
    
	
    CCLOG("fdsf");
    return true;
}
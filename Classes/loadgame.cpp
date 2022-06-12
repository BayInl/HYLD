#include "loadgame.h"
void loadgame::_set_background()
{
    auto backgroundFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("background_1.png");
    auto _background = Sprite::createWithSpriteFrame(backgroundFrame);
    
    _background->setAnchorPoint(Vec2(1, 1));
    _background->setContentSize(visibleSize);
    _background->setPosition(Vec2(visibleSize.width, visibleSize.height));
    this->addChild(_background, -1);
}
cocos2d::Scene* loadgame::createScene()
{
	return loadgame::create();
}
void loadgame::Health_game_advice()
{
	_label_adver_0 = Label::createWithSystemFont(
		Words.getWord("1002") + '\n' + Words.getWord("1003") + '\n' + Words.getWord("1004"), "宋体", 20);
	_label_adver_0->setAnchorPoint(Vec2(0.5, 0));
	this->addChild(_label_adver_0);
	_label_adver_0->setPosition(Vec2(visibleSize.width / 2, 50));
}
void loadgame::_set_button_alonegame()
{
	button_alonegame = ui::Button::create();
	button_alonegame->setTitleText(Words.getWord("1010"));
	button_alonegame->setTitleFontSize(30);
	button_alonegame->setTitleFontName("宋体");
	button_alonegame->setTitleColor(Color3B(199, 230, 232));
	button_alonegame->setAnchorPoint(Vec2(0.5, 0));
	button_alonegame->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2+50));
	button_alonegame->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		cocos2d::Scene* alonegame;
		switch (type) {
		case ui::Widget::TouchEventType::ENDED:
			audio->stopBackgroundMusic();
			alonegame = Battle::createScene();
			transition = TransitionFade::create(0.5f, alonegame);//创建动画
			Director::getInstance()->pushScene(transition);
			break;
		default:
			break;
		}
		});
	this->addChild(button_alonegame, 1);
}
void loadgame::_set_button_onlinegame()
{
	button_onlinegame = ui::Button::create();
	button_onlinegame->setTitleText(Words.getWord("1011"));
	button_onlinegame->setTitleFontSize(30);
	button_onlinegame->setTitleFontName("宋体");
	button_onlinegame->setTitleColor(Color3B(199,230, 232));
	button_onlinegame->setAnchorPoint(Vec2(0.5, 0));
	button_onlinegame->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50));
	button_onlinegame->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type) {
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->popScene();
			break;
		default:
			break;
		}
		});
	this->addChild(button_onlinegame, 1);
}
void loadgame::_set_button_back()
{
    button_back = ui::Button::create("back.png", "back.png", "back.png", ui::Widget::TextureResType::PLIST);
	button_back->setAnchorPoint(Vec2(0, 0));
	button_back->setPosition(Vec2(0, 0));
	button_back->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
			case ui::Widget::TouchEventType::ENDED:			
				Director::getInstance()->popScene();
				break;
			default:
				break;
		}
	});
	this->addChild(button_back, 1);
}
bool loadgame::init()
{
    if (!Scene::init())
        return false;
	
	_set_background();
	_set_button_back();
	Health_game_advice();
	_set_button_alonegame();
	_set_button_onlinegame();
	return true;
}

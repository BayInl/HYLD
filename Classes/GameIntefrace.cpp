#include"GameIntefrace.hpp"
#include"SettingScene.hpp"
#include "TestScene.h"
#include <cocos/editor-support/cocostudio/SimpleAudioEngine.cpp>
auto spritecache = SpriteFrameCache::getInstance();
//获得声音引擎对象
CocosDenshion::SimpleAudioEngine* audio = SimpleAudioEngine::getInstance();
cocos2d::Scene* GameIntefrace::createScene()
{
    return GameIntefrace::create();
}
void GameIntefrace::_set_background() {

    auto backgroundFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("background.png");
    auto _background = Sprite::createWithSpriteFrame(backgroundFrame);

    _background->setAnchorPoint(Vec2(1, 1));
    _background->setContentSize(visibleSize);
    _background->setPosition(Vec2(visibleSize.width, visibleSize.height));
    this->addChild(_background, -1);
}
void GameIntefrace::Health_game_advice()
{
    _label_adver_0 = Label::createWithSystemFont(
        Words.getWord("1002") + '\n' + Words.getWord("1003") + '\n' + Words.getWord("1004"), "宋体", 20);
    _label_adver_0->setAnchorPoint(Vec2(0.5, 0));
    _layer_initial_->addChild(_label_adver_0);
}
void GameIntefrace::_set_button_set() 
{
    
    button_set = ui::Button::create("cog.png", "cog.png", "cog.png");
    
    //this->addChild(button_set_music_effect);
    button_set->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:

            CCLOG("ui::Widget::TouchEventType::BEGAN");
            break;
        case ui::Widget::TouchEventType::ENDED:
            if (flag_setting.is_turnon) {
                button_set_music->setVisible(true);
                button_set->runAction(RotateTo::create(0.4f, -720));
                button_set_music->runAction(GameIntefrace::spawnIn(0.6f));
                //button_set_music_effect->runAction(GameIntefrace::spawnIn(0.65f));

                if (!_line) {//判断_line是否已经创建
                    //画一条线
                    _line = DrawNode::create();
                    _line->setLineWidth(5);
                    _line->drawLine(Vec2(0, 0), Vec2(visibleSize.width, visibleSize.height), Color4F(248, 248, 255, 1));
                    this->addChild(_line, 2);
                }
                else {
                    _line->setVisible(true);
                }
            }
            else {
                
                button_set->runAction(RotateTo::create(0.4f, 720));		
                button_set_music->runAction(GameIntefrace::spawnOut(Vec2(200, 400), 0.6f));
                //button_set_music_effect->runAction(GameIntefrace::spawnOut(Vec2(270, 370), 0.65f));
                _line->setVisible(false);
                button_set_music->setVisible(false);

            }
            //auto setscene =TestScene::createScene();
            //auto setscene = SettingScene::createScene();
            //Director::getInstance()->pushScene(TransitionFade::create(0.5, setscene));
            //Director::getInstance()->replaceScene(setscene);			

            flag_setting.is_turnon = !flag_setting.is_turnon;
            CCLOG("ui::Widget::TouchEventType::ENDED");
            break;
        case ui::Widget::TouchEventType::CANCELED:
            CCLOG("ui::Widget::TouchEventType::CANCELED");
            break;
        case ui::Widget::TouchEventType::MOVED:
            CCLOG("ui::Widget::TouchEventType::MOVED");
            break;
        default:
            break;
        }
        });
    button_set->setTitleText(Words.getWord("1005"));
    button_set->setAnchorPoint(Vec2(0.5, 0.5));
    button_set->setPosition(Vec2(visibleSize.width - button_set->getContentSize().width,
        visibleSize.height - button_set->getContentSize().height));
    button_set->setScale(1.5, 1.5);
    _layer_initial_->addChild(button_set);
}
void GameIntefrace::_set_button_music_background()
{
    CCLOG("1" );
    button_set_music = ui::Button::create(music_background.firstpath, music_background.secondpath, music_background.thirdpath);
	
    button_set_music->setPosition(Vec2(visibleSize.width/2 - button_set_music->getContentSize().width,
        visibleSize.height - button_set_music->getContentSize().height));
    button_set_music->setTitleText(setting.getWord("1001"));
    button_set_music->getTitleRenderer()->setAnchorPoint(Vec2(0, 0.5));
    button_set_music->setTitleFontSize(18);
    button_set_music->getTitleRenderer()->setPositionX(-button_set_music->getContentSize().width-14);
    button_set_music->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
			case ui::Widget::TouchEventType::BEGAN:				
			    CCLOG("ui::Widget::TouchEventType::BEGAN");
			    break;
			case ui::Widget::TouchEventType::ENDED:
                if (music_background.is_turnon) {//要turnoff
                    music_background.firstpath = "turnoff.png";
                    music_background.secondpath = "turnon.png";
                    //music_background.thirdpath = "turnon.png";
                    audio->stopBackgroundMusic();
                }
                else {//要turnon
                    music_background.firstpath = "turnon.png";
                    music_background.secondpath = "turnoff.png";
                    //music_background.thirdpath = "turnoff.png";
                    audio->playBackgroundMusic("Skylightz.mp3");
                }
                music_background.is_turnon = !music_background.is_turnon;
				button_set_music->loadTextures(music_background.firstpath, music_background.secondpath, music_background.thirdpath);
                music_background.is_turnon == 1 ? setting.setWord("Music", "1") : setting.setWord("Music", "0");
                setting.Store("");
				CCLOG("ui::Widget::TouchEventType::ENDED");
				break;
			case ui::Widget::TouchEventType::CANCELED:
				CCLOG("ui::Widget::TouchEventType::CANCELED");
				break;
			case ui::Widget::TouchEventType::MOVED:
				CCLOG("ui::Widget::TouchEventType::MOVED");
				break;
			default:
				break;				
        }
        });
	if(!_layer_initial_->getChildByName("button_set_music"))
        _layer_initial_->addChild(button_set_music);
}
bool GameIntefrace::init()
{
    if (!Scene::init())
    {
        return false;
    }
	//获取声音配置信息
    setting.changePath("Setting.xml");
    music_effect.is_turnon = setting.getWord("MusicEffect") == "1" ? 1 : 0;
    music_background.is_turnon = setting.getWord("Music") == "1" ? 1 : 0;

    if (music_background.is_turnon) {
        audio->playBackgroundMusic("Skylightz.mp3");
        music_background.firstpath = "turnon.png";
		music_background.secondpath = "turnoff.png";
        music_background.thirdpath= "turnoff.png";
    }
    else {
		audio->stopBackgroundMusic();
		music_background.firstpath = "turnoff.png";
		music_background.secondpath = "turnon.png";
		music_background.thirdpath = "turnon.png";
    }
    
	
    spritecache->addSpriteFramesWithFile("plist_setting.plist");
    //Director::getInstance()->getOpenGLView()->setDesignResolutionSize(1280, 720, ResolutionPolicy::SHOW_ALL);
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _layer_initial_ = Layer::create();
    this->addChild(_layer_initial_);
    auto _mouseListener = EventListenerMouse::create();
    Health_game_advice();
    _set_button_set();
    _set_button_music_background();
	
    
    
    auto button_loadgame = ui::Button::create();
    button_loadgame->loadTextures("play.png", "play.png", "play.png");
    button_loadgame->setAnchorPoint(Vec2(1, 0));
    button_loadgame->setPosition(Vec2(visibleSize.width, 0));
    _layer_initial_->addChild(button_loadgame);
	
	
    

    
	
    //渲染开始游戏菜单
    auto _menu_startgame = MenuItemImage::create("play1.png", "play1.png",
        [&](Ref* sender) {Director::getInstance()->end(); });
    _menu_startgame->setScale(0.5, 0.5);
    _menu_startgame->setAnchorPoint(Vec2(1, 0));
    auto menu = Menu::create(_menu_startgame, NULL);

    //设置menu位置
    menu->setAnchorPoint(Vec2(1, 0));
    menu->setPosition(Vec2(visibleSize.width, 0));
    menu->setVisible(false);
    //设置健康游戏忠告位置
    _label_adver_0->setPosition(Vec2(visibleSize.width / 2, menu->getPositionY() + _menu_startgame->getContentSize().height / 3));
    _layer_initial_->addChild(menu, -1);


    _set_background();//设置背景图片
    return true;


// a selector callback
//void menuCloseCallback(cocos2d::Ref* pSender);

// implement the "static create()" method manually

}

ActionInterval* GameIntefrace::spawnIn(float duration)
{
    ActionInterval* rotateTo = RotateTo::create(duration, -1080);
    auto move_ease_in = EaseBackIn::create(MoveTo::create(duration, Vec2(200, 200)));
    return Spawn::create(move_ease_in, rotateTo, nullptr);
}
ActionInterval* GameIntefrace::spawnOut(Vec2 point, float duration)
{
    //auto delay = DelayTime::create(1);
    ActionInterval* rotateTo = RotateTo::create(duration, 1080);
    auto move_ease_out = EaseBackOut::create(MoveTo::create(duration, point));
    return Spawn::create(move_ease_out, rotateTo, nullptr);
}
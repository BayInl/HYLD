#include"GameIntefrace.hpp"
//#include <cocos/editor-support/cocostudio/SimpleAudioEngine.cpp>
#include "editor-support/cocostudio/SimpleAudioEngine.h"
cocos2d::SpriteFrameCache* spritecache = SpriteFrameCache::getInstance();
//获得声音引擎对象
CocosDenshion::SimpleAudioEngine* audio = CocosDenshion::SimpleAudioEngine::getInstance();

void GameIntefrace::_set_button_back()
{
    button_back = ui::Button::create("back.png", "back.png", "back.png", ui::Widget::TextureResType::PLIST);
    button_back->setAnchorPoint(Vec2(1, 1));
    button_back->setPosition(Vec2(visibleSize.width, visibleSize.height));
    _layer_infor_->addChild(button_back);
    button_back->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::ENDED:
            if (text_name->getString() != "") {
                Words.setWord("Username", text_name->getString());
                Words.Store();
            }
            _layer_initial_->setVisible(true);
            _layer_infor_->removeFromParent();
            break;
        default:
            break;
        }
        });
}
void GameIntefrace::Username_description()
{
    //设置提示文字
    _label_Username_description = Label::createWithSystemFont(Words.getWord("1007"), "楷体", 30);
    _label_Username_description->setAnchorPoint(Vec2(0, 0));
    _label_Username_description->setPosition(Vec2(visibleSize.width / 2 - 220, visibleSize.height / 4 * 3));
    _label_Username_description->setTextColor(Color4B::BLACK);
    _layer_infor_->addChild(_label_Username_description);
}
void GameIntefrace::Numberofwins()
{
    _label_Numberofwins = Label::createWithSystemFont(Words.getWord("1009") + Words.getWord(Words.getWord("1009")), "楷体", 30);
    _label_Numberofwins->setAnchorPoint(Vec2(0, 0));
    _label_Numberofwins->setPosition(Vec2(visibleSize.width / 2 - 220, visibleSize.height / 6 * 4 - 70));
    _label_Numberofwins->setTextColor(Color4B::BLACK);
    _layer_infor_->addChild(_label_Numberofwins);
}
void GameIntefrace::Numberoftrophies()
{
    _label_Numberoftrophies = Label::createWithSystemFont(Words.getWord("1008") + Words.getWord(Words.getWord("1008")), "楷体", 30);
    _label_Numberoftrophies->setAnchorPoint(Vec2(0, 0));
    _label_Numberoftrophies->setPosition(Vec2(visibleSize.width / 2 - 220, visibleSize.height / 6 * 4));
    _label_Numberoftrophies->setTextColor(Color4B::BLACK);
    _layer_infor_->addChild(_label_Numberoftrophies);
}
void GameIntefrace::_set_text_name()
{
    text_name = ui::TextField::create(Words.getWord("Username"), "楷体", 30);
    text_name->setAnchorPoint(Vec2(0, 0));
    text_name->setPosition(Vec2(visibleSize.width / 2 + 120, visibleSize.height / 4 * 3));
    text_name->setMaxLengthEnabled(true);
    text_name->setMaxLength(10);
    text_name->setColor(Color3B::BLACK);
    text_name->setPlaceHolderColor(Color3B::BLACK);
    text_name->setPlaceHolder(Words.getWord("Username"));
    text_name->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            text_name->setPlaceHolder("");
            break;
        default:
            break;
        }
        });
    _layer_infor_->addChild(text_name);
}
//上面这些是用于个人信息层的信息显示

cocos2d::Scene* GameIntefrace::createScene()
{
    return GameIntefrace::create();
}
void GameIntefrace::_set_background(Node* node,const std::string &path) {
    auto backgroundFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(path);
    auto _background = Sprite::createWithSpriteFrame(backgroundFrame);

    _background->setAnchorPoint(Vec2(1, 1));
    _background->setContentSize(visibleSize);
    _background->setPosition(Vec2(visibleSize.width, visibleSize.height));
    node->addChild(_background, -1);
}
void GameIntefrace::Health_game_advice()
{
    _label_adver_0 = Label::createWithSystemFont(
        Words.getWord("1002") + '\n' + Words.getWord("1003") + '\n' + Words.getWord("1004"), "宋体", 20);
    _label_adver_0->setAnchorPoint(Vec2(0.5, 0));
    _layer_initial_->addChild(_label_adver_0);
    _label_adver_0->setPosition(Vec2(visibleSize.width / 2,50));
}
void GameIntefrace::_set_button_set() 
{
    button_set = ui::Button::create("cog.png", "cog.png", "cog.png", ui::Widget::TextureResType::PLIST);
    button_set->setTitleText(Words.getWord("1005"));
    button_set->setPosition(Vec2(visibleSize.width - button_set->getContentSize().width,
        visibleSize.height - button_set->getContentSize().height));
    button_set->setScale(1.5, 1.5);
    _layer_initial_->addChild(button_set);
    button_set->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            break;
        case ui::Widget::TouchEventType::ENDED:
            if (flag_setting.is_turnon) {        
                button_set_music->setVisible(true);
                button_set_music_effect->setVisible(true);
                label_volume_description->setVisible(true);
                slider_set_volume->setVisible(true);
				
                button_set->runAction(RotateTo::create(0.4f, -720));
				
                button_set_music->setOpacity(0);
                button_set_music->runAction(FadeIn::create(0.5f));
                button_set_music->runAction(GameIntefrace::spawnIn(Vec2(visibleSize.width-200,
                    700), 0.5f));
				
                button_set_music_effect->setOpacity(0);
                button_set_music_effect->runAction(FadeIn::create(0.6f));           			
                button_set_music_effect->runAction(GameIntefrace::spawnIn(Vec2(visibleSize.width - 200,
                    660), 0.6f));
				
                label_volume_description->setOpacity(0);
				label_volume_description->runAction(FadeIn::create(0.7f));
                label_volume_description->runAction(GameIntefrace::spawnIn(Vec2(visibleSize.width - 270,
                    520), 0.7f));
				
                slider_set_volume->setOpacity(0);
				slider_set_volume->runAction(FadeIn::create(0.65f));
				
                if (!_line_0) {//判断_line是否已经创建
                    //画一条线
                    _line_0 = DrawNode::create();			
                    _line_0->setLineWidth(5);
                    _line_0->drawLine(Vec2(visibleSize.width - 340, 390),
                        Vec2(visibleSize.width - 340, visibleSize.height-20),
                                    Color4F(248, 248, 255, 1));
                    _line_0->drawLine(Vec2(visibleSize.width - 340, 390),
                        Vec2(visibleSize.width-150, 390),
                        Color4F(248, 248, 255, 1));	
                    _line_0->drawLine(Vec2(visibleSize.width - 340, visibleSize.height - 20),
                        Vec2(visibleSize.width - 150, visibleSize.height - 20),
                        Color4F(248, 248, 255, 1));	
                    _layer_initial_->addChild(_line_0, 2);
                }
                _line_0->setOpacity(0);
                _line_0->runAction(FadeIn::create(0.5f));
            }
            else {
                button_set->runAction(RotateTo::create(0.4f, 720));				
				
                button_set_music->setOpacity(255);
                button_set_music->runAction(FadeOut::create(0.6f));
                button_set_music->runAction(GameIntefrace::spawnOut(button_set->getPosition(), 0.55f));
				
                button_set_music_effect->setOpacity(255);
                button_set_music_effect->runAction(FadeOut::create(0.5f));         
                button_set_music_effect->runAction(GameIntefrace::spawnOut(button_set->getPosition(),0.6f));
				
                _line_0->setOpacity(255);
                _line_0->runAction(FadeOut::create(0.5f));

				
                label_volume_description->setOpacity(255);
                label_volume_description->runAction(FadeOut::create(0.7f));
                label_volume_description->runAction(GameIntefrace::spawnOut(button_set->getPosition(), 0.7f));
				
                slider_set_volume->setOpacity(255);
                slider_set_volume->runAction(FadeOut::create(0.65f));

            }
            {
                //设置延时防止动画冲突
                //auto fordelay = DelayTime::create(0.6f);
                //auto forcall = CallFunc::create([&]() {});
                //this->runAction(Sequence::create(fordelay, forcall, nullptr));
            }
            flag_setting.is_turnon = !flag_setting.is_turnon;
            break;
        case ui::Widget::TouchEventType::CANCELED:
            break;
        case ui::Widget::TouchEventType::MOVED:
            break;
        default:
            break;
        }
        });
}
void GameIntefrace::_set_button_music_background()
{
    button_set_music = ui::Button::create(music_background.firstpath, music_background.secondpath, music_background.thirdpath, ui::Widget::TextureResType::PLIST);
    
    button_set_music->setTitleText(setting.getWord("1001"));
    button_set_music->setTitleFontName("楷体");//此处可能会造成 cocos2d: fullPathForFilename: No file found at ****. Possible missing file.
    button_set_music->setTitleFontSize(22);
    button_set_music->setTitleColor(Color3B::BLACK);
    button_set_music->getTitleRenderer()->setAnchorPoint(Vec2(0, 0.5));
    button_set_music->getTitleRenderer()->setPositionX(-button_set_music->getContentSize().width-30);
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
                    music_background.thirdpath = "turnon.png";
                    audio->stopBackgroundMusic();
                }
                else {//要turnon
                    music_background.firstpath = "turnon.png";
                    music_background.secondpath = "turnoff.png";
                    music_background.thirdpath = "turnoff.png";
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
    button_set_music->setVisible(false);
    button_set_music->setPosition(Vec2(visibleSize.width - button_set_music->getContentSize().width,
        visibleSize.height - button_set_music->getContentSize().height));
}
void GameIntefrace::_set_button_music_effect()
{
    button_set_music_effect = ui::Button::create(music_effect.firstpath, music_effect.secondpath, music_effect.thirdpath, ui::Widget::TextureResType::PLIST);
    button_set_music_effect->setTitleText(setting.getWord("1002"));
    button_set_music_effect->setTitleFontName("楷体");
    button_set_music_effect->setTitleFontSize(22);
    button_set_music_effect->setTitleColor(Color3B::BLACK);
    button_set_music_effect->getTitleRenderer()->setAnchorPoint(Vec2(0, 0.5));
    button_set_music_effect->getTitleRenderer()->setPositionX(-button_set_music_effect->getContentSize().width - 30);
	
    button_set_music_effect->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::BEGAN:
            CCLOG("ui::Widget::TouchEventType::BEGAN");
            break;
        case ui::Widget::TouchEventType::ENDED:
            if (music_effect.is_turnon) {//要turnoff
                music_effect.firstpath = "turnoff.png";
                music_effect.secondpath = "turnon.png";
            }
            else {//要turnon
                music_effect.firstpath = "turnon.png";
                music_effect.secondpath = "turnoff.png";
            }
            music_effect.is_turnon = !music_effect.is_turnon;
            button_set_music_effect->loadTextures(music_effect.firstpath, music_effect.secondpath, music_effect.thirdpath);
            music_effect.is_turnon == 1 ? setting.setWord("MusicEffect", "1") : setting.setWord("MusicEffect", "0");
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
    if (!_layer_initial_->getChildByName("button_set_music_effect"))
        _layer_initial_->addChild(button_set_music_effect);
    button_set_music_effect->setVisible(false);
    button_set_music_effect->setPosition(Vec2(visibleSize.width - button_set_music_effect->getContentSize().width,
        visibleSize.height - button_set_music_effect->getContentSize().height));
}
void GameIntefrace::_set_button_music_effect_volume()
{
    label_volume_description=Label::createWithSystemFont(setting.getWord("1003"),"楷体",22);
    label_volume_description->setColor(Color3B::BLACK);
    label_volume_description->setVisible(false);
	
    if (!_layer_initial_->getChildByName("label_volume_description"))
        _layer_initial_->addChild(label_volume_description);
	
    slider_set_volume = ui::Slider::create();
    slider_set_volume->loadBarTexture("Slider_Back.png", ui::Widget::TextureResType::PLIST);
    slider_set_volume->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png", ui::Widget::TextureResType::PLIST);
    slider_set_volume->loadProgressBarTexture("Slider_PressBar.png", ui::Widget::TextureResType::PLIST);
	slider_set_volume->setPercent(volume);
    slider_set_volume->setVisible(false);
	
	slider_set_volume->addEventListener([&](Ref* sender, ui::Slider::EventType type) {
		switch (type)
		{
		case ui::Slider::EventType::ON_PERCENTAGE_CHANGED:
			//改变音量
            volume = slider_set_volume->getPercent();
            audio->setBackgroundMusicVolume(volume /100.0f);
            audio->setEffectsVolume(volume / 100.0f);
			CCLOG("%d", audio->getBackgroundMusicVolume());
            setting.setWord("MusicVolume",std::to_string(volume));
            setting.Store("");
			break;
		default:
			break;
		}
		});
    if (!label_volume_description->getChildByName("slider_set_volume"))
        label_volume_description->addChild(slider_set_volume);
	
	slider_set_volume->setVisible(false);
    slider_set_volume->setRotation(270);
    slider_set_volume->setPositionX(label_volume_description->getContentSize().width+12);
    label_volume_description->setPosition(Vec2(visibleSize.width - button_set_music_effect->getContentSize().width,
        visibleSize.height - button_set_music_effect->getContentSize().height));
}
void GameIntefrace::playgame()
{
    button_playgame = ui::Button::create("forward.png", "forward.png", "forward.png", ui::Widget::TextureResType::PLIST);
    button_playgame->setAnchorPoint(Vec2(1, 0));
    button_playgame->setPosition(Vec2(visibleSize.width, 0));
    button_playgame->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::ENDED:
            scene_loadgame = loadgame::createScene();
			transition = TransitionFade::create(0.5f, scene_loadgame);//创建动画
            Director::getInstance()->pushScene(transition);
            break;
        default:
            break;
        }
        });
    if (!_layer_initial_->getChildByName("button_playgame"))
        _layer_initial_->addChild(button_playgame);
}
void GameIntefrace::_set_button_infor()
{
    button_infor = ui::Button::create("Information.png", "Information.png", "Information.png", ui::Widget::TextureResType::PLIST);
    button_infor->setAnchorPoint(Vec2(0, 0));
    button_infor->setPosition(Vec2(0, visibleSize.height/4*3));
    button_infor->setTitleText(Words.getWord("1006"));
    button_infor->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Widget::TouchEventType::ENDED:
            _layer_infor_ = Layer::create();
            this->addChild(_layer_infor_, 1);
            _layer_initial_->setVisible(false);
            _set_background(_layer_infor_,"backgroundblur.png");//设置背景
            _set_button_back();
            _set_text_name();//设置文本框
            Username_description();//设置昵称文字描述
            Numberoftrophies();//设置奖杯总数
            Numberofwins();//设置总吃鸡数
            break;
        default:
            break;
        }
        });
        _layer_initial_->addChild(button_infor);
}
bool GameIntefrace::init()
{
    if (!Scene::init())
    {
        return false;
    }
	//获取声音配置信息
    spritecache->addSpriteFramesWithFile("Menus/plist_setting.plist","Menus/plist_setting.png");
	
    setting.changePath("Setting.xml");
    music_effect.is_turnon = setting.getWord("MusicEffect") == "1" ? 1 : 0;
    music_background.is_turnon = setting.getWord("Music") == "1" ? 1 : 0;
    volume = atoi(setting.getWord("MusicVolume").c_str());
	
    if (music_background.is_turnon) {
        audio->playBackgroundMusic("Sounds/Skylightz.mp3");
        audio->setBackgroundMusicVolume(volume / 100.0f);
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
    if (music_effect.is_turnon) {
		music_effect.firstpath = "turnon.png";
		music_effect.secondpath = "turnoff.png";
		music_effect.thirdpath = "turnoff.png";
    }
    else {
		music_effect.firstpath = "turnoff.png";
		music_effect.secondpath = "turnon.png";
		music_effect.thirdpath = "turnon.png";
    }
    
    //Director::getInstance()->getOpenGLView()->setDesignResolutionSize(1280, 720, ResolutionPolicy::SHOW_ALL);
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _layer_initial_ = Layer::create();
    this->addChild(_layer_initial_);
    
    _set_background(this, "background.png");//设置背景图片
    
    _set_button_music_background();//设置背景音乐
    
    _set_button_music_effect();//设置音效
    
    _set_button_music_effect_volume();//设置音量
    
    _set_button_set();//放置设置按钮
    Health_game_advice();//游戏健康忠告
    playgame();  //放置开始游戏按钮
    _set_button_infor();//放置个人信息按钮
    return true;
}
//下面这两个是动画
ActionInterval* GameIntefrace::spawnIn(Vec2 point, float duration)
{
    ActionInterval* rotateTo = RotateTo::create(duration, -1080);
    auto move_ease_in = EaseBackIn::create(MoveTo::create(duration, point));
    return Spawn::create(move_ease_in, rotateTo,  nullptr);
}
ActionInterval* GameIntefrace::spawnOut(Vec2 point, float duration)
{
    ActionInterval* rotateTo = RotateTo::create(duration, 1080);
    auto move_ease_out = EaseBackOut::create(MoveTo::create(duration, point));
    return Spawn::create(move_ease_out, rotateTo, nullptr);
}
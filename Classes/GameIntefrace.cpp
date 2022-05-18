#include"GameIntefrace.hpp"
#include"SettingScene.hpp"
cocos2d::Scene* GameIntefrace::createScene()
{
    return GameIntefrace::create();
}
void GameIntefrace::_set_background() {
    auto _background = Sprite::create("background.png");
    _background->setAnchorPoint(Vec2(1, 1));
    _background->setContentSize(visibleSize);
    _background->setPosition(Vec2(visibleSize.width, visibleSize.height));
    this->addChild(_background, -1);
}

bool GameIntefrace::init()
{
    if (!Scene::init())
    {
        return false;
    }
    //Director::getInstance()->getOpenGLView()->setDesignResolutionSize(1280, 720, ResolutionPolicy::SHOW_ALL);

    Director::getInstance()->setGLDefaultValues();
    //this->setColor(Color3B(248,248,255));
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto _layer_initial_ = Layer::create();
    this->addChild(_layer_initial_);
    auto _mouseListener = EventListenerMouse::create();

    //渲染设置菜单
    auto _menu_seeting = MenuItemImage::create("cog1.png", "cog1.png",
        [&](Ref* sender) {
            auto setscene = SettingScene::createScene();
            Director::getInstance()->pushScene(TransitionFade::create(0.5, setscene));
            //Director::getInstance()->replaceScene(setscene);

        });

    //Lambda表达式实现
    auto _setting_scale_x = 0.1;
    auto _setting_scale_y = 0.1;
    _menu_seeting->setScale(_setting_scale_x, _setting_scale_y);
    auto _menu_seeting_menu = Menu::create(_menu_seeting, NULL);
    _menu_seeting_menu->setAnchorPoint(Vec2(1, 1));
    _menu_seeting_menu->setPosition(Vec2(visibleSize.width -
        _menu_seeting->getContentSize().width * _setting_scale_x / 2,
        visibleSize.height - _menu_seeting->getContentSize().height * _setting_scale_y / 2));

    _layer_initial_->addChild(_menu_seeting_menu);

    //健康游戏忠告
    auto _label_adver_0 = Label::createWithSystemFont(
        Words.getWord("1002")+ '\n'+ Words.getWord("1003") + '\n'+ Words.getWord("1004"), "宋体", 20);
    _label_adver_0->setAnchorPoint(Vec2(0.5, 0));
    _layer_initial_->addChild(_label_adver_0);

    //渲染开始游戏菜单
    auto _menu_startgame = MenuItemImage::create("play1.png", "play1.png",
        [&](Ref* sender) {Director::getInstance()->end(); });
    _menu_startgame->setScale(0.5, 0.5);
    _menu_startgame->setAnchorPoint(Vec2(1, 0));
    auto menu = Menu::create(_menu_startgame, NULL);

    //设置menu位置
    menu->setAnchorPoint(Vec2(1, 0));
    menu->setPosition(Vec2(visibleSize.width, 0));

    //设置健康游戏忠告位置
    _label_adver_0->setPosition(Vec2(visibleSize.width / 2, menu->getPositionY() + _menu_startgame->getContentSize().height / 3));
    _layer_initial_->addChild(menu, -1);


    _set_background();//设置背景图片
    return true;


// a selector callback
//void menuCloseCallback(cocos2d::Ref* pSender);

// implement the "static create()" method manually

}
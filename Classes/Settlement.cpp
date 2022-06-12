#include "Settlement.h"
#include <Windows.h>
#include "editor-support/cocostudio/SimpleAudioEngine.h"
USING_NS_CC;

#define FONT_SIZE 38//字体大小
extern CocosDenshion::SimpleAudioEngine* audio;

Scene* Settlement::createScene()
{
    return Settlement::create();
}

// on "init" you need to initialize your instance
bool Settlement::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }
    //置随机数种子
    srand((unsigned)time(NULL));

    AudioEngine::preload("Sounds/Victory.mp3");
    AudioEngine::preload("Sounds/Defeat.mp3");
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
        "Settlement/Click.png",
        "Settlement/Click.png",
        CC_CALLBACK_1(Settlement::menuCloseCallback, this));

    closeItem->setPosition(Vec2(visibleSize / 2) + origin);

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 10);

    Label* ranking[3] = { 0 }; 
    int num[3] = { -1,-2,-3 };
    if (player_ranking_ <= 3) {
        num[player_ranking_ - 1] = 0;//这是玩家的
        ranking[player_ranking_ - 1] = Label::createWithTTF(user_name_, "fonts/arial.ttf", FONT_SIZE);
    }
    for (auto i = 0; i < 3 && i <= number_npc_; i++) {
        if (num[i]) {
            char npc_name[7] = "NPC-00";
            num[i] = rand() % number_npc_ + 1;
            while (num[0] == num[1] || num[0] == num[2] || num[1] == num[2])
                num[i] = rand() % number_npc_ + 1;
            npc_name[4] = num[i] / 10 + '0';
            npc_name[5] = num[i] % 10 + '0';
            ranking[i] = Label::createWithTTF(npc_name, "fonts/arial.ttf", FONT_SIZE);
        }
        ranking[i]->setColor(Color3B::BLACK);
        ranking[i]->setAnchorPoint(Vec2(0, 0.5));
        ranking[i]->setPosition(origin.x + 319,
                                origin.y + 425 - 67 * i);
        this->addChild(ranking[i], 1);
    }

    if (switch_music_)
    {
        if (player_ranking_ == 1)
            audio->playBackgroundMusic("Sounds/Victory.mp3");
        else
            audio->playBackgroundMusic("Sounds/Defeat.mp3");
        audio->setBackgroundMusicVolume(volume_ / 100.0f);
    }

    Sprite* sprite = Sprite::create("Settlement/Defeat.jpg");
    if (player_ranking_ == 1) {
        sprite = Sprite::create("Settlement/Victory.jpg");
    }
    //AudioEngine::resume(AudioID);
    sprite->setPosition(Vec2(visibleSize / 2) + origin);
    this->addChild(sprite, -1);

    //给玩家加官进爵
    if (1 == player_ranking_) {
        trophy_ += 5;
        number_win_ += 1;
    } else if (2 == player_ranking_) {
        trophy_ += 3;
    } else if (2 == player_ranking_) {
        trophy_ += 2;
    }

    return true;
}

void Settlement::menuCloseCallback(Ref* sender)
{
    //cocos2d::AudioEngine::stopAll();
    audio->stopBackgroundMusic();
    Director::getInstance()->popScene();
    Director::getInstance()->popScene();
    auto startMenuScene = GameIntefrace::create();
    Director::getInstance()->replaceScene(cocos2d::TransitionSlideInT::create(0.2f, startMenuScene->createScene()));
    //Director::getInstance()->end();
}
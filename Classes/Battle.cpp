#include "Battle.h"
#include <windows.h>
#include "editor-support/cocostudio/SimpleAudioEngine.h"
USING_NS_CC;
using namespace cocos2d;
extern CocosDenshion::SimpleAudioEngine* audio;
inline long long int gettime()
{
    SYSTEMTIME sys;
    GetLocalTime(&sys);
    //��������ʱ����ת��Ϊ����ʱ���
    return static_cast<long long int>(sys.wMilliseconds) + static_cast<long long int>(sys.wSecond) * 1000
        + static_cast<long long int>(sys.wMinute) * 60 * 1000 +
        static_cast<long long int>(sys.wHour) * 60 * 60 * 1000 +
        static_cast<long long int>(sys.wDay) * 24 * 60 * 60 * 1000 +
        static_cast<long long int>(sys.wMonth) * 30 * 24 * 60 * 60 * 1000 +
        static_cast<long long int>(sys.wYear) * 365 * 30 * 24 * 60 * 60 * 1000;
}

Scene* Battle::createScene()
{
    return Battle::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool Battle::init()
{
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    //�����������
    srand((unsigned)time(NULL));

    this->scheduleUpdate();//����update����

    //Ԥ����
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    // 2. add a menu item with "X" image, which is clicked to quit the program
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(Battle::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    } else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    auto pauseItem = MenuItemImage::create(
        "PauseNormal.png",
        "PauseSelected.png",
        CC_CALLBACK_1(Battle::menuPauseCallback, this));

    if (pauseItem == nullptr ||
        pauseItem->getContentSize().width <= 0 ||
        pauseItem->getContentSize().height <= 0)
    {
        problemLoading("'PauseNormal.png' and 'PauseSelected.png'");
    } else
    {
        float x = origin.x + visibleSize.width - pauseItem->getContentSize().width / 2;
        float y = origin.y + pauseItem->getContentSize().height / 2;
        pauseItem->setPosition(Vec2(x - 100, y));
    }

    // �����˵�
    auto menu = Menu::create(closeItem, pauseItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    // 3. add your codes below...

    //����һЩ���ӵ�ʵ��
    initBox();

    //���ӵ�ͼ�Ͱ�ȫ�� 
    TMXTiledMap* map0 = TMXTiledMap::create("Map/MyMap0.tmx");
    TMXTiledMap* map1 = TMXTiledMap::create("Map/MyMap1.tmx");
    TMXTiledMap* map2 = TMXTiledMap::create("Map/MyMap2.tmx");
    TMXTiledMap* map3 = TMXTiledMap::create("Map/MyMap3.tmx");
    TMXTiledMap* map4 = TMXTiledMap::create("Map/MyMap4.tmx");
    switch (rand() % 5) {
    case 0:
        map = map0;
        break;
    case 1:
        map = map1;
        break;
    case 2:
        map = map2;
        break;
    case 3:
        map = map3;
        break;
    case 4:
        map = map4;
        break;
    default:
        log("MapError!");
    }
    map->setPosition(Vec2(origin.x + visibleSize.width / 2 + MAP_INIT_X,
                          origin.y + visibleSize.height / 2 + MAP_INIT_Y));
    addChild(map, -10, 99); // with a tag of '99'    
    safetyZone->setPosition(Vec2((map->getMapSize().width + 2) * map->getTileSize().width / 2 + MAP_INIT_X / 2,
                                 (map->getMapSize().height + 1) * map->getTileSize().height / 2 + MAP_INIT_Y / 2));
    safetyZone->setOpacity(100);
    addChild(safetyZone, 99);
    poisonousSmoke->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                     origin.y + visibleSize.height / 2));
    poisonousSmoke->setOpacity(100);
    addChild(poisonousSmoke, 98);
    returnToSafetyZone->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                         origin.y + visibleSize.height / 2));
    returnToSafetyZone->setVisible(false);
    addChild(returnToSafetyZone, 100);

    //����һ����ɫ��ʵ��
    if (heroflag == 1)
        hero_player = Knight::create();
    else if (heroflag == 2)
        hero_player = Scientist::create();
    else if (heroflag == 3)
        hero_player = Wizard::create();
    else
        hero_player = Berserker::create();
    this->addChild(hero_player);
    weapon_player = hero_player->bindWeapon();
    hero_player->setAnchorPoint(Vec2(0.5, 0.5));
    hero_player->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
    if (checkCollision(hero_player->getPosition(), Middle) == Grass) {
        hero_player->setOpacity(100);
        weapon_player->setOpacity(100);
    } else {
        hero_player->setOpacity();
        weapon_player->setOpacity();
    }
    hero_player->Animater();//����������
    //������ʿ�Ĵ�������
    if (hero_player->WhatIam() == 1)
    {
        this->addChild(sword_bonus);
        sword_bonus->setPosition(hero_player->getPosition() + Vec2(100, 50));
        sword_bonus->setVisible(false);
    }
    //��������
    this->addChild(weapon_player);
    weapon_player->setPosition(hero_player->getPosition() + Vec2(70, 30));
    if (hero_player->WhatIam() == 4)
        weapon_player->setPosition(hero_player->getPosition() + Vec2(50, -10));
    // �����¼��ļ�����
    auto mouseListener = EventListenerTouchOneByOne::create();
    // �ص�����onTouchBegan():��ָ��һ��������Ļʱ������
    mouseListener->onTouchBegan = CC_CALLBACK_2(Battle::onTouchBegan, this);
    // ʹ��EventDispatcher�����������������¼�
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, weapon_player);
    // �����¼�����
    auto keyListener = EventListenerKeyboard::create();
    keyListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        log("press");
        key_map[keyCode] = true;
    };
    keyListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
        log("release");
        key_map[keyCode] = false;
    };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

    //����NPC
    initNPC();

    //�����Լ��ļ�ʱ��
   //ccSchedulerFunc
    this->schedule(CC_SCHEDULE_SELECTOR(Battle::npc_update), 0.5f);
    this->schedule(CC_SCHEDULE_SELECTOR(Battle::safetyZone_update), 1.0f);

    //���ñ�������
    //auto backgroundAudioID = AudioEngine::play2d("Sounds/goldenslaughterer.mp3", true,0.2f);
    //AudioEngine::resume(backgroundAudioID);
    if (switch_music_)
    {
        audio->playBackgroundMusic("Sounds/goldenslaughterer.mp3", true);
        audio->setBackgroundMusicVolume(volume_ / 100.0f);
    }

    return true;
}

void Battle::initNPC()
{
    //��ʼ��NPC
    for (int i = 0; i < number_npc_; i++) {

        //ȡ�����
        int random = rand() % 4 + 1;
        //����NPC
        if (random == 1)
            hero_npc[i] = Knight::create();
        else if (random == 2)
            hero_npc[i] = Scientist::create();
        else if (random == 3)
            hero_npc[i] = Wizard::create();
        else if (random == 4)
            hero_npc[i] = Berserker::create();
        hero_npc[i]->setAnchorPoint(Vec2(0.5, 0.5));
        //����NPC��λ��
        while (1) {
            int x = (rand() % (int)((map->getMapSize().width - 25) * map->getTileSize().width)) +
                (8 * map->getTileSize().width);
            int y = (rand() % (int)((map->getMapSize().height - 21) * map->getTileSize().height)) +
                (6 * map->getTileSize().width);
            if (checkCollision(Point(x, y), Left) == Wall ||
                checkCollision(Point(x, y), Right) == Wall ||
                checkCollision(Point(x, y), Up) == Wall ||
                checkCollision(Point(x, y), Down) == Wall) {
                continue;
            }
            hero_npc[i]->setPosition(Vec2(x, y));
            break;
        }
        this->addChild(hero_npc[i]);
        hero_npc[i]->Animater();
        if (hero_npc[i]->WhatIam() == 1)
        {
            sword_bonus_npc[i] = SwordBonus::create();
            this->addChild(sword_bonus_npc[i]);
            sword_bonus_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(100, 50));
            sword_bonus_npc[i]->setVisible(false);
        }
        weapon_npc[i] = hero_npc[i]->bindWeapon();
        this->addChild(weapon_npc[i]);
        if (hero_npc[i]->WhatIam() == 4)
            weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(50, -10));
        else
            weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(70, 30));
    }
}

void Battle::npc_move()
{
    for (int i = 0; i < number_npc_; i++) {
        //����NPC�ڲݴ��е�͸���ȣ����Ƴ������ڲݴ����Կɱ���ɱ��
        if (checkCollision(hero_npc[i]->getPosition(), Middle) == Grass) {
            if (checkCollision(hero_player->getPosition(), Middle) == Grass) {
                hero_npc[i]->setOpacity(120);
                weapon_npc[i]->setOpacity(120);
            } else {
                hero_npc[i]->setOpacity(0);
                weapon_npc[i]->setOpacity(0);
            }
        } else {
            hero_npc[i]->setOpacity();
            weapon_npc[i]->setOpacity();
        }

        if (hero_npc[i]->getHealth() < 1) {
            hero_npc[i]->setVisible(false);
            //��Ӧ��������Ϊ���ɼ�������ֱ���Ƴ�
            continue;
        }
        //����NPC��λ��
        //����Ӧ��һ���߼�������Һ�npc����Ͻ�ʱ��Ӧ����Ӧ�ı仯
        int randm = rand() % 4 + 1;
        if (randm == 1) {
            hero_npc[i]->setDirectLeft();
            weapon_npc[i]->setDirectLeft();
            if (checkCollision(hero_npc[i]->getPosition() + Vec2(-20, 0), Left) == Wall) {
                i--;
                continue;
            }
            hero_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(-20, 0));
            weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(-70, 30));
            if (hero_npc[i]->WhatIam() == 4)
                weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(-50, -10));
            continue;
        }
        if (randm == 2) {
            hero_npc[i]->setDirectRight();
            weapon_npc[i]->setDirectRight();
            if (checkCollision(hero_npc[i]->getPosition() + Vec2(20, 0), Right) == Wall) {
                i--;
                continue;
            }
            hero_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(20, 0));
            weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(70, 30));
            if (hero_npc[i]->WhatIam() == 4)
                weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(50, -10));
            continue;
        }
        if (randm == 3) {
            if (checkCollision(hero_npc[i]->getPosition() + Vec2(0, 20), Up) == Wall) {
                i--;
                continue;
            }
            hero_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(0, 20));
            weapon_npc[i]->setPosition(weapon_npc[i]->getPosition() + Vec2(0, 20));
            continue;
        }
        if (randm == 4) {
            if (checkCollision(hero_npc[i]->getPosition() + Vec2(0, -20), Down) == Wall) {
                i--;
                continue;
            }
            hero_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(0, -20));
            weapon_npc[i]->setPosition(weapon_npc[i]->getPosition() + Vec2(0, -20));
            continue;
        }
    }
}

//���ֶԷ�
void Battle::npc_move600()
{
    for (int i = 0; i < number_npc_; i++) {
        float minimumDistance = calculate_modulus(hero_npc[i]->getPosition(), hero_player->getPosition());
        if (checkCollision(hero_player->getPosition(), Middle) == Grass)
            minimumDistance = 1000;
        Vec2 minimumVec = calculate_vec(hero_npc[i]->getPosition(), hero_player->getPosition());
        for (int j = 0; j < number_npc_; j++) {
            if (checkCollision(hero_npc[j]->getPosition(), Middle) != Grass && j != i)//�����Լ�����룬���ڲ��￴����
                if (calculate_modulus(hero_npc[i]->getPosition(), hero_npc[j]->getPosition()) < minimumDistance) {
                    minimumDistance = calculate_modulus(hero_npc[i]->getPosition(), hero_npc[j]->getPosition());
                    minimumVec = calculate_vec(hero_npc[i]->getPosition(), hero_npc[j]->getPosition());
                }
        }//�õ���С����
        Vec2 moveVec = Vec2::ZERO;
        if (minimumDistance < 600) {//ͼ��512
            int healthLower25 = (hero_npc[i]->getHealth() <= 25);
            if (!healthLower25)
                healthLower25 = -1;
            if (hero_npc[i]->getHealth() <= 25) {//Զ��
                if (minimumVec.x > 0) {
                    hero_npc[i]->setDirectLeft();
                    weapon_npc[i]->setDirectLeft();
                    if (checkCollision(hero_npc[i]->getPosition() + Vec2(-60, 0), Left) != Wall &&
                        checkCollision(hero_npc[i]->getPosition() + Vec2(-40, 0), Left) != Wall &&
                        checkCollision(hero_npc[i]->getPosition() + Vec2(-20, 0), Left) != Wall) {
                        moveVec.x -= 60;
                    }
                    weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(-70, 30));
                    if (hero_npc[i]->WhatIam() == 4)
                        weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(-50, -10));
                }
                if (minimumVec.x < 0) {
                    hero_npc[i]->setDirectRight();
                    weapon_npc[i]->setDirectRight();
                    if (checkCollision(hero_npc[i]->getPosition() + Vec2(60, 0), Right) != Wall &&
                        checkCollision(hero_npc[i]->getPosition() + Vec2(40, 0), Right) != Wall &&
                        checkCollision(hero_npc[i]->getPosition() + Vec2(20, 0), Right) != Wall) {
                        moveVec.x += 60;
                    }
                    weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(70, 30));
                    if (hero_npc[i]->WhatIam() == 4)
                        weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(50, -10));
                }
                if (minimumVec.y < 0) {
                    if (checkCollision(hero_npc[i]->getPosition() + Vec2(0, 60), Up) != Wall &&
                        checkCollision(hero_npc[i]->getPosition() + Vec2(0, 40), Up) != Wall &&
                        checkCollision(hero_npc[i]->getPosition() + Vec2(0, 20), Up) != Wall) {
                        moveVec.y += 60;
                    }
                }
                if (minimumVec.y > 0) {
                    if (checkCollision(hero_npc[i]->getPosition() + Vec2(0, -60), Down) != Wall &&
                        checkCollision(hero_npc[i]->getPosition() + Vec2(0, -40), Down) != Wall &&
                        checkCollision(hero_npc[i]->getPosition() + Vec2(0, -20), Down) != Wall) {
                        moveVec.y -= 60;
                    }
                }
            } else {//health > 25
                if (hero_npc[i]->WhatIam() == 1 || hero_npc[i]->WhatIam() == 4) {//��ʿ����սʿ
                    if (minimumDistance > 80) {
                        if (minimumVec.x < 0) {
                            hero_npc[i]->setDirectLeft();
                            weapon_npc[i]->setDirectLeft();
                            if (checkCollision(hero_npc[i]->getPosition() + Vec2(-80, 0), Left) != Wall &&
                                checkCollision(hero_npc[i]->getPosition() + Vec2(-50, 0), Left) != Wall &&
                                checkCollision(hero_npc[i]->getPosition() + Vec2(-20, 0), Left) != Wall) {
                                moveVec.x -= 80;
                            }
                            weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(-70, 30));
                            if (hero_npc[i]->WhatIam() == 4)
                                weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(-50, -10));
                        }
                        if (minimumVec.x > 0) {
                            hero_npc[i]->setDirectRight();
                            weapon_npc[i]->setDirectRight();
                            if (checkCollision(hero_npc[i]->getPosition() + Vec2(80, 0), Right) != Wall &&
                                checkCollision(hero_npc[i]->getPosition() + Vec2(50, 0), Right) != Wall &&
                                checkCollision(hero_npc[i]->getPosition() + Vec2(20, 0), Right) != Wall) {
                                moveVec.x += 80;
                            }
                            weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(70, 30));
                            if (hero_npc[i]->WhatIam() == 4)
                                weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(50, -10));
                        }
                        if (minimumVec.y > 0) {
                            if (checkCollision(hero_npc[i]->getPosition() + Vec2(0, 80), Up) != Wall &&
                                checkCollision(hero_npc[i]->getPosition() + Vec2(0, 50), Up) != Wall &&
                                checkCollision(hero_npc[i]->getPosition() + Vec2(0, 20), Up) != Wall) {
                                moveVec.y += 80;
                            }
                        }
                        if (minimumVec.y < 0) {
                            if (checkCollision(hero_npc[i]->getPosition() + Vec2(0, -80), Down) != Wall &&
                                checkCollision(hero_npc[i]->getPosition() + Vec2(0, -50), Down) != Wall &&
                                checkCollision(hero_npc[i]->getPosition() + Vec2(0, -20), Down) != Wall) {
                                moveVec.y -= 80;
                            }
                        }
                    } else {//����С��80
                        if (minimumVec.x < 0) {
                            hero_npc[i]->setDirectLeft();
                            weapon_npc[i]->setDirectLeft();
                            if (checkCollision(hero_npc[i]->getPosition() + Vec2(minimumVec.x + 10, 0), Left) != Wall) {
                                moveVec.x += minimumVec.x + 10;
                            }
                            weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(-70, 30));
                            if (hero_npc[i]->WhatIam() == 4)
                                weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(-50, -10));
                        }
                        if (minimumVec.x > 0) {
                            hero_npc[i]->setDirectRight();
                            weapon_npc[i]->setDirectRight();
                            if (checkCollision(hero_npc[i]->getPosition() + Vec2(minimumVec.x - 10, 0), Right) != Wall) {
                                moveVec.x += minimumVec.x - 10;
                            }
                            weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(70, 30));
                            if (hero_npc[i]->WhatIam() == 4)
                                weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(50, -10));
                        }
                        if (minimumVec.y > 0) {
                            if (checkCollision(hero_npc[i]->getPosition() + Vec2(0, minimumVec.y - 10), Up) != Wall) {
                                moveVec.y += minimumVec.y - 10;
                            }
                        }
                        if (minimumVec.y < 0) {
                            if (checkCollision(hero_npc[i]->getPosition() + Vec2(0, minimumVec.y + 10), Down) != Wall) {
                                moveVec.y += minimumVec.y + 10;
                            }
                        }
                    }
                } else {//��ʦ����ѧ��
                    if (minimumDistance > 180) {
                        if (minimumVec.x < 0) {
                            hero_npc[i]->setDirectLeft();
                            weapon_npc[i]->setDirectLeft();
                            if (checkCollision(hero_npc[i]->getPosition() + Vec2(-80, 0), Left) != Wall &&
                                checkCollision(hero_npc[i]->getPosition() + Vec2(-50, 0), Left) != Wall &&
                                checkCollision(hero_npc[i]->getPosition() + Vec2(-20, 0), Left) != Wall) {
                                moveVec.x -= 80;
                            }
                            weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(-70, 30));
                            if (hero_npc[i]->WhatIam() == 4)
                                weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(-50, -10));
                        }
                        if (minimumVec.x > 0) {
                            hero_npc[i]->setDirectRight();
                            weapon_npc[i]->setDirectRight();
                            if (checkCollision(hero_npc[i]->getPosition() + Vec2(80, 0), Right) != Wall &&
                                checkCollision(hero_npc[i]->getPosition() + Vec2(50, 0), Right) != Wall &&
                                checkCollision(hero_npc[i]->getPosition() + Vec2(20, 0), Right) != Wall) {
                                moveVec.x += 80;
                            }
                            weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(70, 30));
                            if (hero_npc[i]->WhatIam() == 4)
                                weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(50, -10));
                        }
                        if (minimumVec.y > 0) {
                            if (checkCollision(hero_npc[i]->getPosition() + Vec2(0, 80), Up) != Wall &&
                                checkCollision(hero_npc[i]->getPosition() + Vec2(0, 50), Up) != Wall &&
                                checkCollision(hero_npc[i]->getPosition() + Vec2(0, 20), Up) != Wall) {
                                moveVec.y += 80;
                            }
                        }
                        if (minimumVec.y < 0) {
                            if (checkCollision(hero_npc[i]->getPosition() + Vec2(0, -80), Down) != Wall &&
                                checkCollision(hero_npc[i]->getPosition() + Vec2(0, -50), Down) != Wall &&
                                checkCollision(hero_npc[i]->getPosition() + Vec2(0, -20), Down) != Wall) {
                                moveVec.y -= 80;
                            }
                        }
                    } else {//����С��180
                        if (minimumVec.x < 0) {
                            hero_npc[i]->setDirectLeft();
                            weapon_npc[i]->setDirectLeft();
                            if (checkCollision(hero_npc[i]->getPosition() + Vec2(minimumVec.x + 100, 0), Left) != Wall) {
                                moveVec.x += minimumVec.x + 100;
                            }
                            weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(-70, 30));
                            if (hero_npc[i]->WhatIam() == 4)
                                weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(-50, -10));
                        }
                        if (minimumVec.x > 0) {
                            hero_npc[i]->setDirectRight();
                            weapon_npc[i]->setDirectRight();
                            if (checkCollision(hero_npc[i]->getPosition() + Vec2(minimumVec.x - 100, 0), Right) != Wall) {
                                moveVec.x += minimumVec.x - 100;
                            }
                            weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(70, 30));
                            if (hero_npc[i]->WhatIam() == 4)
                                weapon_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(50, -10));
                        }
                        if (minimumVec.y > 0) {
                            if (checkCollision(hero_npc[i]->getPosition() + Vec2(0, minimumVec.y - 100), Up) != Wall) {
                                moveVec.y += minimumVec.y - 100;
                            }
                        }
                        if (minimumVec.y < 0) {
                            if (checkCollision(hero_npc[i]->getPosition() + Vec2(0, minimumVec.y + 100), Down) != Wall) {
                                moveVec.y += minimumVec.y + 100;
                            }
                        }
                    }
                }
            }
        }
        auto moveBy = MoveBy::create(0.5f, moveVec);
        hero_npc[i]->runAction(moveBy);
        weapon_npc[i]->runAction(moveBy->clone());
    }
}

void Battle::npc_move_safety_zone()
{
    for (int i = 0; i < number_npc_; i++) {
        float minimumDistance = calculate_distance_to_center_of_map(hero_npc[i]->getPosition());
        if (minimumDistance > safetyZone->getContentSize().width * safetyZone->getScale() / 2) {
            Vec2 minimumVec = calculate_vec(hero_npc[i]->getPosition(),
                                            Vec2(map->getMapSize().width * map->getTileSize().width / 2 + map->getPositionX(),
                                                 map->getMapSize().height * map->getTileSize().height / 2 + map->getPositionY()));
            Vec2 moveVec = 70 * Vec2(minimumVec.x / minimumDistance, minimumVec.y / minimumDistance);
            auto moveBy = MoveBy::create(0.5f, moveVec);
            hero_npc[i]->runAction(moveBy);
            weapon_npc[i]->runAction(moveBy->clone());
        }
    }
}

void Battle::npc_attack()
{
    //ʵʱ��ȡλ��
    Vec2 d_npc[HERO_NPC_NUM];
    for (int i = 0; i < number_npc_; i++)
    {
        d_npc[i] = hero_npc[i]->getPosition();
    }
    Vec2 d_player = hero_player->getPosition();
    //NPC�Ĵ�����ֻҪ�����㹻�ͻ��ͷţ�Ϊ��֤ƽ���Խ�NPC�ͷŴ������������ֵ����
    //��ͨ�����ж�
    for (int i = 0; i < number_npc_; i++)
    {
        if (hero_npc[i]->getHealth())
        {
            if (hero_npc[i]->WhatIam() == 1)
            {
                if (npc_attack_time[i] == 0)
                    //��ȡ��ǰʱ��
                    npc_attack_time[i] = gettime();
                else
                    if (gettime() - npc_attack_time[i] < 350) //ʱ�������Ϊ350���룬��ֹ̫��
                        return;
                    else
                        npc_attack_time[i] = gettime();
                if (hero_npc[i]->getEnergy() >= ENERGYMAX_KNIGHT_NPC)
                {
                    hero_npc[i]->SuperSkill();
                    if (hero_npc[i]->isDirectRight())
                        sword_bonus_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(100, 50));
                    else
                    {
                        sword_bonus_npc[i]->setDirectLeft();
                        sword_bonus_npc[i]->setPosition(hero_npc[i]->getPosition() + Vec2(-100, 50));
                    }
                    sword_bonus_npc[i]->setVisible(true);
                    weapon_npc[i]->setVisible(false);
                    sword_bonus_npc[i]->attack();
                    hero_npc[i]->setEnergy(0);
                    Vec2 tempdistance = calculate_distance(hero_player->getPosition(), sword_bonus_npc[i]->getPosition());
                    if (tempdistance.x < 1.1 && tempdistance.y < 1.1)
                    {
                        hero_player->setHealthPlus(-sword_bonus_npc[i]->getDamage());
                    }
                } else
                {
                    if (calculate_distance(d_npc[i], d_player).x <= 2.5)
                    {
                        if (weapon_npc[i]->isVisible())
                        {
                            weapon_npc[i]->attack();
                        } else if (hero_npc[i]->getEnergy() == 0)
                        {
                            sword_bonus_npc[i]->setVisible(false);
                            weapon_npc[i]->setVisible(true);
                            weapon_npc[i]->attack();
                        }
                        Vec2 tempdistance = calculate_distance(hero_player->getPosition(), weapon_npc[i]->getPosition());
                        if (tempdistance.x < 1.1 && tempdistance.y < 1.1)
                        {
                            hero_npc[i]->setEnergyPlus(1);
                            hero_player->setHealthPlus(-weapon_npc[i]->getDamage());
                        }
                    }
                }
                if (hero_player->getHealth() < 1)
                {//�����򲻿ɼ�
                    if (hero_player->WhatIam() == 1)
                        sword_bonus->setVisible(false);
                    hero_player->setVisible(false);
                    weapon_player->setVisible(false);
                }
            }
            if (hero_npc[i]->WhatIam() == 2)
            {
                if (npc_attack_time[i] == 0)
                    //��ȡ��ǰʱ��
                    npc_attack_time[i] = gettime();
                else
                    if (gettime() - npc_attack_time[i] < 900) //ʱ�������Ϊ900���룬��ֹ̫��
                        return;
                    else
                        npc_attack_time[i] = gettime();
                if (hero_npc[i]->getEnergy() >= ENERGYMAX_SCIENTIST_NPC)
                {
                    hero_npc[i]->SuperSkill();
                    Vec2 touchLocation = hero_player->getPosition();        // ��ȡ����������꣬����ƫ����
                    Vec2 offset = touchLocation - weapon_npc[i]->getPosition();
                    if (abs(offset.getAngle() / 3.14f * 180) > 70 && weapon_npc[i]->isDirectRight())
                        return;
                    if (abs(offset.getAngle() / 3.14f * 180) < 110 && !(weapon_npc[i]->isDirectRight()))
                        return;
                    projectiles_sci_npc[i] = BulletBonus::create();         // ����������
                    if (projectiles_sci_npc[i] != nullptr)
                    {
                        if (weapon_player->isDirectRight())
                        {
                            projectiles_sci_npc[i]->setPosition(weapon_npc[i]->getPosition() - Vec2(3, 30));
                        } else
                        {
                            projectiles_sci_npc[i]->setPosition(weapon_npc[i]->getPosition() - Vec2(-3, 30));
                        }
                        projectiles_sci_npc[i]->setRotation(-offset.getAngle() / 3.14f * 180);
                        projectiles_sci_npc[i]->setTag(111);
                        this->addChild(projectiles_sci_npc[i]);
                        offset.normalize();//ƫ����ת��Ϊ��λ����       
                        auto shootAmount = offset * 678;//�����һ��ָ��������ĳ���Ϊ678������
                        auto realDest = shootAmount + projectiles_sci_npc[i]->getPosition(); //Ŀ��λ��      
                        auto actionMove = MoveTo::create(0.36f, realDest);//���������ƶ���Ŀ��λ�ã�Ȼ�����ӳ������Ƴ�
                        auto actionRemove = RemoveSelf::create();
                        projectiles_sci_npc[i]->runAction(Sequence::create(actionMove, actionRemove, nullptr));
                        weapon_npc[i]->attack(); //������������������ײ���
                    }
                } else
                {
                    if (calculate_distance(d_npc[i], d_player).x <= 7)
                    {
                        Vec2 touchLocation = hero_player->getPosition();        // ��ȡ����������꣬����ƫ����
                        Vec2 offset = touchLocation - weapon_npc[i]->getPosition();
                        if (abs(offset.getAngle() / 3.14f * 180) > 70 && weapon_npc[i]->isDirectRight())
                            return;
                        if (abs(offset.getAngle() / 3.14f * 180) < 110 && !(weapon_npc[i]->isDirectRight()))
                            return;
                        projectile_sci_npc[i] = Bullet::create();         // ����������
                        if (weapon_player->isDirectRight())
                        {
                            projectile_sci_npc[i]->setPosition(weapon_npc[i]->getPosition() - Vec2(3, 30));
                        } else
                        {
                            projectile_sci_npc[i]->setPosition(weapon_npc[i]->getPosition() - Vec2(-3, 30));
                        }
                        projectile_sci_npc[i]->setRotation(-offset.getAngle() / 3.14f * 180);
                        projectile_sci_npc[i]->setTag(110);
                        this->addChild(projectile_sci_npc[i]);
                        offset.normalize();//ƫ����ת��Ϊ��λ����       
                        auto shootAmount = offset * 432;//�����һ��ָ��������ĳ���Ϊ432������
                        auto realDest = shootAmount + projectile_sci_npc[i]->getPosition(); //Ŀ��λ��      
                        auto actionMove = MoveTo::create(0.36f, realDest);//���������ƶ���Ŀ��λ�ã�Ȼ�����ӳ������Ƴ�
                        auto actionRemove = RemoveSelf::create();
                        projectile_sci_npc[i]->runAction(Sequence::create(actionMove, actionRemove, nullptr));
                        weapon_npc[i]->attack(); //������������������ײ���
                    }
                }
            }
            if (hero_npc[i]->WhatIam() == 3)
            {
                if (npc_attack_time[i] == 0)
                    //��ȡ��ǰʱ��
                    npc_attack_time[i] = gettime();
                else
                    if (gettime() - npc_attack_time[i] < 1000) //ʱ�������Ϊ1000���룬��ֹ̫��
                        return;
                    else
                        npc_attack_time[i] = gettime();
                if (hero_npc[i]->getEnergy() >= ENERGYMAX_WIZARD_NPC)
                {
                    hero_npc[i]->SuperSkill();
                    if (calculate_distance(d_npc[i], d_player).x <= 7)
                    {
                        Vec2 touchLocation = hero_player->getPosition();        // ��ȡ����������꣬����ƫ����
                        Vec2 offset = touchLocation - weapon_npc[i]->getPosition();
                        if (abs(offset.getAngle() / 3.14f * 180) > 80 && weapon_player->isDirectRight())
                            return;
                        if (abs(offset.getAngle() / 3.14f * 180) < 100 && !(weapon_player->isDirectRight()))
                            return;
                        projectile_wiz_npc[i] = Light::create();
                        projectile_wiz_npc[i]->setScale(2.0);
                        if (weapon_npc[i]->isDirectRight())
                        {
                            projectile_wiz_npc[i]->setPosition(weapon_npc[i]->getPosition() - Vec2(3, 30));
                        } else
                        {
                            projectile_wiz_npc[i]->setPosition(weapon_npc[i]->getPosition() - Vec2(-3, 30));
                        }
                        projectile_wiz_npc[i]->setRotation(-offset.getAngle() / 3.14f * 180);
                        projectile_wiz_npc[i]->setTag(210);
                        this->addChild(projectile_wiz_npc[i]);
                        offset.normalize();//ƫ����ת��Ϊ��λ����            
                        auto shootAmount = offset * 678;//�����һ��ָ��������ĳ���Ϊ567������            
                        auto realDest = shootAmount + projectile_wiz_npc[i]->getPosition();//Ŀ��λ��
                        auto actionMove = MoveTo::create(3.5f, realDest); //���������ƶ���Ŀ��λ�ã�Ȼ�����ӳ������Ƴ�
                        auto actionRemove = RemoveSelf::create();
                        projectile_wiz_npc[i]->runAction(Sequence::create(actionMove, actionRemove, nullptr));
                        weapon_npc[i]->attack(); //������������������ײ���
                    }
                } else
                {
                    if (calculate_distance(d_npc[i], d_player).x <= 7)
                    {
                        Vec2 touchLocation = hero_player->getPosition();        // ��ȡ����������꣬����ƫ����
                        Vec2 offset = touchLocation - weapon_npc[i]->getPosition();
                        if (abs(offset.getAngle() / 3.14f * 180) > 80 && weapon_player->isDirectRight())
                            return;
                        if (abs(offset.getAngle() / 3.14f * 180) < 100 && !(weapon_player->isDirectRight()))
                            return;
                        projectile_wiz_npc[i] = Light::create();
                        if (weapon_npc[i]->isDirectRight())
                        {
                            projectile_wiz_npc[i]->setPosition(weapon_npc[i]->getPosition() - Vec2(3, 30));
                        } else
                        {
                            projectile_wiz_npc[i]->setPosition(weapon_npc[i]->getPosition() - Vec2(-3, 30));
                        }
                        projectile_wiz_npc[i]->setRotation(-offset.getAngle() / 3.14f * 180);
                        projectile_wiz_npc[i]->setTag(210);
                        this->addChild(projectile_wiz_npc[i]);
                        offset.normalize();//ƫ����ת��Ϊ��λ����            
                        auto shootAmount = offset * 567;//�����һ��ָ��������ĳ���Ϊ567������            
                        auto realDest = shootAmount + projectile_wiz_npc[i]->getPosition();//Ŀ��λ��
                        auto actionMove = MoveTo::create(1.5f, realDest); //���������ƶ���Ŀ��λ�ã�Ȼ�����ӳ������Ƴ�
                        auto actionRemove = RemoveSelf::create();
                        projectile_wiz_npc[i]->runAction(Sequence::create(actionMove, actionRemove, nullptr));
                        weapon_npc[i]->attack(); //������������������ײ���
                    }
                }
            }
            if (hero_npc[i]->WhatIam() == 4)
            {
                if (npc_attack_time[i] == 0)
                    //��ȡ��ǰʱ��
                    npc_attack_time[i] = gettime();
                else
                    if (gettime() - npc_attack_time[i] < 300) //ʱ�������Ϊ300���룬��ֹ̫��
                        return;
                    else
                        npc_attack_time[i] = gettime();
                if (hero_npc[i]->getEnergy() >= ENERGYMAX_BERSERKER_NPC)
                {
                    hero_npc[i]->SuperSkill();
                    float volume = volume_;
                    if (!switch_sound_)
                        volume = 0.0f;
                    auto berserker_audio_npc = AudioEngine::play2d("Sounds/berserker_superskill.mp3", false, 0.7f * volume);
                    AudioEngine::resume(berserker_audio_npc);
                    Vec2 touchLocation = hero_player->getPosition();        // ��ȡ����������꣬����ƫ����
                    Vec2 offset = touchLocation - weapon_npc[i]->getPosition();
                    if (abs(offset.getAngle() / 3.14f * 180) > 70 && weapon_npc[i]->isDirectRight())
                        return;
                    if (abs(offset.getAngle() / 3.14f * 180) < 110 && !(weapon_npc[i]->isDirectRight()))
                        return;
                    projectile_ber_npc[i] = Glove::create();         // ����������
                    if (projectile_ber_npc[i] != nullptr)
                    {
                        if (weapon_player->isDirectRight())
                        {
                            projectile_ber_npc[i]->setPosition(weapon_npc[i]->getPosition() - Vec2(3, 30));
                        } else
                        {
                            projectile_ber_npc[i]->setPosition(weapon_npc[i]->getPosition() - Vec2(-3, 30));
                        }
                        projectile_ber_npc[i]->setRotation(-offset.getAngle() / 3.14f * 180);
                        projectile_ber_npc[i]->setTag(310);
                        this->addChild(projectile_ber_npc[i]);
                        offset.normalize();//ƫ����ת��Ϊ��λ����       
                        auto shootAmount = offset * 300;//�����һ��ָ��������ĳ���Ϊ300������
                        auto realDest = shootAmount + projectile_ber_npc[i]->getPosition(); //Ŀ��λ��      
                        auto actionMove = MoveTo::create(0.36f, realDest);//���������ƶ���Ŀ��λ�ã�Ȼ�����ӳ������Ƴ�
                        auto actionRemove = RemoveSelf::create();
                        projectile_ber_npc[i]->runAction(Sequence::create(actionMove, actionRemove, nullptr));
                        weapon_npc[i]->attack(); //������������������ײ���
                    }
                } else
                {
                    if (calculate_distance(d_npc[i], d_player).x <= 2.5)
                    {
                        weapon_npc[i]->attack();
                        Vec2 tempdistance = calculate_distance(hero_player->getPosition(), weapon_npc[i]->getPosition());
                        if (tempdistance.x < 1.1 && tempdistance.y < 1.1)
                        {
                            hero_npc[i]->setEnergyPlus(1);
                            hero_player->setHealthPlus(-weapon_npc[i]->getDamage());
                        }
                        if (hero_player->getHealth() < 1)
                        {//�����򲻿ɼ�
                            if (hero_player->WhatIam() == 1)
                                sword_bonus->setVisible(false);
                            hero_player->setVisible(false);
                            weapon_player->setVisible(false);
                        }
                    }
                }
            }
        }
    }
}

void Battle::npc_update(float delta)
{
    npc_move();
    npc_move600();
    npc_move_safety_zone();
}

void Battle::safetyZone_update(float delta)
{
    if (scale < 0)
        scale = 0.0f;
    safetyZone->setScale(scale);
    if (calculate_distance_to_center_of_map(hero_player->getPosition()) >
        safetyZone->getContentSize().width * scale / 2) {
        hero_player->setHealthPlus(-6);
        returnToSafetyZone->setVisible(true);
    } else {
        returnToSafetyZone->setVisible(false);
    }
    for (int i = 0; i < number_npc_; i++) {
        if (calculate_distance_to_center_of_map(hero_npc[i]->getPosition()) >
            safetyZone->getContentSize().width * scale / 2)
            hero_npc[i]->setHealthPlus(-6);
    }
    scale -= 0.005f;//update: 0.005f
}

void Battle::initBox()
{
    //��ʼ��Box
    for (int i = 0; i < BOX_NUM; i++) {
        boxwhat[i] = BoxWhat::create();
        boxhealth[i] = BoxHealth::create();
        boxcharge[i] = BoxCharge::create();
        boxhell[i] = BoxHell::create();
        boxwhat[i]->setAnchorPoint(Vec2(0.5, 0.5));
        boxhealth[i]->setAnchorPoint(Vec2(0.5, 0.5));
        boxcharge[i]->setAnchorPoint(Vec2(0.5, 0.5));
        boxhell[i]->setAnchorPoint(Vec2(0.5, 0.5));
        //����Box��λ��
        //what
        while (1) {
            int x = (rand() % (int)((map->getMapSize().width - 25) * map->getTileSize().width)) +
                (8 * map->getTileSize().width);
            int y = (rand() % (int)((map->getMapSize().height - 21) * map->getTileSize().height)) +
                (6 * map->getTileSize().width);
            if (checkCollision(Point(x, y), Left) == Wall ||
                checkCollision(Point(x, y), Right) == Wall ||
                checkCollision(Point(x, y), Up) == Wall ||
                checkCollision(Point(x, y), Down) == Wall) {
                continue;
            }
            boxwhat[i]->setPosition(Vec2(x, y));
            break;
        }
        this->addChild(boxwhat[i]);
        log("BOXWHAT ADD");
        //health
        while (1) {
            int x = (rand() % (int)((map->getMapSize().width - 25) * map->getTileSize().width)) +
                (8 * map->getTileSize().width);
            int y = (rand() % (int)((map->getMapSize().height - 21) * map->getTileSize().height)) +
                (6 * map->getTileSize().width);
            if (checkCollision(Point(x, y), Left) == Wall ||
                checkCollision(Point(x, y), Right) == Wall ||
                checkCollision(Point(x, y), Up) == Wall ||
                checkCollision(Point(x, y), Down) == Wall) {
                continue;
            }
            boxhealth[i]->setPosition(Vec2(x, y));
            break;
        }
        this->addChild(boxhealth[i]);
        log("BOXHEALTH ADD");
        //charge
        while (1) {
            int x = (rand() % (int)((map->getMapSize().width - 25) * map->getTileSize().width)) +
                (8 * map->getTileSize().width);
            int y = (rand() % (int)((map->getMapSize().height - 21) * map->getTileSize().height)) +
                (6 * map->getTileSize().width);
            if (checkCollision(Point(x, y), Left) == Wall ||
                checkCollision(Point(x, y), Right) == Wall ||
                checkCollision(Point(x, y), Up) == Wall ||
                checkCollision(Point(x, y), Down) == Wall) {
                continue;
            }
            boxcharge[i]->setPosition(Vec2(x, y));
            break;
        }
        this->addChild(boxcharge[i]);
        log("BOXCHARGE ADD");
        //hell
        while (1) {
            int x = (rand() % (int)((map->getMapSize().width - 25) * map->getTileSize().width)) +
                (8 * map->getTileSize().width);
            int y = (rand() % (int)((map->getMapSize().height - 21) * map->getTileSize().height)) +
                (6 * map->getTileSize().width);
            if (checkCollision(Point(x, y), Left) == Wall ||
                checkCollision(Point(x, y), Right) == Wall ||
                checkCollision(Point(x, y), Up) == Wall ||
                checkCollision(Point(x, y), Down) == Wall) {
                continue;
            }
            boxhell[i]->setPosition(Vec2(x, y));
            break;
        }
        this->addChild(boxhell[i]);
        log("BOXHELL ADD");
    }
}

Vec2 Battle::calculate_distance(const Vec2& a, const Vec2& b)
{
    return Vec2(abs(a.x - b.x) / map->getTileSize().width, abs(a.y - b.y) / map->getTileSize().height);
}

float Battle::calculate_distance_to_center_of_map(const Vec2& coord)
{
    Vec2 toCenter = Vec2(map->getMapSize().width * map->getTileSize().width / 2 + map->getPositionX(),
                         map->getMapSize().height * map->getTileSize().height / 2 + map->getPositionY()) - coord;
    return sqrt(toCenter.x * toCenter.x + toCenter.y * toCenter.y);
}

Vec2 Battle::calculate_vec(const Vec2& a, const Vec2& b)
{
    return b - a;
}

float Battle::calculate_modulus(const Vec2& a, const Vec2& b)
{
    Vec2 to = b - a;
    return sqrt(to.x * to.x + to.y * to.y);
}

void Battle::setPause(bool status)
{
    is_game_pause = status;
}

void Battle::menuCloseCallback(Ref* pSender)
{
    //�رճ���
    Director::getInstance()->end();
    //doPause();
}

void Battle::menuPauseCallback(Ref* pSender)
{
    //��ͣ����
    if (is_game_pause)
    {
        Director::getInstance()->resume();
        setPause(false);
    } else
    {
        Director::getInstance()->pause();
        setPause(true);
    }
}

bool Battle::onTouchBegan(Touch* touch, Event* unused_event)
{
    if (hero_player->getHealth() <= 0)
    {
        return true;
    } else
    {
        if (hero_player->WhatIam() == 4)//��Ҳٿؿ�սʿʱ��ִ�����
        {
            //����hammer����������ִ��attack()�ģ�����Ҫ������ײ���
            if (mouse_click_time == 0)
                //��ȡ��ǰʱ��
                mouse_click_time = gettime();
            else
                if (gettime() - mouse_click_time < 200) //ʱ�������Ϊ200���룬��ֹ���̫��
                    return true;
                else
                    mouse_click_time = gettime();
            weapon_player->attack();
            for (int i = 0; i < number_npc_; i++) {
                if (hero_npc[i]->getHealth() < 1) {//�����򲻿ɼ�
                    if (hero_npc[i]->WhatIam() == 1)
                        sword_bonus_npc[i]->setVisible(false);
                    hero_npc[i]->setVisible(false);
                    weapon_npc[i]->setVisible(false);
                    continue;
                }
                Vec2 tempdistance = calculate_distance(hero_npc[i]->getPosition(), weapon_player->getPosition());
                if (tempdistance.x < 1.1 && tempdistance.y < 1.1) {
                    hero_player->setEnergyPlus(1);
                    hero_npc[i]->setHealthPlus(-weapon_player->getDamage());
                }
            }
        } else if (hero_player->WhatIam() == 1)//��Ҳٿ���ʿʱ��ִ�����
        {//����sword��sword_bonus����������ִ��attack()�ģ�����Ҫ������ײ���
            if (mouse_click_time == 0)
                //��ȡ��ǰʱ��
                mouse_click_time = gettime();
            else
                if (gettime() - mouse_click_time < 360) //ʱ�������Ϊ360���룬��ֹ���̫��
                    return true;
                else
                    mouse_click_time = gettime();
            if (weapon_player->isVisible())
            {
                weapon_player->attack();
            } else if (hero_player->getEnergy() == 0)
            {
                sword_bonus->setVisible(false);
                weapon_player->setVisible(true);
                weapon_player->attack();
            } else
            {
                sword_bonus->attack();
                hero_player->setEnergy(0);
            }
            for (int i = 0; i < number_npc_; i++) {
                if (hero_npc[i]->getHealth() < 1) {//�����򲻿ɼ�
                    if (hero_npc[i]->WhatIam() == 1)
                        sword_bonus_npc[i]->setVisible(false);
                    hero_npc[i]->setVisible(false);
                    weapon_npc[i]->setVisible(false);
                    continue;
                }
                Vec2 tempdistance = calculate_distance(hero_npc[i]->getPosition(), weapon_player->getPosition());
                if (tempdistance.x < 1.1 && tempdistance.y < 1.1) {
                    if (sword_bonus->isVisible())
                        hero_npc[i]->setHealthPlus(-sword_bonus->getDamage());
                    else
                    {
                        hero_player->setEnergyPlus(1);
                        hero_npc[i]->setHealthPlus(-weapon_player->getDamage());
                    }
                }
            }
        } else  if (hero_player->WhatIam() == 2) //��Ҳٿؿ�ѧ��ʱ��ִ�����
        {
            if (mouse_click_time == 0)             //��ȡ��ǰʱ��
                mouse_click_time = gettime();
            else
                if (gettime() - mouse_click_time < 400) //ʱ�������Ϊ400���룬��ֹ���̫��
                    return true;
                else
                    mouse_click_time = gettime();
            Vec2 touchLocation = touch->getLocation();        // ��ȡ����������꣬����ƫ����
            Vec2 offset = touchLocation - weapon_player->getPosition();
            if (abs(offset.getAngle() / 3.14f * 180) > 70 && weapon_player->isDirectRight())
                return true;
            if (abs(offset.getAngle() / 3.14f * 180) < 110 && !(weapon_player->isDirectRight()))
                return true;
            projectile_sci = Bullet::create();         // ����������
            if (weapon_player->isDirectRight())
            {
                projectile_sci->setPosition(weapon_player->getPosition() - Vec2(3, 30));
            } else
            {
                projectile_sci->setPosition(weapon_player->getPosition() - Vec2(-3, 30));
            }
            projectile_sci->setRotation(-offset.getAngle() / 3.14f * 180);
            projectile_sci->setTag(100);
            this->addChild(projectile_sci);
            offset.normalize();//ƫ����ת��Ϊ��λ����       
            auto shootAmount = offset * 432;//�����һ��ָ��������ĳ���Ϊ432������
            auto realDest = shootAmount + projectile_sci->getPosition(); //Ŀ��λ��      
            auto actionMove = MoveTo::create(0.36f, realDest);//���������ƶ���Ŀ��λ�ã�Ȼ�����ӳ������Ƴ�
            auto actionRemove = RemoveSelf::create();
            projectile_sci->runAction(Sequence::create(actionMove, actionRemove, nullptr));
            weapon_player->attack(); //������������������ײ���
        } else if (hero_player->WhatIam() == 3)//��Ҳٿط�ʦʱ��ִ�����
        {
            if (mouse_click_time == 0)            //��ȡ��ǰʱ��
                mouse_click_time = gettime();
            else
                if (gettime() - mouse_click_time < 800) //ʱ�������Ϊ800���룬��ֹ���̫��
                    return true;
                else
                    mouse_click_time = gettime();
            Vec2 touchLocation = touch->getLocation();        //��ȡ����������꣬����ƫ����
            Vec2 offset = touchLocation - weapon_player->getPosition();
            if (abs(offset.getAngle() / 3.14f * 180) > 80 && weapon_player->isDirectRight())
                return true;
            if (abs(offset.getAngle() / 3.14f * 180) < 100 && !(weapon_player->isDirectRight()))
                return true;
            projectile_wiz = Light::create();
            if (weapon_player->isDirectRight())
            {
                projectile_wiz->setPosition(weapon_player->getPosition() - Vec2(3, 30));
            } else
            {
                projectile_wiz->setPosition(weapon_player->getPosition() - Vec2(-3, 30));
            }
            projectile_wiz->setRotation(-offset.getAngle() / 3.14f * 180);
            projectile_wiz->setTag(200);
            this->addChild(projectile_wiz);
            offset.normalize();//ƫ����ת��Ϊ��λ����            
            auto shootAmount = offset * 567;//�����һ��ָ��������ĳ���Ϊ567������            
            auto realDest = shootAmount + projectile_wiz->getPosition();//Ŀ��λ��
            auto actionMove = MoveTo::create(1.5f, realDest); //���������ƶ���Ŀ��λ�ã�Ȼ�����ӳ������Ƴ�
            auto actionRemove = RemoveSelf::create();
            projectile_wiz->runAction(Sequence::create(actionMove, actionRemove, nullptr));
            weapon_player->attack(); //������������������ײ���
        }
    }
    return true;
}
Point Battle::positionToTileCoord(const Point& cocosCoord, const Direction& drt)//��������
{
    int x, y;
    if (Left == drt) {
        x = (cocosCoord.x - HERO_WIDTH / 2 - map->getPositionX()) /
            map->getTileSize().width;
        y = (((map->getMapSize().height - 1) * map->getTileSize().height) -
             (cocosCoord.y - map->getPositionY())) / map->getTileSize().height;
    } else if (Right == drt) {
        x = (cocosCoord.x + HERO_WIDTH / 2 - map->getPositionX()) /
            map->getTileSize().width;
        y = (((map->getMapSize().height - 1) * map->getTileSize().height) -
             (cocosCoord.y - map->getPositionY())) / map->getTileSize().height;
    } else if (Up == drt) {
        x = (cocosCoord.x - map->getPositionX()) / map->getTileSize().width;
        y = (((map->getMapSize().height - 1) * map->getTileSize().height) -
             (cocosCoord.y + HERO_HEIGHT / 2 -
              map->getPositionY())) / map->getTileSize().height;
    } else if (Down == drt) {
        x = (cocosCoord.x - map->getPositionX()) / map->getTileSize().width;
        y = (((map->getMapSize().height - 1) * map->getTileSize().height) -
             (cocosCoord.y - HERO_HEIGHT / 2 -
              map->getPositionY())) / map->getTileSize().height;
    } else {//Middle
        x = (cocosCoord.x - map->getPositionX()) / map->getTileSize().width;
        y = (((map->getMapSize().height - 1) * map->getTileSize().height) -
             (cocosCoord.y - map->getPositionY())) / map->getTileSize().height;
    }
    return Point(x, y);
}

Battle::CollisionType Battle::checkCollision(const Point& heroPotion, const Direction& drt)
{
    Point tileCoord = positionToTileCoord(heroPotion, drt);

    //����Ƿ񳬳���ͼ�߽�
    if (tileCoord.x<1 || tileCoord.x>map->getMapSize().width - 1 ||
        tileCoord.y<1 || tileCoord.y>map->getMapSize().height - 1)
        return Wall;//��������ͼ�߽磬�߼�������

    //�ж�Ŀ�������Ƿ�Ϊǽ��
    int tileGid = map->getLayer("obstacle")->
        getTileGIDAt(Point(tileCoord.x, tileCoord.y + 1));//������ʱy����һ�����ﱣ��ͬ��
    if (tileGid)
        return Wall;

    //�ж�Ŀ�������Ƿ�Ϊ�ݵ�
    int tileGidOfGrass = map->getLayer("grass")->
        getTileGIDAt(Point(tileCoord.x, tileCoord.y + 1));//������ʱy����һ�����ﱣ��ͬ��
    if (tileGidOfGrass)
        return Grass;
    return Moveble;
}

void Battle::update(float delta)
{
    collect_box();
    npc_attack();
    if (projectile_sci != nullptr && this->getChildByTag(100) != nullptr) {//�������ѧ���ӵ�
        attack_sci();
    }
    for (int i = 0; i < 8; i++) {
        if (projectiles_sci[i] != nullptr && this->getChildByTag(101 + i) != nullptr) {//�������ѧ�Ҵ���
            attack_sci_bonus(projectiles_sci[i]);
        }
    }
    if (projectile_wiz != nullptr && this->getChildByTag(200) != nullptr) {//������Ů���չ�
        attack_wiz();
    }
    if (projectiles_wiz != nullptr && this->getChildByTag(201) != nullptr) {//������Ů�״���
        attack_wiz_bonus();
    }
    if (projectile_ber != nullptr && this->getChildByTag(300) != nullptr) {//�������սʿ����
        attack_ber();
    }

    //NPC����
    for (int i = 0; i < number_npc_; i++)
    {
        if (projectile_sci_npc[i] != nullptr && this->getChildByTag(110) != nullptr) {//�������ѧ���ӵ�
            attack_sci_npc();
        }
        if (projectile_wiz_npc[i] != nullptr && this->getChildByTag(210) != nullptr) {//������Ů���չ��ʹ���
            attack_wiz_npc();
        }
        if (projectiles_sci_npc[i] != nullptr && this->getChildByTag(111) != nullptr)  //�������ѧ�Ҵ���
        {
            attack_sci_bonus_npc(projectiles_sci_npc[i], i);
        }

        if (projectile_ber_npc[i] != nullptr && this->getChildByTag(310) != nullptr) {//�������սʿ����
            attack_ber_npc();
        }
    }

    if (key_map[left])
    {
        hero_player->setDirectLeft();
        weapon_player->setDirectLeft();
        if (hero_player->WhatIam() == 1)
        {
            sword_bonus->setDirectLeft();
            sword_bonus->setPosition(hero_player->getPosition() + Vec2(-100, 50));
        }
        weapon_player->setPosition(hero_player->getPosition() + Vec2(-70, 30));
        if (hero_player->WhatIam() == 4)
            weapon_player->setPosition(hero_player->getPosition() + Vec2(-50, -10));
        relativeMovement(0.02, Vec2(-5, 0), false);
    }
    if (key_map[right])
    {
        hero_player->setDirectRight();
        weapon_player->setDirectRight();
        if (hero_player->WhatIam() == 1)
        {
            sword_bonus->setDirectRight();
            sword_bonus->setPosition(hero_player->getPosition() + Vec2(100, 50));
        }
        weapon_player->setPosition(hero_player->getPosition() + Vec2(70, 30));
        if (hero_player->WhatIam() == 4)
            weapon_player->setPosition(hero_player->getPosition() + Vec2(50, -10));
        relativeMovement(0.02, Vec2(5, 0), false);
    }
    if (key_map[down])
    {
        relativeMovement(0.02, Vec2(0, -5), false);
    }
    if (key_map[up])
    {
        relativeMovement(0.02, Vec2(0, 5), false);
    }
    if (key_map[q])
    {
        if (hero_player->WhatIam() == 4)
        {
            if (hero_player->getEnergy() >= ENERGYMAX_BERSERKER)
            {
                hero_player->SuperSkill();
                float volume = volume_;
                if (!switch_sound_)
                    volume = 0;
                auto berserker_audio = AudioEngine::play2d("Sounds/berserker_superskill.mp3", false, 0.7f * volume);
                AudioEngine::resume(berserker_audio);
                Vec2 offset = Vec2(1, 0);
                if (hero_player->isDirectRight())
                    offset = Vec2(1, 0);
                else
                    offset = Vec2(-1, 0);
                // ����������
                projectile_ber = Glove::create();
                if (hero_player->isDirectRight())
                {
                    projectile_ber->setPosition(hero_player->getPosition());
                } else
                {
                    projectile_ber->setPosition(hero_player->getPosition());
                }
                if (hero_player->isDirectRight())
                    ;
                else
                    projectile_ber->setScaleX(-1.0f);
                projectile_ber->setTag(300);
                this->addChild(projectile_ber);
                //�����һ��ָ��������ĳ���Ϊ900������
                auto shootAmount = offset * 900;
                //Ŀ��λ��
                auto realDest = shootAmount + projectile_ber->getPosition();
                //���������ƶ���Ŀ��λ�ã�Ȼ�����ӳ������Ƴ�
                auto actionMove = MoveTo::create(1.5f, realDest);
                auto actionRemove = RemoveSelf::create();
                projectile_ber->runAction(Sequence::create(actionMove, actionRemove, nullptr));
            }
        } else if (hero_player->WhatIam() == 2)
        {
            if (hero_player->getEnergy() >= ENERGYMAX_SCIENTIST)
            {
                hero_player->SuperSkill();
                Vec2 offset[8] = { Vec2(1, 0), Vec2(1, 1) ,Vec2(1, -1),Vec2(-1, 0) ,Vec2(-1, 1) ,Vec2(-1, -1),Vec2(0, 1),Vec2(0, -1) };
                Vec2 shootAmount[8];
                Vec2 realDest[8];
                // ����������
                for (int i = 0; i < 8; i++) {
                    projectiles_sci[i] = BulletBonus::create();
                    projectiles_sci[i]->setTag(101 + i);
                    this->addChild(projectiles_sci[i]);
                }

                for (int i = 0; i < 8; i++)
                    projectiles_sci[i]->setPosition(hero_player->getPosition());

                projectiles_sci[1]->setRotation(-45);
                projectiles_sci[2]->setRotation(45);
                projectiles_sci[3]->setRotation(-180);
                projectiles_sci[4]->setRotation(-135);
                projectiles_sci[5]->setRotation(135);
                projectiles_sci[6]->setRotation(-90);
                projectiles_sci[7]->setRotation(90);

                //�����һ��ָ��������ĳ���Ϊ654������
                for (int i = 0; i < 8; i++)
                    shootAmount[i] = offset[i] * 654;
                //Ŀ��λ��
                for (int i = 0; i < 8; i++)
                    realDest[i] = shootAmount[i] + projectiles_sci[i]->getPosition();
                //���������ƶ���Ŀ��λ�ã�Ȼ�����ӳ������Ƴ�
                MoveTo* actionMove[8];
                for (int i = 0; i < 8; i++)
                    actionMove[i] = MoveTo::create(0.4f, realDest[i]);
                auto actionRemove = RemoveSelf::create();
                for (int i = 0; i < 8; i++)
                    projectiles_sci[i]->runAction(Sequence::create(actionMove[i], actionRemove, nullptr));
            }
        } else if (hero_player->WhatIam() == 3)
        {
            if (hero_player->getEnergy() >= ENERGYMAX_WIZARD)
            {
                hero_player->SuperSkill();
                Vec2 offset = Vec2(1, 0);
                if (hero_player->isDirectRight())
                    offset = Vec2(1, 0);
                else
                    offset = Vec2(-1, 0);
                // ����������
                projectiles_wiz = LightBonus::create();
                projectiles_wiz->setScale(1.6f, 2.1f);
                if (hero_player->isDirectRight())
                {
                    projectiles_wiz->setPosition(hero_player->getPosition() - Vec2(3, 30));
                } else
                {
                    projectiles_wiz->setPosition(hero_player->getPosition() - Vec2(-3, 30));
                }
                projectiles_wiz->setTag(201);
                this->addChild(projectiles_wiz);
                //�����һ��ָ��������ĳ���Ϊ2500������
                auto shootAmount = offset * 2500;
                //Ŀ��λ��
                auto realDest = shootAmount + projectiles_wiz->getPosition();
                //���������ƶ���Ŀ��λ�ã�Ȼ�����ӳ������Ƴ�
                auto actionMove = MoveTo::create(12.5f, realDest);
                auto actionRemove = RemoveSelf::create();
                projectiles_wiz->runAction(Sequence::create(actionMove, actionRemove, nullptr));
            }
        } else if (hero_player->WhatIam() == 1)
        {
            if (hero_player->getEnergy() >= ENERGYMAX_KNIGHT)
            {
                hero_player->SuperSkill();
                sword_bonus->setVisible(true);
                weapon_player->setVisible(false);
            }
        }
    }
    if (key_map[shift])
    {
        if (hero_player->isDirectRight())
        {
            relativeMovement(0.02, Vec2(20, 0), true);
        } else
        {
            relativeMovement(0.02, Vec2(-20, 0), true);
        }
    }
    //�����ɫ������ֵС��0��������Ϊ���ɼ�
    for (int i = 0; i < number_npc_; i++)
    {
        if (hero_player->getHealth() <= 0)
        {
            hero_player->setEnergy(2);
            if (hero_player->WhatIam() == 1)
                sword_bonus->setVisible(false);
            hero_player->setVisible(false);
            weapon_player->setVisible(false);
        }
        if (hero_npc[i]->getHealth() <= 0)
        {
            hero_npc[i]->setEnergy(2);
            if (hero_npc[i]->WhatIam() == 1)
                sword_bonus_npc[i]->setVisible(false);
            hero_npc[i]->setVisible(false);
            weapon_npc[i]->setVisible(false);
        }
    }

    replaceToSettlement();
}

//����ƶ�  ���뽫���в����������ƶ��ľ���ȫ������ڴ˴������� ////////////////  ATTENTION  /////////////////
void Battle::relativeMovement(float duration, const Vec2& deltaPosition, bool shiftOn)
{
    auto moveBy = MoveBy::create(duration, -deltaPosition);
    Vec2 vecMoving = Vec2::ZERO;
    Vec2 vecShift = Vec2::ZERO;

    if (checkCollision(hero_player->getPosition(), Middle) == Grass) {
        hero_player->setOpacity(100);
        weapon_player->setOpacity(100);
    } else {
        hero_player->setOpacity();
        weapon_player->setOpacity();
    }

    bool wallOnRight = (checkCollision(deltaPosition + hero_player->getPosition(), Right) == Wall);
    bool wallOnLeft = (checkCollision(deltaPosition + hero_player->getPosition(), Left) == Wall);
    bool wallOnUp = (checkCollision(deltaPosition + hero_player->getPosition(), Up) == Wall);
    bool wallOnDown = (checkCollision(deltaPosition + hero_player->getPosition(), Down) == Wall);

    if (!shiftOn) {
        if (wallOnRight && wallOnDown && (!key_map[left] && !key_map[up]) ||
            wallOnRight && wallOnUp && (!key_map[left] && !key_map[down]) ||
            wallOnLeft && wallOnDown && (!key_map[right] && !key_map[up]) ||
            wallOnLeft && wallOnUp && (!key_map[right] && !key_map[down]))
            return;
        if (wallOnRight) {
            vecMoving.x = 5;
        }
        if (wallOnLeft) {
            vecMoving.x = -5;
        }
        if (wallOnUp) {
            vecMoving.y = 5;
        }
        if (wallOnDown) {
            vecMoving.y = -5;
        }
    } else {
        if (wallOnRight) {
            vecShift.x = 20;
        }
        if (wallOnLeft) {
            vecShift.x = -20;
        }
        if (wallOnUp) {
            vecShift.y = 20;
        }
        if (wallOnDown) {
            vecShift.y = -20;
        }
    }

    auto relativeMove = MoveBy::create(duration, vecMoving);
    auto moveByShift = MoveBy::create(duration, vecShift);
    auto moveByShiftWithEase = EaseExponentialOut::create(moveByShift);
    auto spawn = Spawn::create(moveBy, relativeMove, moveByShiftWithEase, nullptr);
    map->runAction(spawn);
    safetyZone->runAction(spawn->clone());

    //���в��������ߵľ���ȫ�����������
    for (int i = 0; i < BOX_NUM; i++)
    {
        boxwhat[i]->runAction(spawn->clone());
        boxhealth[i]->runAction(spawn->clone());
        boxcharge[i]->runAction(spawn->clone());
        boxhell[i]->runAction(spawn->clone());
    }
    for (int i = 0; i < number_npc_; i++) {
        hero_npc[i]->runAction(spawn->clone());
        weapon_npc[i]->runAction(spawn->clone());
        if (hero_npc[i]->WhatIam() == 1)
            sword_bonus_npc[i]->runAction(spawn->clone());
    }
}

//��ѧ����ͨ�ӵ�����ײ���
void Battle::attack_sci()
{
    log("%f,%f", projectile_sci->getPosition().x, projectile_sci->getPosition().y);
    for (int i = 0; i < number_npc_; i++) {
        if (hero_npc[i]->getHealth() < 1) {
            if (hero_npc[i]->WhatIam() == 1)
                sword_bonus_npc[i]->setVisible(false);
            hero_npc[i]->setVisible(false);
            weapon_npc[i]->setVisible(false);
            continue;
        }
        Vec2 pos_a = hero_npc[i]->getPosition();
        Vec2 pos_b = projectile_sci->getPosition();
        Vec2 d = calculate_distance(pos_a, pos_b);
        if (d.x < 1.1 && d.y < 1.1)
        {
            hero_npc[i]->setHealthPlus(-projectile_sci->getDamage());
            hero_player->setEnergyPlus(1);
            log("DAMAGE sci");
            projectile_sci->removeFromParentAndCleanup(true);
            projectile_sci = nullptr;
            return;
        }
    }
}

//��ѧ�Ҵ����ӵ�����ײ���
void Battle::attack_sci_bonus(BulletBonus* projectiles)
{
    log("%f,%f", projectiles->getPosition().x, projectiles->getPosition().y);
    for (int i = 0; i < number_npc_; i++) {
        if (hero_npc[i]->getHealth() < 1) {
            if (hero_npc[i]->WhatIam() == 1)
                sword_bonus_npc[i]->setVisible(false);
            hero_npc[i]->setVisible(false);
            weapon_npc[i]->setVisible(false);
            continue;
        }
        Vec2 pos_a = hero_npc[i]->getPosition();
        Vec2 pos_b = projectiles->getPosition();
        Vec2 d = calculate_distance(pos_a, pos_b);
        if (d.x < 1.1 && d.y < 1.1)
        {
            hero_npc[i]->setHealthPlus(-projectiles->getDamage());
            log("DAMAGE sci super");
            projectiles->removeFromParentAndCleanup(true);
            projectiles = nullptr;
            return;
        }
    }
}

//��ʦ��ͨ��������ײ���
void Battle::attack_wiz()
{
    log("%f,%f", projectile_wiz->getPosition().x, projectile_wiz->getPosition().y);
    for (int i = 0; i < number_npc_; i++) {
        if (hero_npc[i]->getHealth() < 1) {//�����򲻿ɼ�
            if (hero_npc[i]->WhatIam() == 1)
                sword_bonus_npc[i]->setVisible(false);
            hero_npc[i]->setVisible(false);
            weapon_npc[i]->setVisible(false);
            continue;
        }
        Vec2 pos_a = hero_npc[i]->getPosition();
        Vec2 pos_b = projectile_wiz->getPosition();
        Vec2 d = calculate_distance(pos_a, pos_b);
        if (d.x < 1.1 && d.y < 1.1)
        {
            if (light_time == 0)
                //��ȡ��ǰʱ��
                light_time = gettime();
            else
                if (gettime() - light_time < 100)  //���ڹ����������˺���ʱ�������Ϊ100����
                    return;
                else
                    light_time = gettime();
            hero_npc[i]->setHealthPlus(-projectile_wiz->getDamage());
            log("DAMAGE wiz");
            hero_player->setEnergyPlus(1);
            return;
        }
    }
}

//��ʦ���й�������ײ���
void Battle::attack_wiz_bonus()
{
    log("%f,%f", projectiles_wiz->getPosition().x, projectiles_wiz->getPosition().y);
    for (int i = 0; i < number_npc_; i++) {
        if (hero_npc[i]->getHealth() < 1) {//�����򲻿ɼ�
            if (hero_npc[i]->WhatIam() == 1)
                sword_bonus_npc[i]->setVisible(false);
            hero_npc[i]->setVisible(false);
            weapon_npc[i]->setVisible(false);
            continue;
        }
        Vec2 pos_a = hero_npc[i]->getPosition();
        Vec2 pos_b = projectiles_wiz->getPosition();
        Vec2 d = calculate_distance(pos_a, pos_b);
        if (d.x < 3 && d.y < 5)
        {
            if (light_time == 0)
                //��ȡ��ǰʱ��
                light_time = gettime();
            else
                if (gettime() - light_time < 120)  //���ڹ����������˺���ʱ�������Ϊ120����
                    return;
                else
                    light_time = gettime();
            hero_npc[i]->setHealthPlus(-projectiles_wiz->getDamage());
            log("DAMAGE wiz super");
            return;
        }
    }
}

//��սʿ���й�������ײ���
void Battle::attack_ber()
{
    log("%f,%f", projectile_ber->getPosition().x, projectile_ber->getPosition().y);
    for (int i = 0; i < number_npc_; i++) {
        if (hero_npc[i]->getHealth() < 1) {//�����򲻿ɼ�
            if (hero_npc[i]->WhatIam() == 1)
                sword_bonus_npc[i]->setVisible(false);
            hero_npc[i]->setVisible(false);
            weapon_npc[i]->setVisible(false);
            continue;
        }
        Vec2 pos_a = hero_npc[i]->getPosition();
        Vec2 pos_b = projectile_ber->getPosition();
        Vec2 d = calculate_distance(pos_a, pos_b);
        if (d.x < 1.1 && d.y < 1.1)
        {
            hero_npc[i]->setHealthPlus(-projectile_ber->getDamage());
            log("DAMAGE ber super");
            projectile_ber->removeFromParentAndCleanup(true);
            projectile_ber = nullptr;
            return;
        }
    }
}

//��ѧ��npc��ͨ�ӵ�����ײ���
void Battle::attack_sci_npc()
{
    for (int i = 0; i < number_npc_; i++) {
        if (projectile_sci_npc[i] == nullptr)
            ;
        else
        {
            log("%f,%f", projectile_sci_npc[i]->getPosition().x, projectile_sci_npc[i]->getPosition().y);
            for (int j = 0; j < number_npc_; j++)
            {
                if (j == i)//npc�������Լ�����
                    continue;
                if (hero_npc[j]->getHealth() < 1) {
                    if (hero_npc[j]->WhatIam() == 1)
                        sword_bonus_npc[j]->setVisible(false);
                    hero_npc[j]->setVisible(false);
                    weapon_npc[j]->setVisible(false);
                    continue;
                }
                Vec2 pos_a = hero_npc[j]->getPosition();
                Vec2 pos_b = projectile_sci_npc[i]->getPosition();
                Vec2 d = calculate_distance(pos_a, pos_b);
                if (d.x < 1.1 && d.y < 1.1)
                {
                    hero_npc[j]->setHealthPlus(-projectile_sci_npc[i]->getDamage());
                    hero_npc[i]->setEnergyPlus(1);
                    log("DAMAGE sci npc");
                    projectile_sci_npc[i]->removeFromParentAndCleanup(true);
                    projectile_sci_npc[i] = nullptr;
                    return;
                }
            }
            if (hero_player->getHealth() < 1) {
                if (hero_player->WhatIam() == 1)
                    sword_bonus->setVisible(false);
                hero_player->setVisible(false);
                weapon_player->setVisible(false);
                continue;
            }
            Vec2 pos_a = hero_player->getPosition();
            Vec2 pos_b = projectile_sci_npc[i]->getPosition();
            Vec2 d = calculate_distance(pos_a, pos_b);
            if (d.x < 1.1 && d.y < 1.1)
            {
                hero_player->setHealthPlus(-projectile_sci_npc[i]->getDamage());
                hero_npc[i]->setEnergyPlus(1);
                log("DAMAGE sci npc");
                projectile_sci_npc[i]->removeFromParentAndCleanup(true);
                projectile_sci_npc[i] = nullptr;
                return;
            }
        }
    }
}


//��ѧ��npc�����ӵ�����ײ���
void Battle::attack_sci_bonus_npc(BulletBonus* projectiles, int m)
{
    if (projectiles == nullptr)
        return;
    else
    {
        log("%f,%f", projectiles->getPosition().x, projectiles->getPosition().y);
        for (int i = 0; i < number_npc_; i++) {
            if (i == m)
                continue;
            if (hero_npc[i]->getHealth() < 1) {
                if (hero_npc[i]->WhatIam() == 1)
                    sword_bonus_npc[i]->setVisible(false);
                hero_npc[i]->setVisible(false);
                weapon_npc[i]->setVisible(false);
                continue;
            }
            Vec2 pos_a = hero_npc[i]->getPosition();
            Vec2 pos_b = projectiles->getPosition();
            Vec2 d = calculate_distance(pos_a, pos_b);
            if (d.x < 1.1 && d.y < 1.1)
            {
                hero_npc[i]->setHealthPlus(-projectiles->getDamage());
                log("DAMAGE sci super npc");
                projectiles->removeFromParentAndCleanup(true);
                projectiles = nullptr;
                return;
            }
        }
        if (hero_player->getHealth() < 1) {
            if (hero_player->WhatIam() == 1)
                sword_bonus->setVisible(false);
            hero_player->setVisible(false);
            weapon_player->setVisible(false);
            return;
        }
        Vec2 pos_a = hero_player->getPosition();
        Vec2 pos_b = projectiles->getPosition();
        Vec2 d = calculate_distance(pos_a, pos_b);
        if (d.x < 1.1 && d.y < 1.1)
        {
            hero_player->setHealthPlus(-projectiles->getDamage());
            log("DAMAGE sci super npc");
            projectiles->removeFromParentAndCleanup(true);
            projectiles = nullptr;
            return;
        }
    }
}

//��ʦnpc��ͨ�����ʹ��й�������ײ���
void Battle::attack_wiz_npc()
{
    for (int i = 0; i < number_npc_; i++) {
        if (projectile_wiz_npc[i] == nullptr)
            ;
        else
        {
            log("%f,%f", projectile_wiz_npc[i]->getPosition().x, projectile_wiz_npc[i]->getPosition().y);
            for (int j = 0; j < number_npc_; j++)
            {
                if (j == i)//npc�������Լ�����
                    continue;
                if (hero_npc[j]->getHealth() < 1)
                {//�����򲻿ɼ�
                    if (hero_npc[j]->WhatIam() == 1)
                        sword_bonus_npc[j]->setVisible(false);
                    hero_npc[j]->setVisible(false);
                    weapon_npc[j]->setVisible(false);
                    continue;
                }
                Vec2 pos_a = hero_npc[j]->getPosition();
                Vec2 pos_b = projectile_wiz_npc[i]->getPosition();
                Vec2 d = calculate_distance(pos_a, pos_b);
                if (d.x < 1.1 && d.y < 1.1)
                {
                    if (light_time_npc[i] == 0)
                        //��ȡ��ǰʱ��
                        light_time_npc[i] = gettime();
                    else
                        if (gettime() - light_time_npc[i] < 200)  //���ڹ����������˺���ʱ�������Ϊ200����
                            return;
                        else
                            light_time_npc[i] = gettime();
                    hero_npc[j]->setHealthPlus(-projectile_wiz_npc[i]->getDamage());
                    hero_npc[i]->setEnergyPlus(1);
                    log("DAMAGE wiz npc");
                    return;
                }
            }
            if (hero_player->getHealth() < 1) {
                if (hero_player->WhatIam() == 1)
                    sword_bonus->setVisible(false);
                hero_player->setVisible(false);
                weapon_player->setVisible(false);
                continue;
            }
            Vec2 pos_a = hero_player->getPosition();
            Vec2 pos_b = projectile_wiz_npc[i]->getPosition();
            Vec2 d = calculate_distance(pos_a, pos_b);
            if (d.x < 1.1 && d.y < 1.1)
            {
                if (light_time_npc[i] == 0)
                    //��ȡ��ǰʱ��
                    light_time_npc[i] = gettime();
                else
                    if (gettime() - light_time_npc[i] < 120)  //���ڹ����������˺���ʱ�������Ϊ120����
                        return;
                    else
                        light_time_npc[i] = gettime();
                hero_player->setHealthPlus(-projectile_wiz_npc[i]->getDamage());
                hero_npc[i]->setEnergyPlus(1);
                log("DAMAGE wiz npc");
                return;
            }
        }
    }
}

//��սʿnpc���й�������ײ���
void Battle::attack_ber_npc()
{
    for (int i = 0; i < number_npc_; i++) {
        if (projectile_ber_npc[i] == nullptr)
            ;
        else
        {
            log("%f,%f", projectile_ber_npc[i]->getPosition().x, projectile_ber_npc[i]->getPosition().y);
            for (int j = 0; j < number_npc_; j++)
            {
                if (j == i)//npc�������Լ�����
                    continue;
                if (hero_npc[j]->getHealth() < 1) {
                    if (hero_npc[j]->WhatIam() == 1)
                        sword_bonus_npc[j]->setVisible(false);
                    hero_npc[j]->setVisible(false);
                    weapon_npc[j]->setVisible(false);
                    continue;
                }
                Vec2 pos_a = hero_npc[j]->getPosition();
                Vec2 pos_b = projectile_ber_npc[i]->getPosition();
                Vec2 d = calculate_distance(pos_a, pos_b);
                if (d.x < 1.1 && d.y < 1.1)
                {
                    hero_npc[j]->setHealthPlus(-projectile_ber_npc[i]->getDamage());
                    log("DAMAGE ber bonus npc");
                    projectile_ber_npc[i]->removeFromParentAndCleanup(true);
                    projectile_ber_npc[i] = nullptr;
                    return;
                }
            }
            if (hero_player->getHealth() < 1) {
                if (hero_player->WhatIam() == 1)
                    sword_bonus->setVisible(false);
                hero_player->setVisible(false);
                weapon_player->setVisible(false);
                continue;
            }
            Vec2 pos_a = hero_player->getPosition();
            Vec2 pos_b = projectile_ber_npc[i]->getPosition();
            Vec2 d = calculate_distance(pos_a, pos_b);
            if (d.x < 1.1 && d.y < 1.1)
            {
                hero_player->setHealthPlus(-projectile_ber_npc[i]->getDamage());
                log("DAMAGE ber bonus npc");
                projectile_ber_npc[i]->removeFromParentAndCleanup(true);
                projectile_ber_npc[i] = nullptr;
                return;
            }
        }
    }
}


//�ռ��������ӵļ��
void Battle::collect_box()
{
    for (int i = 0; i < BOX_NUM; i++)
    {
        if (boxwhat[i]->isVisible())
        {
            if (hero_player->getHealth() >= 1)
            {
                Vec2 d_player = calculate_distance(hero_player->getPosition(), boxwhat[i]->getPosition());
                if (d_player.x < 1.1 && d_player.y < 1.1)
                {
                    if (boxwhat[i]->isWhat())
                    {
                        hero_player->setHealthPlus(-boxwhat[i]->getDamage());
                        log("Boxwhat Damage!");
                    } else
                    {
                        hero_player->setHealthPlus(boxwhat[i]->getHeal());
                        hero_player->setEnergyPlus(boxwhat[i]->getCharge());
                        log("Boxwhat Reverse!");
                    }
                    boxwhat[i]->setVisible(false);
                    continue;
                }
            }
            Vec2 d_npc[HERO_NPC_NUM];
            for (int j = 0; j < number_npc_; j++)
            {
                if (hero_npc[j]->getHealth() >= 1)
                {
                    d_npc[j] = calculate_distance(hero_npc[j]->getPosition(), boxwhat[i]->getPosition());
                    if (d_npc[j].x < 1.1 && d_npc[j].y < 1.1)
                    {
                        if (boxwhat[i]->isWhat())
                        {
                            hero_npc[j]->setHealthPlus(-boxwhat[i]->getDamage());
                            log("Boxwhat Damage!");
                        } else
                        {
                            hero_npc[j]->setHealthPlus(boxwhat[i]->getHeal());
                            hero_npc[j]->setEnergyPlus(boxwhat[i]->getCharge());
                            log("Boxwhat Reverse!");
                        }
                        boxwhat[i]->setVisible(false);
                    }
                }
            }
        }
        if (boxhealth[i]->isVisible())
        {
            if (hero_player->getHealth() >= 1)
            {
                Vec2 d_player = calculate_distance(hero_player->getPosition(), boxhealth[i]->getPosition());
                if (d_player.x < 1.1 && d_player.y < 1.1)
                {
                    hero_player->setHealthPlus(boxhealth[i]->getHeal());
                    log("Boxhealth!");
                    boxhealth[i]->setVisible(false);
                    continue;
                }
            }
            Vec2 d_npc[HERO_NPC_NUM];
            for (int j = 0; j < number_npc_; j++)
            {
                if (hero_npc[j]->getHealth() >= 1)
                {
                    d_npc[j] = calculate_distance(hero_npc[j]->getPosition(), boxhealth[i]->getPosition());
                    if (d_npc[j].x < 1.1 && d_npc[j].y < 1.1)
                    {
                        hero_npc[j]->setHealthPlus(boxhealth[i]->getHeal());
                        log("Boxhealth!");
                        boxhealth[i]->setVisible(false);
                        continue;
                    }
                }
            }
        }
        if (boxcharge[i]->isVisible())
        {
            if (hero_player->getHealth() >= 1)
            {
                Vec2 d_player = calculate_distance(hero_player->getPosition(), boxcharge[i]->getPosition());
                if (d_player.x < 1.1 && d_player.y < 1.1)
                {
                    hero_player->setEnergyPlus(boxcharge[i]->getCharge());
                    log("Boxcharge!");
                    boxcharge[i]->setVisible(false);
                    continue;
                }
            }
            Vec2 d_npc[HERO_NPC_NUM];
            for (int j = 0; j < number_npc_; j++)
            {
                if (hero_npc[j]->getHealth() >= 1)
                {
                    d_npc[j] = calculate_distance(hero_npc[j]->getPosition(), boxcharge[i]->getPosition());
                    if (d_npc[j].x < 1.1 && d_npc[j].y < 1.1)
                    {
                        hero_npc[j]->setEnergyPlus(boxcharge[i]->getCharge());
                        log("Boxcharge!");
                        boxcharge[i]->setVisible(false);
                        continue;
                    }
                }
            }
        }
        if (boxhell[i]->isVisible())
        {
            if (hero_player->getHealth() >= 1)
            {
                Vec2 d_player = calculate_distance(hero_player->getPosition(), boxhell[i]->getPosition());
                if (d_player.x < 1.1 && d_player.y < 1.1)
                {
                    hero_player->setHealthPlus(-boxhell[i]->getDamage());
                    log("Boxhell!");
                    boxhell[i]->setVisible(false);
                    continue;
                }
            }
            Vec2 d_npc[HERO_NPC_NUM];
            for (int j = 0; j < number_npc_; j++)
            {
                if (hero_npc[j]->getHealth() >= 1)
                {
                    d_npc[j] = calculate_distance(hero_npc[j]->getPosition(), boxhell[i]->getPosition());
                    if (d_npc[j].x < 1.1 && d_npc[j].y < 1.1)
                    {
                        hero_npc[j]->setHealthPlus(-boxhell[i]->getDamage());
                        log("Boxhell!");
                        boxhell[i]->setVisible(false);
                        continue;
                    }
                }
            }
        }
    }
}

//������Ϸ
void Battle::replaceToSettlement() {
    //debug
    //hero_player->setHealthPlus(-100);
    //hero_npc[0]->setHealthPlus(-100);

    int num_npc_alive = 0;
    for (int i = 0; i < number_npc_; i++) {
        if (hero_npc[i]->getHealth() > 0)
            ++num_npc_alive;
    }
    if (hero_player->getHealth() <= 0 || !num_npc_alive) { //������� �� ֻ����Ҵ��
        player_ranking_ = num_npc_alive + 1;
        audio->stopBackgroundMusic();
        auto startMenuScene = Settlement::create();
        //startMenuScene->retain();
        //removeFromParent();
        Director::getInstance()->replaceScene(cocos2d::TransitionSlideInT::create(0.2f, startMenuScene->createScene()));
    }
}
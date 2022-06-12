#ifndef __SETTLEMENT_H__
#define __SETTLEMENT_H__

#include "cocos2d.h"
#include "GameIntefrace.hpp"
#include "AudioEngine.h"
#include "GlobalVars.h"

class Settlement : public cocos2d::Scene
{
public:
    virtual bool init();

    static cocos2d::Scene* createScene();

    // a selector callback
    void menuCloseCallback(Ref* sender);

    // implement the "static create()" method manually
    CREATE_FUNC(Settlement);
};

#endif // __HELLOWORLD_SCENE_H__
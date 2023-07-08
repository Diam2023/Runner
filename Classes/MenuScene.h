//
// Created by 35691 on 7/8/2023.
//

#pragma once
#include "cocos2d.h"

class MenuScene : public cocos2d::Scene
{
    static cocos2d::Scene* createScene();

    virtual bool init();

    void exitCallback(cocos2d::Ref* pSender);

    void startCallback(cocos2d::Ref* pSender);

    void settingCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(MenuScene);
};

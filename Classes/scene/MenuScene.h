//
// Created by 35691 on 7/8/2023.
//

#pragma once
#include "cocos2d.h"

class MenuScene : public cocos2d::Scene
{

  protected:
    cocos2d::Size visibleSize;
  public:
    static cocos2d::Scene* createScene();

    bool init() override;

    void startCallback(cocos2d::Ref* pSender);

    void settingCallback(cocos2d::Ref* pSender);

    void exitCallback(cocos2d::Ref* pSender);

    static MenuScene* create()
    {
        auto* pRet = new (std::nothrow) MenuScene();
        if (pRet && pRet->init())
        {
            pRet->autorelease();
        }
        else
        {
            delete pRet;
            pRet = nullptr;
        }
        return pRet;
    }
};

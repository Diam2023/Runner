//
// Created by 35691 on 7/10/2023.
//
#pragma once


#include "cocos2d.h"



class GameScene : public cocos2d::Scene
{
  public:
    static cocos2d::Scene* createScene();

    bool init() override;

    CREATE_FUNC(GameScene);

};

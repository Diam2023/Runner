//
// Created by 35691 on 7/10/2023.
//

#include "GameScene.h"

#include "cocos/renderer/backend/opengl/ProgramGL.h"
#include "cocos/renderer/backend/opengl/DeviceGL.h"

USING_NS_CC;

cocos2d::Scene* GameScene::createScene()
{
    CCLOGINFO("Create GameScene");
    return GameScene::create();
}

bool GameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    return true;
}

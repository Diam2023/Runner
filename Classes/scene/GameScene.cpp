//
// Created by 35691 on 7/10/2023.
//

#include "GameScene.h"

#include "sprite/MajorRole.h"
#include "utils/ImageAutoPolygon.h"

USING_NS_CC;


const int DRAG_BODYS_TAG = 0x80;

cocos2d::Scene* GameScene::createScene()
{
    CCLOGINFO("Create GameScene");
    return GameScene::create();
}

bool GameScene::init()
{
    if (!Scene::initWithPhysics())
    {
        return false;
    }

    // Open Debug Message
    this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    auto physicsBody_ = PhysicsBody::createBox(Size(400.0f, 1.0f),
                                              PhysicsMaterial(0.1f, 1.0f, 0.0f));
    physicsBody_->setDynamic(false);
    auto drawNode = DrawNode::create();
    drawNode->drawLine(Vec2(1.0f, 1.0f), Vec2(200.0f, 1.0f), Color4F(1.0f, 0.5f, 0, 1));
    drawNode->addComponent(physicsBody_);

    this->addChild(drawNode);
    // PhysicsBody

    auto majorRole = MajorRole::create(0.8f);

    majorRole->setPosition(80, 100);

    this->addChild(majorRole);

    return true;
}

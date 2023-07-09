//
// Created by 35691 on 7/8/2023.
//

#include "MenuScene.h"
#include <string>

using namespace cocos2d;

cocos2d::Scene* MenuScene::createScene()
{
    CCLOGINFO("Create MenuScene");
    return MenuScene::create();
}

bool MenuScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    // visible origin coordinate of the OpenGL view in points.
    auto origin = Director::getInstance()->getVisibleOrigin();
    float offset = 5;


    if (visibleSize.equals(Size::ZERO))
    {
        // ERROR Handle
        const static std::string visibleSizeErrorMessage = "Error VisibleSize!";
        CCLOGERROR("%s", visibleSizeErrorMessage.c_str());
        throw std::runtime_error(visibleSizeErrorMessage);
    }

    // Font
    const static std::string defaultFontFilePath = "fonts/Marker Felt.ttf";

    // Title Label
    auto titleLabel = Label::createWithTTF("Runner", defaultFontFilePath, 48);
    // Menu Label
    auto startLabel = Label::createWithTTF("Start", defaultFontFilePath, 24);
    auto settingLabel = Label::createWithTTF("Setting", defaultFontFilePath, 24);
    auto exitLabel = Label::createWithTTF("Exit", defaultFontFilePath, 24);


    // Create Menu
    auto startMenuItem = MenuItemLabel::create(startLabel, CC_CALLBACK_1(MenuScene::startCallback, this));
    auto settingMenuItem = MenuItemLabel::create(settingLabel, CC_CALLBACK_1(MenuScene::settingCallback, this));
    auto exitMenuItem = MenuItemLabel::create(exitLabel, CC_CALLBACK_1(MenuScene::exitCallback, this));

    startMenuItem->setPosition(0, settingMenuItem->getContentSize().height + offset);

    exitMenuItem->setPosition(0, -1 * settingMenuItem->getContentSize().height - offset);

    Vector<MenuItem*> menuItems;
    menuItems.pushBack(startMenuItem);
    menuItems.pushBack(settingMenuItem);
    menuItems.pushBack(exitMenuItem);

    // startMenuItem->setPosition()
    // Menu
    auto menu = Menu::createWithArray(menuItems);

    // Set to start position
    titleLabel->setPosition(menu->getPosition().x, visibleSize.height - titleLabel->getContentSize().height - offset);

    this->addChild(titleLabel);

    this->addChild(menu, 1);

    return true;
}

void MenuScene::startCallback(cocos2d::Ref* pSender)
{

    CCLOGINFO("MenuScene Exit");

    // Lunch GameScene
    // Director::getInstance()->replaceScene()
}

void MenuScene::settingCallback(cocos2d::Ref* pSender)
{
    // TODO 2023 0708
}

void MenuScene::exitCallback(cocos2d::Ref* pSender)
{

    CCLOGINFO("MenuScene Exit");
    Director::getInstance()->end();
}
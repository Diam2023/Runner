//
// Created by 35691 on 7/14/2023.
//

#include "MajorRole.h"
#include "common.h"
#include "utils/ImageAutoPolygon.h"

USING_NS_CC;

MajorRole* MajorRole::create(float sizeRatio)
{
    auto texture = new (std::nothrow) Texture2D();
    texture->initWithString("我",
                            app::fonts::FounderFont,
                            DefaultSize * sizeRatio);
    auto tempSprite = new (std::nothrow) Sprite();
    if (!tempSprite->initWithTexture(texture))
    {
        CCLOGERROR("Error Initialize Temp!!!");
        return nullptr;
    }
    tempSprite->autorelease();
    auto role = new MajorRole();
    role->setSizeRatio(sizeRatio);

    auto tmpSprite =
        Sprite::createWithSpriteFrame(tempSprite->getSpriteFrame());
    tmpSprite->setAnchorPoint(Vec2::ZERO);
    RenderTexture* pRender = RenderTexture::create(
        static_cast<int>(tmpSprite->getContentSize().width),
        static_cast<int>(tmpSprite->getContentSize().height),
        backend::PixelFormat::RGBA8888);

    pRender->setSprite(tmpSprite);
    pRender->begin();
    tmpSprite->visit();
    pRender->end();

    role->initWithTexture(texture);

//    auto command = new CallbackCommand();
//    command->init(pRender->getGlobalZOrder());
//    command->func = [pRender, role]() {
//        auto callbackFunc = [role](Image* image) {
//            if (image)
//            {
//                auto polygon = ImageAutoPolygon::generatePolygon(image);
//                role->setPolygonInfo(polygon);
//                role->updatePoly();
//                role->setVisible(true);
//            }
//            CC_SAFE_DELETE(image);
//        };
//        pRender->newImage(callbackFunc);
//    };
//    Director::getInstance()->getRenderer()->addCommand(command);

//    {
//        RenderTexture* pRender = RenderTexture::create(
//            static_cast<int>(tmpSprite->getContentSize().width),
//            static_cast<int>(tmpSprite->getContentSize().height),
//            backend::PixelFormat::RGBA8888);
//
////        pRender->setSprite(tmpSprite);
//        pRender->begin();
//        tmpSprite->visit();
//        pRender->end();
//
        pRender->createNewImage([role](Image* image) {
            auto polygon = ImageAutoPolygon::generatePolygon(image);
            role->initWithPolygon(polygon);
            // role->updatePoly();
            role->setVisible(true);

        });
//    }

    //    pRender->saveToFile(
    //        "abss.png",
    //        true,
    //        [role](RenderTexture* texture, const std::string& file) {
    //            auto info = AutoPolygon::generatePolygon(file);
    //            // First Thing Is Initialize With Info
    //            if (!role->initWithFile(file))
    //            {
    //                CCLOGERROR("Error Initialize Role!!!");
    //                return;
    //            }
    //
    //            role->setPolygonInfo(info);
    //            role->updatePoly();
    //
    //            auto triangles = info.triangles;
    //            auto points = new Vec2[triangles.indexCount];
    //            for (uint32_t i = 0; i < triangles.indexCount; ++i)
    //            {
    //                points[i].x =
    //                triangles.verts[triangles.indices[i]].vertices.x -
    //                              role->getContentSize().width / 2;
    //                points[i].y =
    //                triangles.verts[triangles.indices[i]].vertices.y -
    //                              role->getContentSize().height / 2;
    //            }
    //
    //            //            auto body = PhysicsBody::createPolygon(points,
    //            // static_cast<int>(
    //            // triangles.indexCount));
    //            //            role->setPhysicsBody(body);
    //            role->setVisible(true);
    //            delete[] points;
    //        });

    //    ImageAutoPolygon::generatePolygon(
    //        [role](cocos2d::PolygonInfo info) {
    //
    //            // First Thing Is Initialize With Info
    //            if (!role->initWithPolygon(info))
    //            {
    //                CCLOGERROR("Error Initialize Role!!!");
    //                return;
    //            }
    //
    //            auto triangles = info.triangles;
    //            auto points = new Vec2[triangles.indexCount];
    //            for (uint32_t i = 0; i < triangles.indexCount; ++i)
    //            {
    //                points[i].x =
    //                triangles.verts[triangles.indices[i]].vertices.x -
    //                              role->getContentSize().width / 2;
    //                points[i].y =
    //                triangles.verts[triangles.indices[i]].vertices.y -
    //                              role->getContentSize().height / 2;
    //            }
    //
    //            auto body = PhysicsBody::createPolygon(points,
    //                                                   static_cast<int>(
    //                                                       triangles.indexCount));
    //            role->setPhysicsBody(body);
    //            role->setVisible(true);
    //            delete[] points;
    //        },
    //        tempSprite);
    role->setVisible(false);
    role->autorelease();
    return role;
}

MajorRole::MajorRole() : sizeRatio(1)
{
}

MajorRole::~MajorRole()
{
    CCLOGINFO("Destroy MajorRole");
}

float MajorRole::getSizeRatio() const
{
    return sizeRatio;
}

void MajorRole::setSizeRatio(float sizeRatio)
{
    MajorRole::sizeRatio = sizeRatio;
}

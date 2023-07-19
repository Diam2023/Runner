//
// Created by 35691 on 7/14/2023.
//

#include "MajorRole.h"
#include "common.h"
#include "utils/ImageAutoPolygon.h"
#include "renderer/CCTexture2D.h"

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
    //! TODO Do not use This in Debug Draw Sprite
    tmpSprite->visit();
    pRender->end();

    role->initWithTexture(texture);

    pRender->createNewImage([role](Image* image) {
        auto polygonInfo = ImageAutoPolygon::generatePolygon(image);

        // TODO Rewrite This Code For Support PolygonSprite Bug
        // First Thing Is Initialize With Info
        //         role->setPolygonInfo(polygonInfo);
        //        role->updatePoly();
        // TODO Rewrite initWithPolygon!!!
        //        if (!role->initWithPolygon(polygonInfo))
        //        {
        //            CCLOGERROR("Error Initialize Role!!!");
        //            return;
        //        }

        auto triangles = polygonInfo.triangles;
        auto points = new Vec2[triangles.indexCount];
        for (uint32_t i = 0; i < triangles.indexCount; ++i)
        {
            points[i].x = triangles.verts[triangles.indices[i]].vertices.x -
                          role->getContentSize().width / 2;
            points[i].y = triangles.verts[triangles.indices[i]].vertices.y -
                          role->getContentSize().height / 2;
        }

        // Create A PhysicsBody
        auto body =
            PhysicsBody::createPolygon(points,
                                       static_cast<int>(triangles.indexCount));
        role->setPhysicsBody(body);
        role->setVisible(true);
        delete[] points;
        CC_SAFE_DELETE(image);
    });

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

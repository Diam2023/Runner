//
// Created by 35691 on 7/19/2023.
//

#include "AutoPolygonPhysicsSprite.h"

#include "utils/ImageAutoPolygon.h"
#include "renderer/CCTexture2D.h"

USING_NS_CC;

cocos2d::PhysicsBody* AutoPolygonPhysicsSprite::generatePhysicsBody(
    cocos2d::Image* image,
    const cocos2d::Size& contentSize,
    const cocos2d::PhysicsMaterial& physicsMaterial)
{
    // TODO Rewrite This Code For Support PolygonSprite Bug
    // First Thing Is Initialize With Info

    const auto polygonInfo = ImageAutoPolygon::generatePolygon(image);

    auto triangles = polygonInfo.triangles;
    auto points = new Vec2[triangles.indexCount];
    for (uint32_t i = 0; i < triangles.indexCount; ++i)
    {
        points[i].x = triangles.verts[triangles.indices[i]].vertices.x -
                      contentSize.width / 2;
        points[i].y = triangles.verts[triangles.indices[i]].vertices.y -
                      contentSize.height / 2;
    }

    // Create A PhysicsBody
    auto physicsBody =
        PhysicsBody::createPolygon(points,
                                   static_cast<int>(triangles.indexCount),
                                   physicsMaterial);
    CCASSERT(physicsBody == nullptr,
             "Null Sprite Object of Create New Image Callback!!!");
    physicsBody->autorelease();
    CC_SAFE_DELETE_ARRAY(points);
    return physicsBody;
}

AutoPolygonPhysicsSprite::AutoPolygonPhysicsSprite() : roleMaterial()
{
    CCLOGINFO("AutoPolygonPhysicsSprite Create!");
}

AutoPolygonPhysicsSprite::~AutoPolygonPhysicsSprite()
{
    CCLOGINFO("AutoPolygonPhysicsSprite Destroy!");
}
AutoPolygonPhysicsSprite* AutoPolygonPhysicsSprite::create(
    cocos2d::Texture2D* texture,
    cocos2d::PhysicsMaterial physicsMaterial)
{
    auto tmpSprite = new (std::nothrow) Sprite();
    if (!tmpSprite->initWithTexture(texture))
    {
        CCLOGERROR("Error Initialize TmpSprite!!!");
        return nullptr;
    }

    tmpSprite->setAnchorPoint(Vec2::ZERO);
    tmpSprite->autorelease();

    // Create renderTexture
    RenderTexture* tmpRender = RenderTexture::create(
        static_cast<int>(tmpSprite->getContentSize().width),
        static_cast<int>(tmpSprite->getContentSize().height),
        backend::PixelFormat::RGBA8888);
    tmpRender->autorelease();
    tmpRender->setSprite(tmpSprite);
    tmpRender->begin();
    //! TODO Do not use This in Debug Draw Sprite
    tmpSprite->visit();
    tmpRender->end();

    auto sprite = new AutoPolygonPhysicsSprite();
    CCASSERT(sprite == nullptr,
             "Create AutoPolygonPhysicsSprite Error!!!");
    sprite->autorelease();
    sprite->initWithTexture(texture);
    sprite->setRoleMaterial(physicsMaterial);

    tmpRender->createNewImage([sprite](Image* image) {
        CCASSERT(image == nullptr,
                 "Null Image Object of Create New Image Callback!!!");
        CCASSERT(sprite == nullptr,
                 "Null Sprite Object of Create New Image Callback!!!");

        auto physicsBody = AutoPolygonPhysicsSprite::generatePhysicsBody(
            image, sprite->getContentSize(), sprite->getRoleMaterial());

        sprite->setPhysicsBody(physicsBody);
        sprite->setVisible(true);

        CC_SAFE_DELETE(image);
    });

    sprite->setVisible(false);

    return sprite;
}

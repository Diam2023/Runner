//
// Created by 35691 on 7/14/2023.
//

#include "MajorRole.h"
#include "renderer/CCTexture2D.h"
#include "AutoPolygonPhysicsSprite.h"
#include "physics/CCPhysicsShape.h"

#include "common.h"

USING_NS_CC;

MajorRole* MajorRole::create(float sizeRatio, PhysicsMaterial roleMaterial)
{
    auto texture = new (std::nothrow) Texture2D();
    texture->initWithString("我",
                            app::fonts::FounderFont,
                            DefaultSize * sizeRatio);
    auto role = new MajorRole();
    CCASSERT(role != nullptr, "Role Is Null!!!");
    role->autorelease();

    role->setRatioSize(sizeRatio);
    role->setRoleMaterial(roleMaterial);
    role->init(texture);

    return role;
}

MajorRole::MajorRole() : AutoPolygonPhysicsSprite(), ratioSize(1)
{
    CCLOGINFO("Create MajorRole");
}

MajorRole::~MajorRole()
{
    CCLOGINFO("Destroy MajorRole");
}

float MajorRole::getRatioSize() const
{
    return ratioSize;
}

void MajorRole::setRatioSize(float ratioSize_)
{
    MajorRole::ratioSize = ratioSize_;
}

bool MajorRole::updateRoleMaterial()
{
    auto physicsBody = this->getPhysicsBody();

    if (physicsBody == nullptr)
    {
        return false;
    }
    return true;
}

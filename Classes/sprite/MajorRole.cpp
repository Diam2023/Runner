//
// Created by 35691 on 7/14/2023.
//

#include "MajorRole.h"
#include "common.h"

USING_NS_CC;


MajorRole* MajorRole::create(float sizeRatio)
{
    auto texture = new (std::nothrow) Texture2D();

    texture->initWithString("我",
                            app::fonts::FounderFont,
                            DefaultSize * sizeRatio);

    auto role = new (std::nothrow) MajorRole();

    role->setSizeRatio(sizeRatio);

    CCASSERT(role != nullptr, "Error new Role!!!");

    if (!role->initWithTexture(texture))
    {
        CCLOGERROR("Error Initialize Role!!!");
        return nullptr;
    }

    role->autorelease();
    CC_SAFE_DELETE(texture);

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

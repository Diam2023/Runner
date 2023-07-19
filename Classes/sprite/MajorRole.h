//
// Created by 35691 on 7/14/2023.
//
#pragma once

#include "AutoPolygonPhysicsSprite.h"

class MajorRole final : public AutoPolygonPhysicsSprite
{
  protected:
    /**
     * Ratio of Role size
     */
    float ratioSize;

    float getRatioSize() const;
    void setRatioSize(float);

  public:
    /**
     * Default Of Font Size
     */
    constexpr static const float DefaultSize = 50;

    MajorRole();
    ~MajorRole() override;

    /**
     * Create A Major Role
     * @param sizeRatio
     * @param roleMaterial
     * @return
     */
    static MajorRole* create(float sizeRatio = 1,
                             cocos2d::PhysicsMaterial roleMaterial =
                                 cocos2d::PHYSICSBODY_MATERIAL_DEFAULT);

    /**
     * update RoleMaterial
     * @return
     */
    bool updateRoleMaterial();
};

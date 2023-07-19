//
// Created by 35691 on 7/14/2023.
//
#pragma once

#include "cocos2d.h"

#include <string>

class MajorRole final : public cocos2d::Sprite
{
  protected:

    /**
     * Ratio of Role size
     */
    float sizeRatio;

    /**
     * Role Material
     */
    cocos2d::PhysicsMaterial roleMaterial;
  public:
    // get And Setter
    const cocos2d::PhysicsMaterial& getRoleMaterial() const;
    void setRoleMaterial(const cocos2d::PhysicsMaterial&);

    float getSizeRatio() const;
    void setSizeRatio(float);

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
    static MajorRole* create(float sizeRatio = 1, cocos2d::PhysicsMaterial roleMaterial = cocos2d::PHYSICSBODY_MATERIAL_DEFAULT);

    /**
     * update RoleMaterial
     * @return
     */
    bool updateRoleMaterial();
};

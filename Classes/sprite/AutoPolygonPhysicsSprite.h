//
// Created by 35691 on 7/19/2023.
//

#pragma once

#include "cocos2d.h"

class AutoPolygonPhysicsSprite : public cocos2d::Sprite
{
  protected:
    /**
     * Sprite Material
     */
    cocos2d::PhysicsMaterial roleMaterial;

  public:
    const cocos2d::PhysicsMaterial& getRoleMaterial() const
    {
        return roleMaterial;
    }
    void setRoleMaterial(const cocos2d::PhysicsMaterial& roleMaterial_)
    {
        AutoPolygonPhysicsSprite::roleMaterial = roleMaterial_;
    }

  public:
    /**
     * Use Maltreat construct
     */
    explicit AutoPolygonPhysicsSprite(
        cocos2d::PhysicsMaterial roleMaterial =
            cocos2d::PHYSICSBODY_MATERIAL_DEFAULT);

    ~AutoPolygonPhysicsSprite() override;

    /**
     * init AutoPolygonPhysicsSprite With texture
     * @param texture texture of Sprite
     */
    void init(cocos2d::Texture2D* texture);

    //    /**
    //     * Create A AutoPolygonPhysicsSprite With texture and physicsMaterial
    //     * @tparam T_ Drive Of AutoPolygonPhysicsSprite
    //     * @param texture texture of Sprite
    //     * @param physicsMaterial physicsMaterial For PhysicsBody
    //     * @return A new Auto Relase AutoPolygonPhysicsSprite Instance
    //     */
    //    template <typename T_>
    //    static T_* create(cocos2d::Texture2D *texture,
    //    cocos2d::PhysicsMaterial physicsMaterial =
    //    cocos2d::PHYSICSBODY_MATERIAL_DEFAULT);

    /**
     * Create A PhysicsBody With Auto Split Polygon
     * @param image image
     * @param contentSize size of sprite
     * @param physicsMaterial material
     * @return A auto release PhysicsBody Instance
     */
    static cocos2d::PhysicsBody* generatePhysicsBody(
        cocos2d::Image* image,
        const cocos2d::Size& contentSize,
        const cocos2d::PhysicsMaterial& physicsMaterial);
};

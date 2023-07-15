//
// Created by 35691 on 7/14/2023.
//
#pragma once

#include "cocos2d.h"

#include <string>

class MajorRole final : public cocos2d::Sprite
{
  private:

    /**
     * ratio of my size
     */
    float sizeRatio;

  public:
    float getSizeRatio() const;
    void setSizeRatio(float sizeRatio);

  public:
    /**
     * Default Of Font Size
     */
    constexpr static const float DefaultSize = 50;

    MajorRole();
    ~MajorRole() override;

    static MajorRole* create(float sizeRatio = 1);
};

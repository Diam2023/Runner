//
// Created by 35691 on 7/16/2023.
//
#pragma once

#include "cocos2d.h"

/**
 * 原版AutoPolygon不能使用Sprite或者Image創建，這裏提供Image與Sprite轉換
 * 將Sprite
 */
class ImageAutoPolygon
{
  public:

    ImageAutoPolygon();
    explicit ImageAutoPolygon(cocos2d::Image* image);

    ~ImageAutoPolygon() = default;

    void init(cocos2d::Image* image);

    /**
     * trace all the points along the outline of the image,
     * @warning must create AutoPolygon with filename to use this function
     * @param   rect    a texture rect for specify an area of the image
     * @param   threshold   the value when alpha is greater than this value will
     * be counted as opaque, default to 0.0
     * @return  a vector of vec2 of all the points found in clockwise order
     * @code
     * auto ap = AutoPolygon("grossini.png");
     * auto rect = Rect(100, 100, 200, 200);
     * std::vector<Vec2> points = ap.trace(rect);//default threshold is 0.0
     * @endcode
     */
    std::vector<cocos2d::Vec2> trace(const cocos2d::Rect& rect,
                                     float threshold = 0.0f);

    /**
     * reduce the amount of points so its faster for GPU to process and draw
     * based on Ramer-Douglas-Peucker algorithm
     * @param   points  a vector of Vec2 points as input
     * @param   rect    a texture rect for specify an area of the image to avoid
     * over reduction
     * @param   epsilon the perpendicular distance where points smaller than
     * this value will be discarded
     * @return  a vector of Vec2 of the remaining points in clockwise order
     * @code
     * auto ap = AutoPolygon();
     * std::vector<Vec2> reduced = ap.reduce(inputPoints, rect);//default
     * epsilon is 2
     * @endcode
     */
    std::vector<cocos2d::Vec2> reduce(const std::vector<cocos2d::Vec2>& points,
                                      const cocos2d::Rect& rect,
                                      float epsilon = 2.0f);

    /**
     * expand the points along their edge, useful after you reduce the points
     * that cuts into the sprite using ClipperLib
     * @param   points  a vector of Vec2 points as input
     * @param   rect    a texture rect for specify an area of the image, the
     * expanded points will be clamped in this rect, ultimately resulting in a
     * quad if the expansion is too great
     * @param   epsilon the distance which the edges will expand
     * @return  a vector of Vec2 as the result of the expansion
     * @code
     * auto ap = AutoPolygon();
     * std::vector<Vec2> expanded = ap.expand(inputPoints, rect, 2.0);
     * @endcode
     */
    std::vector<cocos2d::Vec2> expand(const std::vector<cocos2d::Vec2>& points,
                                      const cocos2d::Rect& rect,
                                      float epsilon);

    /**
     * Triangulate the input points into triangles for rendering
     * using poly2tri
     * @warning points must be closed loop, cannot have 2 points sharing the
     * same position and cannot intersect itself
     * @param   points  a vector of vec2 points as input
     * @return  a Triangles object with points and indices
     * @code
     * auto ap = AutoPolygon();
     * TrianglesCommand::Triangles myPolygons = ap.triangulate(myPoints);
     * @endcode
     */
    cocos2d::TrianglesCommand::Triangles triangulate(
        const std::vector<cocos2d::Vec2>& points);

    /**
     * calculate the UV coordinates for each points based on a texture rect
     * @warning This method requires the AutoPolygon object to know the texture
     * file dimension
     * @param   rect    a texture rect to specify where to map the UV
     * @param   verts   a pointer to the verts array, served both as input and
     * output verts
     * @param   count   the count for the verts array
     * @code
     * auto ap = AutoPolygon("grossini.png");
     * TrianglesCommand::Triangles myPolygons = ap.triangulate(myPoints);
     * ap.calculateUV(rect, myPolygons.verts, 20);
     * @endcode
     */
    void calculateUV(const cocos2d::Rect& rect,
                     cocos2d::V3F_C4B_T2F* verts,
                     ssize_t count);

    /**
     * a helper function, packing trace, reduce, expand, triangulate and
     * calculate uv in one function
     * @param   rect    texture rect, use Rect::ZERO for the size of the
     * texture, default is Rect::ZERO
     * @param   epsilon the value used to reduce and expand, default to 2.0
     * @param   threshold   the value where bigger than the threshold will be
     * counted as opaque, used in trace
     * @return  a PolygonInfo, to use with sprite
     * @code
     * auto ap = AutoPolygon("grossini.png");
     * PolygonInfo myInfo = ap.generateTriangles();//use all default values
     * auto sp1 = Sprite::create(myInfo);
     * polygonInfo myInfo2 = ap.generateTriangles(Rect::ZERO, 5.0, 0.1);//ap can
     * be reused to generate another set of PolygonInfo with different settings
     * auto sp2 = Sprite::create(myInfo2);
     * @endcode
     */
    cocos2d::PolygonInfo generateTriangles(
        const cocos2d::Rect& rect = cocos2d::Rect::ZERO,
        float epsilon = 2.0f,
        float threshold = 0.05f);

    /**
     * a helper function, packing autoPolygon creation, trace, reduce, expand,
     * triangulate and calculate uv in one function
     * @warning if you want to repetitively generate polygons, consider create
     * an AutoPolygon object, and use generateTriangles function, as it only
     * reads the file once
     * @param   filename     A path to image file, e.g., "scene1/monster.png".
     * @param   rect    texture rect, use Rect::ZERO for the size of the
     * texture, default is Rect::ZERO
     * @param   epsilon the value used to reduce and expand, default to 2.0
     * @param   threshold   the value where bigger than the threshold will be
     * counted as opaque, used in trace
     * @return  a PolygonInfo, to use with sprite
     * @code
     * auto sp = Sprite::create(AutoPolygon::generatePolygon("grossini.png"));
     * @endcode
     */
    //    static cocos2d::PolygonInfo generatePolygon(const std::string&
    //    filename, const cocos2d::Rect& rect = cocos2d::Rect::ZERO, float
    //    epsilon = 2.0f, float threshold = 0.05f);
    static cocos2d::PolygonInfo generatePolygon(
        cocos2d::Image* image,
        const cocos2d::Rect& rect = cocos2d::Rect::ZERO,
        float epsilon = 2.0f,
        float threshold = 0.05f);

    static void generatePolygon(
        std::function<void(cocos2d::PolygonInfo)> callback,
        cocos2d::Sprite* sprite,
        const cocos2d::Rect& rect = cocos2d::Rect::ZERO,
        float epsilon = 2.0f,
        float threshold = 0.05f);

  protected:
    cocos2d::Vec2 findFirstNoneTransparentPixel(const cocos2d::Rect& rect,
                                                float threshold);
    std::vector<cocos2d::Vec2> marchSquare(const cocos2d::Rect& rect,
                                           const cocos2d::Vec2& first,
                                           float threshold);
    unsigned int getSquareValue(unsigned int x,
                                unsigned int y,
                                const cocos2d::Rect& rect,
                                float threshold);

    unsigned char getAlphaByIndex(unsigned int i);
    unsigned char getAlphaByPos(const cocos2d::Vec2& pos);

    [[nodiscard]] int getIndexFromPos(unsigned int x, unsigned int y) const
    {
        return y * _width + x;
    }

    [[nodiscard]] cocos2d::Vec2 getPosFromIndex(unsigned int i) const
    {
        return {static_cast<float>(i % _width), static_cast<float>(i / _width)};
    }

    std::vector<cocos2d::Vec2> rdp(const std::vector<cocos2d::Vec2>& v,
                                   float optimization);
    float perpendicularDistance(const cocos2d::Vec2& i,
                                const cocos2d::Vec2& start,
                                const cocos2d::Vec2& end);

    // real rect is the size that is in scale with the texture file
    cocos2d::Rect getRealRect(const cocos2d::Rect& rect);

    cocos2d::Image* _image;
    unsigned char* _data;
    unsigned int _width;
    unsigned int _height;
    float _scaleFactor;
    unsigned int _threshold{};
};

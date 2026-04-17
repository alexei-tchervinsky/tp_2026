//
//  framerectangle.hpp
//  OOP
//
//  Created by Тимур Ахметханов on 21.12.2024.
//

#ifndef FRAMERECTANGLE_HPP
#define FRAMERECTANGLE_HPP

#include "point.hpp"

class FrameRectangle {
public:
    FrameRectangle(float width, float height, const Point& pos);
    float getWidth() const;
    float getHeight() const;
    Point getPos() const;

private:
    float width_;
    float height_;
    Point pos_;
};

#endif

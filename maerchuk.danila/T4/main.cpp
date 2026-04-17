//
//  main.cpp
//  OOP
//
//  Created by Тимур Ахметханов on 21.12.2024.
//

#include "shape.hpp"
#include "circle.hpp"
#include "square.hpp"
#include <iostream>
#include <iomanip>


void PrintShapeInfo(const Shape& shape) {
    std::string name = shape.getName();
    float area = shape.getArea();
    FrameRectangle frame = shape.getFrameRectangle();

    Point topLeft = frame.getPos();
    float width = frame.getWidth();
    float height = frame.getHeight();

    float left = topLeft.getX();
    float bottom = topLeft.getY() - height;
    float right = topLeft.getX() + width;
    float top = topLeft.getY();

    std::cout << std::fixed << std::setprecision(1);
    std::cout << name << " " << area << " " << left << " " << bottom << " " << right << " " << top << std::endl;
}



int main() {
    // insert code here...
    std::cout << "Hello, World!\n";

    Point circleCenter(2.0f, 3.0f);
    Circle circle(circleCenter, 5.0f);
    PrintShapeInfo(circle);

    Point squareCenter(1.0f, 1.0f);
    Square square(squareCenter, 4.0f);
    PrintShapeInfo(square);

    return 0;
}

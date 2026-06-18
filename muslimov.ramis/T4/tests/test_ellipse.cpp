#include <gtest/gtest.h>
#include "../include/ellipse.hpp"

constexpr double EPS = 1e-9;
constexpr double PI = 3.14159265358979323846;

TEST(EllipseTest, ConstructAndArea) {
    Ellipse e({1.0, 2.0}, 2.0, 1.0); // ry, rx
    EXPECT_NEAR(e.getArea(), PI * 2.0 * 1.0, EPS);
    Point c = e.getCenter();
    EXPECT_NEAR(c.x, 1.0, EPS);
    EXPECT_NEAR(c.y, 2.0, EPS);
}

TEST(EllipseTest, MoveAndScale) {
    Ellipse e({0,0}, 1.0, 1.0);
    e.move(2.0, 3.0);
    Point c = e.getCenter();
    EXPECT_NEAR(c.x, 2.0, EPS);
    EXPECT_NEAR(c.y, 3.0, EPS);

    e.scale(3.0);
    EXPECT_NEAR(e.getArea(), PI * 3.0 * 3.0, EPS); // area scaled by s^2
}

TEST(EllipseTest, InvalidRadii) {
    EXPECT_THROW(Ellipse({0,0}, 0.0, 1.0), std::invalid_argument);
    EXPECT_THROW(Ellipse({0,0}, 1e-13, 1e-13), std::invalid_argument);
}

// //Намеренная утечка, для проверки санитайзеров
// TEST(LeakMemmoryAddress, LeakMemmoryAddress){
//      int* p = new int(42);
//      (void)p;
// }

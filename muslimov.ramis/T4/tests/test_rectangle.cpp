// #include <gtest/gtest.h>
// #include "../include/rectangle.hpp"

// constexpr double EPS = 1e-9;

// TEST(RectangleTest, ConstructAndAccessors) {
//     Rectangle r({0.0, 0.0}, {4.0, 3.0});
//     EXPECT_NEAR(r.getArea(), 12.0, EPS);
//     Point c = r.getCenter();
//     EXPECT_NEAR(c.x, 2.0, EPS);
//     EXPECT_NEAR(c.y, 1.5, EPS);

//     double l,b,ri,t;
//     r.getBoundingBox(l,b,ri,t);
//     EXPECT_NEAR(l, 0.0, EPS);
//     EXPECT_NEAR(b, 0.0, EPS);
//     EXPECT_NEAR(ri, 4.0, EPS);
//     EXPECT_NEAR(t, 3.0, EPS);
// }

// TEST(RectangleTest, MoveAndScale) {
//     Rectangle r({0.0,0.0},{2.0,1.0});
//     r.move(1.0, 2.0);
//     Point c = r.getCenter();
//     EXPECT_NEAR(c.x, 2.0, EPS);
//     EXPECT_NEAR(c.y, 2.5, EPS);

//     r.scale(2.0);
//     EXPECT_NEAR(r.getWidth(), 4.0, EPS);
//     EXPECT_NEAR(r.getHeight(), 2.0, EPS);
//     EXPECT_NEAR(r.getArea(), 8.0, EPS);
// }

// TEST(RectangleTest, InvalidCorners) {
//     EXPECT_THROW(Rectangle({0,0},{0,0}), std::invalid_argument);
//     EXPECT_THROW(Rectangle({0,0},{1e-13, 1e-13}), std::invalid_argument); // если EPS используется
// }

// TEST(RectangleTest, ScaleInvalidFactor) {
//     Rectangle r({0,0},{2,1});
//     EXPECT_THROW(r.scale(0.0), std::invalid_argument);
//     EXPECT_THROW(r.scale(std::numeric_limits<double>::quiet_NaN()), std::invalid_argument);
// }

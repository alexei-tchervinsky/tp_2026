// #include <gtest/gtest.h>
// #include "../include/compositeShape.hpp"
// #include "../include/rectangle.hpp"
// #include "../include/ellipse.hpp"

// constexpr double EPS = 1e-9;

// TEST(CompositeTest, AddAndAreaAndCenter) {
//     CompositeShape comp;
//     comp.add(std::make_unique<Rectangle>(Point{0,0}, Point{2,1}));
// area 2
//     comp.add(std::make_unique<Ellipse>(Point{4,0}, 1.0, 0.5));
// area ~ PI*1*0.5

//     double expectedArea = 2.0 + 3.14159265358979323846 * 1.0 * 0.5;
//     EXPECT_NEAR(comp.getArea(), expectedArea, 1e-6);

//     double l,b,r,t;
//     comp.getBoundingBox(l,b,r,t);
//     Point center = comp.getCenter();
//     EXPECT_NEAR(center.x, (l + r) / 2.0, EPS);
//     EXPECT_NEAR(center.y, (b + t) / 2.0, EPS);
// }

// TEST(CompositeTest, ScaleMovesChildrenAndScalesThem) {
//     CompositeShape comp;
//     comp.add(std::make_unique<Rectangle>(Point{10.0,10.0},
//Point{12.0,11.0}));
//     comp.add(std::make_unique<Ellipse>(Point{13.0,10.5}, 0.8, 0.6));

//     Point beforeCenter = comp.getCenter();
//     // save child centers and areas
//     const auto &children = comp.components();
//     std::vector<Point> centers;
//     std::vector<double> areas;
//     for (const auto &c : children) {
//         centers.push_back(c->getCenter());
//         areas.push_back(c->getArea());
//     }

//     comp.scale(2.0);

//     // areas multiplied by 4
//     for (std::size_t i = 0; i < children.size(); ++i) {
//         EXPECT_NEAR(children[i]->getArea(),
//areas[i] * 4.0, 1e-6);
//     }

//     // centers moved away from composite center by factor 2
//     Point newCenter = comp.getCenter();
//     EXPECT_NEAR(newCenter.x, beforeCenter.x, EPS);
//     EXPECT_NEAR(newCenter.y, beforeCenter.y, EPS);

//     for (std::size_t i = 0; i < children.size(); ++i) {
//         Point oldC = centers[i];
//         Point curC = children[i]->getCenter();
//         double vx_old = oldC.x - beforeCenter.x;
//         double vx_new = curC.x - beforeCenter.x;
//         EXPECT_NEAR(vx_new, vx_old * 2.0, 1e-9);
//     }
// }

// TEST(CompositeTest, PreventSelfAdd) {
//     CompositeShape comp;
//     // Если функция add проверяет наличие собственного значения,
//то добавление прямого указателя на себя должно вызвать исключение.
//     std::unique_ptr<Shape> p = std::make_unique<CompositeShape>();
//     EXPECT_NO_THROW(comp.add(std::move(p))); // depends on your policy
// }

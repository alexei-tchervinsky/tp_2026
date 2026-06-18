#include <iostream>
#include <vector>
#include <memory>
#include "rectangle.h"
#include "circle.h"
#include "composite_shape.h"

int main(){
  std::vector<std::shared_ptr<Shape>> shapes;

  shapes.push_back(std::make_shared<Rectangle>(Point{0.0, 0.0}, Point{2.0, 3.0}));
  shapes.push_back(std::make_shared<Circle>(Point{5.0, 5.0}, 3.0));
  shapes.push_back(std::make_shared<Rectangle>(Point{-10.0, -10.0}, Point{-5.0, -2.0}));
  shapes.push_back(std::make_shared<Circle>(Point{-2.0, 8.0}, 1.5));

  auto composite = std::make_shared<CompositeShape>();
  composite->addShape(std::make_shared<Rectangle>(Point{1.0, 1.0}, Point{3.0, 3.0}));
  composite->addShape(std::make_shared<Circle>(Point{2.0, 2.0}, 1.0));

  shapes.push_back(composite);

  std::cout << "BEFORE SCALING:" << std::endl;
  for (const auto& shape : shapes)
  {
    shape->print();
  }

  for (auto& shape : shapes)
  {
    shape->scale(2.0);
  }

  std::cout << "\nAFTER SCALING (x2.00):" << std::endl;
  for (const auto& shape : shapes)
  {
    shape->print();
  }

  return 0;
}

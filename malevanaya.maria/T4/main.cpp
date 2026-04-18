#include <iostream>
#include <vector>
#include <memory>

#include "circle.hpp"
#include "rectangle.hpp"
#include "composite_shape.hpp"

int main() {
    std::vector<std::unique_ptr<Shape>> list;

    list.push_back(std::make_unique<Circle>(Point{ 5, 5 }, 2));
    list.push_back(std::make_unique<Rectangle>(Point{ 0, 0 }, Point{ 2, 2 }));
    list.push_back(std::make_unique<Circle>(Point{ -2, -2 }, 1));
    list.push_back(std::make_unique<Rectangle>(Point{ 10, 10 }, Point{ 12, 15 }));

    auto comp = std::make_unique<CompositeShape>();
    comp->add(std::make_unique<Circle>(Point{ 1, 1 }, 0.5));
    comp->add(std::make_unique<Rectangle>(Point{ 0, 0 }, Point{ 2, 2 }));

    list.push_back(std::move(comp));

    std::cout << "BEFORE SCALE:\n";
    for (const auto& s : list) s->print();

    for (auto& s : list) s->scale(2.0);

    std::cout << "\nAFTER SCALE (x2):\n";
    for (const auto& s : list) s->print();

    return 0;
}

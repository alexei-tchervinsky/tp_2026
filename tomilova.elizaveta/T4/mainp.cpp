#include <iostream>
#include "vector"
#include "memory"
#include "rectangle.hpp"
#include "circle.hpp"
#include "composit_shape.hpp"

void printInfo(const Shape& shape){
    if (shape.getName() == "CompositeShape"){
        const CompositeShape& composite = static_cast<const CompositeShape&>(shape);
        composite.print();
    }
    else{
        Point center = shape.getCenter();
        std::cout << "[" << shape.getName() <<
        ", (" << center.x << ", " << center.y << "), "
        << shape.getArea() << "]" << '\n';
    }
}

int main(){
   try {
        // контейнер с фигурами
        std::vector<std::unique_ptr<Shape>> shapes;

        // простые фигуры
        shapes.push_back(std::make_unique<Rectangle>(Point{0.0, 0.0}, Point{2.0, 2.0}));
        shapes.push_back(std::make_unique<Circle>(Point{5.0, 5.0}, 3.0));
        shapes.push_back(std::make_unique<Rectangle>(Point{-5.0, -5.0}, Point{-2.0, -3.0}));
        shapes.push_back(std::make_unique<Circle>(Point{-10.0, 10.0}, 1.5));

        // составная фигура
        auto composite = std::make_unique<CompositeShape>();
        composite->addShape(std::make_unique<Rectangle>(Point{1.0, 1.0}, Point{3.0, 3.0}));
        composite->addShape(std::make_unique<Circle>(Point{2.0, 2.0}, 1.0));

        shapes.push_back(std::move(composite));


        std::cout << "--- BEFORE SCALE ---" << std::endl;
        for (size_t i = 0; i < shapes.size(); ++i) {
            printInfo(*shapes[i]);
        }

        // Увеличение фигур в 2 раза
        for (size_t i = 0; i < shapes.size(); ++i) {
            shapes[i]->scale(2.0);
        }


        std::cout << "\n--- AFTER SCALE (x2.0) ---" << std::endl;
        for (size_t i = 0; i < shapes.size(); ++i) {
            printInfo(*shapes[i]);
        }

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

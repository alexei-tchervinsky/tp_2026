#include "Rectangle.hpp"
#include "Ring.hpp"
#include "CompositeShape.hpp"

bool isEqual(float a, float b, float epsilon = 1e-5) {
    return std::abs(a - b) < epsilon;
}

void testRectangleMethods() {
    Rectangle rect(Point{ 0, 0 }, Point{ 4, 5 });
    assert(isEqual(rect.getArea(), 20.0f));

    rect.move(3.0f, 4.0f);
    FrameRectangle frame = rect.getFrameRectangle();
    assert(isEqual(frame.getPosition().x_, 5.0f));
    assert(isEqual(frame.getPosition().y_, 6.5f));

    rect.scale(2.0f);
    assert(isEqual(rect.getArea(), 80.0f));

    Shape* clonedRect = rect.clone();
    assert(std::string(clonedRect->getName()) == "RECTANGLE");
    delete clonedRect;
}

void testRingMethods() {
    Ring ring(2.0f, 5.0f, Point{ 0, 0 });
    assert(isEqual(ring.getArea(), PI * (25 - 4)));

    ring.move(Point{ 3.0f, 4.0f });
    FrameRectangle frame = ring.getFrameRectangle();
    assert(isEqual(frame.getPosition().x_, 3.0f));
    assert(isEqual(frame.getPosition().y_, 4.0f));

    ring.scale(2.0f);
    assert(isEqual(ring.getArea(), PI * (100 - 16)));

    Shape* clonedRing = ring.clone();
    assert(std::string(clonedRing->getName()) == "RING");
    delete clonedRing;
}

void testPolymorphism() {
    Shape* shapes[2];
    shapes[0] = new Rectangle(Point{ 0, 0 }, Point{ 4, 5 });
    shapes[1] = new Ring(2.0f, 5.0f, Point{ 0, 0 });

    assert(isEqual(shapes[0]->getArea(), 20.0f));
    assert(isEqual(shapes[1]->getArea(), PI * (25 - 4)));

    shapes[0]->move(3.0f, 4.0f);
    shapes[1]->move(Point{ 1.0f, 1.0f });
    FrameRectangle frame0 = shapes[0]->getFrameRectangle();
    FrameRectangle frame1 = shapes[1]->getFrameRectangle();
    assert(isEqual(frame0.getPosition().x_, 5.0f));
    assert(isEqual(frame0.getPosition().y_, 6.5f));
    assert(isEqual(frame1.getPosition().x_, 1.0f));
    assert(isEqual(frame1.getPosition().y_, 1.0f));

    Shape* clonedShape = shapes[0]->clone();
    assert(std::string(clonedShape->getName()) == "RECTANGLE");
    delete clonedShape;

    delete shapes[0];
    delete shapes[1];
}

void testInvarianceOnMove() {
    Rectangle rect(Point{ 0, 0 }, Point{ 4, 5 });
    float initialWidth = rect.getFrameRectangle().getWidth();
    float initialHeight = rect.getFrameRectangle().getHeight();
    float initialArea = rect.getArea();

    rect.move(3.0f, 4.0f);
    assert(isEqual(rect.getFrameRectangle().getWidth(), initialWidth));
    assert(isEqual(rect.getFrameRectangle().getHeight(), initialHeight));
    assert(isEqual(rect.getArea(), initialArea));

    Ring ring(2.0f, 5.0f, Point{ 0, 0 });
    float initialRingArea = ring.getArea();

    ring.move(Point{ 3.0f, 4.0f });
    assert(isEqual(ring.getArea(), initialRingArea));
}

void testQuadraticAreaScaling() {
    Rectangle rect(Point{ 0, 0 }, Point{ 4, 5 });
    float initialArea = rect.getArea();
    float scaleFactor = 2.0f;
    rect.scale(scaleFactor);
    assert(isEqual(rect.getArea(), initialArea * scaleFactor * scaleFactor));

    Ring ring(2.0f, 5.0f, Point{ 0, 0 });
    float initialRingArea = ring.getArea();
    ring.scale(scaleFactor);
    assert(isEqual(ring.getArea(), initialRingArea * scaleFactor * scaleFactor));
}

void testInvalidParameters() {
    try {
        Rectangle invalidRect(Point{ 4, 5 }, Point{ 0, 0 });
        assert(false);
    }
    catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "leftBottom must be less than rightTop in both x and y coordinates");
    }

    try {
        Ring invalidRing(-2.0f, 5.0f, Point{ 0, 0 });
        assert(false);
    }
    catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Radius values must be positive");
    }

    try {
        Ring invalidRing2(5.0f, 2.0f, Point{ 0, 0 });
        assert(false);
    }
    catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Inner radius must be smaller than outer radius");
    }

    Rectangle rect(Point{ 0, 0 }, Point{ 4, 5 });
    try {
        rect.scale(-1.0f);
        assert(false);
    }
    catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Scale factor must be positive");
    }

    Ring ring(2.0f, 5.0f, Point{ 0, 0 });
    try {
        ring.scale(0.0f);
        assert(false);
    }
    catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Scale factor must be positive");
    }
}

void testCompositeShapeAddAndAccess() {
    CompositeShape composite(5);

    Rectangle rect(Point{ 0, 0 }, Point{ 4, 5 });
    Ring ring(2.0f, 5.0f, Point{ 0, 0 });
    composite.addShape(rect);
    composite.addShape(ring);

    assert(std::string(composite.getShape(0).getName()) == "RECTANGLE");
    assert(std::string(composite.getShape(1).getName()) == "RING");

    try {
        composite.addShape(rect);
        composite.addShape(ring);
        composite.addShape(rect);
        composite.addShape(ring);
        composite.addShape(rect);
        assert(false);
    }
    catch (const std::runtime_error& e) {
        assert(std::string(e.what()) == "CompositeShape is full");
    }

    try {
        composite.getShape(10);
        assert(false);
    }
    catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Shape index out of range");
    }
}

void testCompositeShapeScale() {
    CompositeShape composite(2);
    Rectangle rect(Point{ 0, 0 }, Point{ 4, 5 });
    Ring ring(2.0f, 5.0f, Point{ 10, 10 });
    composite.addShape(rect);
    composite.addShape(ring);

    float initialArea1 = composite.getShape(0).getArea();
    float initialArea2 = composite.getShape(1).getArea();
    composite.scale(2.0f);
    assert(isEqual(composite.getShape(0).getArea(), initialArea1 * 4));
    assert(isEqual(composite.getShape(1).getArea(), initialArea2 * 4));

    Point centerBefore = composite.getCenter();
    composite.scale(0.5f);
    Point centerAfter = composite.getCenter();
    assert(isEqual(centerBefore.x_, centerAfter.x_));
    assert(isEqual(centerBefore.y_, centerAfter.y_));
}

void testCompositeShapeMove() {
    CompositeShape composite(2);
    Rectangle rect(Point{ 0, 0 }, Point{ 4, 5 });
    Ring ring(2.0f, 5.0f, Point{ 10, 10 });
    composite.addShape(rect);
    composite.addShape(ring);

    composite.move(Point{ 20, 20 });
    Point centerAfter = composite.getCenter();
    assert(isEqual(centerAfter.x_, 20.0f));
    assert(isEqual(centerAfter.y_, 20.0f));

    composite.move(10, -10);
    centerAfter = composite.getCenter();
    assert(isEqual(centerAfter.x_, 30.0f));
    assert(isEqual(centerAfter.y_, 10.0f));
}

void testCompositeShapeInvalidParameters() {
    try {
        CompositeShape composite(-1);
        assert(false);
    }
    catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Max count must be a positive number");
    }

    CompositeShape composite(2);
    Rectangle rect(Point{ 0, 0 }, Point{ 4, 5 });
    composite.addShape(rect);
    try {
        composite.scale(-2.0f);
        assert(false);
    }
    catch (const std::invalid_argument& e) {
        assert(std::string(e.what()) == "Scale factor must be positive");
    }
}

void testCompositeShapeOperations() {
    CompositeShape shape1(5);
    shape1.addShape(Rectangle(Point{ 5, 3 }, Point{ 9, 7 }));
    shape1.addShape(Ring(3.0f, 7.0f, Point{ 2, 6 }));

    CompositeShape shape2(shape1);
    assert(shape2.getShapeCount() == shape1.getShapeCount());
    for (size_t i = 0; i < shape1.getShapeCount(); ++i) {
        assert(&shape2.getShape(i) != &shape1.getShape(i));
    }

    CompositeShape shape3(std::move(shape1));
    assert(shape1.getShapeCount() == 0);
    assert(shape3.getShapeCount() > 0);
    assert(shape2.getShapeCount() == shape3.getShapeCount());

    CompositeShape shape4(3);
    shape4 = shape2;
    assert(shape4.getShapeCount() == shape2.getShapeCount());
    for (size_t i = 0; i < shape2.getShapeCount(); ++i) {
        assert(&shape4.getShape(i) != &shape2.getShape(i));
    }

    CompositeShape shape5(2);
    shape5 = std::move(shape4);
    assert(shape4.getShapeCount() == 0);
    assert(shape5.getShapeCount() > 0);
}

int main() {
    try {
        testRectangleMethods();
        testRingMethods();
        testPolymorphism();

        testInvarianceOnMove();
        testQuadraticAreaScaling();
        testInvalidParameters();

        testCompositeShapeAddAndAccess();
        testCompositeShapeScale();
        testCompositeShapeMove();
        testCompositeShapeInvalidParameters();
        testCompositeShapeOperations();

        std::cout << "All tests passed successfully!\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
    }
    return 0;
}
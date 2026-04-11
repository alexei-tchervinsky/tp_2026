#include <iostream>
#include "point.h"
#include "rectangle.h"
#include "square.h"
#include "circle.h"
#include "ring.h"
#include "ellips.h"
#include "rhombus.h"
#include "isosceles_trapezoid.h"
#include "rectangular_trapezoid.h"
#include "composite_shape.h"
#include <iomanip>

// #include <iostream>
// #include <vector>
// #include <memory>
int main() {
std::cout << "========= RECANGLE =========\n\n";
std::cout << std::fixed << std::setprecision(2);
{

  Rectangle rect( {0,0}, {10, 10});

  std::cout << "rect: {0,0}, {10,10}";

  std::cout << "\nchecking methods...\n";

  std::cout << "\ngetArea(): " << rect.getArea() << "\n";
  Point p = rect.getCenter();
  std::cout << "Center: " << "(" << p.x_ << "; " << p.y_ << ")\n";
  rect.move(5, 5);
  Point p2 = rect.getCenter();
  std::cout << "Moved dx = 5, dy = 5: " << "(" << p2.x_ << "; " << p2.y_ << ")\n";
  rect.scale(4);
  std::cout << "scale(4) :" << rect.getArea() << "\n";
  std::cout << "getName():" << rect.getName() << "\n";
}

std::cout << "\n\n========= CIRCLE =========\n\n";
{

  Circle circ( {5,5}, 5);

  std::cout << "circ ({5,5}, 5)";

  std::cout << "\nchecking methods...\n";

  std::cout << "\ngetArea(): " << circ.getArea() << "\n";
  Point p = circ.getCenter();
  std::cout << "Center: " << "(" << p.x_ << "; " << p.y_ << ")\n";
  circ.move(5, 5);
  Point p2 = circ.getCenter();
  std::cout << "Moved dx = 5, dy = 5: " << "(" << p2.x_ << "; " << p2.y_ << ")\n";
  circ.scale(4);
  std::cout << "scale(4) :" << circ.getArea() << "\n";
  std::cout << "getName():" << circ.getName() << "\n";
}

std::cout << "\n\n========= RING =========\n\n";
{

  Ring ring( {5,5}, 5, 3);

  std::cout << "RING ({5,5}, 5, 3)";

  std::cout << "\nchecking methods...\n";

  std::cout << "\ngetArea(): " << ring.getArea() << "\n";
  Point p = ring.getCenter();
  std::cout << "Center: " << "(" << p.x_ << "; " << p.y_ << ")\n";
  ring.move(5, 5);
  Point p2 = ring.getCenter();
  std::cout << "Moved dx = 5, dy = 5: " << "(" << p2.x_ << "; " << p2.y_ << ")\n";
  ring.scale(4);
  std::cout << "scale(4) :" << ring.getArea() << "\n";
  std::cout << "getName():" << ring.getName() << "\n";
}

std::cout << "\n\n========= ELLIPS =========\n\n";
{

  Ellips ell( {5,5}, 5, 3);

  std::cout << "Ellips ({5,5}, 5, 3)";

  std::cout << "\nchecking methods...\n";

  std::cout << "\ngetArea(): " << ell.getArea() << "\n";
  Point p = ell.getCenter();
  std::cout << "Center: " << "(" << p.x_ << "; " << p.y_ << ")\n";
  ell.move(5, 5);
  Point p2 = ell.getCenter();
  std::cout << "Moved dx = 5, dy = 5: " << "(" << p2.x_ << "; " << p2.y_ << ")\n";
  ell.scale(4);
  std::cout << "scale(4) :" << ell.getArea() << "\n";
  std::cout << "getName():" << ell.getName() << "\n";
}

std::cout << "\n\n========= SQUARE =========\n\n";
{

  Square sqr( {0,0}, 5);

  std::cout << "Square ( {0,0} 5)";

  std::cout << "\nchecking methods...\n";

  std::cout << "\ngetArea(): " << sqr.getArea() << "\n";
  Point p = sqr.getCenter();
  std::cout << "Center: " << "(" << p.x_ << "; " << p.y_ << ")\n";
  sqr.move(5, 5);
  Point p2 = sqr.getCenter();
  std::cout << "Moved dx = 5, dy = 5: " << "(" << p2.x_ << "; " << p2.y_ << ")\n";
  sqr.scale(4);
  std::cout << "scale(4) :" << sqr.getArea() << "\n";
  std::cout << "getName():" << sqr.getName() << "\n";
}


std::cout << "\n\n========= RHOMBUS =========\n\n";
{

  Rhombus rhomb( {5,5}, 5, 3);

  std::cout << "Rhombus ({5,5}, 5, 3)";

  std::cout << "\nchecking methods...\n";

  std::cout << "\ngetArea(): " << rhomb.getArea() << "\n";
  Point p = rhomb.getCenter();
  std::cout << "Center: " << "(" << p.x_ << "; " << p.y_ << ")\n";
  rhomb.move(5, 5);
  Point p2 = rhomb.getCenter();
  std::cout << "Moved dx = 5, dy = 5: " << "(" << p2.x_ << "; " << p2.y_ << ")\n";
  rhomb.scale(4);
  std::cout << "scale(4) :" << rhomb.getArea() << "\n";
  std::cout << "getName():" << rhomb.getName() << "\n";
}


std::cout << "\n\n========= IsoscelesTrapezoid=========\n\n";
{

  IsoscelesTrapezoid isoTrap( {0,0}, 6, 3, 8);

  std::cout << "isoTrap ({0,0}, 6, 3)";

  std::cout << "\nchecking methods...\n";

  std::cout << "\ngetArea(): " << isoTrap.getArea() << "\n";
  Point p = isoTrap.getCenter();
  std::cout << "Center: " << "(" << p.x_ << "; " << p.y_ << ")\n";
  isoTrap.move(5, 5);
  Point p2 = isoTrap.getCenter();
  std::cout << "Moved dx = 5, dy = 5: " << "(" << p2.x_ << "; " << p2.y_ << ")\n";
  isoTrap.scale(4);
  std::cout << "scale(4) :" << isoTrap.getArea() << "\n";
  std::cout << "getName():" << isoTrap.getName() << "\n";
}

std::cout << "\n\n========= RectangularTrapezoid=========\n\n";
{

  RectangularTrapezoid rectTrap( {0,0}, 6, 3, 8);

  std::cout << "rectTrap ({0,0}, 6, 3)";

  std::cout << "\nchecking methods...\n";

  std::cout << "\ngetArea(): " << rectTrap.getArea() << "\n";
  Point p = rectTrap.getCenter();
  std::cout << "Center: " << "(" << p.x_ << "; " << p.y_ << ")\n";
  rectTrap.move(5, 5);
  Point p2 = rectTrap.getCenter();
  std::cout << "Moved dx = 5, dy = 5: " << "(" << p2.x_ << "; " << p2.y_ << ")\n";
  rectTrap.scale(4);
  std::cout << "scale(4) :" << rectTrap.getArea() << "\n";
  std::cout << "getName():" << rectTrap.getName() << "\n";
}


std::cout << "\n\n=======COMPOSITE SHAPE=======\n\n";
{
std::unique_ptr<Rectangle> rect = std::make_unique<Rectangle>(Point{0, 0}, Point{4, 4});
std::unique_ptr<Circle> circ = std::make_unique<Circle>(Point{5,5}, 1);
std::unique_ptr<Rhombus> rhomb = std::make_unique<Rhombus>(Point {7,7}, 7, 1);


CompositeShape composite;
composite.addShape(std::move(rect));
composite.addShape(std::move(rhomb));
composite.addShape(std::move(circ));


std::cout << "Center: (" << composite.getCenter().x_ << ", " << composite.getCenter().y_ << ")\n";
std::cout << "Area: " << composite.getArea() << '\n';

composite.scale(2.0);

std::cout << "\nafter scale (x4):\n";
std::cout << "Center: (" << composite.getCenter().x_ << ", " << composite.getCenter().y_ << ")\n";
std::cout << "Area: " << composite.getArea() << '\n';
}










}
/*
  std::cout << "========= RHOMB =========\n\n";
  std::cout << std::fixed << std::setprecision(2);

  std::unique_ptr<Rhombus> rhomb = std::make_unique<Rhombus>(Point{10, 10}, 3.0, 2.0);

  std::cout << "center: 10; 10\nhHalf = 3.0\nvHalf = 2.0\n";

  std::cout << "\nchecking methods...\n";

  std::cout << "\ngetArea():" << rhomb->getArea() << "\n";
  Point p = rhomb->getCenter();
  std::cout << "Center: " << "(" << p.x << "; " << p.y << ")\n";
  rhomb->move(5, 5);
  Point p2 = rhomb->getCenter();
  std::cout << "Moved dx = 5, dy = 5: " << "(" << p2.x << "; " << p2.y << ")\n";
  rhomb->scale(4);
  std::cout << "scale(4) :" << rhomb->getArea() << "\n";
  std::cout << "getName():" << rhomb->getName() << "\n";




  std::unique_ptr<Rectangle> rect = std::make_unique<Rectangle>(Point{0, 0}, Point{4, 4});


  CompositeShape composite;
  composite.addShape(std::move(rect));
  composite.addShape(std::move(rhomb));

  std::cout << "\n ======= composite ======= \n" << std::endl;

  std::cout << "Center: (" << composite.getCenter().x << ", " << composite.getCenter().y << ")" << std::endl;
  std::cout << "Area: " << composite.getArea() << std::endl;

  composite.scale(2.0);

  std::cout << "\nafter scale (x2):" << std::endl;
  std::cout << "Center: (" << composite.getCenter().x << ", " << composite.getCenter().y << ")" << std::endl;
  std::cout << "Area: " << composite.getArea() << std::endl;










  std::cout << "========= RHOMB =========\n\n";
  std::cout << std::fixed << std::setprecision(2);

  std::unique_ptr<Rhombus> rhomb = std::make_unique<Rhombus>(Point{10, 10}, 3.0, 2.0);

  std::cout << "center: 10; 10\nhHalf = 3.0\nvHalf = 2.0\n";

  std::cout << "\nchecking methods...\n";

  std::cout << "\ngetArea():" << rhomb->getArea() << "\n";
  Point p = rhomb->getCenter();
  std::cout << "Center: " << "(" << p.x << "; " << p.y << ")\n";
  rhomb->move(5, 5);
  Point p2 = rhomb->getCenter();
  std::cout << "Moved dx = 5, dy = 5: " << "(" << p2.x << "; " << p2.y << ")\n";
  rhomb->scale(4);
  std::cout << "scale(4) :" << rhomb->getArea() << "\n";
  std::cout << "getName():" << rhomb->getName() << "\n";




  std::unique_ptr<Rectangle> rect = std::make_unique<Rectangle>(Point{0, 0}, Point{4, 4});


  CompositeShape composite;
  composite.addShape(std::move(rect));
  composite.addShape(std::move(rhomb));

  std::cout << "\n ======= composite ======= \n" << std::endl;

  std::cout << "Center: (" << composite.getCenter().x << ", " << composite.getCenter().y << ")" << std::endl;
  std::cout << "Area: " << composite.getArea() << std::endl;

  composite.scale(2.0);

  std::cout << "\nafter scale (x2):" << std::endl;
  std::cout << "Center: (" << composite.getCenter().x << ", " << composite.getCenter().y << ")" << std::endl;
  std::cout << "Area: " << composite.getArea() << std::endl;









  std::cout << "========= RHOMB =========\n\n";
  std::cout << std::fixed << std::setprecision(2);

  std::unique_ptr<Rhombus> rhomb = std::make_unique<Rhombus>(Point{10, 10}, 3.0, 2.0);

  std::cout << "center: 10; 10\nhHalf = 3.0\nvHalf = 2.0\n";

  std::cout << "\nchecking methods...\n";

  std::cout << "\ngetArea():" << rhomb->getArea() << "\n";
  Point p = rhomb->getCenter();
  std::cout << "Center: " << "(" << p.x << "; " << p.y << ")\n";
  rhomb->move(5, 5);
  Point p2 = rhomb->getCenter();
  std::cout << "Moved dx = 5, dy = 5: " << "(" << p2.x << "; " << p2.y << ")\n";
  rhomb->scale(4);
  std::cout << "scale(4) :" << rhomb->getArea() << "\n";
  std::cout << "getName():" << rhomb->getName() << "\n";




  std::unique_ptr<Rectangle> rect = std::make_unique<Rectangle>(Point{0, 0}, Point{4, 4});


  CompositeShape composite;
  composite.addShape(std::move(rect));
  composite.addShape(std::move(rhomb));

  std::cout << "\n ======= composite ======= \n" << std::endl;

  std::cout << "Center: (" << composite.getCenter().x << ", " << composite.getCenter().y << ")" << std::endl;
  std::cout << "Area: " << composite.getArea() << std::endl;

  composite.scale(2.0);

  std::cout << "\nafter scale (x2):" << std::endl;
  std::cout << "Center: (" << composite.getCenter().x << ", " << composite.getCenter().y << ")" << std::endl;
  std::cout << "Area: " << composite.getArea() << std::endl;











  std::cout << "========= RHOMB =========\n\n";
  std::cout << std::fixed << std::setprecision(2);

  std::unique_ptr<Rhombus> rhomb = std::make_unique<Rhombus>(Point{10, 10}, 3.0, 2.0);

  std::cout << "center: 10; 10\nhHalf = 3.0\nvHalf = 2.0\n";

  std::cout << "\nchecking methods...\n";

  std::cout << "\ngetArea():" << rhomb->getArea() << "\n";
  Point p = rhomb->getCenter();
  std::cout << "Center: " << "(" << p.x << "; " << p.y << ")\n";
  rhomb->move(5, 5);
  Point p2 = rhomb->getCenter();
  std::cout << "Moved dx = 5, dy = 5: " << "(" << p2.x << "; " << p2.y << ")\n";
  rhomb->scale(4);
  std::cout << "scale(4) :" << rhomb->getArea() << "\n";
  std::cout << "getName():" << rhomb->getName() << "\n";




  std::unique_ptr<Rectangle> rect = std::make_unique<Rectangle>(Point{0, 0}, Point{4, 4});


  CompositeShape composite;
  composite.addShape(std::move(rect));
  composite.addShape(std::move(rhomb));

  std::cout << "\n ======= composite ======= \n" << std::endl;

  std::cout << "Center: (" << composite.getCenter().x << ", " << composite.getCenter().y << ")" << std::endl;
  std::cout << "Area: " << composite.getArea() << std::endl;

  composite.scale(2.0);

  std::cout << "\nafter scale (x2):" << std::endl;
  std::cout << "Center: (" << composite.getCenter().x << ", " << composite.getCenter().y << ")" << std::endl;
  std::cout << "Area: " << composite.getArea() << std::endl;













  std::cout << "========= RHOMB =========\n\n";
  std::cout << std::fixed << std::setprecision(2);

  std::unique_ptr<Rhombus> rhomb = std::make_unique<Rhombus>(Point{10, 10}, 3.0, 2.0);

  std::cout << "center: 10; 10\nhHalf = 3.0\nvHalf = 2.0\n";

  std::cout << "\nchecking methods...\n";

  std::cout << "\ngetArea():" << rhomb->getArea() << "\n";
  Point p = rhomb->getCenter();
  std::cout << "Center: " << "(" << p.x << "; " << p.y << ")\n";
  rhomb->move(5, 5);
  Point p2 = rhomb->getCenter();
  std::cout << "Moved dx = 5, dy = 5: " << "(" << p2.x << "; " << p2.y << ")\n";
  rhomb->scale(4);
  std::cout << "scale(4) :" << rhomb->getArea() << "\n";
  std::cout << "getName():" << rhomb->getName() << "\n";




  std::unique_ptr<Rectangle> rect = std::make_unique<Rectangle>(Point{0, 0}, Point{4, 4});


  CompositeShape composite;
  composite.addShape(std::move(rect));
  composite.addShape(std::move(rhomb));

  std::cout << "\n ======= composite ======= \n" << std::endl;

  std::cout << "Center: (" << composite.getCenter().x << ", " << composite.getCenter().y << ")" << std::endl;
  std::cout << "Area: " << composite.getArea() << std::endl;

  composite.scale(2.0);

  std::cout << "\nafter scale (x2):" << std::endl;
  std::cout << "Center: (" << composite.getCenter().x << ", " << composite.getCenter().y << ")" << std::endl;
  std::cout << "Area: " << composite.getArea() << std::endl;


}
*/



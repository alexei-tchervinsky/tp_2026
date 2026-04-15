#include "Point.hpp"
#include "FrameRectangle.hpp"
#include "Shape.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "CompositeShape.hpp"
#include <exception>

int main()
{
	try
	{
		Rectangle rect1;
		Rectangle rect2("Rect2", Point(-2, -2), Point(3, 1));
		Rectangle *rect3 = rect1.clone();
		Circle circ1("Circ1", Point(1, 1), 4);
		Circle *circ2 = circ1.clone();
		std::cout << "Methods tests:\n"
							<< "Rect1 S = " << rect1.getArea() << "; Rect2 S = " << rect2.getArea() << "; Rect3 name = " << rect3->getName() << "; Circ2 S = " << circ2->getArea() << std::endl;
		std::cout << "\nbefore move:" << "\nRect1: " << rect1 << "\nRect2: " << rect2 << "\nCircle1 : " << circ1 << std::endl;
		rect1.move(4);
		circ1.move(15);
		std::cout << "\nafter move:" << "\nRect1: " << rect1 << "\nCircle1: " << circ1 << "\nCircle2: " << *circ2 << std::endl;
		circ2->move(-100);
		std::cout << "\navter move circ2:" << "\nCircle1: " << circ1 << "\nCircle2: " << *circ2 << std::endl;
		Circle circ3;
		std::cout << "\nbefore scale:" << "\nRect2: " << rect2 << "\nCircle3: " << circ3 << std::endl;
		rect2.scale(2);
		circ3.scale(4);
		std::cout << "\nafter scale:" << "\nRect2: " << rect2 << "\nCircle3: " << circ3 << std::endl;

		double k = 3;

		std::cout << "\n\ntests Rectangle:";
		Rectangle rect("Rect", Point(10, 10), Point(25, 25));
		double width = rect.getFrameRectangle().WIDTH;
		double height = rect.getFrameRectangle().WIDTH;
		double s = rect.getArea();
		rect.move(k);
		if (width == rect.getFrameRectangle().WIDTH && height == rect.getFrameRectangle().HEIGHT && s == rect.getArea())
		{
			std::cout << "\nmove - TRUE.";
		}
		else
		{
			std::cerr << "\nERORR: FALSE";
		}
		rect.scale(k);
		if ((width * height * k * k) == rect.getArea())
		{
			std::cout << "\nscale - TRUE.";
		}
		else
		{
			std::cerr << "\nERORR: FALSE";
		}

		std::cout << "\ntests Circle:";
		Circle circ("Circ", Point(101.25, 10.5), 13.5);
		width = circ.getFrameRectangle().WIDTH;
		height = circ.getFrameRectangle().HEIGHT;
		s = circ.getArea();
		circ.move(k);
		if (width == circ.getFrameRectangle().WIDTH && height == circ.getFrameRectangle().HEIGHT && s == circ.getArea())
		{
			std::cout << "\nmove - TRUE.";
		}
		else
		{
			std::cerr << "\nERORR: FALSE";
		}
		circ.scale(k);
		if ((3.14 * width / 2 * k * width / 2 * k) == circ.getArea())
		{
			std::cout << "\nscale - TRUE.";
		}
		else
		{
			std::cerr << "\n\nERORR: FALSE";
		}

		std::cout << "\n\ntests CompositeShape";
		CompositeShape cs;
		cs.push_back(circ1);
		cs.push_back(*circ2);
		cs.push_back(rect1);
		cs.push_back(rect2);
		for (std::size_t i = 0; i < cs.size(); ++i)
		{
			std::cout << "\nbefore: " << cs[i]->getArea();
		}
		cs.move(4);
		cs.scale(2);
		for (std::size_t i = 0; i < cs.size(); ++i)
		{
			std::cout << "\nafter: " << cs[i]->getArea();
		}
		delete circ2;
		delete rect3;
	}
	catch (const std::exception &ex)
	{
		std::cerr << ex.what();
	}
	return 0;
}

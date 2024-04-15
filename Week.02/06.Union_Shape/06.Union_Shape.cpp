#include <iostream>
#include <fstream>


enum class ShapeType {
	Circle,
	Rectangle,
	Square
};

struct Circle {
	double radius;
};

struct Square {
	double side;
};

struct Rectangle {
	double width;
	double height;
};

union Shape {
	Circle circle;
	Square square;
	Rectangle rectangle;
};

double evaluateArea(const Shape& shape, ShapeType type)
{
	switch (type)
	{
	case ShapeType::Circle:
		return 3.14 * shape.circle.radius * shape.circle.radius;
	case ShapeType::Square:
		return shape.square.side * shape.square.side;
	case ShapeType::Rectangle:
		return shape.rectangle.width * shape.rectangle.height;
	default:
		return 0;
	}
}

int main()
{
	Shape testShape;
	testShape.circle.radius = 4;
	std::cout << evaluateArea(testShape, ShapeType::Circle) << std::endl;

	Shape secondTestShape;
	secondTestShape.square.side = 4;
	std::cout << evaluateArea(secondTestShape, ShapeType::Square) << std::endl;

	Shape thirdTestShape;
	thirdTestShape.rectangle.width = 4;
	thirdTestShape.rectangle.height = 3;
	std::cout << evaluateArea(thirdTestShape, ShapeType::Rectangle) << std::endl;

	std::cout << sizeof(Shape);
}
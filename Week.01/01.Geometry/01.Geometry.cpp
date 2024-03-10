#include <iostream>

using std::cout;
using std::endl;

struct Point {
	double x;
	double y;
};

struct Circle {
	double r;
	Point center;
};

struct Vector {
	int size;
	double coordinates[100]{ 0 };
};


int myMin(const int& a, const int& b)
{
	return a > b ? a : b;
}
int checkQuadrant(const Point& p)
{
	if (p.x > 0 && p.y > 0)
	{
		return 1;
	}
	else if (p.x > 0 && p.y < 0)
	{
		return 4;
	}
	else if (p.x < 0 && p.y > 0)
	{
		return 2;
	}
	else if (p.x < 0 && p.y < 0)
	{
		return 3;
	}
}

double getDistance(const Point& p1, const Point& p2)
{
	double dx = p1.x - p2.x;
	double dy = p1.y - p2.y;

	return sqrt(dx * dx + dy * dy);
}

bool checkIsPointOnCircle(const Circle& circle, const Point& p)
{
	double distance = getDistance(circle.center, p);

	return abs(distance - circle.r) <= 0.001;
}

bool checkIfTwoCirclesCross(const Circle& c1, const Circle& c2)
{
	double distance = getDistance(c1.center, c2.center);

	return distance < c1.r + c2.r;
}

bool checkIsInCircle(const Circle& c1, const  Circle& c2)
{
	double distance = getDistance(c1.center, c2.center);

	return distance < c1.r && c1.r - c2.r > 0;
}

double calculateScalarOfTwoVectors(const Vector& v1, const Vector& v2)
{
	double result = 0;

	int endPoint = myMin(v1.size, v2.size);

	for (int i = 0; i < endPoint; i++)
	{
		result += v1.coordinates[i] + v2.coordinates[i];
	}

	return result;
}

int main()
{
	Point p1 = { 1, 0 };
	Point p2 = { 1, -1 };
	Point p3 = { -1, 1 };
	Point p4 = { -1, -1 };

	cout << checkQuadrant(p1) << endl;
	cout << checkQuadrant(p2) << endl;
	cout << checkQuadrant(p3) << endl;
	cout << checkQuadrant(p4) << endl;

	cout << getDistance(p1, p2) << endl;

	Circle c1 = { 1, {0, 0} };
	Circle c2 = { 1, {1, 0} };

	cout << checkIsPointOnCircle(c1, p1) << endl;
	cout << checkIfTwoCirclesCross(c1, c2) << endl;
	cout << checkIsInCircle(c1, c2);
}
#pragma once

#include "Point.h"
#include "Triangle.h"

class Triangle
{
private:
	Point* _a;
	Point* _b;
	Point* _c;

public:
	Triangle();
	Triangle(const Point& a, const Point& b, const Point& c);
	Triangle(double point1[2], double point2[2], double point3[2]);
	Triangle(const Triangle& triangle);
	~Triangle();

	void setA(const Point& a);
	Point* getA() const;

	void setB(const Point& b);
	Point* getB() const;

	void setC(const Point& c);
	Point* getC() const;

	bool isTriangle() const;

	void move(double k);

	double getPerimeter() const;

	bool isEqual(const Triangle& triangle) const;
};
#pragma once

#include "Point.h"

class Triangle
{
private:
	Point* _a;
	Point* _b;
	Point* _c;

public:
	Triangle();
	Triangle(const Point& a, const Point& b, const Point& c);
	Triangle(const Triangle& triangle);
	~Triangle();

	void setA(const Point& a);
	Point* getA() const;

	void setB(const Point& b);
	Point* getB() const;

	void setC(const Point& c);
	Point* getC() const;

	bool isTriangle();

	void move(double k);

	double getPerimeter();

	bool isEqual(const Triangle& triangle);
};
#pragma once
#include "point.h"


class Triangle
{
private:
	Point* a_;
	Point* b_;
	Point* c_;

public:
	Triangle();
	Triangle(const Point& a, const Point& b, const Point& c);
	Triangle(const Triangle& triangle);
	~Triangle();

	void setA(const Point& a);
	void setB(const Point& b);
	void setC(const Point& c);

	Point getA() const;
	Point getB() const;
	Point getC() const;

	bool isTriangle() const;

	double getPerimeter() const;

	void move(double k);

	bool isEqual(const Triangle& triangle) const;
};
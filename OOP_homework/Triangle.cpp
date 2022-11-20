#include "Triangle.h"
#include <algorithm>

Triangle::Triangle()
{
	this->_a = new Point(0, 0);
	this->_b = new Point(0, 0);
	this->_c = new Point(0, 0);
}

Triangle::Triangle(const Point& a, const Point& b, const Point& c)
{
	this->_a = new Point(a);
	this->_b = new Point(b);
	this->_c = new Point(c);
}

Triangle::Triangle(double point1[2], double point2[2], double point3[2])
{
	this->_a = new Point(point1[0], point1[1]);
	this->_b = new Point(point2[0], point2[1]);
	this->_c = new Point(point3[0], point3[1]);
}

Triangle::Triangle(const Triangle& triangle)
{
	this->_a = new Point(*triangle._a);
	this->_b = new Point(*triangle._b);
	this->_c = new Point(*triangle._c);
}

Triangle::~Triangle()
{
	delete _a;
	delete _b;
	delete _c;
}

void Triangle::setA(const Point& a)
{
	delete _a;
	_a = new Point(a);
}

Point* Triangle::getA() const
{
	return new Point(*(this->_a));
}

void Triangle::setB(const Point& b)
{
	delete _b;
	_b = new Point(b);
}

Point* Triangle::getB() const
{
	return new Point(*(this->_b));
}

void Triangle::setC(const Point& c)
{
	delete _c;
	_c = new Point(c);
}

Point* Triangle::getC() const
{
	return new Point(*(this->_a));
}

bool Triangle::isTriangle() const
{
	double length1 = (this->_a)->getDistance(*_b);
	double length2 = (this->_b)->getDistance(*_c);
	double length3 = (this->_c)->getDistance(*_a);

	double lengthArray[3] = { length1, length2, length3 };
	std::sort(std::begin(lengthArray), std::end(lengthArray));

	return lengthArray[0] + lengthArray[1] > lengthArray[2];
}

void Triangle::move(double k)
{
	this->_a->move(k);
	this->_b->move(k);
	this->_c->move(k);
}

double Triangle::getPerimeter() const
{
	if(!this->isTriangle())
	{
		throw std::exception("Это не треугольник!");
	}

	double length1 = (this->_a)->getDistance(*_b);
	double length2 = (this->_b)->getDistance(*_c);
	double length3 = (this->_c)->getDistance(*_a);

	return length1 + length2 + length3;
}

bool Triangle::isEqual(const Triangle& triangle) const
{
	Point* pointA = triangle.getA();
	Point* pointB = triangle.getB();
	Point* pointC = triangle.getC();

	bool isEqualA = this->_a->isEqual(*pointA);
	bool isEqualB = this->_b->isEqual(*pointB);
	bool isEqualC = this->_c->isEqual(*pointC);

	delete pointA;
	delete pointB;
	delete pointC;

	return isEqualA && isEqualB && isEqualC;
}

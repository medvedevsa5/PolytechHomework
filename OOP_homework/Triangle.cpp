#include "triangle.h"
#include "point.h"
#include <cmath>
#include <algorithm>

Triangle::Triangle()
{
	this->_a = new Point();
	this->_b = new Point();
	this->_c = new Point();
}

Triangle::Triangle(const Point& a, const Point& b, const Point& c)
{
	this->_a = new Point(a);
	this->_b = new Point(b);
	this->_c = new Point(c);
}

Triangle::Triangle(const Triangle& triangle)
{
	this->_a = new Point(*triangle._a);
	this->_b = new Point(*triangle._b);
	this->_c = new Point(*triangle._c);
}

Triangle::~Triangle()
{
	delete this->_a;
	delete this->_b;
	delete this->_c;
}

void Triangle::setA(const Point& a)
{
	this->_a->setX(a.getX());
	this->_a->setY(a.getY());
}

void Triangle::setB(const Point& b)
{
	this->_b->setX(b.getX());
	this->_b->setY(b.getY());
}

void Triangle::setC(const Point& c)
{
	this->_c->setX(c.getX());
	this->_c->setY(c.getY());
}

Point Triangle::getA() const
{
	return Point(*_a);
}

Point Triangle::getB() const
{
	return Point(*_b);
}

Point Triangle::getC() const
{
	return Point(*_c);
}

bool Triangle::isTriangle() const
{
	double lengthAB = this->_a->getDistance(*this->_b);
	double lengthBC = this->_b->getDistance(*this->_c);
	double lengthCA = this->_c->getDistance(*this->_a);

	double lengthArray[3] = { lengthAB, lengthBC, lengthCA };

	std::sort(std::begin(lengthArray), std::end(lengthArray));

	return lengthArray[0] + lengthArray[1] > lengthArray[2];
}

double Triangle::getPerimeter() const
{
	double lengthAB = this->_a->getDistance(*this->_b);
	double lengthBC = this->_b->getDistance(*this->_c);
	double lengthCA = this->_c->getDistance(*this->_a);

	if (!this->isTriangle())
	{
		double lengthArray[3] = { lengthAB, lengthBC, lengthCA };

		std::sort(std::begin(lengthArray), std::end(lengthArray));

		return lengthArray[2];
	}
	else 
	{
		return lengthAB + lengthBC + lengthCA;
	}
}

void Triangle::move(double k)
{
	this->_a->move(k);
	this->_b->move(k);
	this->_c->move(k);
}

bool Triangle::isEqual(const Triangle& triangle) const
{
	return this->_a->isEqual(triangle.getA()) 
		&& this->_b->isEqual(triangle.getB()) 
		&& this->_c->isEqual(triangle.getC());
}

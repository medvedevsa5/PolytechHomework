#include "triangle.h"
#include "point.h"
#include <cmath>
#include <algorithm>

Triangle::Triangle()
{
	this->a_ = new Point();
	this->b_ = new Point();
	this->c_ = new Point();
}

Triangle::Triangle(const Point& a, const Point& b, const Point& c)
{
	this->a_ = new Point(a);
	this->b_ = new Point(b);
	this->c_ = new Point(c);
}

Triangle::Triangle(const Triangle& triangle)
{
	this->a_ = new Point(*triangle.a_);
	this->b_ = new Point(*triangle.b_);
	this->c_ = new Point(*triangle.c_);
}

Triangle::~Triangle()
{
	delete this->a_;
	delete this->b_;
	delete this->c_;
}

void Triangle::setA(const Point& a)
{
	this->a_->setX(a.getX());
	this->a_->setY(a.getY());
}

void Triangle::setB(const Point& b)
{
	this->b_->setX(b.getX());
	this->b_->setY(b.getY());
}

void Triangle::setC(const Point& c)
{
	this->c_->setX(c.getX());
	this->c_->setY(c.getY());
}

Point Triangle::getA() const
{
	return Point(*a_);
}

Point Triangle::getB() const
{
	return Point(*b_);
}

Point Triangle::getC() const
{
	return Point(*c_);
}

bool Triangle::isTriangle() const
{
	double lengthAB = this->a_->getDistance(this->getA());
	double lengthBC = this->b_->getDistance(this->getB());
	double lengthCA = this->c_->getDistance(this->getC());

	double lengthArray[3] = { lengthAB, lengthBC, lengthCA };

	std::sort(std::begin(lengthArray), std::end(lengthArray));

	return lengthArray[0] + lengthArray[1] > lengthArray[2];
}

double Triangle::getPerimeter() const
{
	double lengthAB = this->a_->getDistance(*this->b_);
	double lengthBC = this->b_->getDistance(*this->c_);
	double lengthCA = this->c_->getDistance(*this->a_);

	if (!this->isTriangle())
	{
		return std::max(lengthAB, std::max(lengthBC, lengthCA));
	}
	else
	{
		return lengthAB + lengthBC + lengthCA;
	}
}

void Triangle::move(double k)
{
	this->a_->move(k);
	this->b_->move(k);
	this->c_->move(k);
}

bool Triangle::isEqual(const Triangle& triangle) const
{
	return this->a_->isEqual(triangle.getA()) 
		&& this->b_->isEqual(triangle.getB()) 
		&& this->c_->isEqual(triangle.getC());
}

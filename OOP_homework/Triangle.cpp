#include "Triangle.h"
#include "Point.h"
#include <iostream>
#include <cmath>
#include <algorithm>

const double COMPARISON_EPSILON = 0.000001;

Triangle::Triangle()
{
	std::cerr << std::endl << "Вызов конструктора Triangle" << std::endl;
	this->a_ = new Point();
	this->b_ = new Point();
	this->c_ = new Point();
}

Triangle::Triangle(const Point& a, const Point& b, const Point& c)
{
	std::cerr << std::endl << "Вызов конструктора Triangle" << std::endl;
	this->a_ = new Point(a);
	this->b_ = new Point(b);
	this->c_ = new Point(c);
}

Triangle::Triangle(const Triangle& triangle)
{
	std::cerr << std::endl << "Вызов конструктора Triangle" << std::endl;
	this->a_ = new Point(*triangle.a_);
	this->b_ = new Point(*triangle.b_);
	this->c_ = new Point(*triangle.c_);
}

Triangle::~Triangle()
{
	std::cerr << std::endl << "Вызов деструктора Triangle" << std::endl;
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
	double lengthAB = this->a_->getDistance(this->getB());
	double lengthBC = this->b_->getDistance(this->getC());
	double lengthCA = this->c_->getDistance(this->getA());

	double lengthArray[3] = { lengthAB, lengthBC, lengthCA };

	std::sort(std::begin(lengthArray), std::end(lengthArray));

	return lengthArray[0] + lengthArray[1] > lengthArray[2];
}

double Triangle::getPerimeter() const
{
	double lengthAB = this->a_->getDistance(this->getB());
	double lengthBC = this->b_->getDistance(this->getC());
	double lengthCA = this->c_->getDistance(this->getA());

	if (!this->isTriangle())
	{
		return std::max(lengthAB, std::max(lengthBC, lengthCA));
	}
	else
	{
		return lengthAB + lengthBC + lengthCA;
	}
}

// Расчёт площади по формуле Герона.
double Triangle::getArea() const
{
	double sideAB = this->getA().getDistance(this->getB());
	double sideBC = this->getB().getDistance(this->getC());
	double sideAC = this->getC().getDistance(this->getA());

	double halfPerimeter = this->getPerimeter() / 2;

	double area =
		sqrt(halfPerimeter *
			(halfPerimeter - sideAB) *
			(halfPerimeter - sideBC) *
			(halfPerimeter - sideAC));

	return area;
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

void Triangle::operator=(const Triangle& triangle)
{
}

bool Triangle::operator==(const Triangle& triangle)
{
	return this->isEqual(triangle);
}

bool Triangle::operator<(const Triangle& triangle)
{
	double firstArea = this->getArea();
	double seconArea = triangle.getArea();

	return std::abs(firstArea - seconArea) < COMPARISON_EPSILON;
}

Triangle Triangle::operator+(double k)
{
	return Triangle(*this->a_ + k, *this->b_ + k, *this->c_ + k);
}

Triangle& Triangle::operator+=(const double k)
{
	*this->a_ += k;
	*this->b_ += k;
	*this->c_ += k;

	return *this;
}

std::ostream& operator<<(std::ostream& output, const Triangle& triangle)
{
	Point* point = new Point(triangle.getA());
	output << *point;
	output << ", ";

	delete point;
	point = new Point(triangle.getB());

	output << *point;
	output << ", ";

	delete point;
	point = new Point(triangle.getC());

	output << *point;
	
	delete point;

	return output;
}

std::istream& operator>>(std::istream& input, Triangle& triangle)
{
	input >> *triangle.a_;
	input >> *triangle.b_;
	input >> *triangle.c_;

	return input;
}

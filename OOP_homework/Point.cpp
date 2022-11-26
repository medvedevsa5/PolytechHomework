#include "point.h"
#include <cmath>

const double COMPARISON_EPSILON = 0.00'000'1;

Point::Point()
{
	_x = 0;
	_y = 0;
}

Point::Point(double x, double y)
{
	this->_x = x;
	this->_y = y;
}

Point::Point(const Point& point)
{
	this->_x = point._x;
	this->_y = point._y;
}

Point::~Point()
{
}

void Point::setX(const double x)
{
	this->_x = x;
}

void Point::setY(const double y)
{
	this->_y = y;
}

double Point::getX() const
{
	return this->_x;
}

double Point::getY() const
{
	return this->_y;
}

bool Point::isEqual(const Point& point) const
{
	return abs(this->_x - point._x) < COMPARISON_EPSILON && abs(this->_y - point._y) < COMPARISON_EPSILON;
}

double Point::getDistance(const Point& point) const
{
	double firstPow = std::pow(point._x - this->_x, 2);
	double secondPow = std::pow(point._y - this->_y, 2);
	return std::sqrt(firstPow + secondPow);
}

void Point::move(double k)
{
	this->_x += k;
	this->_y += k;
}

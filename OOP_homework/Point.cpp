#include "Point.h"
#include <cmath>

Point::Point()
{
	this->_x = 0;
	this->_y = 0;
}
Point::Point(double x, double y)
{
	this->_x = x;
	this->_y = y;
}
Point::Point(const Point& point)
{
	this->_x = point.getX();
	this->_y = point.getY();
}
Point::~Point(){}


double Point::getX() const
{
	return this->_x;

}
void Point::setX(double x) 
{
	this->_x = x;
}

double Point::getY() const
{
	return this->_y;
}
void Point::setY(double y)
{
	this->_y = y;
}

bool Point::isEqual(const Point& point) const
{
	return this->_x == point.getX() && this->_y == point.getY() ? true : false;
}

double Point::getDistance(const Point& point) const
{
	double distance = sqrt(pow(this->_x - point._x, 2) + pow(this->_y - point._y, 2));
	return distance;
}

void Point::move(double k)
{
	this->_x += k;
	this->_y += k;
}

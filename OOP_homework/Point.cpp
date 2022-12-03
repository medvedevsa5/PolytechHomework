#include "point.h"
#include <cmath>

const double COMPARISON_EPSILON = 0.000001;

Point::Point()
{
	x_ = 0;
	y_ = 0;
}

Point::Point(double x, double y)
{
	this->x_ = x;
	this->y_ = y;
}

Point::Point(const Point& point)
{
	this->x_ = point.x_;
	this->y_ = point.y_;
}

Point::~Point()
{
}

void Point::setX(const double x)
{
	this->x_ = x;
}

void Point::setY(const double y)
{
	this->y_ = y;
}

double Point::getX() const
{
	return this->x_;
}

double Point::getY() const
{
	return this->y_;
}

bool Point::isEqual(const Point& point) const
{
	return abs(this->getX() - point.getX()) < COMPARISON_EPSILON
		&& abs(this->getY() - point.getY()) < COMPARISON_EPSILON;
}

double Point::getDistance(const Point& point) const
{
	double firstPow = std::pow(point.getX() - this->getX(), 2);
	double secondPow = std::pow(point.getY() - this->getY(), 2);
	return std::sqrt(firstPow + secondPow);
}

void Point::move(double k)
{
	this->setX(this->getX() + k);
	this->setY(this->getY() + k);
}

bool Point::operator==(const Point& right) const
{
	double differenceX = this->getX() - right.getX();
	double differenceY = this->getY() - right.getY();

	return abs(differenceX) < COMPARISON_EPSILON
		&& abs(differenceY) < COMPARISON_EPSILON;
}

bool Point::operator<(const Point& right) const
{
	double squareSum1 = pow(this->getX(), 2) + pow(this->getY(), 2);
	double squareSum2 = pow(right.getX(), 2) + pow(right.getY(), 2);

	bool isEqual = abs(squareSum1 - squareSum2) < COMPARISON_EPSILON;

	return !isEqual && (squareSum1 < squareSum2);
}

bool Point::operator>=(const Point& right) const
{
	double squareSum1 = pow(this->getX(), 2) + pow(this->getY(), 2);
	double squareSum2 = pow(right.getX(), 2) + pow(right.getY(), 2);

	bool isEqual = abs(squareSum1 - squareSum2) < COMPARISON_EPSILON;

	return isEqual || (squareSum1 > squareSum2);
}

Point Point::operator+(const double k) const
{

	return Point();
}


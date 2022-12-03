#include "Point.h"
#include <cmath>
#include <iostream>

const double COMPARISON_EPSILON = 0.000001;

Point::Point()
{
	std::cerr << std::endl << "Вызов конструктора Point" << std::endl;
	x_ = 0;
	y_ = 0;
}

Point::Point(double x, double y) : Point::Point()
{
	this->x_ = x;
	this->y_ = y;
}

Point::Point(const Point& point) : Point::Point()
{
	this->x_ = point.x_;
	this->y_ = point.y_;
}

Point::~Point()
{
	std::cerr << std::endl << "Вызов деструктора Point" << std::endl;
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
	return Point(this->getX() + k, this->getY() + k);
}

Point& Point::operator+=(double k)
{
	this->setX(this->getX() + k);
	this->setY(this->getY() + k);

	return *this;
}

std::ostream& operator<<(std::ostream& output, Point& point)
{
	output << "[" << " " << point.getX() << ", " << point.getY() << " " << "]";
	return output;
}

std::istream& operator>>(std::istream& input, Point& point)
{
	double x = 0;
	double y = 0;

	input >> x >> y;

	point.setX(x);
	point.setX(y);

	return input;
}

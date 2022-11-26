#pragma once

class Point
{
private:
	double _x;
	double _y;

public:
	Point();
	Point(double x, double y);
	Point(const Point& point);
	~Point();

	void setX(const double x);
	void setY(const double y);

	double getX() const;
	double getY() const;

	bool isEqual(const Point& point) const;

	double getDistance(const Point& point) const;

	void move(double k);
};

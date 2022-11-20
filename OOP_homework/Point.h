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

public:
	double getX() const;
	void setX(double x);

	double getY() const;
	void setY(double y);

	bool isEqual(const Point& point) const;
	double getDistance(const Point& point) const;

	void move(double k);
};

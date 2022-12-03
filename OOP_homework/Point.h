#pragma once

class Point
{
private:
	double x_;
	double y_;

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

	

	bool operator==(const Point& right) const;

	bool operator<(const Point& right) const;

	bool operator>=(const Point& right) const;

	Point operator+(const double k) const;
	
	Point operator+=(const Point& right);
};

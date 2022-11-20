// OOP_homework.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iomanip>
#include <iterator>
#include "Triangle.h"
#include "Point.h"

const double COMPARE_EPSILON = 0.000001;

double getArea(const Triangle& triangle);
bool isEqualArea(const Triangle** triangleArray, const int length);


int main()
{
	setlocale(LC_ALL, "ru");

	double coord1[2] = { 0, 0 };
	double coord2[2] = { 0, 0 };
	double coord3[2] = { 0, 0 };

	//std::cout << "Введите координаты точки a : ";
	//std::cin >> coord1[0] >> coord1[1];
	//std::cout << "Введите координаты точки b : ";
	//std::cin >> coord2[0] >> coord2[1];
	//std::cout << "Введите координаты точки c : ";
	//std::cin >> coord3[0] >> coord3[1];

	//Point* point1 = new Point(coord1[0], coord1[1]);
	//Point* point2 = new Point(coord2[0], coord2[1]);
	//Point* point3 = new Point(coord3[0], coord3[1]);

	Triangle** triangleArray = new Triangle*[10];

	Point* point1 = new Point(rand() % 101 - 50, rand() % 101 - 50);
	Point* point2 = new Point(rand() % 101 - 50, rand() % 101 - 50);
	Point* point3 = new Point(rand() % 101 - 50, rand() % 101 - 50);
	for (size_t i = 0; i < 10; i++)
	{
		triangleArray[i] = new Triangle(*point1, *point2, *point3);

	}
	delete point1;
	delete point2;
	delete point3;

	for (int i = 0; i < 10 - 1; i++)
	{
		try
		{
			std::cout << "Площади " << (triangleArray[i]->isEqual(*triangleArray[i + 1]) ? "равны" : "не равны") << std::endl;
		}
		catch (std::exception e)
		{
			std::cout << "Ошибка!!!! " << e.what();
		}
	}

	for(int i = 0; i < 10; i++)
	{
		delete triangleArray[i];
	}
	delete[] triangleArray;

}

bool isEqualArea(const Triangle** triangleArray, const int length)
{
	bool isEqual = true;
	bool difference = 0.0;

	for (size_t i = 0; i < length - 1; i++)
	{
		difference = getArea(*triangleArray[i]) - getArea(*triangleArray[i+1]);
		if(fabs(difference) < COMPARE_EPSILON)
		{
			isEqual = false;
			break;
		}
	}
	return isEqual;
}

double getArea(const Triangle& triangle)
{
	Point* pointA = triangle.getA();
	Point* pointB = triangle.getB();
	Point* pointC = triangle.getC();

	double lengthAB = pointA->getDistance(*pointB);
	double lengthBC = pointB->getDistance(*pointC);
	double lengthCA = pointC->getDistance(*pointA);

	double halfPerimeter = triangle.getPerimeter() / 2;

	double area = sqrt(halfPerimeter*(halfPerimeter - lengthAB)*(halfPerimeter - lengthBC)*(halfPerimeter - lengthCA));

	return area;
}

void output(const Triangle** triangleArr, int arrLength)
{
	
}


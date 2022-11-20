// OOP_homework.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Triangle.h"
#include "Point.h"

int main()
{
	setlocale(LC_ALL, "ru");

	double Coord1[2] = { 0, 0 };
	double Coord2[2] = { 0, 0 };
	double Coord3[2] = { 0, 0 };

	std::cout << "Введите координаты точки a : ";
	std::cin >> Coord1[0] >> Coord1[1];
	std::cout << "Введите координаты точки b : ";
	std::cin >> Coord2[0] >> Coord2[1];
	std::cout << "Введите координаты точки c : ";
	std::cin >> Coord3[0] >> Coord3[1];

	Point* point1 = new Point(Coord1[0], Coord1[1]);
	Point* point2 = new Point(Coord2[0], Coord2[1]);
	Point* point3 = new Point(Coord3[0], Coord3[1]);

	Triangle* triangle1 = new Triangle(*point1, *point2, *point3);

	try
	{
		std::cout << triangle1->getPerimeter();
	}
	catch(std::exception e)
	{
		std::cout << "Ошибка!!!! " << e.what();
	}


	delete triangle1;
	//delete triangle2;
	//delete triangle3;
}

bool isEqualSquare(const Triangle**)
{
	return false;
}

void output(const Triangle**)
{
	
}
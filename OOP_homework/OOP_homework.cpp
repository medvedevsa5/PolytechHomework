// OOP_homework.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "Triangle.h"

int main()
{
	Triangle* triangle1 = new Triangle();
	Triangle* triangle2 = new Triangle();
	Triangle* triangle3 = new Triangle();

	std::cout << triangle1->getPerimeter();

	delete triangle1;
	delete triangle2;
	delete triangle3;
}

bool isEqualSquare(const Triangle**)
{
	return false;
}

void output(const Triangle**)
{
	
}
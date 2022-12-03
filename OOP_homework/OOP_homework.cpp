#include <iostream>
#include <cmath>
#include "Point.h"
#include "Triangle.h"

bool isEqualSquare(const Triangle& triangle1, const Triangle& triangle2);
void output(const Triangle& triangle);
void wrongInputTerminate();

const double COMPARISON_EPSILON = 0.00'000'1;

int main()
{
	setlocale(LC_ALL, "ru");

	FILE* stream;
	freopen_s(&stream, "output.txt", "w", stderr);

	double coordArray[2] = { 0, 0 };

	Triangle* triangle1 = new Triangle();
	Triangle* triangle2 = new Triangle();

	std::cout << "Введите шесть координат 1 треугольника: ";
	std::cin >> *triangle1;
	if (!std::cin) wrongInputTerminate();
	std::cout << std::endl;

	std::cout << "Введите шесть координат 1 треугольника: ";
	std::cin >> *triangle2;
	if (!std::cin) wrongInputTerminate();
	std::cout << std::endl;

	std::cout << "Вершины треугольника 1 - ";
	std::cout << *triangle1 << std::endl;
	
	std::cout << "Вершины треугольника 2 - ";
	std::cout << *triangle1 << std::endl;


	std::cout << "Треугольники" 
		<< (triangle1->isEqual(*triangle2) ? " " : " не ") 
		<< "равны. " << std::endl;

	try
	{
		std::cout
			<< "Периметр треугольника 1 - " << triangle1->getPerimeter()
			<< ", треугольника 2 - " << triangle2->getPerimeter()
			<< std::endl;

		std::cout << "Треугольники" 
			<< (isEqualSquare(*triangle1, *triangle2) ? " " : " не ") 
			<< "равны по площади. " << std::endl;
	}
	catch(std::exception &e)
	{
		std::cout << "Ошибка! - " << e.what();
	}

	delete triangle1;
	delete triangle2;
}


bool isEqualSquare(const Triangle& triangle1, const Triangle& triangle2)
{
	double firstArea = triangle1.getArea();

	double secondArea = triangle2.getArea();

	return (abs(firstArea - secondArea) < COMPARISON_EPSILON);
}


void output(const Triangle& triangle)
{
	std::cout << triangle;
}


void wrongInputTerminate()
{
	std::cerr << "Неверный ввод!";
	exit(-1);
}

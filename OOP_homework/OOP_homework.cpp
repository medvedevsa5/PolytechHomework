#include <iostream>
#include <cmath>
#include "Point.h"
#include "Triangle.h"

bool isEqualSquare(const Triangle& triangle1, const Triangle& triangle2);
void output(const Triangle& triangle);
void wrongInputTerminate();

const double COMPARISON_EPSILON = 0.000'001;

int main()
{
	setlocale(LC_ALL, "ru");

	double coordArray[2] = { 0, 0 };

	Point pointA = Point();
	Point pointB = Point();
	Point pointC = Point();

	Triangle* triangle1 = nullptr;
	Triangle* triangle2 = nullptr;

	//-----------------------------------------------------------------

	std::cout << "Введите координаты точки A первого треугольника: ";
	std::cin >> coordArray[0] >> coordArray[1];

	if (!std::cin) wrongInputTerminate();

	pointA.setX(coordArray[0]);
	pointA.setY(coordArray[1]);

	std::cout << "Введите координаты точки B первого треугольника: ";
	std::cin >> coordArray[0] >> coordArray[1];

	if (!std::cin) wrongInputTerminate();

	pointB.setX(coordArray[0]);
	pointB.setY(coordArray[1]);

	std::cout << "Введите координаты точки C первого треугольника: ";
	std::cin >> coordArray[0] >> coordArray[1];

	if (!std::cin) wrongInputTerminate();

	pointC.setX(coordArray[0]);
	pointC.setY(coordArray[1]);

	triangle1 = new Triangle(pointA, pointB, pointC);

	//-----------------------------------------------------------------

	std::cout << std::endl;

	//-----------------------------------------------------------------

	std::cout << "Введите координаты точки A второго треугольника: ";
	std::cin >> coordArray[0] >> coordArray[1];

	if (!std::cin) wrongInputTerminate();

	pointA.setX(coordArray[0]);
	pointA.setY(coordArray[1]);

	std::cout << "Введите координаты точки B второго треугольника: ";
	std::cin >> coordArray[0] >> coordArray[1];

	if (!std::cin) wrongInputTerminate();

	pointB.setX(coordArray[0]);
	pointB.setY(coordArray[1]);

	std::cout << "Введите координаты точки C второго треугольника: ";
	std::cin >> coordArray[0] >> coordArray[1];

	if (!std::cin) wrongInputTerminate();

	pointC.setX(coordArray[0]);
	pointC.setY(coordArray[1]);

	triangle2 = new Triangle(pointA, pointB, pointC);

	//-----------------------------------------------------------------

	std::cout << std::endl;

	std::cout << "Вершины треугольника 1 - ";
	output(*triangle1);
	std::cout << std::endl;
	
	std::cout << "Вершины треугольника 2 - ";
	output(*triangle2);
	std::cout << std::endl << std::endl;

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
	double firstAB = triangle1.getA().getDistance(triangle1.getB());
	double firstBC = triangle1.getB().getDistance(triangle1.getC());
	double firstAC = triangle1.getC().getDistance(triangle1.getA());;

	double firstHalfPerimeter = triangle1.getPerimeter() / 2;

	double firstArea =
		sqrt(firstHalfPerimeter *
			(firstHalfPerimeter - firstAB) *
			(firstHalfPerimeter - firstBC) *
			(firstHalfPerimeter - firstAC));

	double secondAB = triangle2.getA().getDistance(triangle2.getB());
	double secondBC = triangle2.getB().getDistance(triangle2.getC());;
	double secondAC = triangle2.getC().getDistance(triangle2.getA());;;

	double secondHalfPerimeter = triangle2.getPerimeter() / 2;

	double secondArea =
		sqrt(secondHalfPerimeter *
			(secondHalfPerimeter - secondAB) *
			(secondHalfPerimeter - secondBC) *
			(secondHalfPerimeter - secondAC));

	return (abs(firstArea - secondArea) < COMPARISON_EPSILON);
}

void output(const Triangle& triangle)
{
	std::cout
		<< "{" << triangle.getA().getX() << ", " << triangle.getA().getY() << "} "
		<< "{" << triangle.getB().getX() << ", " << triangle.getB().getY() << "} "
		<< "{" << triangle.getC().getX() << ", " << triangle.getC().getY() << "} ";
}

void wrongInputTerminate()
{
	std::cerr << "Неверный ввод!";
	exit(-1);
}

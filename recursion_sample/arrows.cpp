#include <iostream>
#include <cmath>


typedef double(*IntegrateFunction)(double);

// Метод средних прямоугольников
double integrateRectangle(IntegrateFunction f, double a, double b, int n)
{
	double sum = 0.0;
	double step = (b - a) / n;
	for (int i = 0; i < n; ++i)
	{
		sum += f(a + step * (i + 0.5));
	}
	return sum * step;
}

// Точность определяется по правилу Рунге
// https://ru.wikipedia.org/wiki/%D0%9F%D1%80%D0%B0%D0%B2%D0%B8%D0%BB%D0%BE_%D0%A0%D1%83%D0%BD%D0%B3%D0%B5
double integrate(IntegrateFunction f, double a, double b, double error)
{
	if (error <= 0)
	{
		throw std::invalid_argument("Error should be positive");
	}
	const double THETA = 1.0 / 3.0;
	int nSteps = 1;
	double res1 = integrateRectangle(f, a, b, nSteps);
	nSteps *= 2;
	double res2 = integrateRectangle(f, a, b, nSteps);
	while (abs(res2 - res1) * THETA > error)
	{
		res1 = res2;
		nSteps *= 2;
		res2 = integrateRectangle(f, a, b, nSteps);
	}
	return res2;
}

double f1(double x)
{
	return x * x;
}

double f2(double x)
{
	return x * x * x;
}

int main()
{
	double lower;
	std::cout << "Lower bound: ";
	std::cin >> lower;
	double upper;
	std::cout << "Upper bound: ";
	std::cin >> upper;
	double error;
	std::cout << "Error: ";
	std::cin >> error;

	std::cout << "1/x: " << integrate([](double x) { return 1.0 / log(x); }, lower, upper, error) << '\n';

	return 0;
}
// homework_9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

const long double MAX_INTERVAL[2] = { -1 + std::numeric_limits<long double>::epsilon(), 1 - std::numeric_limits<long double>::epsilon() };

void printSheet(int** matrix, int columnCount, int rowCount);

long double getTaylor(long double x, long double absError, int numberMax);
long double getCoefficient(int x);
long double getPower(long double base, int power);
long double getAbs(long double number);

int main()
{
	setlocale(LC_ALL, "ru");

	long double absError = 0;
	long double x = 0;
	int numberMax = 0;
	long double interval[2] = { 0, 0 };
	long double intervalStep = 0;
	int** matrix = nullptr;

	try
	{
		std::cout << "Введите погрешность вычисления: ";
		std::cin >> absError;
		std::cout << "Введите максимальное число слагаемых ряда: ";
		std::cin >> numberMax;
		std::cout << "Введите начало и конец промежутка (включительно): ";
		std::cin >> interval[0] >> interval[1];
		if(interval[0] > interval[1]) 
		{
			std::cout << "Начало не может быть больше конца!";
			return -1;
		}
		if(interval[0] < MAX_INTERVAL[0] || interval[1] > MAX_INTERVAL[1])
		{
			std::cout << "Неразрешённый промежуток!";
			return -1;
		}
		std::cout << "Введите шаг интервала: ";
		std::cin >> intervalStep;
	}
	catch(std::exception e)
	{
		std::cout << "Вы где-то напортачили!";
	}

	int sheetWidth = 20;

	
	std::cout << std::endl << std::setw(sheetWidth - 5) << " x |" << std::setw(sheetWidth) << "using Taylor |" << std::setw(sheetWidth) << "using cmath |" << std::endl;
	std::cout << std::string(sheetWidth * 3 - 5, '=') << std::endl;

	for (long double x = interval[0]; x < interval[1]+intervalStep/2; x += intervalStep)
	{
		long double taylor = getTaylor(x, absError, numberMax);
		long double standartLib = (1 / sqrtl(1 - powl(x, 2)));

		std::cout << std::setw(sheetWidth - 5 - 2) << x << " |" << std::setw(sheetWidth - 2) << taylor << " |" << std::setw(sheetWidth - 2) << standartLib << " |" << std::endl;
	}
}

// вернуть результат 
long double getTaylor(long double x, long double absError, int numberMax)
{
	if (numberMax < 1)
	{
		throw std::exception("Количество шагов не может быть меньше 1! ");
	}
	if (numberMax == 1)
	{
		return 1;
	}
	else 
	{
		long double coefficient = getCoefficient(numberMax);
		long double poweredX = getPower(x, (numberMax - 1) * 2);
		long double member = coefficient * poweredX;

		if (abs(member) < absError) member = 0;

		return (member + getTaylor(x, absError, numberMax - 1));
	}
}

// вернуть коэффициент перед х
long double getCoefficient(int numberMax)
{
	if (numberMax <= 1)
	{
		return 1;
	}
	else
	{
		long double numerator = 2 * numberMax - 3;
		long double denominator = 2 * numberMax - 2;
		return ((numerator / denominator) * getCoefficient(numberMax - 1));
	}
}

// вернуть степень числа
long double getPower(long double base, int power)
{
	if (power < 1) return 1;
	return base * getPower(base, power - 1);
}

// вернуть абсолютное значение long double
long double getAbs (long double number)
{
	return number >= 0 ? number : -number;
}

// вывод результатов в виде таблицы
void printSheet(int** matrix, int columnCount, int rowCount)
{
	std::cout << std::setw(10) << " x |" << std::setw(15) << "using Taylor |" << std::setw(15) << "using cmath |" << std::endl;
	std::cout << std::string(40, '=') << std::endl;
	for (size_t i = 0; i < columnCount; i++)
	{
		std::cout << std::setw(10) << " x |" << std::setw(15) << "using Taylor |" << std::setw(15) << "using cmath |" << std::endl;
	}
}
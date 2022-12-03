// homework_9.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <unordered_map>

enum ErrorCase
{
	ErrorError,
	TermCountError,
	IntervalOrderError,
	IntervalLengthError,
	StepError
};

const long double MAX_INTERVAL[2] = 
	{ -1 + std::numeric_limits<long double>::epsilon(), 1 - std::numeric_limits<long double>::epsilon() };

const int MAX_TERM_NUMBER = 10000;
const int SHEET_WIDTH = 20;

long double getTaylor(long double x, long double absError, int numberMax);
long double getCoefficient(int x);
long double getPower(long double base, int power);
long double getAbs(long double number);

void terminateWithError(const ErrorCase& error);

// --------------------------------------------------------------------------------
// Всё ненужное удалил, но, что насчёт 1 пункта - оказывается, всё и так работало.
// Если ввести погрешность 0.00001, а количество слагаемых 10, то функция 
// getTaylor инициирует исключение.
// --------------------------------------------------------------------------------

int main()
{
	setlocale(LC_ALL, "ru");

	long double absError = 0;
	long double x = 0;
	int numberMax = 0;
	long double interval[2] = { 0, 0 };
	long double intervalStep = 0;

	try
	{
		std::cout << "Введите погрешность вычисления: ";
		std::cin >> absError;
		if (absError < 0)
			terminateWithError(ErrorCase::ErrorError);

		std::cout << "Введите максимальное число слагаемых ряда: ";
		std::cin >> numberMax;
		if (numberMax < 0 || numberMax > MAX_TERM_NUMBER)
			terminateWithError(ErrorCase::TermCountError);

		std::cout << "Введите начало и конец промежутка (включительно): ";
		std::cin >> interval[0] >> interval[1];
		if(interval[0] > interval[1]) 
			terminateWithError(ErrorCase::IntervalOrderError);

		if(interval[0] < MAX_INTERVAL[0] || interval[1] > MAX_INTERVAL[1])
			terminateWithError(ErrorCase::IntervalLengthError);

		std::cout << "Введите шаг интервала: ";
		std::cin >> intervalStep;
		if (intervalStep >= 1 || intervalStep <= 0)
			terminateWithError(ErrorCase::StepError);
	}
	catch(std::exception& e)
	{
		std::cout << "Вы где-то напортачили! - " << e.what();
		return -1;
	}

	std::cout << std::endl << std::setw(SHEET_WIDTH - 5) << " x |" << std::setw(SHEET_WIDTH) << "using Taylor |" << std::setw(SHEET_WIDTH) << "using cmath |" << std::endl;
	std::cout << std::string(SHEET_WIDTH * 3 - 5, '=') << std::endl;

	for (long double x = interval[0]; x < interval[1] + intervalStep / 2; x += intervalStep)
	{
		long double taylor = 0;
		long double standartLib = 0;
		try 
		{
			taylor = getTaylor(x, absError, numberMax);
			standartLib = (1 / sqrtl(1 - powl(x, 2)));
		}
		catch(std::exception& e)
		{
			std::cout << std::setw(SHEET_WIDTH - 5 - 2) << x << " |" << std::setw(SHEET_WIDTH * 2 - 2) << e.what() << " |" << std::endl;
			continue;
		}
		std::cout << std::setw(SHEET_WIDTH - 5 - 2) << x << " |" << std::setw(SHEET_WIDTH - 2) << taylor << " |" << std::setw(SHEET_WIDTH - 2) << standartLib << " |" << std::endl;	
	}
}

// вернуть результат 
long double getTaylor(long double x, long double absError, int numberMax)
{
	int i = 1;
	long double term = 1;
	long double result = 0;

	while(i < numberMax && getAbs(term) > absError)
	{
		long double coefficient = getCoefficient(i);
		long double poweredX = getPower(x, (i - 1) * 2);

		term = coefficient * poweredX;
		result += term;
		i++;
	}

	if(getAbs(term) < absError && i >= numberMax )
	{
		throw std::exception("Максимальная точность не достигнута!");
	}

	return result;

}

// вернуть коэффициент перед х
long double getCoefficient(int position)
{
	if (position <= 1)
	{
		return 1;
	}
	else
	{
		long double numerator = 2 * position - 3;
		long double denominator = 2 * position - 2;
		return ((numerator / denominator) * getCoefficient(position - 1));
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

void terminateWithError(const ErrorCase& error)
{
	std::string errorMessage = "";

	switch (error)
	{
	case ErrorCase::ErrorError:
		errorMessage = "Погрешность должна быть больше 0!";
		break;
	case ErrorCase::TermCountError:
		errorMessage = "Число слагаемых не может быть меньше 0!";
		break;
	case ErrorCase::IntervalOrderError:
		errorMessage = "Начало не может быть больше конца!";
		break;
	case ErrorCase::IntervalLengthError:
		errorMessage = "Неразрешённый промежуток!";
		break;
	case ErrorCase::StepError:
		errorMessage = "Шаг интервала не может быть больше 1 или меньше 0";
		break;
	default:
		errorMessage = "Произошла непредвиденная ошибка!";
		break;
	}

	std::hash<std::string> hashGenerator;

	size_t stringHash = hashGenerator(errorMessage);

	std::cout << "Ошибка! - " << errorMessage;

	exit(stringHash);
}

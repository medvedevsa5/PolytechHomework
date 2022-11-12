#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>

bool isReal(char*& str);
bool isMantissa(const char*& str);
bool isExhibitor(const char*& str);
bool isUnsignedInteger(const char* leftBorder, const char* rightBorder);
bool isDigit(const char*& str);
bool isSign(const char*& str);
char* endOfStr(const char*& str);

const int MAX_INPUT_LENGTH = 256;

int main()
{
	std::setlocale(LC_ALL, "Russian");
	std::cin >> std::setw(MAX_INPUT_LENGTH);

	char* nomber = new char[MAX_INPUT_LENGTH];

	for (;;)
	{
		std::cout << "Введите вещественное число в экспоненциальной форме записи : ";
		
		std::cin >> nomber;

		std::cout << isReal(nomber) ? "Правда\n\n" : "Ложь\n\n";
	}

	delete[] nomber;
}

bool isReal(const char *& str)
{
	isSign(str);

	return isMantissa(str) && isExhibitor(str) && *str == '\0';
}

bool isMantissa(const char*& str)
{
	const char* rightBorder = endOfStr(str);
	const char* EPosition = str - 1;
	if (*EPosition == 'E')
	{
		return (isSign(str) && (str + 1 != rightBorder)) ? (isUnsignedInteger(str + 1, rightBorder)) : false;
	}
}

bool isExhibitor(const char*& str)
{

}

bool isUnsignedInteger(const char* leftBorder, const char* rightBorder)
{
	if (leftBorder == rightBorder)
	{
		return true;
	}
	if (isdigit(*leftBorder))
	{
		return isUnsignedInteger(leftBorder + 1, rightBorder);
	}
	else
	{
		return false;
	}
}

bool isDigit(const char*& str)
{
	return std::isdigit(*str);
}

bool isSign(const char*& str)
{
	return (*str == '-' || *str == '+');
}

char* endOfStr(char* num)
{
	return (*num == '\0') ? num : endOfStr(num + 1);
}
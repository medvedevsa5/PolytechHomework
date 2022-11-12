#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>

bool isReal(char* str);
bool isMantissa(char* str, char* EPosition);
bool isExhibitor(char* str);
bool isUnsignedInteger(char* leftBorder, char* rightBorder);
bool isDigit(char* str);
bool isSign(char* str);
char* endOfStr(char* str);

const int MAX_INPUT_LENGTH = 256;

int main()
{
	std::setlocale(LC_ALL, "Russian");
	std::cin >> std::setw(MAX_INPUT_LENGTH);

	char* inputNumber = new char[MAX_INPUT_LENGTH];

	for (;;)
	{
		std::cout << "Введите вещественное число в экспоненциальной форме записи : ";
		
		std::cin >> inputNumber;

		if(inputNumber == "quit")
		{
			delete[] inputNumber;
			return 0;
		}

		std::cout << std::endl;

		std::cout << (isReal(inputNumber) ? "Число вещественное\n\n" : "Число не вещественное\n\n");
	}

	delete[] inputNumber;
}

bool isReal(char* str)
{
	bool isSigned = isSign(str);

	char* EString = strstr(str, "E");

	if (!EString)
	{
		return false;
	}
	else if (isDigit(str + isSigned))
	{
		return isMantissa(str + isSigned, EString) && isExhibitor(EString + 1);
	}
	else
	{
		return false;
	}
}

bool isMantissa(char* str, char* EString)
{
	char* dotString = strstr(str, ".");

	if(!dotString)
	{
		dotString = EString;
		if (isUnsignedInteger(str, dotString))
		{
			return true;
		}
	}
	if (dotString + 1 == EString)
	{
		return false;
	}
	if (isUnsignedInteger(str, dotString) && isUnsignedInteger(dotString + 1, EString))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool isExhibitor(char* str)
{
	char* rightBorder = endOfStr(str);
	char* EPosition = str - 1;
	if (*EPosition == 'E')
	{
		return (isSign(str) && (str + 1) != rightBorder) ? (isUnsignedInteger(str + 1, rightBorder)) : false;
	}
	else
	{
		return false;
	}
}

bool isUnsignedInteger(char* leftBorder, char* rightBorder)
{
	if (leftBorder == rightBorder)
	{
		return true;
	}
	if (isDigit(leftBorder))
	{
		return isUnsignedInteger(leftBorder + 1, rightBorder);
	}
	else
	{
		return false;
	}
}

bool isDigit(char* str)
{
	return std::isdigit(*str);
}

bool isSign(char* str)
{
	return (*str == '-' || *str == '+');
}

char* endOfStr(char* num)
{
	return (*num == '\0') ? num : endOfStr(num + 1);
}
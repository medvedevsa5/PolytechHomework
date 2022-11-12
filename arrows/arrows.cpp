#include <iostream>
#include <iomanip>


bool isReal(char* num);
bool isMantissa(char* num, char* EPosition);
bool isExponent(char* num);
bool isUnsignedInt(char* leftBorder, char* rightBorder);
bool isSign(char* num);
char* endOfStr(char* num);


bool isReal(char* num)
{
    char* EPosition = strstr(num, "E");
    if (!EPosition)
        EPosition = strstr(num, "e");
    if (isdigit(*num) or *num == '.')
        return (isMantissa(num, EPosition) and isExponent(EPosition + 1));
    else
        return false;
}

bool isMantissa(char* num, char* EPosition)
{
    char* dotPosition = strstr(num, ".");
    if (dotPosition + 1 == EPosition)
        return false;
    if (isUnsignedInt(num, dotPosition) and isUnsignedInt(dotPosition + 1, EPosition))
        return true;
    else
        return false;
}

bool isUnsignedInt(char* leftBorder, char* rightBorder)
{
    if (leftBorder == rightBorder)
        return true;
    if (isdigit(*leftBorder))
        return isUnsignedInt(leftBorder + 1, rightBorder);
    else
        return false;
}

bool isExponent(char* num)
{
    char* rightBorder = endOfStr(num);
    char* EPosition = num - 1;
    if (*EPosition == 'E')
    {
        if (isSign(num) and (num + 1 != rightBorder))
            return (isUnsignedInt(num + 1, rightBorder));
        else
            return false;
    }
    else if (*EPosition == 'e')
    {
        if (isdigit(*num))
            return (isUnsignedInt(num, rightBorder));
        else
            return false;
    }
    else
        return false;
}

char* endOfStr(char* num)
{
    if (*num == '\0')
        return (num);
    return endOfStr(num + 1);
}

bool isSign(char* num)
{
    if (*num == '-' or *num == '+')
        return true;
    else
        return false;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    while (true)
    {
        char* num = new char[100]();
        std::cout << "Введите вещественное число: ";
        std::cin >> std::setw(100) >> num;
        if (isReal(num))
            std::cout << "Это вещественное число\n";
        else
            std::cout << "Это не вещественное число\n";
    }
}

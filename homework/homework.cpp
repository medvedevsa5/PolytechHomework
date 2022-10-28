#define COMPLETE_TEST
#include <iostream>
#include <string>
#include <fstream>

char* trimCharString(char* result, const char delim);
char* removeZeroChar(char* result, const int length);
char* getSimilarChars(char* result, const char* source1, const char* source2);

int main() 
{
	setlocale(LC_ALL, "ru");

#if defined(COMPLETE_TEST)

	char* filepath = new char[256];
	std::cout << "Введите путь к файлу (можно с \" \"): ";
	std::cin >> filepath;
	trimCharString(filepath, '\"');

	std::ifstream filestream;
	filestream.open(filepath);
	if (!filestream.is_open())
	{
		std::cerr << "Файл не открылся!";
		return -1;
	}

	int firstLineLength = 0;
	int secondLineLength = 0;
	char* firstLine = nullptr;
	char* secondLine = nullptr;
	char* result = nullptr;

	while(!filestream.eof())
	{
		filestream >> firstLineLength;
		firstLine = new char[firstLineLength + 1];

		filestream.ignore(std::cin.rdbuf()->in_avail(), '\n');
		filestream >> secondLineLength;
		secondLine = new char[secondLineLength + 1];

		filestream.ignore(std::cin.rdbuf()->in_avail(), '\n');
		filestream >> firstLine;
		firstLine[firstLineLength] = '\0';

		filestream.ignore(std::cin.rdbuf()->in_avail(), '\n');
		filestream >> secondLine;
		secondLine[secondLineLength] = '\0';

		std::cout << "\nВы ввели:\n"
			<< '\t' << "1. строку { " << firstLine << " } размером " << firstLineLength << " символов.\n"
			<< '\t' << "2. строку { " << secondLine << " } размером " << secondLineLength << " символов.\n";
		
		int maxLength = (firstLineLength >= secondLineLength) ? firstLineLength : secondLineLength;
		result = new char[maxLength];
		result = getSimilarChars(result, firstLine, secondLine);

		std::cout << "\nСтрока состоящая из идентичных символов:\n"
			<< "-\n" << result << "\n-";
	}

	delete[] filepath;
	delete[] firstLine;
	delete[] secondLine;
	delete[] result;

#endif
	return 0;
}

/// <summary>
/// Удаляет любые вхождения заданного символа из строки
/// </summary>
/// <param name="result"> - строка в которой следует удалить символ</param>
/// <param name="delim"> - символ, который следует удалить</param>
/// <returns></returns>
char * trimCharString(char* result, const char delim)
{
	int length = 0;
	while (*(result + length))
	{
		++length;
	}
	for (size_t i = 0; i < length; i++)
	{
		if(*(result + i) == '"')
		{
			*(result + i) = '\0';
		}
		if (*(result + length - i) == '"')
		{
			*(result + length - i) = '\0';
		}
	}
	result = removeZeroChar(result, length);
	return result;
}

/// <summary>
/// Переносит все нуль-терминаторы в конец строки
/// </summary>
/// <param name="result"> - строка</param>
/// <param name="length"> - длина строки</param>
/// <returns></returns>
char * removeZeroChar(char* result, const int length)
{
	int offset = 0;
	for (size_t i = 0; i < length; i++)
	{
		if (*(result + i) == '\0')
		{
			offset++;
			continue;
		}
		else
		{
			char temp = *(result + i - offset);
			*(result + i - offset) = *(result + i);
			*(result + i) = temp;

			i = i - offset;
			offset = 0;
		}
	}
	return result;
}

/// <summary>
/// Сформировать новую строку из символов, общих для двух исходных строк.
/// </summary>
/// <param name="result"></param>
/// <param name="source1"></param>
/// <param name="source2"></param>
/// <returns></returns>
char * getSimilarChars(char *result, const char* source1, const char* source2)
{
	int i = 0;
	while (*source1 || *source2)
	{
		if (*(source1) == *(source2))
		{
			*(result + i) = *source1;
			++i;
		}
		++source1;
		++source2;
	}
	*(result + i) = '\0';
	return result;
}

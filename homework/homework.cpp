#pragma warn C6001
#include <iostream>
#include <fstream>

enum ErrorCase
{
	FileNotOpenedError = 1,
	NullPointerError,
	IOError,
	BadAllocError,
	GeneralError
};

void printError(const int error);
char* trimCharString(char* result, const char delim);
char* removeZeroChar(char* result, const int length);

char* getSimilarChars(char* result, const char* source1, const char* source2);

int main() 
{
	setlocale(LC_ALL, "ru");

	char* filepath = new char[256];
	std::cout << "Введите путь к файлу (можно с \" \"): ";
	std::cin >> filepath;
	trimCharString(filepath, '\"');

	std::ifstream filestream;
	filestream.open(filepath);
	
	if (!filestream.is_open())
	{
		printError(ErrorCase::FileNotOpenedError);
		delete[] filepath;
		return -1;
	}
	
	delete[] filepath;

	int firstLineLength = 0;
	int secondLineLength = 0;

	char* firstLine = nullptr;
	char* secondLine = nullptr;
	char* result = nullptr;

	while (filestream.good())
	{
		try 
		{
			filestream >> firstLineLength;
			firstLineLength += 1;
			firstLine = new char[firstLineLength];
			for (size_t i = 0; i < firstLineLength; i++)
			{
				*(firstLine + i) = '\0';
			}

			filestream >> secondLineLength;
			secondLineLength += 1;
			secondLine = new char[secondLineLength];
			for (size_t i = 0; i < secondLineLength; i++)
			{
				*(secondLine + i) = '\0';
			}

			filestream.ignore(std::cin.rdbuf()->in_avail(), '\n');
			filestream.getline(firstLine, firstLineLength, '\n');
			filestream.getline(secondLine, secondLineLength, '\n');
		}
		catch(const std::ios::failure& e)
		{
			printError(ErrorCase::IOError);
			std::cerr << e.what();
			filestream.close();
			delete[] firstLine;
			delete[] secondLine;
			return -1;
		}
		catch(const std::bad_alloc& e)
		{
			printError(ErrorCase::BadAllocError);
			std::cerr << e.what();
			filestream.close();
			delete[] firstLine;
			delete[] secondLine;
			return -1;
		}
		catch(const std::exception& e)
		{
			printError(ErrorCase::GeneralError);
			std::cerr << e.what();
			filestream.close();
			delete[] firstLine;
			delete[] secondLine;
			return -1;
		}

		std::cout << "\nВы ввели:\n"
			<< '\t' << "1. строку { " << firstLine << " } размером " << firstLineLength - 1 << " символов.\n"
			<< '\t' << "2. строку { " << secondLine << " } размером " << secondLineLength - 1 << " символов.\n";
		
		int maxLength = (firstLineLength >= secondLineLength) ? firstLineLength : secondLineLength;
		result = new char[maxLength];
		
		for (size_t i = 0; i < maxLength; i++)
		{
			*(result + i) = '\0';
		}

		result = getSimilarChars(result, firstLine, secondLine);
		std::cout << "\nСтрока состоящая из идентичных символов:\n"
			<< "-\n" << result << "\n-" << '\n';
		
		delete[] firstLine;
		delete[] secondLine;
		delete[] result;
	}

	filestream.close();

	return 0;
}


/// <summary>
/// Удалить любые вхождения заданного символа из строки
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
/// Перенести все нуль-терминаторы в конец строки
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
	while (*source1 && *source2)
	{
		if (*(source1) == *(source2))
		{
			*(result + i) = *source1;
			++i;
		}
		++source1;
		++source2;
	}
	return result;
}

void printError(const int error)
{
	const char* errorString = nullptr;
	switch (error)
	{
	case 1:
		errorString = "Файл не открылся!";
		break;
	case 2:
		errorString = "Указатель на массив пустой!";
		break;
	case 3:
		errorString = "Ошибка при чтении / открытии файла.";
		break;
	case 4:
		errorString = "Введён неверный размер массива ";
		break;
	case 5:
		errorString = "Произошла необработанная ошибка";
		break;
	default:
		errorString = "Произошла произошла необработанная ошибка";
		break;
	}
	printf("\n\x1B[31m%s\033[0m\n", errorString);
}

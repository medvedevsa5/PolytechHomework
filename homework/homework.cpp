#include <iostream>
#include <fstream>

const std::string OUTPUT_FILE_NAME = "output.txt";

enum ErrorCase
{
	FileNotOpenError = 1,
	NullPointerError,
	IOError,
	BadAllocError,
	GeneralError
};

char* trimCharString(char* result, const char delim);
char* removeZeroChar(char* result, const int length);

void terminateProgram(const ErrorCase& error, char* firstArray = nullptr, char* secondArray = nullptr, char* thirdArray = nullptr);
void printError(const ErrorCase& error);

char* getSimilarChars(char* result, const char* source1, const char* source2);

int main() 
{
	setlocale(LC_ALL, "ru");

	char* filepath = new char[256];
	std::cout << "Введите путь к файлу (можно с \" \"): ";
	std::cin >> filepath;
	trimCharString(filepath, '\"');

	std::ifstream inputFilestream;
	std::ofstream outputFilestream;
	inputFilestream.open(filepath);
	outputFilestream.open(OUTPUT_FILE_NAME);
	
	if (!inputFilestream.is_open())
	{
		printError(ErrorCase::FileNotOpenError);
		inputFilestream.close();
		delete[] filepath;
		return -1;
	}
	
	delete[] filepath;

	int firstLineLength = 0;
	int secondLineLength = 0;

	char* firstLine = nullptr;
	char* secondLine = nullptr;
	char* result = nullptr;

	while (inputFilestream.good())
	{
		try 
		{
			inputFilestream >> firstLineLength;
			firstLineLength += 1;
			firstLine = new char[firstLineLength];

			for (size_t i = 0; i < firstLineLength; i++)
			{
				*(firstLine + i) = '\0';
			}

			inputFilestream >> secondLineLength;
			secondLineLength += 1;
			secondLine = new char[secondLineLength];

			for (size_t i = 0; i < secondLineLength; i++)
			{
				*(secondLine + i) = '\0';
			}

			inputFilestream.ignore(std::cin.rdbuf()->in_avail(), '\n');
			inputFilestream.getline(firstLine, firstLineLength, '\n');
			inputFilestream.getline(secondLine, secondLineLength, '\n');
		}
		catch(const std::ios::failure& e)
		{
			printError(ErrorCase::IOError);
			inputFilestream.close();
			outputFilestream.close();
			delete[] firstLine;
			delete[] secondLine;
			return -1;
		}
		catch(const std::bad_alloc& e)
		{
			printError(ErrorCase::BadAllocError);
			inputFilestream.close();
			outputFilestream.close();
			delete[] firstLine;
			delete[] secondLine;
			return -1;
		}
		catch(const std::exception& e)
		{
			printError(ErrorCase::GeneralError);
			inputFilestream.close();
			outputFilestream.close();
			delete[] firstLine;
			delete[] secondLine;
			return -1;
		}

		std::cout << "\nВы ввели:\n"
			<< '\t' << "1. строку [ " << firstLine << " ] размером " << firstLineLength - 1 << " символов.\n"
			<< '\t' << "2. строку [ " << secondLine << " ] размером " << secondLineLength - 1 << " символов.\n";
		
		int maxLength = (firstLineLength >= secondLineLength) ? firstLineLength : secondLineLength;
		result = new char[maxLength];
		
		for (size_t i = 0; i < maxLength; i++)
		{
			*(result + i) = '\0';
		}

		result = getSimilarChars(result, firstLine, secondLine);
		
		outputFilestream << result << std::endl;
		outputFilestream.flush();

		delete[] firstLine;
		firstLine = nullptr;

		delete[] secondLine;
		secondLine = nullptr;

		delete[] result;
		result = nullptr;
	}

	inputFilestream.close();
	outputFilestream.close();

	return 0;
}


// удалить любые вхождения заданного символа из строки
char * trimCharString(char* result, const char delim)
{
	int length = 0;
	while (*(result + length))
	{
		++length;
	}
	for (size_t i = 0; i < length; i++)
	{
		if(*(result + i) == delim)
		{
			*(result + i) = '\0';
		}
		if (*(result + length - i) == delim)
		{
			*(result + length - i) = '\0';
		}
	}
	result = removeZeroChar(result, length);
	return result;
}


// перенести все нуль-терминаторы в конец строки
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

// сформировать новую строку из символов, общих для двух исходных строк.
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

void printError(const ErrorCase &error)
{
	const char* errorString = nullptr;
	switch (error)
	{
	case ErrorCase::FileNotOpenError:
		errorString = "Файл не открылся!";
		break;
	case ErrorCase::NullPointerError:
		errorString = "Указатель на массив пустой!";
		break;
	case ErrorCase::IOError:
		errorString = "Ошибка при чтении / открытии файла.";
		break;
	case ErrorCase::BadAllocError:
		errorString = "Введён неверный размер массива.";
		break;
	case ErrorCase::GeneralError:

	default:
		errorString = "Произошла необработанная ошибка.";
		break;
	}
	std::cout << "\n\x1B[31m" << errorString << "\n\033[0m";
}

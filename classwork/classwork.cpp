// classwork.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>


void inArray(int** matrix, int rowCount, int columnCount);
void outArray(int** matrix, int rowCount, int columnCount);


int main()
{
	setlocale(LC_ALL, "ru");

	int rowCount = 0;
	int columnCount = 0;

	std::cin >> rowCount;
	std::cin >> columnCount;

	int** matrix = new int* [rowCount];
	for (size_t i = 0; i < rowCount; i++)
	{
		*(matrix + i) = new int[columnCount];
	}

	inArray(matrix, rowCount, columnCount);

	std::cout << std::endl << std::endl;

	outArray(matrix, rowCount, columnCount);

	for (size_t i = 0; i < rowCount; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;

	return 0;
}

void inArray(int** matrix, int rowCount, int columnCount)
{
	std::string input = "";

	for (size_t i = 0; i < rowCount; i++)
	{
		for (size_t j = 0; j < columnCount; j++)
		{
			std::cin >> input;
			try
			{
				matrix[i][j] = std::stoi(input);
			}
			catch(std::invalid_argument)
			{
				std::cerr << "Неверный ввод!";
				abort();
			}
		}
	}
}

void outArray(int** matrix, int rowCount, int columnCount)
{
	for (size_t i = 0; i < rowCount; i++)
	{
		for (size_t j = 0; j < columnCount; j++)
		{
			std::cout << matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

#include <iostream>
#include <windows.h>
#include <cmath>
#include <string>
#include <fstream>

const int ROW_WARNING = 256;
const int COLUMN_WARNING = 256;
const int ROW_MAXIMUM = 16384;
const int COLUMN_MAXIMUM = 16384;

const std::string OUTPUT_FILE_NAME = "matrix.txt";

const HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

int** getSnake(int** matrix, const int rowCount, const int columnCount);
void writeMatrix(int** matrix, int rowCount, int columnCount);


int main()
{
	setlocale(LC_ALL, "ru");

	int rowCount = 0;
	int columnCount = 0;
	std::string input = "";

	std::cout << "Введите количество срок матрицы: ";
	std::cin >> input;
	std::cout << std::endl;
	try
	{
		rowCount = std::stoi(input);
	}
	catch(std::exception)
	{
		std::cout << "Количество строк должно быть числом диапазона Int.\n\n";
		system("pause");
		return -1;
	}

	std::cout << "А теперь количество столбцов: ";
	std::cin >> input;
	std::cout << std::endl;
	try
	{
		columnCount = std::stoi(input);
	}
	catch (std::invalid_argument)
	{
		std::cout << "Количество столбцов должно быть числом диапазона Int.\n\n";
		system("pause");
		return -1;
	}

	if(rowCount > ROW_MAXIMUM || columnCount > COLUMN_MAXIMUM)
	{
		std::cout << "Вы даже файл открыть свой не сможете...";
		return -1;
	}
	if(rowCount > ROW_WARNING || columnCount > COLUMN_WARNING)
	{
		std::cout << "Выходной файл будет огромным и вы вряд ли поймёте что в нём написано. Вы действительно хотите продолжить? (Y/N) ";
		std::cin.ignore(std::cin.rdbuf()->in_avail(), '\n');
		char ch = std::cin.get();
		if ((tolower(ch) != 'y')) return 0;
	}

	int** matrix = nullptr;

	matrix = new int* [rowCount];
	for (size_t i = 0; i < rowCount; i++)
	{
		matrix[i] = new int[columnCount];
	}

	matrix = getSnake(matrix, rowCount, columnCount);

	std::cout << "\nМатрица готова. Запись в файл...";

	writeMatrix(matrix, rowCount, columnCount);

	std::cout << "\nВыходная матрица записана в файл " << OUTPUT_FILE_NAME << std::endl << std::endl;

	for (size_t i = 0; i < rowCount; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;

	system("pause");

	return 0;
}

// вернуть спираль из натуральных чисел, расположенных против часовой стрелки по возрастанию
int** getSnake(int** matrix, const int rowCount, const int columnCount)
{
	int emptyElemetsCount = rowCount * columnCount;
	
	int xCoord = 0;
	int yCoord = 0;

	int leftWall = 0;
	int bottomWall = 0;
	int rightWall = 0;
	int topWall = 0;

	bool isMovingHorizontal = false;
	bool isReverse = false;

	int zahlen = 1;

	while (emptyElemetsCount > 0)
	{
		matrix[yCoord][xCoord] = zahlen;
		emptyElemetsCount -= 1;
		zahlen += 1;

		if (!isMovingHorizontal && !isReverse)
		{
			if (yCoord + 1 > (rowCount - 1) - bottomWall)
			{
				isMovingHorizontal = !isMovingHorizontal;
				leftWall += 1;
				xCoord += 1;
				continue;
			}
			yCoord += 1;
		}
		else if (isMovingHorizontal && !isReverse)
		{
			if (xCoord + 1 > (columnCount - 1) - rightWall)
			{
				isMovingHorizontal = !isMovingHorizontal;
				isReverse = !isReverse;
				bottomWall += 1;
				yCoord -= 1;
				continue;
			}
			xCoord += 1;
		}
		else if (!isMovingHorizontal && isReverse)
		{
			if (yCoord - 1 < topWall)
			{
				isMovingHorizontal = !isMovingHorizontal;
				rightWall += 1;
				xCoord -= 1;
				continue;
			}
			yCoord -= 1;
		}
		else if (isMovingHorizontal && isReverse)
		{
			if (xCoord - 1 < leftWall)
			{
				isMovingHorizontal = !isMovingHorizontal;
				isReverse = !isReverse;
				topWall += 1;
				yCoord += 1;
				continue;
			}
			xCoord -= 1;
		}
	}
	return matrix;
}

void writeMatrix(int** matrix, int rowCount, int columnCount)
{
	std::ofstream outputStream(OUTPUT_FILE_NAME);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD coord = {0, 0};

	GetConsoleScreenBufferInfo(output, &csbi);
	coord = csbi.dwCursorPosition;

	//int rowCountDepth = 1;
	//while(rowCount % rowCountDepth != rowCount)
	//{
	//	rowCountDepth *= 10;
	//}
	//rowCountDepth; 

	int onePercent = rowCount / 100;

	int outputStringLength = 0;

	for (size_t i = 0; i < rowCount; i++)
	{
		if ((onePercent * 10) % (i + 1) == 0)
		{
			std::string outputString = std::to_string((int)(100 * (double)i / (double)rowCount)) + "%";
			coord.X -= outputStringLength - 1;
			outputStringLength = outputString.length();
			SetConsoleCursorPosition(output, coord);
			std::cout << outputString;
			coord.X += outputStringLength - 1;
		}

		outputStream << matrix[i][0];
		for (size_t j = 1; j < columnCount; j++)
		{
			outputStream << "\t" << matrix[i][j];
		}
		outputStream << std::endl << std::endl;
	}

	coord.X -= 2;
	SetConsoleCursorPosition(output, coord);
	std::cout << "100%" << std::endl;

	outputStream.close();
}
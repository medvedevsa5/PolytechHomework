#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

const int ROW_WARNING = 256;
const int COLUMN_WARNING = 256;
const int ROW_MAXIMUM = 16384;
const int COLUMN_MAXIMUM = 16384;

const std::string OUTPUT_FILE_NAME = "matrix.txt";

const HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);

void firstTask();
void secondTask();

int** getSnake(int** matrix, const int rowCount, const int columnCount);

int main()
{
	setlocale(LC_ALL, "ru");

	//firstTask();

	secondTask();

	system("pause");

	return 0;
}

void firstTask() 
{
	const int staticRowCount = 5;
	const int staticColumnCount = 4;

	int staticArray[staticRowCount][staticColumnCount] =
	{
		{10, 0, 30, 40},
		{10, 20, 0, 40},
		{10, 20, 30, 40},
		{10, 20, 0, 40},
		{10, 20, 30, 40}
	};

	int notZeroColumns = 0;

	for (size_t j = 0; j < staticColumnCount; j++)
	{
		notZeroColumns += 1;
		for (size_t i = 0; i < staticRowCount; i++)
		{
			if (staticArray[i][j] == 0)
			{
				notZeroColumns -= 1;
				break;
			}
		}
	}

	std::cout << "Количество ненулевых строк из " << notZeroColumns;
}

void secondTask()
{
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
	catch (std::exception)
	{
		std::cout << "Количество строк должно быть числом диапазона Int.\n\n";
		system("pause");
		exit(-1);
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
		exit(-1);
	}

	if (rowCount > ROW_MAXIMUM || columnCount > COLUMN_MAXIMUM)
	{
		std::cout << "Вы даже файл открыть свой не сможете...";
		exit(-1);
	}

	if (rowCount > ROW_WARNING || columnCount > COLUMN_WARNING)
	{
		std::cout << "Выходной файл будет огромным и вы вряд ли поймёте что в нём написано. Вы действительно хотите продолжить? (Y/N) ";
		std::cin.ignore(std::cin.rdbuf()->in_avail(), '\n');
		char ch = std::tolower(std::cin.get());
		if (ch != 'y') exit(-1);
		std::cout << std::endl;
	}

	int** matrix = nullptr;
	matrix = new int* [rowCount];
	for (size_t i = 0; i < rowCount; i++)
	{
		matrix[i] = new int[columnCount];
	}

	matrix = getSnake(matrix, rowCount, columnCount);

	std::cout << "Матрица готова. Запись в файл..." << std::endl;

	std::ofstream outputStream(OUTPUT_FILE_NAME);

	for (size_t i = 0; i < rowCount; i++)
	{
		for (size_t j = 0; j < columnCount; j++)
		{
			outputStream << matrix[i][j] << '\t';
		}
		outputStream << std::endl << std::endl;
	}

	std::cout << "Выходная матрица записана в файл " << OUTPUT_FILE_NAME << std::endl << std::endl;

	for (size_t i = 0; i < rowCount; i++)
	{
		delete[] matrix[i];
	}
	delete[] matrix;
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
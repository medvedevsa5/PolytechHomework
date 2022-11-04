#include <iostream>
#include <fstream>

const int ROW_WARNING = 256;
const int COLUMN_WARNING = 256;
const int ROW_MAXIMUM = 16384;
const int COLUMN_MAXIMUM = 16384;

const std::string OUTPUT_FILE_NAME = "matrix.txt";

int** getSnake(int** matrix, const int rowCount, const int columnCount);

int main()
{
	setlocale(LC_ALL, "ru");

	int rowCount = 0;
	int columnCount = 0;

	std::cout << "Введите количество срок матрицы: ";
	std::cin >> rowCount;
	std::cout << std::endl;

	std::cout << "А теперь количество столбцов: ";
	std::cin >> columnCount;
	std::cout << std::endl;

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
		if ((tolower(ch) != 'y') || (tolower(ch) != 'д')) return 0;
	}

	int** matrix = nullptr;

	try
	{
		matrix = new int* [rowCount];
		for (size_t i = 0; i < rowCount; i++)
		{
			matrix[i] = new int[columnCount];
		}
	}
	catch (std::bad_alloc& e)
	{
		std::cout << "Введён неправильный размер массива!";
		std::cout << "\n - " << e.what();
		return -1;
	}

	matrix = getSnake(matrix, rowCount, columnCount);

	std::ofstream outputStream(OUTPUT_FILE_NAME);

	for (size_t i = 0; i < rowCount; i++)
	{
		outputStream << matrix[i][0];

		for (size_t j = 1; j < columnCount; j++)
		{
			outputStream << "\t" << matrix[i][j];
		}
		
		delete[] matrix[i];
		outputStream << std::endl << std::endl;
	}

	outputStream.close();
	delete[] matrix;

	std::cout << "\nВыходная матрица записана в файл " << OUTPUT_FILE_NAME << std::endl << std::endl;

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

int getInput()
{
	int 

}

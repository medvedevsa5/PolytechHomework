#include <iostream>
#include <cmath>

int** getSnake(int** matrix, int rowCount, int columnCount);

int main()
{
	setlocale(LC_ALL, "ru");

	int rowCount = 0;
	int columnCount = 0;
	int numbers = 0;

	std::cin >> rowCount;
	std::cin >> columnCount;

	int** matrix = new int* [rowCount];
	
	for (size_t i = 0; i < rowCount; i++)
	{
		matrix[i] = new int[columnCount];
		for (size_t j = 0; j < columnCount; j++)
		{
			++numbers;
		}
	}

	matrix = getSnake(matrix, rowCount, columnCount);

	std::cout << "Выходная матрица:" << std::endl<< std::endl;

	for (size_t i = 0; i < rowCount; i++)
	{
		for (size_t j = 0; j < columnCount; j++)
		{
			std::cout << '\t' << matrix[i][j] << ' ';
		}
		std::cout << std::endl << std::endl;
	}
	return 0;
}

int** getSnake(int** matrix, int rowCount, int columnCount)
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

		if(!isMovingHorizontal && !isReverse)
		{
			if(yCoord + 1 > (rowCount - 1) - bottomWall)
			{
				isMovingHorizontal = !isMovingHorizontal;
				leftWall += 1;
				xCoord += 1;
				zahlen += 1;
				continue;
			}
			zahlen += 1;
			yCoord += 1;
		}
		else if(isMovingHorizontal && !isReverse)
		{
			if (xCoord + 1 > (columnCount - 1) - rightWall)
			{
				isMovingHorizontal = !isMovingHorizontal;
				isReverse = !isReverse;
				bottomWall += 1;
				yCoord -= 1;
				zahlen += 1;
				continue;
			}
			zahlen += 1;
			xCoord += 1;
		}
		else if(!isMovingHorizontal && isReverse)
		{
			if (yCoord - 1 < topWall)
			{
				isMovingHorizontal = !isMovingHorizontal;
				rightWall += 1;
				xCoord -= 1;
				zahlen += 1;
				continue;
			}
			zahlen += 1;
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
				zahlen += 1;
				continue;
			}
			zahlen += 1;
			xCoord -= 1;
		}
	}

	return matrix;
}

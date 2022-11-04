#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>

const int ROW_WARNING = 256;
const int COLUMN_WARNING = 256;
const int ROW_MAXIMUM = 16384;
const int COLUMN_MAXIMUM = 16384;
const std::string OUTPUT_FILE_NAME = "matrix.txt";
const HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

void firstTask();
void secondTask();
int** getSnake(int** matrix, const int rowCount, const int columnCount);

class StatusBar
{
	HANDLE _output = 0;
	COORD _position = { 0, 0 };
	int _length = 0;
	char _chunk = '*';
	int _chunkCount = 0;

public:
	StatusBar(HANDLE output, COORD position, int length, char chunk = '*')
	{
		_output = output;
		_position = position;
		_length = length;
		_chunk = '*';
	}

	void Draw()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(_output, &csbi);
		COORD previousPosition = csbi.dwCursorPosition;

		SetConsoleCursorPosition(_output, _position);
		std::cout << "[";
		_position.X += _length + 1;
		SetConsoleCursorPosition(_output, _position);
		std::cout << "]";
		_position.X -= _length + 1;
		SetConsoleCursorPosition(_output, previousPosition);
	}

	void AddChunk(int count)
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		COORD previousPosition = { 0, 0 };
		GetConsoleScreenBufferInfo(_output, &csbi);
		previousPosition = csbi.dwCursorPosition;

		if (_chunkCount < _length)
		{
			while (count--) 
			{
				_position.X += 1;
				SetConsoleCursorPosition(_output, _position);
				std::cout << _chunk;
				_chunkCount += 1;
			}
			SetConsoleCursorPosition(_output, previousPosition);
		}
	}
};

int main()
{
	setlocale(LC_ALL, "ru");

	firstTask();

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

	std::cout << "Количество ненулевых строк из " << notZeroColumns << std::endl;
}

void secondTask()
{
	int rowCount = 0;
	int columnCount = 0;
	
	std::ifstream inputFileStream;
	std::string filePath = "";
	std::cout << "Введите путь к файлу: ";
	std::cin >> filePath;
	inputFileStream.open(filePath);

	if(!inputFileStream.is_open())
	{
		std::cout << "Не удалось открыть файл";
		exit(-1);
	}

	try
	{
		std::string row = "";
		std::cin >> row;
		rowCount = std::stoi(row);
	}
	catch (std::invalid_argument)
	{
		std::cout << "Количество строк должно быть числом диапазона Int.\n\n";
		system("pause");
		exit(-1);
	}

	try
	{
		std::string column = "";
		std::cin >> column;
		columnCount = std::stoi(column);
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
		std::cout << "Выходной файл будет огромным и вы вряд ли поймёте что в нём написано.\n Вы действительно хотите продолжить? (Y/N) ";
		std::cin.ignore(std::cin.rdbuf()->in_avail(), '\n');
		char ch = std::tolower(std::cin.get());
		if (ch != 'y') exit(-1);

		std::cout << std::endl;
	}

	//--
	int** matrix = new int* [rowCount];
	for (size_t i = 0; i < rowCount; i++)
	{
		matrix[i] = new int[columnCount];
	}

	matrix = getSnake(matrix, rowCount, columnCount);

	std::cout << "Матрица готова. Запись в файл... ";

	std::ofstream outputStream(OUTPUT_FILE_NAME);
	
	// получение текущего местоположения курсора
	CONSOLE_SCREEN_BUFFER_INFO csbi;									
	GetConsoleScreenBufferInfo(outputHandle, &csbi);					
	COORD statusPosition = csbi.dwCursorPosition;						

	// инициализация полоски со статусом записи в файл 
	StatusBar* writerStatus = new StatusBar(outputHandle, statusPosition, 20);
	writerStatus->Draw();

	// запись матрицы в файл
	for (size_t i = 0; i < rowCount; i++)								
	{																
		if( (i + 1) % (rowCount / 20) == 0)								
		{																
			writerStatus->AddChunk(1);									
		}																
		for (size_t j = 0; j < columnCount; j++)						
		{																
			outputStream << matrix[i][j] << '\t' << '\t';				
		}																
		delete[] matrix[i];												
		outputStream << std::endl << std::endl;							
	}
	delete[] matrix;
	delete writerStatus;
	outputStream.close();

	std::cout << std::endl<< std::endl << "Выходная матрица записана в файл " << OUTPUT_FILE_NAME << std::endl << std::endl;
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

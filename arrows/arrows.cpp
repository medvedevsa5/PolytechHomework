#include <iostream>
#include <chrono>
#include <thread>

class MemoryLeaker
{
private:
	int* _leakerArray = nullptr;
	int _length = 0;

public:
	MemoryLeaker()
	{
		srand((unsigned)time(NULL) / 2);
		_length = rand() % 10001;
		_leakerArray = new int[_length];

		for (size_t i = 0; i < _length; i++)
		{
			_leakerArray[i] = (rand() % 10001);
		}
	}
};


int main()
{
	using namespace std::this_thread;
	using namespace std::chrono_literals;

	int i = 0;
	while (i++ < 10);
	{
		new MemoryLeaker();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	return 0;
}


#include <iostream>

bool foo1();
bool foo2();

bool isActivated[2] = { false, false };

int main()
{
    foo1() && foo2();
    std::cout << "Test 1 - " << isActivated[0] << " and " << isActivated[1] << std::endl;

    isActivated[0] = false;
    isActivated[1] = false;
    
    foo1() & foo2();

    std::cout << "Test 2 - " << isActivated[0] << " and " << isActivated[1] << std::endl;
}

bool foo1()
{
    isActivated[0] = true;

    return false;
}

bool foo2()
{
    isActivated[1] = true;

    return false;
}

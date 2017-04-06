#include <iostream>
#include <random>

using namespace std;

int main()
{
    random_device rd;
    mt19937_64 mt(rd());
    for(int n = 0; n < 1000000; n++)
        mt();

    return 0;
}

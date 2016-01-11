#include <iostream>
#include <cstring>

using namespace std;

int main()
{
    char const* str = "Hello world";
    unsigned const len = std::strlen(str);
#pragma omp parallel for num_threads(4)
    for (unsigned thread = 0; thread < 4; ++thread)
    {
        for (unsigned i = 0; i < len; ++i)
        {
            std::cout << str[i] << std::endl;
        }
    }
}
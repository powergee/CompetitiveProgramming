#include <iostream>
#include <string>

int main()
{
    int n;
    std::string str;
    std::cin >> n >> str;

    int lCount = 0, rCount = 0;
    for (char ch : str)
    {
        if (ch == 'L')
            ++lCount;
        else ++rCount;
    }

    std::cout << rCount + lCount + 1;

    return 0;
}
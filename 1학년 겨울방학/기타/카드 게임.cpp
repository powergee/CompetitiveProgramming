#include <iostream>

int main()
{
    int sum = 0;
    for (int i = 0; i < 5; ++i)
    {
        int score;
        std::cin >> score;
        sum += score;
    }

    std::cout << sum;

    return 0;
}
#include <iostream>
#include <string>

int time[26]{

    3, 3, 3,
    4, 4, 4,
    5, 5, 5,
    6, 6, 6,
    7, 7, 7,
    8, 8, 8, 8,
    9, 9, 9,
    10, 10, 10, 10};

int main()
{
    std::string str;
    std::cin >> str;

    int sum = 0;
    for (char ch : str)
        sum += time[ch - 'A'];

    printf("%d", sum);

    return 0;
}
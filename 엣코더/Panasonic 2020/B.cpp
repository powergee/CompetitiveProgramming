#include <iostream>

int main()
{
    long long h, w;
    std::cin >> h >> w;

    if (h == 1 || w == 1)
    {
        std::cout << 1;
        return 0;
    }

    long long row1, row2;
    if (w % 2 == 0)
        row1 = row2 = w / 2;
    else row1 = w / 2 + 1, row2 = w / 2;

    long long result = 0;
    if (h % 2 == 0)
        result += (h / 2) * (row1 + row2);
    else result += (h / 2) * (row1 + row2) + row1;

    std::cout << result;

    return 0;
}
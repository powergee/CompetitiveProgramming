#include <iostream>
#include <string>

bool IsPalin(std::string& s, int left, int right)
{
    for (int i = left; i <= (right + left) / 2; ++i)
        if (s[i] != s[right - i])
            return false;
    return true;
}

int main()
{
    std::string input;
    std::cin >> input;

    int n = input.size();
    std::cout << (IsPalin(input, 0, n-1) && IsPalin(input, 0, (n-1)/2 - 1) && IsPalin(input, (n+3)/2 - 1, n-1) ? "Yes" : "No");

    return 0;
}
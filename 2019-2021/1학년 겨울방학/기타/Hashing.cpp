#include <iostream>
#include <string>
#define M 1234567891
#define r 31

typedef long long Long;

int main()
{
    int l;
    std::cin >> l;

    std::string str;
    std::cin >> str;

    Long result = 0;
    Long R = 1;
    for (int i = 0; i < l; ++i)
    {
        result += ((str[i] - 'a' + 1) * R) % M;
        R = (31 * R) % M;
    }
    result %= M;

    std::cout << result;

    return 0;
}
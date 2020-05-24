#include <iostream>
#include <cmath>

int main()
{
    long long a, b, c;
    std::cin >> a >> b >> c;
    bool yes;

    if (c < a+b)
        yes = false;
    else yes = 4*a*b < (c-a-b)*(c-a-b);
    

    std::cout << (yes ? "Yes" : "No");

    return 0;
}
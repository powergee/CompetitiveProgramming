#include <iostream>
#include <algorithm>

int main()
{
    long long n, a, b;
    std::cin >> n >> a >> b;
    std::cout << (n/(a+b)) * a + std::min(a, n%(a+b));
    return 0;
}
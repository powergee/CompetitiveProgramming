#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--)
    {
        int n;
        std::cin >> n;
        std::cout << n/2 + (n % 2 ? 1 : 0) << "\n";
    }

    return 0;
}
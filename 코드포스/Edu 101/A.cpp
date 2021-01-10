#include <iostream>
#include <string>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--)
    {
        std::string line;
        std::cin >> line;

        int open = line.find('(');
        int close = line.find(')');
        int n = line.size();

        if (n % 2 == 0 && open != n-1 && close != 0)
            printf("YES\n");
        else 
            printf("NO\n");
    }

    return 0;
}
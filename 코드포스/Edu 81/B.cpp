#include <iostream>
#include <algorithm>
#include <string>

int balance[100000];

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--)
    {
        int n, x;
        std::cin >> n >> x;

        std::string s;
        std::cin >> s;
        balance[0] = s[0] == '0' ? 1 : -1;
        for (int i = 1; i < n; ++i)
            balance[i] = balance[i - 1] + (s[i] == '0' ? 1 : -1);

        int result = x == 0 ? 1 : 0;

        for (int i = 0; i < n; ++i)
        {
            if ((balance[n - 1] == 0 && balance[i] == x) ||
                (balance[n - 1] > 0 && x - balance[i] >= 0 && (x - balance[i]) % balance[n - 1] == 0) ||
                (balance[n - 1] < 0 && x - balance[i] <= 0 && (x - balance[i]) % balance[n - 1] == 0))
                ++result;
        }

        if (balance[n - 1] == 0 && result > 0)
            printf("-1\n");
        else printf("%d\n", result);
    }
    
    return 0;
}
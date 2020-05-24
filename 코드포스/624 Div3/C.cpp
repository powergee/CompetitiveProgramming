#include <iostream>
#include <algorithm>
#include <string>

int retryCount[200000];
int chCount[26];

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--)
    {
        int n, m;
        std::cin >> n >> m;

        std::string str;
        std::cin >> str;

        std::fill(retryCount, retryCount + n, 0);
        std::fill(chCount, chCount + 26, 0);
        for (int i = 0; i < m; ++i)
        {
            int pos;
            std::cin >> pos;
            ++retryCount[pos - 1];
        }

        int add = 0;

        for (int i = n - 1; i >= 0; --i)
        {
            add += retryCount[i];
            chCount[str[i] - 'a'] += add + 1;
        }

        for (int i = 0; i < 26; ++i)
            printf("%d ", chCount[i]);
        printf("\n");
    }

    return 0;
}
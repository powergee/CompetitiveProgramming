#include <iostream>
#include <string>
#include <algorithm>
#define UNDEF -2
#define NOTFOUND -1

std::string s, t;
int dp[100000][26];

int Find(int start, char ch)
{
    if (start >= s.size())
        return NOTFOUND;

    int& result = dp[start][ch - 'a'];
    if (result != UNDEF)
        return result;

    if (s[start] == ch)
        return result = start;
    else return result = Find(start + 1, ch);
}

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--)
    {
        std::fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(int), UNDEF);

        std::cin >> s >> t;
        int count = 0;
        int start = 0;
        bool fail = false;
        for (int i = 0; i < t.size(); ++i)
        {
            int found = Find(start, t[i]);
            if (found == NOTFOUND)
            {
                ++count;
                found = Find(0, t[i]);

                if (found == NOTFOUND)
                {
                    fail = true;
                    break;
                }
            }

            start = found + 1;
        }

        if (start != 0)
            ++count;

        if (fail)
            printf("-1\n");
        else printf("%d\n", count);
    }

    return 0;
}
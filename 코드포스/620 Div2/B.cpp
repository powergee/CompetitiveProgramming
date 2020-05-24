#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

bool IsPalin(const std::string& s)
{
    int size = (int)s.size();
    for (int i = 0; i < size / 2; ++i)
        if (s[i] != s[size - 1 - i])
            return false;

    return true;
}

int n, m;
std::vector<std::string> str;
std::vector<bool> isPalin;
std::vector<int> pair;

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n >> m;
    pair.resize(n, -1);

    for (int i = 0; i < n; ++i)
    {
        std::string s;
        std::cin >> s;
        str.push_back(s);
        isPalin.push_back(IsPalin(s));
    }

    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (pair[i] != -1 || pair[j] != -1)
                continue;

            bool arePair = true;
            for (int k = 0; k < m; ++k)
            {
                if (str[i][k] != str[j][m - 1 - k])
                {
                    arePair = false;
                    break;
                }
            }

            pair[i] = j;
            pair[j] = i;
        }
    }

    

    return 0;
}
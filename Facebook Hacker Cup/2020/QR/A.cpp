#include <iostream>
#include <string>

char isPossible(std::string& iStr, std::string& oStr, int from, int to)
{
    if (from == to)
        return 'Y';
    else if (from < to)
    {
        if (iStr[from+1] == 'N' || oStr[from] == 'N')
            return 'N';
        return isPossible(iStr, oStr, from+1, to);
    }
    else
    {
        if (iStr[from-1] == 'N' || oStr[from] == 'N')
            return 'N';
        return isPossible(iStr, oStr, from-1, to);
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        int n;
        std::string iStr, oStr;
        std::cin >> n >> iStr >>oStr;

        std::cout << "Case #" << t << ":\n";
        for (int from = 0; from < n; ++from)
        {
            for (int to = 0; to < n; ++to)
                std::cout << isPossible(iStr, oStr, from, to);
            std::cout << '\n';
        }
    }

    return 0;
}
#include <iostream>
#include <algorithm>

std::pair<std::string, std::string> queries[10000];

void Update(std::pair<int, int>& old, int newLeft, int newRight)
{
    if (old.first <= newLeft && newLeft <= old.second)
    {
        if (old.second <= newRight)
        {
            old.first = newLeft;
        }
        else 
        {
            old.first = newLeft;
            old.second = newRight;
        }
    }
    else if (newLeft <= old.first && old.first <= newRight)
    {
        if (newRight <= old.second)
        {
            old.second = newRight;
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;

    for (int c = 1; c <= T; ++c)
    {
        int U;
        std::cin >> U;
        std::cout << "Case #" << c << ": ";
        for (int i = 0; i < 10000; ++i)
            std::cin >> queries[i].first >> queries[i].second;

        std::pair<int, int> pos[26];
        std::fill(pos, pos + 26, std::make_pair(-1, 11));
        std::string answer = "          ";
        
        for (int i = 0; i < 10000; ++i)
        {
            std::string& A = queries[i].first;
            std::string& B = queries[i].second;
            if (A.size() > B.size())
            {
                Update(pos[B[0] - 'A'], 1, 9);
                for (int j = 1; j < (int)B.size(); ++j)
                    Update(pos[B[j] - 'A'], 0, 9);
            }
            else
            {
                Update(pos[B[0] - 'A'], 1, A[0] - '0');
                for (int j = 1; j < (int)B.size(); ++j)
                    Update(pos[B[j] - 'A'], 0, 9);
            }
        }

        for (int loop = 0; loop < 26; ++loop)
        {
            for (int i = 0; i < 26; ++i)
            {
                if (pos[i].first == -1)
                    continue;

                int possible = 0;
                int availPos = 0;
                for (int j = pos[i].first; j <= pos[i].second; ++j)
                {
                    if (answer[j] == ' ')
                    {
                        ++possible;
                        availPos = j;
                    }
                }

                if (possible == 1)
                    answer[availPos] = 'A' + i;
            }
        }

        std::cout << answer << "\n";
    }

    return 0;
}
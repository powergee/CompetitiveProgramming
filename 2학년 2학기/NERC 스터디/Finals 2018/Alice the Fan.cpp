#include <iostream>
#include <algorithm>
#include <queue>

const std::pair<int, int> NOT_JUDGED = {0, 0};
const std::pair<int, int> NO_ANSWER = {-1, -1};
const std::pair<int, int> priority[] = {
    {3, 0}, {3, 1}, {3, 2}, {2, 3}, {1, 3}, {0, 3}};

std::pair<int, int> answer[5];
std::pair<int, int> dp[201][201][4][4][4][4][5];

bool isValidMatch(int aScore, int bScore, int aWin, int bWin, int aWon, int bWon, int index)
{
    if (aScore < 0 || bScore < 0 || aWin < 0 || bWin < 0 || ((aWin > 0 || bWin > 0) && (aWon == 3 || bWon == 3)))
        return false;

    if (aScore == 0 && bScore == 0 && aWin == 0 && bWin == 0)
        return true;

    auto& result = dp[aScore][bScore][aWin][bWin][aWin][bWon][index];

    if (result == NO_ANSWER)
        return false;
    else if (result != NOT_JUDGED)
    {
        answer[index] = result;
        int aWinDiff = (result.first > result.second ? -1 : 0);
        int bWinDiff = (result.first > result.second ? 0 : -1);
        if (index < 4)
            return isValidMatch(aScore-result.first, bScore-result.second, aWin+aWinDiff, bWin+bWinDiff, aWon-aWinDiff, bWon-bWinDiff, index+1);
        else
            return true;
    }

    if (index < 4)
    {
        if (aWin > 0 && aScore >= 25)
        {
            // 25점으로 a가 이김
            for (int b = 0; b <= 23; ++b)
            {
                if (isValidMatch(aScore-25, bScore-b, aWin-1, bWin, aWon+1, bWon, index+1))
                {
                    result = {25, b};
                    answer[index] = result;
                    return true;
                }
            }

            // 26점 이상으로 a가 이김
            for (int a = 26; a <= aScore; ++a)
            {
                if (isValidMatch(aScore-a, bScore-(a-2), aWin-1, bWin, aWon+1, bWon, index+1))
                {
                    result = {a, a-2};
                    answer[index] = result;
                    return true;
                }
            }
        }

        if (bWin > 0 && bScore >= 25)
        {
            // 25점으로 b가 이김
            for (int a = 0; a <= 23; ++a)
            {
                if (isValidMatch(aScore-a, bScore-25, aWin, bWin-1, aWon, bWon+1, index+1))
                {
                    result = {a, 25};
                    answer[index] = result;
                    return true;
                }
            }

            // 26점 이상으로 b가 이김
            for (int b = 26; b <= bScore; ++b)
            {
                if (isValidMatch(aScore-(b-2), bScore-b, aWin, bWin-1, aWon, bWon+1, index+1))
                {
                    result = {b-2, b};
                    answer[index] = result;
                    return true;
                }
            }
        }

        result = NO_ANSWER;
        return false;
    }
    else
    {
        if (aWin + bWin != 1)
        {
            result = NO_ANSWER;
            return false;
        }

        if (aWin && ((aScore == 15 && bScore <= 13) || (aScore > 15 && aScore - bScore == 2)) ||
            bWin && ((bScore == 15 && aScore <= 13) || (bScore > 15 && bScore - aScore == 2)))
        {
            result = {aScore, bScore};
            answer[index] = result;
            return true;
        }
        else
        {
            result = NO_ANSWER;
            return false;
        }
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int a, b;
        scanf("%d %d", &a, &b);

        bool found = false;
        for (int i = 0; i < sizeof(priority)/sizeof(priority[0]) && !found; ++i)
        {
            auto& match = priority[i];
            if (isValidMatch(a, b, match.first, match.second, 0, 0, 0))
            {
                printf("%d:%d\n", match.first, match.second);
                for (int j = 0; j < match.first+match.second; ++j)
                    printf("%d:%d ", answer[j].first, answer[j].second);
                printf("\n");
                found = true;
            }
        }

        if (!found)
            printf("Impossible\n");
    }

    return 0;
}
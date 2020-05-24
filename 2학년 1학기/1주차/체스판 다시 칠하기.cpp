#include <iostream>
#include <string>
#include <algorithm>

std::string board[50];

std::string chess[2][8] {
    {
        "WBWBWBWB",
        "BWBWBWBW",
        "WBWBWBWB",
        "BWBWBWBW",
        "WBWBWBWB",
        "BWBWBWBW",
        "WBWBWBWB",
        "BWBWBWBW",
    },

    {
        "BWBWBWBW",
        "WBWBWBWB",
        "BWBWBWBW",
        "WBWBWBWB",
        "BWBWBWBW",
        "WBWBWBWB",
        "BWBWBWBW",
        "WBWBWBWB",
    }
};

int Count(int row, int col)
{
    int result = 1e9;

    for (int chessIdx = 0; chessIdx < 2; ++chessIdx)
    {
        int currCount = 0;
        for (int dr = 0; dr < 8; ++dr)
        {
            for (int dc = 0; dc < 8; ++dc)
            {
                if (chess[chessIdx][dr][dc] != board[dr + row][dc + col])
                    ++currCount;
            }
        }

        result = std::min(currCount, result);
    }

    return result;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie();
    std::cout.tie();

    int n, m;
    std::cin >> n >> m;

    for (int i = 0; i < n; ++i)
        std::cin >> board[i];

    int result = 1e9;
    for (int r = 0; r <= n - 8; ++r)
        for (int c = 0; c <= m - 8; ++c)
            result = std::min(result, Count(r, c));

    std::cout << result;

    return 0;
}
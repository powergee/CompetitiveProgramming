#include <iostream>
#include <algorithm>

int n;
std::string board[50];

int FindLongest()
{
    int result = 0;

    for (int r = 0; r < n; ++r)
    {
        char ch = board[r][0];
        int length = 1;
        for (int c = 1; c < n; ++c)
        {
            if (ch == board[r][c])
                ++length;
            else
            {
                result = std::max(result, length);
                ch = board[r][c];
                length = 1;
            }
        }

        result = std::max(result, length);
    }

    for (int c = 0; c < n; ++c)
    {
        char ch = board[0][c];
        int length = 1;
        for (int r = 1; r < n; ++r)
        {
            if (ch == board[r][c])
                ++length;
            else
            {
                result = std::max(result, length);
                ch = board[r][c];
                length = 1;
            }
        }

        result = std::max(result, length);
    }

    return result;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n;
    for (int i = 0; i < n; ++i)
        std::cin >> board[i];
    
    int result = 0;
    for (int r = 0; r < n; ++r)
    {
        for (int c = 0; c < n - 1; ++c)
        {
            if (board[r][c] != board[r][c + 1])
            {
                std::swap(board[r][c], board[r][c + 1]);
                result = std::max(FindLongest(), result);
                std::swap(board[r][c], board[r][c + 1]);
            }
        }
    }

    for (int c = 0; c < n; ++c)
    {
        for (int r = 0; r < n - 1; ++r)
        {
            if (board[r][c] != board[r + 1][c])
            {
                std::swap(board[r][c], board[r + 1][c]);
                result = std::max(FindLongest(), result);
                std::swap(board[r][c], board[r + 1][c]);
            }
        }
    }

    std::cout << result;

    return 0;
}
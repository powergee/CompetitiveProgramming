#include <iostream>
#include <vector>

char map[200][201];

int main()
{
    int T;
    scanf("%d", &T);

    while (T--)
    {
        int n;
        scanf("%d", &n);

        for (int row = 0; row < n; ++row)
            scanf("%s", map[row]);
        
        // std::vector<std::pair<int, int>> leftZero, leftOne;
        // std::vector<std::pair<int, int>> rightZero, rightOne;

        // map[0][1] == '0' ? leftZero.emplace_back(0, 1) : leftOne.emplace_back(0, 1);
        // map[1][0] == '0' ? leftZero.emplace_back(1, 0) : leftOne.emplace_back(1, 0);
        // map[n-1][n-2] == '0' ? rightZero.emplace_back(n-1, n-2) : rightOne.emplace_back(n-1, n-2);
        // map[n-2][n-1] == '0' ? rightZero.emplace_back(n-2, n-1) : rightOne.emplace_back(n-2, n-1);

        std::vector<std::pair<int, int>> answer;

        if (map[0][1] == '0' && map[1][0] == '0' && map[n-1][n-2] == '0' && map[n-2][n-1] == '0')
            answer.emplace_back(0, 1), answer.emplace_back(1, 0);

        else if (map[0][1] == '0' && map[1][0] == '0' && map[n-1][n-2] == '0' && map[n-2][n-1] == '1')
            answer.emplace_back(n-1, n-2);

        else if (map[0][1] == '0' && map[1][0] == '0' && map[n-1][n-2] == '1' && map[n-2][n-1] == '0')
            answer.emplace_back(n-2, n-1);

        else if (map[0][1] == '0' && map[1][0] == '0' && map[n-1][n-2] == '1' && map[n-2][n-1] == '1')
            ;

        else if (map[0][1] == '0' && map[1][0] == '1' && map[n-1][n-2] == '0' && map[n-2][n-1] == '0')
            answer.emplace_back(0, 1);

        else if (map[0][1] == '0' && map[1][0] == '1' && map[n-1][n-2] == '0' && map[n-2][n-1] == '1')
            answer.emplace_back(0, 1), answer.emplace_back(n-2, n-1);

        else if (map[0][1] == '0' && map[1][0] == '1' && map[n-1][n-2] == '1' && map[n-2][n-1] == '0')
            answer.emplace_back(0, 1), answer.emplace_back(n-1, n-2);

        else if (map[0][1] == '0' && map[1][0] == '1' && map[n-1][n-2] == '1' && map[n-2][n-1] == '1')
            answer.emplace_back(1, 0);

        else if (map[0][1] == '1' && map[1][0] == '0' && map[n-1][n-2] == '0' && map[n-2][n-1] == '0')
            answer.emplace_back(1, 0);

        else if (map[0][1] == '1' && map[1][0] == '0' && map[n-1][n-2] == '0' && map[n-2][n-1] == '1')
            answer.emplace_back(0, 1), answer.emplace_back(n-1, n-2);

        else if (map[0][1] == '1' && map[1][0] == '0' && map[n-1][n-2] == '1' && map[n-2][n-1] == '0')
            answer.emplace_back(0, 1), answer.emplace_back(n-2, n-1);

        else if (map[0][1] == '1' && map[1][0] == '0' && map[n-1][n-2] == '1' && map[n-2][n-1] == '1')
            answer.emplace_back(0, 1);

        else if (map[0][1] == '1' && map[1][0] == '1' && map[n-1][n-2] == '0' && map[n-2][n-1] == '0')
            ;

        else if (map[0][1] == '1' && map[1][0] == '1' && map[n-1][n-2] == '0' && map[n-2][n-1] == '1')
            answer.emplace_back(n-2, n-1);

        else if (map[0][1] == '1' && map[1][0] == '1' && map[n-1][n-2] == '1' && map[n-2][n-1] == '0')
            answer.emplace_back(n-1, n-2);

        else if (map[0][1] == '1' && map[1][0] == '1' && map[n-1][n-2] == '1' && map[n-2][n-1] == '1')
            answer.emplace_back(0, 1), answer.emplace_back(1, 0);
        
        printf("%d\n", (int)answer.size());
        for (auto ele : answer)
            printf("%d %d\n", ele.first+1, ele.second+1);
    }

    return 0;
}
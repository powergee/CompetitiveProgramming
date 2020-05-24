#include <iostream>
#include <algorithm>
#include <vector>
#include <tuple>

bool IsValidFor(bool* cam, int s, int e)
{
    for (int i = s; i < e; ++i)
        if (cam[i])
            return false;
    return true;
}

int main()
{
    int T;
    scanf("%d", &T);

    for (int c = 1; c <= T; ++c)
    {
        std::vector<std::tuple<int, int, int>> sche;
        int n;
        scanf("%d", &n);
        std::vector<char> answer(n + 1, '\0');

        for (int i = 0; i < n; ++i)
        {
            int s, e;
            scanf("%d %d", &s, &e);
            sche.emplace_back(s, e, i);
        }

        std::sort(sche.begin(), sche.end());

        bool cam[1440] {0,};
        bool jam[1440] {0,};
        bool possible = true;
        for (auto p : sche)
        {
            int s, e, i;
            std::tie(s, e, i) = p;

            if (IsValidFor(cam, s, e))
            {
                std::fill(cam + s, cam + e, true);
                answer[i] = 'C';
            }
            else if (IsValidFor(jam, s, e))
            {
                std::fill(jam + s, jam + e, true);
                answer[i] = 'J';
            }
            else possible = false;

            if (!possible) break;
        }

        printf("Case #%d: ", c);
        if (possible)
            printf("%s\n", &answer[0]);
        else
            printf("IMPOSSIBLE\n");
    }

    return 0;
}
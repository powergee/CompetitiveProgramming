#include <iostream>
#include <algorithm>
#include <string>

int costSum[100000];
std::string path;

int main()
{
    std::cin.sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--)
    {
        int a, b, p;
        std::cin >> a >> b >> p;
        std::cin >> path;
        int n = path.size();

        int pos = 0;
        costSum[0] = 0;
        while ((pos + 1) < n)
        {
            int cost;
            if (path[pos] == 'A')
                cost = a;
            else cost = b;
            char now = path[pos];
            cost += costSum[pos];

            while ((pos + 1) < n && now == path[pos])
                costSum[++pos] = cost;
        }

        int lack = costSum[n - 1] - p;
        bool found = false;
        for (int i = 0; i < n; ++i)
        {
            if (costSum[i] >= lack)
            {
                found = true;
                int lastPos = i;
                while (lastPos < n && costSum[lastPos] == costSum[i])
                    ++lastPos;

                std::cout << std::min(lastPos, n) << '\n';
                break;
            }
        }

        if (!found)
        {
            std::cout << n << '\n';
        }
    }

    return 0;
}